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
#include <dark/core.h>
#include <dark/runtime.h>
/**
****
****    macros used as a dsl to define DaRKSTEP classes and objects
****
**/

/**
 * The base Class object is defined in runtime.h, and is based on NSClass
 * 
 * 3 global tuples are created for each Class:
 *  type    Object        - Instance Variables
 *  vtable  ObjectVTable  - Instance Methods
 *  class   $Object       - Optional, Class Methods/Variables
 * 
 * A method is on overrideable function where a type* is the first argument. These
 * are used as mulimethods. Subclasses consist of type punning and vtables. The
 * subclass type must be aranged identially to its base class.
 * The vtable is used with subclassing to allow calling the
 * most derived subclass first. The optional class object is a singleton struct
 * and not malloc'd.
 * Classes are created dynamically at runtine, and the vtable is linked to the most
 * derived class implementation. Call base classes by downcasting to the appropriate 
 * base type*.
 * 
 * 
 * A full class definition consists of:
 * 
 * a type.
 * a list of delegate signatures defining object methods.
 * a vtable struct
 * Optional class struct
 * a class loader
 * the method implemtations
 * 
 */

/**
 * type: Instance Variables
 * 
 * A type whose 1st member is an 'isa' is a class of that isa type,
 * and it becomes the object definition for a DaRKSTEP object. 
 */
#define type(T)                                                         \
    typedef struct T T;                                                 \
    static Class T##_isa_cache = Nil;                                   \
    struct T

// #define type(T)                                                         \
//     typedef struct T T;                                                 \
//     struct T
/**
 * vtable: Instance Methods
 * 
 * A singleton vtable object per Class
 */

#define vtable(T)                                                       \
    struct T##_vtable T##_vtable;                                       \
    struct T##_vtable

/**
 * class: Class Methods/Variables
 * 
 * A singleton class object per Class
 */
#define class(T)                                                        \
    struct $##T $##T;                                                   \
    struct $##T

/**
 * Multi-methods are overloadable functions
 */
#define method static inline overload

/**
 *  delegate
 *      declares the prototype for methods
 * 
 */
#define delegate(T, name, type, signature)                              \
    method type name signature;                                         \
    typedef type (*T##name)signature;

/**
 *  alloc
 *      Allocate memory for type struct
 */
#define alloc(T) (T*)DSmalloc(sizeof(T))

/**
 *  new
 *      Allocate and construct a new object
 */
#define new(T, args...) New(alloc(T), ## args)

/**
 *  extends
 *      extends base class by calling it's constructor
 */
#define extends(T, args...) New((T*)self, ## args) 


/**
 *  super
 *      call the base version of the method
 *      SUPER is redefined per class
 *      warning: don't do this at home
 */
#define super(method) method((SUPER*)self)

/**
 *  using
 *      call a destrutor when this object goes out of scope
 */
#define using(class) class* __attribute__((cleanup(class##_dtor)))

/**
 *  instanceof
 *      Check if an object is an instance of a class
 */
#define instanceof(class, obj) InstanceOf(GetClass(#class), obj)

/**
 *  of
 *      type constraint
 */
#define of(class) (Class)GetClass(#class)

/**
 * vptr
 * 
 * Define function to retrieve vptr
 * Declare cache value for isa
 */
#define vptr(T)                                                         \
    struct T##_vtable* T##_vptr(T* self);                               \
    static inline struct T##_vtable* T##_vptr(T* self) {                \
        return (struct T##_vtable*)self->isa->vtable;                   \
    };                                                                  \

// #define vptr(T)                                                         \
//     struct T##_vtable* T##_vptr(T* self);                               \
//     static Class T##_isa_cache = Nil;                                   \
//     static inline struct T##_vtable* T##_vptr(T* self) {                \
//         return (struct T##_vtable*)self->isa->vtable;                   \
//     };                                                                  \


/**
 * virtual
 * 
 * Get the most derived vptr for T
 */
#define virtual(T) T##_vptr(self)

/**
 * createClass
 * 
 * Initialize Class Definition
 */
#define createClass(base, T) CreateClass(base, #T, sizeof(T), (IMP*)&T##_vtable)

#define CreateComponent(T) CreateClass(nullptr, #T, sizeof(T), nullptr)
/**
 * addMethod
 * 
 * Add method to Class vtable
 */
#define addMethod(cls, T, addr) Add(cls, (char*)#addr, ((IMP)(T##addr)addr))



/**
 * Class loader signature
 */
typedef Class* (*ClassLoadClass)(Class base);


/**
 * Gets a chached version of GetClass(T) used to speed up class construction
 */
#define isa(T) (T##_isa_cache = ((T##_isa_cache != Nil) ? T##_isa_cache : GetClass(#T)))
