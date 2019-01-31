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
 *  ivar    DSOject         - Instance Variables
 *  vtable  DSObjectVTable  - Instance Methods
 *  class   $DSObject       - Class Methods/Variables
 * 
 * An ivar whose 1st member is an 'isa' is a class of that isa type,
 * and it becomes the object definition for a DaRKSTEP object. 
 */
#define ivar(T)                                                         \
    typedef struct T T;                                                 \
    struct T

#define vtable(T)                                                       \
    struct T##_vtable T##_vtable;                                       \
    struct T##_vtable

#define class(T)                                                        \
    struct $##T $##T;                                                   \
    struct $##T

/**
 *  MACRO method
 *      map overloaded function to a fully resolved typedef
 * 
 *  example:
 * 
 *      method (DSObject, ToString, char*, (const DSObject*) );
 * 
 *  will create a both a forward declaration and typedef:
 *  
 *      char* overload ToString(const DSObject*);
 *      typedef char* (*DSObjectToString)(const DSObject*);
 * 
 *  These two definitions are then mapped in the vtable as
 *      
 *      vtable (DSObjec) {
 *          DSObjectToString ToString;
 *          ...
 * 
 */
#define method(class, name, type, signature)                            \
    type overload name signature;                                       \
    typedef type (*class##name)signature;

#define ctor(class, args...)                                            \
    class* overload class##_init(class* const, ## args);

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
#define instanceof(class, obj) InstanceOf(get##class##Isa(), obj)

/**
 *  MACRO of
 *      type constraint
 */
#define of(class) (Class)get##class##Isa()

/**
 * Note! These remaining macros are used 
 * to load runtime class definitions
 * 
 * 
 *  MACRO $implementation
 *      start a class definition- create objects
 *      defines the inline vptr accessor
 *      defines lazy accessors for class size and reference
 * 
 *  warning: only 1 $implementation per file due to vptr scoping
 */
#define $implementation(T)                                              \
static inline struct T##_vtable* _vptr(T* this) {                       \
    return (struct T##_vtable*)this->isa->vtable;                       \
}                                                                       \
Class _##T##_isa = nullptr;                                             \
Class get##T##Isa() {                                                   \
    _##T##_isa = _##T##_isa != nullptr                                  \
        ? _##T##_isa                                                    \
        : objc_getClass(#T);                                            \
    return _##T##_isa;                                                  \
}                                                                       \
Class T##Implementation(Class super);                                   \
Class T##Implementation(Class super)                                    \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &T##_vtable;                                              \
    char* class_name = #T;                                              \
    Class isa = objc_allocateClassPair(super, #T, 0);                   \
    isa->vtable = &vt[0];               
    

/**
 *  MACRO $method
 *      
 */
#define $method(name, imp, type)                                        \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 *  MACRO $virtual method
 *      this just documents that this is a virtual method
 */
#define $virtual(name, imp, type)                                       \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 *  MACRO $override method
 *      this just documents that this is a overriden method
 *      
 */
#define $override(name, imp, type)                                      \
    class_addMethod(isa, #name, imp, type);                             \
    vt[k++] = imp; 

/**
 *  MACRO $ivar
 *      
 */
#define $ivar(name, len, type)                                          \
    class_addIvar(isa, #name, len, log2(len), type);

/**
 *  MACRO $isa method
 *      
 */
#define $class_method(name, imp, type)                                  \
    class_addMethod(GETMETA(isa), #name, imp, type);                    \

/**
 *  MACRO  $isa ivar
 *      
 */
#define $class_ivar(name, len, type)                                    \
    class_addIvar(GETMETA(isa), #name, len, log2(len), type);

/**
 *  MACRO $end
 *      wrap up class definitions     
 */
#define $end                                                            \
    return methodizeClass(isa);                                         \
}

#endif _DSCLASS_H_ 
