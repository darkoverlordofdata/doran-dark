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
 * 
 * special requirements -
 * 
 * key = char*
 * entry = Class*
 * singleton object
 * 
 */

typedef struct _class 		*Class;
typedef struct classmap Classes;
struct node {
    struct node *next;
    char *key;
    Class value;
};

type (ClassNode)
{
    ClassNode* next;
    char* key;
    Class value;

}

struct classmap classmap;
struct classmap {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    // struct node **table;
    ClassNode **table;
};


static inline Classes* GetClasses(void);
/* destroy a dictionary */
method void Dispose(Classes*);

/* insert a new key-value pair into an existing dictionary */
method void Add(Classes*, const char *key, Class value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */

method Class Get (Classes* self, char* key); 

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
static inline Class CreateClass(Class supercls, const char *name, IMP* vtable)
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



#define CLASSMAP_INITIAL_SIZE (1024)
#define CLASSMAP_GROWTH_FACTOR (0)
#define CLASSMAP_MAX_LOAD_FACTOR (1)

/**
 * Initialize the singleton
 * 
 */
static inline Classes* GetClasses()
{
    if (classmap.size != 0) return &classmap;

    classmap.size = CLASSMAP_INITIAL_SIZE;
    classmap.n = 0;
    classmap.table = DSmalloc(sizeof(struct node *) * classmap.size);

    assert(classmap.table != 0);

    for (int i = 0; i < classmap.size; i++) classmap.table[i] = 0;

    return &classmap;
}

method void Dispose(Classes* self)
{
    if (true)return; // not needed with GC

    int i;
    struct node *e;
    struct node *next;

    for(i = 0; i < self->size; i++) {
        for(e = self->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            /** e->value is owned elsewhere */
            // free(e->value);
            free(e);
        }
    }

    free(self->table);
    // free(d);
}

#define CLASSMAP_MULTIPLIER (97)

static inline unsigned long classmap_hash(const char *s)
{
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * CLASSMAP_MULTIPLIER + *us;
    }

    return h;
}


/* insert a new key-value pair into an existing dictionary */
method void Add(Classes* self, const char *key, Class value)
{
    struct node *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = DSmalloc(sizeof(*e));

    assert(e);

    e->key = strdup(key);
    // e->value = strdup(value);
    e->value = value;

    h = classmap_hash(key) % self->size;

    e->next = self->table[h];
    self->table[h] = e;

    self->n++;

    /** Ran out of room?*/
    assert(self->n < self->size * CLASSMAP_MAX_LOAD_FACTOR);
}

method Class Get(Classes* self, char *key)
{
    // struct node *e;

    for (struct node* e = self->table[classmap_hash(key) % self->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
            return e->value;
        }
    }

    return 0;
}
