/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <dark/core/class.h>
#include <dark/runtime.h>
#include <assert.h>


/**
 * dedicated hashmap for class definitions
 * this is a simple hastable. 
 * Size is kept large, and collisions are a linked list.
 * as long as the collision rate stays low, this is suficient and simple.
 * 
 * 
 * special requirements -
 * 
 * key = char*
 * entry = Class*
 * add only, no remove
 * singleton object
 * 
 */
type (ClassNode)
{
    ClassNode* next;
    char* key;
    Class value;
};

type (Classes) 
{
    int size;           /* size of the pointer data */
    int n;              /* number of elements stored */
    ClassNode **data;
};

#define CLASSMAP_INITIAL_SIZE (1024)
#define CLASSMAP_GROWTH_FACTOR (0)
#define CLASSMAP_MAX_LOAD_FACTOR (1)
#define CLASSMAP_MULTIPLIER (97)


/**
 * Declare a singleton data 
 */
static Classes _Classes;

static inline Classes* GetClasses(void);
method void Dispose(Classes*);
method void Add(Classes*, const char *key, Class value);
method Class Get(Classes* self, char* key); 

/**
 * Create new class object
 * 
 * @paran size
 * @returns allocated memory
 * 
 */
static inline Class NewClass(size_t size)
{
    return (Class) DScalloc(1, size);
}

/**
 * Get Class by name
 * 
 * @param name
 * @returns the class
 * 
 */
static inline Class GetClass(const char *name)
{
    if (!name) return Nil;
    Class result = Get(GetClasses(), name);
    return result;

}


/**
 * Get Superclass
 * 
 * @param class
 * @returns the superclass of the given class
 * 
 */
static inline Class GetSuperclass(Class cls)
{
    if (!cls) return nil;
    return cls->super_class;
}

/**
 * Is Meta Class
 * 
 * @param class
 * @returns true if it's a metaclass
 * 
 */
static inline bool IsMetaClass(Class cls)
{
    if (!cls) return false;
    return ISMETA(cls);
}
/**
 * Get Instance Size
 * 
 * @param class
 * @returns the size of an instance of class
 * 
 */
static inline size_t GetInstanceSize(Class cls)
{
    if (!cls) return 0;
    return cls->size;
}


/**
 * Set Supoerclass
 * 
 * @param class
 * @param superclass
 * 
 */
static inline void SetSuperclass(Class cls, Class supercls)
{
    Class meta = cls->isa;

    if (supercls) {
        cls->super_class = supercls;
        meta->super_class = supercls->isa;
        meta->isa = supercls->isa->isa;
    } else {
        cls->super_class = Nil;  
        meta->super_class = cls; 
        meta->isa = meta;    
    }    
}

/**
 * Initialize Class
 * 
 * @param supercls
 * @param name
 * @param class
 * @param meta
 * @returns the class after upating
 * 
 */
static inline Class InitializeClass(Class supercls, const char *name, Class cls, Class meta)
{
    cls->isa = meta;
    SetSuperclass(cls, supercls);

    cls->name = strdup(name);
    meta->name = strdup(name);
    cls->flags = CLS_CLASS | CLS_CONSTRUCTING;
    meta->flags = CLS_META | CLS_CONSTRUCTING;

    
    if (supercls) {
        cls->size = supercls->size;
        meta->size = supercls->isa->size;
    } else {
        cls->size = sizeof(Class);  // just an isa
        meta->size = sizeof(struct _class);
    }

    cls->count = 0;
    cls->version = 1;
    return cls;
}


/**
 * Create Class
 * 
 * @param superclass
 * @param name
 * @param vtable
 * @returns a new class
 * 
 */
static inline Class CreateClass(Class supercls, const char *name, const int size, IMP* vtable)
{
    Class cls, meta;

    if (GetClass(name)) {
        println("CreateClass failed - %s already exists", name);
        return nil;
    }

    if (supercls && (supercls->flags & CLS_CONSTRUCTING)) {
        println("Can't make subclass of an in-construction class for %s", name);
        return nil;
    }

    cls = NewClass(sizeof(struct _class));
    meta = NewClass(sizeof(struct _class));

    InitializeClass(supercls, name, cls, meta);
    cls->vtable = vtable;
    cls->size = size;
    _id += 1;
    cls->id = _id;

    if (supercls)
        println("CreateClass %s %s %s", name, supercls->name, meta->name);
    else
        println("CreateClass %s %s", name, meta->name);
        
    return cls;
}

/**
 * Register Class
 * 
 * @param class to register
 */
static inline void RegisterClass(Class cls)
{
    if ((cls->flags & CLS_CONSTRUCTED)  ||  
        (cls->isa->flags & CLS_CONSTRUCTED)) 
    {
        println("RegisterClassPair: class '%s' was already "
                     "registered!", cls->name);
        return;
    }

    if (!(cls->flags & CLS_CONSTRUCTING)  ||  
        !(cls->isa->flags & CLS_CONSTRUCTING)) 
    {
        println("RegisterClassPair: class '%s' was not "
                     "allocated with CreateClass!", cls->name);
        return;
    }

    if (ISMETA(cls)) {
        println("RegisterClassPair: class '%s' is a metaclass, "
                     "not a class!", cls->name);
        return;
    }

    // Clear lifecycle bits
    cls->flags &= ~CLS_CONSTRUCTING;
    cls->isa->flags &= ~CLS_CONSTRUCTING;
    cls->flags |= CLS_CONSTRUCTED;
    cls->isa->flags |= CLS_CONSTRUCTED;

    if (Get(GetClasses(), cls->name) == nullptr) {
        Add(GetClasses(), cls->name, cls);
    }
}



/**
 * Add method to a class
 * 
 * @param class
 * @param name
 * @param func address
 * @returns true on success
 * 
 */
static inline overload bool Add(Class cls, char* name, IMP imp)
{
    IMP old;
    if (!cls) return false;
    cls->vtable[cls->count++] = imp;
    return true;
}


/**
 * Get the singleton
 * optionally initialize
 */
static inline Classes* GetClasses()
{
    if (_Classes.size != 0) return &_Classes;

    _Classes.size = CLASSMAP_INITIAL_SIZE;
    _Classes.n = 0;
    _Classes.data = DSmalloc(sizeof(ClassNode *) * _Classes.size);

    assert(_Classes.data != 0);

    for (int i = 0; i < _Classes.size; i++) _Classes.data[i] = 0;

    return &_Classes;
}

/**
 * Dispose the classes map
 */
method void Dispose(Classes* self)
{
    if (true)return; // not needed with GC

    ClassNode *node;
    ClassNode *next;

    for (int i = 0; i < self->size; i++) {
        for (node = self->data[i]; node != nullptr; node = next) {
            next = node->next;

            free(node->key);
            /** e->value is owned elsewhere */
            // free(e->value);
            free(node);
        }
    }

    free(self->data);
    // free(d);
}

/**
 * hash of a string
 * 
 * djb2
 * sdbm
 * http://www.cse.yorku.ca/~oz/hash.html
 */
static inline unsigned long sdbm_hash(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;    
}

static inline unsigned long dbj2_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;    
}

/**
 *  Add the Class definition to the dictionary
 */
method void Add(Classes* self, const char *key, Class value)
{
    assert(key);
    assert(value);

    ClassNode* node = DSmalloc(sizeof(*node));

    assert(node);

    node->key = strdup(key);
    node->value = value;

    unsigned long hit = dbj2_hash(key) % self->size;

    node->next = self->data[hit];
    self->data[hit] = node;

    self->n++;

    /** Ran out of room?*/
    assert(self->n < self->size * CLASSMAP_MAX_LOAD_FACTOR);
}

/**
 *  Get the Class definition from the dictionary
 */
method Class Get(Classes* self, char *key)
{
    // struct node *e;
    int hits = 0;

    for (ClassNode* node = self->data[dbj2_hash(key) % self->size]; 
            node != nullptr; 
            node = node->next) 
    {
        hits+= 1;
        if(!strcmp(node->key, key)) {
            if (hits > 2) println("WARNING: Collision count: %d", hits);
            /* got it */
            return node->value;
        }
    }

    return nullptr;
}
