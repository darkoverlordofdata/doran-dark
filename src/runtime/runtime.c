#include <dark/DSClass.h>
#include <dark/DSLog.h>
#include <dark/runtime.h>

/** builtin selectors */
SEL $alloc = "alloc";
SEL $init = "init";
SEL $toString = "ToString";
SEL $equals = "Equals";
SEL $getHashCode = "GetHashCode";
SEL $dispose = "Dispose";
SEL $referenceEquals = "ReferenceEquals";
SEL $instanceEquals = "InstanceEquals";
SEL $compareTo = "CompareTo";
SEL $length = "Length";
SEL $add = "Add";
SEL $isEmpty = "IsEmpty";
SEL $contains = "Contains";
SEL $remove = "Remove";
SEL $resize = "Resize";
SEL $set = "Set";
SEL $get = "Get";
SEL $clear = "Clear";

Class implement_DSObject();
Class implement_DSClass(Class super);
Class implement_DSComparable(Class super);
Class implement_DSCollection(Class super);
Class implement_DSArray(Class super);

/* NX_hashmap interface for Class objects */
HASHMAP_FUNCS_CREATE(NX, const char, struct objc_class)

/** class_hash is not gc'd */
struct hashmap* class_hash;
struct hashmap _class_hash;

void _objc_init_class_hash(void)
{
    if (class_hash)
        return;
    class_hash = &_class_hash;
    hashmap_init(class_hash, hashmap_hash_string, hashmap_compare_string, 0);


}

void objc_init() {


    if (!class_hash) _objc_init_class_hash();
    /** 
     * register framework classes 
     * 
     * apple goes through segments here and links in pre-compiled classes.
     * as i'm not using compiled objective-c, the 'prebuilt' classes
     * will be fabricated instead of loaded.
     */

    /** Class & MetaClass */
    Class obj;
    objc_registerClassPair(obj = implement_DSObject());

    Class cls;
    objc_registerClassPair(cls = implement_DSClass(obj));

    Class col;
    objc_registerClassPair(col = implement_DSCollection(obj));

    Class array;
    objc_registerClassPair(array = implement_DSArray(col));

    // objc_registerClassPair(implementDSDSList(col));
    // objc_registerClassPair(implementDSDSHashmap(col));

    // Class cmp = objc_allocateClassPair(obj, "DSComparable", 0);
    // objc_registerClassPair(cmp);

    // objc_registerClassPair(objc_allocateClassPair(cmp, "DSBoolean", 0));

    // Class num = objc_allocateClassPair(cmp, "DSNumber", 0);
    // objc_registerClassPair(num);

    // objc_registerClassPair(objc_allocateClassPair(num, "DSChar", 0));
    // objc_registerClassPair(objc_allocateClassPair(num, "DSDouble", 0));
    // objc_registerClassPair(objc_allocateClassPair(num, "DSFloat", 0));
    // objc_registerClassPair(objc_allocateClassPair(num, "DSInteger", 0));
    // objc_registerClassPair(objc_allocateClassPair(num, "DSLong", 0));
    // objc_registerClassPair(objc_allocateClassPair(num, "DSShort", 0));

    // objc_registerClassPair(objc_allocateClassPair(obj, "DSString", 0));
    // objc_registerClassPair(objc_allocateClassPair(obj, "DSStringBuilder", 0));


}

/***********************************************************************
* look_up_class
* Map a class name to a class using various methods.
* This is the common implementation of objc_lookUpClass and objc_getClass, 
* and is also used internally to get additional search options.
* Sequence:
* 1. class_hash
* 2. unconnected_class_hash (optional)
* 3. classLoader callback
* 4. classHandler callback (optional)
**********************************************************************/
Class look_up_class(const char *aClassName, bool includeUnconnected, 
                    bool includeClassHandler)
{
    Class result = nil;
    result = (Class)NX_hashmap_get(class_hash, aClassName);
    return result;
}

/***********************************************************************
* objc_getClass.  Return the id of the named class.  If the class does
* not exist, call _objc_classLoader and then objc_classHandler, either of 
* which may create a new class.
* Warning: doesn't work if aClassName is the name of a posed-for class's isa!
**********************************************************************/
Class objc_getClass(const char *aClassName)
{
    if (!aClassName) return Nil;

    // NO unconnected, YES class handler
    return look_up_class(aClassName, NO, YES);
}
/***********************************************************************
* _objcTweakMethodListPointerForClass.
* Change the class's method list pointer to a method list array. 
* Does nothing if the method list pointer is already a method list array.
* If the class is currently in use, methodListLock must be held by the caller.
**********************************************************************/
static void _objcTweakMethodListPointerForClass(Class cls)
{    
    struct objc_method_list *	originalList;
    const int					initialEntries = 4;
    size_t							mallocSize;
    struct objc_method_list **	ptr;

    // Do nothing if methodLists is already an array.
    if (cls->methodLists  &&  !(cls->info & CLS_NO_METHOD_ARRAY)) return;

    // Remember existing list
    originalList = (struct objc_method_list *) cls->methodLists;

    // Allocate and zero a method list array
    mallocSize   = sizeof(struct objc_method_list *) * initialEntries;
    ptr	     = (struct objc_method_list **) DSCalloc(1, mallocSize);

    // Insert the existing list into the array
    ptr[initialEntries - 1] = END_OF_METHODS_LIST;
    ptr[0] = originalList;

    // Replace existing list with array
    cls->methodLists = ptr;
    cls->info ^= CLS_NO_METHOD_ARRAY;
}


/***********************************************************************
* _objc_insertMethods.
* Adds methods to a class.
* Does not flush any method caches.
* Does not take any locks.
* If the class is already in use, use class_addMethods() instead.
**********************************************************************/
void _objc_insertMethods(Class cls, struct objc_method_list *mlist, struct objc_category *cat)
{
    struct objc_method_list ***list;
    struct objc_method_list **ptr;
    ptrdiff_t endIndex;
    size_t oldSize;
    size_t newSize;

    if (!cls->methodLists) {
        
        // cls has no methods - simply use this method list
        cls->methodLists = (struct objc_method_list **)mlist;
        cls->info |= CLS_NO_METHOD_ARRAY;
        return;
    }

    // Log any existing methods being replaced
    // if (PrintReplacedMethods) {
    //     int i;
    //     for (i = 0; i < mlist->method_count; i++) {
    //         extern IMP findIMPInClass(Class cls, SEL sel);
    //         SEL sel = sel_registerName((char *)mlist->method_list[i].method_name);
    //         IMP newImp = mlist->method_list[i].method_imp;
    //         IMP oldImp;

    //         if ((oldImp = findIMPInClass(cls, sel))) {
    //             logReplacedMethod(cls->name, sel, ISMETA(cls), 
    //                               cat ? cat->category_name : nil, 
    //                               oldImp, newImp);
    //         }
    //     }
    // }

    // Create method list array if necessary
    _objcTweakMethodListPointerForClass(cls);

    list = &cls->methodLists;

    // Locate unused entry for insertion point
    ptr = *list;
    while ((*ptr != 0) && (*ptr != END_OF_METHODS_LIST))
        ptr += 1;


    // If array is full, add to it
    if (*ptr == END_OF_METHODS_LIST)
    {
        // Calculate old and new dimensions
        endIndex = ptr - *list;
        oldSize  = (endIndex + 1) * sizeof(void *);
        newSize  = oldSize + sizeof(struct objc_method_list *); // only increase by 1

        // Grow the method list array by one.
        *list = (struct objc_method_list **)DSRealloc(*list, newSize);

        // Zero out addition part of new array
        bzero (&((*list)[endIndex]), newSize - oldSize);

        // Place new end marker
        (*list)[(newSize/sizeof(void *)) - 1] = END_OF_METHODS_LIST;

        // Insertion point corresponds to old array end
        ptr = &((*list)[endIndex]);
    }

    // Right shift existing entries by one
    bcopy (*list, (*list) + 1, (uint8_t *)ptr - (uint8_t *)*list);

    // Insert at method list at beginning of array
    **list = mlist;
}

