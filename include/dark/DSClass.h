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
 *  MACRO method_proto
 *      declares the prototype for methods
 * 
 */
#define method_proto(T, name, type, signature)                          \
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
 * These remaining macros are used to 
 * generate the objc_load<DSname> function
 * used to load runtime class definitions
 * and build vtables
 * 
 *  MACRO $implementation
 *      start a class definition- create objects
 *      defines the inline vptr accessor
 *      defines lazy accessors for class size and reference
 * 
 */
#define _vptr(T) T##_vptr(this)

/**
 * Return the reference to the vtable
 * Load the vtable
 */
#define class_load(T)                                                   \
function struct T##_vtable* T##_vptr(T* this) {                         \
    return (struct T##_vtable*)this->isa->vtable;                       \
}                                                                       \
function Class objc_load##T(Class super)                                \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &T##_vtable;                                              \
    char* class_name = #T;                                              \
    Class isa = objc_allocateClassPair(super, #T, 0);                   \
    isa->vtable = &vt[0];               

/**
 * Add method address to the vtable
 */
#define class_method(name, imp, type)                                   \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 * Add method override address to the vtable
 */
#define class_override(name, imp, type)                                 \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 * Add virtual method address to the vtable
 */
#define vtable_virtual(name, imp, type)                                 \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 * Add member metadata about type
 */
#define class_member(name, len, type)                                   \
    class_addIvar(isa, #name, len, log2(len), type);

/**
 * Add vtable to runtime
 */
// #define class_fini                                                 \
//     return methodizeClass(isa);                                         \
// }
#define class_fini                                                 \
    return isa;                                         \
}
