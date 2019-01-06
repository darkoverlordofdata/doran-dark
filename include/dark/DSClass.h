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
#define ivar(name)                                                      \
    typedef struct name name;                                           \
    struct name

#define vtable(class)                                                   \
    struct class##vtable class##vtable;                                 \
    struct class##vtable

#define class(name)                                                     \
    struct $##name $##name;                                             \
    struct $##name

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
#define $implementation(class)                                          \
static inline struct class##vtable* _vptr(class* this) {                \
    return (struct class##vtable*)this->isa->vtable;                    \
}                                                                       \
static int _##class##_size = -1;                                        \
static int get##class##Size() {                                         \
    _##class##_size = _##class##_size > 0                               \
        ? _##class##_size                                               \
        : class_getAlignedInstanceSize(objc_getClass(#class));          \
    return _##class##_size;                                             \
}                                                                       \
static Class _##class##_isa = nullptr;                                  \
static Class get##class##Isa() {                                        \
    _##class##_isa = _##class##_isa != nullptr                          \
        ? _##class##_isa                                                \
        : objc_getClass(#class);                                        \
    return _##class##_isa;                                              \
}                                                                       \
Class class##Implementation(Class super);                               \
Class class##Implementation(Class super)                                \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &class##vtable;                                           \
    char* class_name = #class;                                          \
    Class isa = objc_allocateClassPair(super, #class, 0);               \
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
#define $vptr(class) ((struct class##vtable*)(this->isa->vtable))

#endif _DSCLASS_H_ 
