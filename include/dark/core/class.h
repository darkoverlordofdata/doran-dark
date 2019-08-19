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
****    All macros used to define DaRKSTEP classes and objects
****
**/

/**
 * 3 global tuples are created for each Class:
 *  type    DSOject         - Instance Variables
 *  vtable  ObjectVTable  - Instance Methods
 *  class   $Object       - Class Methods/Variables
 * 
 * A type whose 1st member is an 'isa' is a class of that isa type,
 * and it becomes the object definition for a DaRKSTEP object. 
 */
#define type(T)                                                         \
    typedef struct T T;                                                 \
    struct T

/**
 * Singleton vtable object per Class
 */
#define vtable(T)                                                       \
    struct T##_vtable T##_vtable;                                       \
    struct T##_vtable

/**
 * Singleton class object per Class
 */
#define class(T)                                                        \
    struct $##T $##T;                                                   \
    struct $##T

/**
 * All functions are static inlined
 */
#define function static inline

/**
 * Multi-methods are overloadable functions
 */
#define method function overload

/**
 *  MACRO interface
 *      declares the prototype for methods
 * 
 */
#define interface(T, name, type, signature)                             \
    method type name signature;                                         \
    typedef type (*T##name)signature;

/**
 *  MACRO ctor_proto
 *      declares the prototype for constructor
 * 
 */
#define ctor_proto(T, args...)                                          \
    method T* T##_init(T* const, ## args);

/**
 *  MACRO alloc
 *      Allocate memory for type struct
 */
#define alloc(T) (T*)DSmalloc(sizeof(T))

/**
 *  MACRO new
 *      Allocate and initialize a new object
 */
#define new(T, args...) T##_init(alloc(T), ## args)

/**
 *  MACRO using
 *      call a destrutor when this object goes out of scope
 */
#define using(class) class* __attribute__((cleanup(class##_dtor)))

/**
 *  MACRO instanceof
 *      Check of an object is an instance of a class
 */
#define instanceof(class, obj) InstanceOf(objc_getClass(#class), obj)

/**
 *  MACRO of
 *      type constraint
 */
#define of(class) (Class)objc_getClass(#class)

/**
 * Define function to retrieve vptr
 */
#define vptr(T)\
    struct T##_vtable* T##_vptr(T* this) {                              \
        return (struct T##_vtable*)this->isa->vtable;                   \
    };                                                                  \

/**
 * Get the vptr for T
 */
#define get_vptr(T) T##_vptr(this)

/**
 * 
 */
#define createClass(super, T) objc_allocateClassPair(super, #T, 0, &T##_vtable)

/**
 * 
 */
#define addMethod(cls, T, IMP) class_addMethod(cls, #IMP, (T##IMP)IMP, "")

typedef Class* (*objc_LoadClass)(Class super);

