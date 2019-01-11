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
    struct T##_vtable T##_vtable;                                         \
    struct T##_vtable

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
static inline struct T##_vtable* _vptr(T* this) {                       \
    return (struct T##_vtable*)this->isa->vtable;                       \
}                                                                       \
int _##T##_size = -1;                                            \
int get##T##Size() {                                             \
    _##T##_size = _##T##_size > 0                                       \
        ? _##T##_size                                                   \
        : class_getAlignedInstanceSize(objc_getClass(#T));              \
    return _##T##_size;                                                 \
}                                                                       \
Class _##T##_isa = nullptr;                                      \
Class get##T##Isa() {                                            \
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
 *      wrap up, define vtable     
 */
#define $end                                                            \
    return methodizeClass(isa);                                         \
}

/**
 *  MACRO Vptr
 *      Returns the vtable base for this class
 */
#define $vptr(T) ((struct T##_vtable*)(this->isa->vtable))

// DSChar* NewDSChar(char value) { 
//     return DSChar_init(DSChar_alloc(), value); 
// }

#define new(T, args...) T##_init(T##_alloc(), ## args)
// #define new(T, ...) T##_init(T##_alloc(), ## __VA_ARGS__)

// #define auto __auto_type
#define var __auto_type
#define instanceof(class, obj) InstanceOf(get##class##Isa(), obj)
#define of(class) (Class)get##class##Isa()

#define $(T) _Generic((T),                                              \
                                                                        \
        _Bool:              $DSBoolean.Create,                          \
        char:               $DSChar.Create,                             \
        signed char:        $DSChar.Create,                             \
        const char *:       $DSString.Create,                           \
        char *:             $DSString.Create,                           \
        short int:          $DSShort.Create,                            \
        unsigned short int: $DSShort.Create,                            \
        unsigned int:       $DSInteger.Create,                          \
        long int:           $DSLong.Create,                             \
        unsigned long int:  $DSLong.Create,                             \
        int:                $DSInteger.Create,                          \
        float:              $DSFloat.Create,                            \
        double:             $DSDouble.Create,                           \
        default:            $DSString.Create)(T)


#define typeof(T) _Generic((T),        /* wrap a primitive type */      \
                                                                        \
        _Bool: "bool",                                                  \
        unsigned char: "unsigned char",                                 \
        char: "char",                                                   \
        signed char: "signed char",                                     \
        short int: "short int",                                         \
        unsigned short int: "unsigned short int",                       \
        int: "int",                                                     \
        unsigned int: "unsigned int",                                   \
        long int: "long int",                                           \
        unsigned long int: "unsigned long int",                         \
        long long int: "long long int",                                 \
        unsigned long long int: "unsigned long long int",               \
        float: "float",                                                 \
        double: "double",                                               \
        long double: "long double",                                     \
        char *: "pointer to char",                                      \
        void *: "pointer to void",                                      \
        int *: "pointer to int",                                        \
        const char *: "const pointer to char",                          \
        DSObject *: "DSObject",                                         \
        DSComparable * : "DSComparable",                                \
        DSBoolean *: "DSBoolean",                                       \
        DSChar *: "DSChar",                                             \
        DSDouble *: "DSDouble",                                         \
        DSFloat *: "DSFloat",                                           \
        DSInteger *: "DSInteger",                                       \
        DSLong *: "DSLong",                                             \
        DSNumber *: "DSNumber",                                         \
        DSShort *: "DSShort",                                           \
        DSString *: "DSString",                                         \
        DSStringBuilder *: "DSStringBuilder",                           \
        DSArray *: "DSArray",                                           \
        DSHashmap *: "DSHashmap",                                       \
        DSList *: "DSList",                                             \
        DSClass : "DSClass",                                            \                                               
        default: "unknown")

        // Vec2 : "Vec2",                                                  \
        // Vec3 : "Vec3",                                                  \
        // Vec4 : "Vec4",                                                  \
        // Matrix : "Matrix",                                              \

#endif _DSCLASS_H_ 
