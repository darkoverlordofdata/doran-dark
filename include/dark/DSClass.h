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
 * 3 global tuples are created for each Class:
 *  ivar    DSOject         - Instance Variables
 *  vtable  DSObjectVTable  - Instance Methods
 *  class   $DSObject       - Class Methods/Variables
 */
#define ivar(T)                                                         \
    typedef struct T T;                                                 \
    struct T

#define vtable(T)                                                       \
    struct T##vtable T##vtable;                                         \
    struct T##vtable

#define class(T)                                                        \
    struct $##T $##T;                                                   \
    struct $##T

/**
 *  MACRO overload
 *      method overload 
 */
#define overload __attribute__((overloadable))


/**
 *  MACRO $implementation
 *      start a class definition- create objects
 *      defines the inline vptr accessor
 *      defines lazy accessors for class size and reference
 * 
 *  warning: only 1 $implementation per main file due to vptr scoping
 */
#define $implementation(T)                                              \
static inline struct T##vtable* _vptr(T* this) {                        \
    return (struct T##vtable*)this->isa->vtable;                        \
}                                                                       \
static int _##T##_size = -1;                                            \
static int get##T##Size() {                                             \
    _##T##_size = _##T##_size > 0                                       \
        ? _##T##_size                                                   \
        : class_getAlignedInstanceSize(objc_getClass(#T));              \
    return _##T##_size;                                                 \
}                                                                       \
static Class _##T##_isa = nullptr;                                      \
static Class get##T##Isa() {                                            \
    _##T##_isa = _##T##_isa != nullptr                                  \
        ? _##T##_isa                                                    \
        : objc_getClass(#T);                                            \
    return _##T##_isa;                                                  \
}                                                                       \
Class T##Implementation(Class super);                                   \
Class T##Implementation(Class super)                                    \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &T##vtable;                                               \
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
    //vt[k++] = imp; 

/**
 *  MACRO  $isa ivar
 *      
 */
#define $class_ivar(name, len, type)                                    \
    class_addIvar(GETMETA(isa), #name, len, log2(len), type);

/**
 *  MACRO $end
 *      wrap up, define vtable     
 */
#define $end                                                            \
    return methodizeClass(isa);                                         \
}

/**
 *  MACRO Vptr
 *      Returns the vtable base for this class
 */
#define $vptr(T) ((struct T##vtable*)(this->isa->vtable))


// DSChar* NewDSChar(char value) { 
//     return DSChar_init(DSChar_alloc(), value); 
// }

#define new(T, args...) T##_init(T##_alloc(), ## args)
// #define new(T, ...) T##_init(T##_alloc(), ## __VA_ARGS__)

#define auto __auto_type

#endif _DSCLASS_H_ 
