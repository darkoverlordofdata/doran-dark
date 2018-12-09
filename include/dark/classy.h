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
#ifndef _CLASSY_H
#define _CLASSY_H
#include <gc.h>
#include <tgc.h>
extern tgc_t gc;

/**
 * overload
 * 
 * shortcut for declaring the overloadable attribute
 */
#define overload __attribute__((overloadable))

/** 
 * class
 * 
 * defines structs for class & metaclass: Name_t, NameClass_t
 * defines type for class: Name
 * defines metadata singleton: NameClass
 * defines metadata reference function: IsaName()
 * 
 */
#define class(name) \
    struct name##Class; \
    struct name; \
    extern struct name##Class name; \
    typedef struct name* T##name; \
    struct Class* Isa##name(); \
    struct name


// #define class(name) \
//     typedef struct name##Class_t name##Class_t; \
//     extern name##Class_t name##Class; \
//     typedef struct name##_t name##_t;\
//     typedef name##_t* name;\
//     name##Class_t* Isa##name(); \
//     typedef struct name##_t

/** 
 * register class
 * 
 * declares the metaclass implementation
 * declares the Isa implementation
 */
// #define register(name) \
//     name##Class_t name##Class; \
//     name##Class_t* Isa##name() 

#define register(name) \
    struct name##Class name; \
    TClass Isa##name()

/**
 *  returns a reference to the class name 
 */
#define isa(name) Isa##name()

#define AddMetadata(name) (Metadata.classes[Metadata.count++] = &name)


/** 
 * Create a new class instance 
 * allocates memory for 1 object
 * 
 */
#define new(class) dark_malloc (sizeof(struct class))

// #define new(class) tgc_calloc_opt(&gc, 1, sizeof(class##_t), TGC_ROOT, Object_Dtor)
// #define new(class) tgc_calloc(&gc, 1, sizeof(class##_t))

/** 
 * Delete an object created with new 
 * deallocates the memory for 1 object
 * 
 */
#define delete(x) dark_free(x)
/** 
/** 
 * creates an array of structs
 * 
 * allocates memory for array of struct objects
 */
#define allocate(class, n) dark_malloc (n * sizeof(struct class))
// #define allocate(class, n) tgc_calloc_opt(&gc, n, sizeof(class##_t), TGC_ROOT, nullptr )


#endif _CLASSY_H 
