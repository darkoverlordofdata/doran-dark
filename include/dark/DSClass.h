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
#ifndef _DSCLASS_H_
#define _DSCLASS_H_
#include "core.h"
#include "runtime.h"
#include <dark/DSLog.h>
/**
****
****    All macros used to define DaRKSTEP classes and objects
****
**/

/**
 * 3 global tuples are created for each Class:
 *  type    DSOject         - Instance Variables
 *  vtable  DSObjectVTable  - Instance Methods
 *  class   $DSObject       - Class Methods/Variables
 * 
 * An ivar whose 1st member is an 'isa' is a class of that isa type,
 * and it becomes the object definition for a DaRKSTEP object. 
 */
#define type(T)                                                         \
    typedef struct T T;                                                 \
    struct T

#define vtable(T)                                                       \
    struct T##_vtable T##_vtable;                                       \
    struct T##_vtable

#define class(T)                                                        \
    struct $##T $##T;                                                   \
    struct $##T

#define proc static inline

#define method proc overload

/**
 *  MACRO def_method
 *      declarations for method
 * 
 */
#define def_method(T, name, type, signature)                                \
    method type name signature;                                             \
    typedef type (*T##name)signature;

/**
 *  MACRO def_ctor
 *      declarations for constructor
 * 
 */
#define def_ctor(T, args...)                                                \
    method T* T##_init(T* const, ## args);
/**
 *  MACRO alloc
 *      Allocate memory for ivar struct
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
 * Note! These remaining macros are used 
 * to load runtime class definitions
 * and build the vtable 
 * 
 *  MACRO $implementation
 *      start a class definition- create objects
 *      defines the inline vptr accessor
 *      defines lazy accessors for class size and reference
 * 
 */
#define vtable_ptr(T)                                                   \
proc struct T##_vtable* T##_vptr(T* this) {                             \
    return (struct T##_vtable*)this->isa->vtable;                       \
}

#define get_vptr(T) T##_vptr(this)

#define class_bind(T)                                                   \
proc Class objc_load##T(Class super)                                    \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &T##_vtable;                                              \
    char* class_name = #T;                                              \
    Class isa = objc_allocateClassPair(super, #T, 0);                   \
    isa->vtable = &vt[0];               


#define class_method(name, imp, type)                                   \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

#define class_override(name, imp, type)                                 \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

#define vtable_virtual(name, imp, type)                                 \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

#define class_member(name, len, type)                                   \
    class_addIvar(isa, #name, len, log2(len), type);

#define class_methodize                                                 \
    return methodizeClass(isa);                                         \
}


#endif _DSCLASS_H_ 
