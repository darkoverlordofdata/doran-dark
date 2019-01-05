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
/** Class Macro's */

/**
 *  MACRO class
 *      typedef'd structs
 */
#define class(name)                                                     \
    typedef struct name name;                                           \
    struct name

/**
 * 3 clobal variables are created for each Class:
 *  DSOject         - Ivar Instance Variables
 *  DSObjectVTable  - Instance Methods
 *  $DSObject       - Class Methods/Variables
 */
#define Ivar(name)                                                      \
    typedef struct name name;                                           \
    struct name

#define VTable(name)                                                    \
    struct name##VTable name##VTable;                                   \
    struct name##VTable

#define Singleton(name)                                                 \
    struct name name;                                                   \
    struct name

/**
 *  MACRO overload
 *      method overload 
 */
#define overload __attribute__((overloadable))


/**
 *  MACRO $implementation
 *      start a class definition- create objects
 */
#define $implementation(class)                                          \
static int _##class##_size = -1;                                        \
static int get##class##Size() {                                         \
    _##class##_size = _##class##_size > 0                               \
        ? _##class##_size                                               \
        : class_getAlignedInstanceSize(objc_getClass(#class));          \
    return _##class##_size;                                             \
}                                                                       \
Class class##Implementation(Class super);                               \
Class class##Implementation(Class super)                                \
{                                                                       \
    int k = 0;                                                          \
    IMP* vt = &class##VTable;                                           \
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

    // // return DSNumberVTable.LongValue(this);
    // struct DSNumberVTable* v = (struct DSNumberVTable*)(this->isa->vtable);
    // DSLog("LongValue: vtable %x", v->LongValue);
    // return v->LongValue(this);

#define Vptr(class) ((struct class##VTable*)(this->isa->vtable))


#endif _DSCLASS_H_ 
