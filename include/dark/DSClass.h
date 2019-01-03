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
#ifndef _CLASS_H_
#define _CLASS_H_
#include "core.h"
#include "runtime.h"
/**
 * 
 * 
 */
/**
 * DSClass 
 * we don't have a seperate metaclass, for simplicity, it's just
 * appended to the class data.
 * DSClass holds the list of classes.
 */
struct DSClass {
    Class isa;
    Class superclass;
    char* name;
    long version;
    long info; 
    long instance_size;

} DSClass;

struct DSClassList {
    long count;
    Class classes[100];
} DSClassList;

/**
 *  MACRO begin_class
 *      start a class definition- create objects
 */
#define begin_class(class) Class class##Implementation(Class super)     \
{                                                                       \
    Class obj = objc_allocateClassPair(super, #class, 0);

/**
 *  MACRO method
 *      
 */
#define method(name, imp, type) class_addMethod(obj, name, imp, type);
/**
 *  MACRO ivar
 *      
 */
#define ivar(name, len, type) class_addIvar(obj, name, len, log2(len), type);

/**
 *  MACRO class method
 *      
 */
#define class_method(name, imp, type) class_addMethod(GETMETA(obj), name, imp, type);
/**
 *  MACRO  class ivar
 *      
 */
#define class_ivar(name, len, type) class_addIvar(GETMETA(obj), name, len, log2(len), type);

/**
 *  MACRO end_class
 *      wrap up, define vtable     
 */
#define end_class                                                       \
    return methodizeClass(obj);                                         \
}


/**
 *  MACRO class
 *      start a class definition
 */
#define class(name)                                                     \
    typedef struct name name;   /* define name */                       \
    Class DSDefine##name();     /* forward reference DSDefinexxx() */   \ 
    Class name##Implemention(Class super);                              \
    struct name

#define IVAR(name)                                                      \
    typedef struct name name;   /* define name */                       \
    Class name##Implemention(Class super);                              \
    struct name
/**
 *  MACRO overload
 *      method overload 
 */
#define overload __attribute__((overloadable))

/**
 *  MACRO ISA
 *      generate isa value from name
 */
#define ISA(class) &class##Class


/**
 *  MACRO class_alloc
 *      allocate an instance sized chunk of gc'd memory
 */
#define class_alloc(cls) DSMalloc((&cls##Class)->instance_size)

/**
 *  MACRO class_isa
 *      returns a muggled isa ptr from a class
 */
#define class_isa(cls) ((Class)(((UInt64)cls->isa)&MUGGLE))

/**
 *  MACRO DSDefine
 *      define a class runtime metadata loader
 * 
 * a valid object has in isa that points to a valid class
 * to verify, classes have 4 MSB set to MAJIK
 * 
 * 
 * @param class name
 * @param super superclass name
 * @param var temporary variable to use
 * @param block of custom settings
 */
#define DSDefine(class, super, var, block)                              \
Class class_load##class()                                               \
{   /* set defaults */                                                  \
    class##Class = (struct class##Class) {                              \
        .isa            = ISA(class),                                   \
        .superclass     = ISA(super),                                   \
        .name           = #class,                                       \
        .instance_size  = sizeof(class),                                \
        .Equals         = DSObjectClass.Equals,                         \
        .GetHashCode    = DSObjectClass.GetHashCode,                    \
        .Dispose        = DSObjectClass.Dispose,                        \
        .ReferenceEquals= DSObjectClass.ReferenceEquals,                \
        .InstanceEquals = DSObjectClass.InstanceEquals,                 \
        .ToString       = DSObjectClass.ToString,                       \
    };                                                                  \
    /* temporary variable used by block */                              \
    struct class##Class *var = &class##Class;                           \
    /* excute the code block of customizations */                       \
    do { block } while(0);                                              \
    DSClassList.classes[DSClassList.count++] = &class##Class;           \
    return ISA(class);                                                  \
}

#endif _CLASS_H_ 
