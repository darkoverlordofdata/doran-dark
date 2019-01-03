#include <dark/DSClass.h>
#include <dark/DSLog.h>
#include <dark/runtime.h>

#define WORD_SHIFT 3UL
#define WORD_MASK 7UL
#define WORD_BITS 64


Class _calloc_class(size_t size)
{
    return (Class) DSCalloc(1, size);
}

Class class_getSuperclass(Class cls)
{
    if (!cls) return nil;
    return cls->super_class;
}

bool class_isMetaClass(Class cls)
{
    if (!cls) return NO;
    return ISMETA(cls);
}

/** use for malloc */
size_t class_getInstanceSize(Class cls)
{
    if (!cls) return 0;
    return cls->instance_size;
}

size_t class_getAlignedInstanceSize(Class cls)
{
    if (!cls) return 0;
    return (class_getInstanceSize(cls) + WORD_MASK) & ~WORD_MASK;
}

//https://opensource.apple.com/source/objc4/objc4-437/runtime/


void set_super_class(Class cls, Class supercls, bool cls_is_new)
{
    Class meta = cls->isa;

    if (supercls) {
        cls->super_class = supercls;
        meta->super_class = supercls->isa;
        meta->isa = supercls->isa->isa;

        // Superclass is no longer a leaf for cache flushing
        if (supercls->info & CLS_LEAF) {
            supercls->info ^=CLS_LEAF;
            supercls->isa->info ^=CLS_LEAF;
        }
    } else {
        cls->super_class = Nil;  // super_class of root class is nil
        meta->super_class = cls; // super_class of root metaclass is root class
        meta->isa = meta;    // metaclass of root metaclass is root metaclass

        // Root class is never a leaf for cache flushing, because the 
        // root metaclass is a subclass. (This could be optimized, but 
        // is too uncommon to bother.)
        cls->info ^= CLS_LEAF;
        meta->info ^= CLS_LEAF;
    }    
}

Class objc_initializeClassPair(Class supercls, const char *name, Class cls, Class meta)
{
    // Connect to super_classes and metaclasses
    cls->isa = meta;
    set_super_class(cls, supercls, YES);

    // Set basic info
    cls->name = strdup(name);
    meta->name = strdup(name);
    cls->version = 0;
    meta->version = 7;
    cls->info = CLS_CLASS | CLS_CONSTRUCTING | CLS_EXT | CLS_LEAF;
    meta->info = CLS_META | CLS_CONSTRUCTING | CLS_EXT | CLS_LEAF;

    // Set instance size based on super_class.
    if (supercls) {
        cls->instance_size = supercls->instance_size;
        meta->instance_size = supercls->isa->instance_size;
    } else {
        cls->instance_size = sizeof(Class);  // just an isa
        meta->instance_size = sizeof(struct objc_class);
    }
    
    // No ivars. No methods. Empty cache. No protocols. No layout. Empty ext.
    cls->ivars = nil;
    cls->methodLists = nil;
    // cls->cache = (Cache)&_objc_empty_cache;
    cls->protocols = nil;

    meta->ivars = nil;
    meta->methodLists = nil;
    // meta->cache = (Cache)&_objc_empty_cache;
    meta->protocols = nil;
    
    return cls;
}


Class objc_allocateClassPair(Class supercls, const char *name, 
                             size_t extraBytes)
{
    Class cls, meta;

    if (objc_getClass(name)) return nil;
    // fixme reserve class name against simultaneous allocation

    if (supercls  &&  (supercls->info & CLS_CONSTRUCTING)) {
        // Can't make subclass of an in-construction class
        return nil;
    }

    // Allocate new classes. 
    if (supercls) {
        cls = _calloc_class(supercls->isa->instance_size + extraBytes);
        meta = _calloc_class(supercls->isa->instance_size + extraBytes);
    } else {
        cls = _calloc_class(sizeof(struct objc_class) + extraBytes);
        meta = _calloc_class(sizeof(struct objc_class) + extraBytes);
    }


    objc_initializeClassPair(supercls, name, cls, meta);
    
    return cls;
}

void objc_registerClassPair(Class cls)
{
    if ((cls->info & CLS_CONSTRUCTED)  ||  
        (cls->isa->info & CLS_CONSTRUCTED)) 
    {
        _objc_inform("objc_registerClassPair: class '%s' was already "
                     "registered!", cls->name);
        return;
    }

    if (!(cls->info & CLS_CONSTRUCTING)  ||  
        !(cls->isa->info & CLS_CONSTRUCTING)) 
    {
        _objc_inform("objc_registerClassPair: class '%s' was not "
                     "allocated with objc_allocateClassPair!", cls->name);
        return;
    }

    if (ISMETA(cls)) {
        _objc_inform("objc_registerClassPair: class '%s' is a metaclass, "
                     "not a class!", cls->name);
        return;
    }

    // Clear "under construction" bit, set "done constructing" bit
    cls->info &= ~CLS_CONSTRUCTING;
    cls->isa->info &= ~CLS_CONSTRUCTING;
    cls->info |= CLS_CONSTRUCTED;
    cls->isa->info |= CLS_CONSTRUCTED;

    if (NX_hashmap_get(class_hash, cls->name) == nullptr) {
        NX_hashmap_put(class_hash, cls->name, cls);
        // _objc_inform("objc_registerClassPair %s length = %d", cls->name, cls->instance_size);
        NX_hashmap_put(class_hash, cls->name, cls);
        Class kls = NX_hashmap_get(class_hash, cls->name);
        // _objc_inform("objc_registerClassPair %s length = %d", kls->name, kls->instance_size);
    }
}

/* These next three functions are the heart of ObjC method lookup. 
 * If the class is currently in use, methodListLock must be held by the caller.
 */
static inline struct objc_method *_findMethodInList(struct objc_method_list * mlist, SEL sel) {
    int i;
    if (!mlist) return nil;
    for (i = 0; i < mlist->method_count; i++) {
        struct objc_method *m = &mlist->method_list[i];
        if (m->method_name == sel) {
            return m;
        }
    }
    return nil;
}

static inline struct objc_method * _findMethodInClass(Class cls, SEL sel) __attribute__((always_inline));
static inline struct objc_method * _findMethodInClass(Class cls, SEL sel) {
    // Flattened version of nextMethodList(). The optimizer doesn't 
    // do a good job with hoisting the conditionals out of the loop.
    // Conceptually, this looks like:
    // while ((mlist = nextMethodList(cls, &iterator))) {
    //     objc_method *m = _findMethodInList(mlist, sel);
    //     if (m) return m;
    // }

    if (!cls->methodLists) {
        // No method lists.
        return nil;
    }
    else if (cls->info & CLS_NO_METHOD_ARRAY) {
        // One method list.
        struct objc_method_list **mlistp;
        mlistp = (struct objc_method_list **)&cls->methodLists;

        // *mlistp = fixupSelectorsInMethodList(cls, *mlistp);
        return _findMethodInList(*mlistp, sel);
    }
    else {
        // Multiple method lists.
        struct objc_method_list **mlistp;
        for (mlistp = cls->methodLists; 
             *mlistp != nil  &&  *mlistp != END_OF_METHODS_LIST; 
             mlistp++) 
        {
            struct objc_method *m;
            // *mlistp = fixupSelectorsInMethodList(cls, *mlistp);
            m = _findMethodInList(*mlistp, sel);
            if (m) return m;
        }
        return nil;
    }
}

static inline struct objc_method * _getMethod(Class cls, SEL sel) {
    for (; cls; cls = cls->super_class) {
        struct objc_method *m;
        m = _findMethodInClass(cls, sel);
        if (m) return m;
    }
    return nil;
}


/***********************************************************************
* class_addMethod
**********************************************************************/
static IMP _class_addMethod(Class cls, SEL name, IMP imp, 
                            const char *types, bool replace)
{
    struct objc_method *m;
    IMP result = nil;

    if (!types) types = "";


    if ((m = _findMethodInClass(cls, name))) {
        // already exists
        // fixme atomic
        result = m->method_imp;
        if (replace) {
            m->method_imp = imp;
        }
    } else {
        // fixme could be faster
        struct objc_method_list *mlist = 
            (struct objc_method_list *)DSCalloc(sizeof(struct objc_method_list), 1);
        mlist->method_count = 1;
        mlist->method_list[0].method_name = name;
        mlist->method_list[0].method_types = strdup(types);
        // if (!ignoreSelector(name)) {
            mlist->method_list[0].method_imp = imp;
        // } else {
        //     mlist->method_list[0].method_imp = (IMP)&_objc_ignored_method;
        // }
        
        _objc_insertMethods(cls, mlist, nil);
        result = nil;
    }

    return result;
}


/***********************************************************************
* class_addMethod
**********************************************************************/
bool class_addMethod(Class cls, SEL name, IMP imp, const char *types)
{
    IMP old;
    if (!cls) return NO;

    old = _class_addMethod(cls, name, imp, types, NO);
    return !old;
}

/***********************************************************************
* class_addIvar
**********************************************************************/
bool class_addIvar(Class cls, const char *name, size_t size, 
                   uint8_t alignment, const char *type)
{
    bool result = YES;

    if (!cls) return NO;
    if (ISMETA(cls)) return NO;
    if (!(cls->info & CLS_CONSTRUCTING)) return NO;

    if (!type) type = "";
    if (name  &&  0 == strcmp(name, "")) name = nil;
    
    // Check for existing ivar with this name
    // fixme check superclasses?
    if (cls->ivars) {
        int i;
        for (i = 0; i < cls->ivars->ivar_count; i++) {
            if (0 == strcmp(cls->ivars->ivar_list[i].ivar_name, name)) {
                result = NO;
                break;
            }
        }
    }

    if (result) {
        struct objc_ivar_list *old = cls->ivars;
        size_t oldSize;
        int newCount;
        struct objc_ivar *ivar;
        size_t alignBytes;
        size_t misalign;
        
        if (old) {
            oldSize = sizeof(struct objc_ivar_list) + 
                (old->ivar_count - 1) * sizeof(struct objc_ivar);
            newCount = 1 + old->ivar_count;
        } else {
            oldSize = sizeof(struct objc_ivar_list) - sizeof(struct objc_ivar);
            newCount = 1;
        }

        // allocate new ivar list
        cls->ivars = (struct objc_ivar_list *)
            DSCalloc(oldSize+sizeof(struct objc_ivar), 1);
        if (old) memcpy(cls->ivars, old, oldSize);
        // if (old  &&  malloc_size(old)) free(old);
        if (old) DSFree(old);
        cls->ivars->ivar_count = newCount;
        ivar = &cls->ivars->ivar_list[newCount-1];

        // set ivar name and type
        ivar->ivar_name = strdup(name);
        ivar->ivar_type = strdup(type);

        // align if necessary
        alignBytes = 1 << alignment;
        misalign = cls->instance_size % alignBytes;
        // DSObject not internally aligned
        if (misalign) cls->instance_size += (long)(alignBytes - misalign);

        // set ivar offset and increase instance size
        ivar->ivar_offset = (int)cls->instance_size;
        cls->instance_size += (long)size;
    }

    return result;
}

