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

/** 
 * create a new class instance 
 */
#define DSNew(class) DSMalloc (sizeof(class))


/** 
 * start a class definition
 */
#define class(name) \
    typedef struct name name;   /* define name */ \
    Class* DSIsa##name();       /* forward reference DSIsaName() */ \ 
    struct name

/**
 * paste together a reference to class metadata 
 */
#define isa(name) &name##Class

/**
 * method overload 
 */
#define overload __attribute__((overloadable))

class (Class) {
	Class* isa;
	Class* superclass;
	char* name;
};

/**
 * Class metaclass
 */
struct DSClass {
    int count;
    Class* classes[100];
} DSClass;

/**
 *  DSDefine - define a class runtime metadata
 * 
 * @param class name
 * @param super superclass name
 * @param var temporary variable to use
 * @param block 
 */
#define DSDefine(class, super, var, block) \
Class* DSIsa##class() \
{   /* set defaults */ \
    class##Class = (struct class##Class) { \
        .isa            = &class##Class, \
        .superclass     = &super##Class, \
        .name           = #class, \
        .Equals         = DSObjectClass.Equals, \
        .GetHashCode    = DSObjectClass.GetHashCode, \
        .Dispose        = DSObjectClass.Dispose, \
        .ReferenceEquals= DSObjectClass.ReferenceEquals, \
        .InstanceEquals = DSObjectClass.InstanceEquals, \
        .ToString       = DSObjectClass.ToString, \
    }; \
    /* temporary variable used by block */ \
    struct class##Class *var = &class##Class; \
    /* excute the code block of customizations */ \
    do { block } while(0);\
    DSClass.classes[DSClass.count++] = &class##Class; \
    return &class##Class; \
}

/** 
 * start of metaclass definition
 */
#define DSMetaClass(name) \
    Class* DSIsa##name()

/**
 * load the metaclass info for name 
 */
#define DSLoadClass(name) DSIsa##name()

/**
 * add a class to the global class list
 */
#define DSAddMetadata(name) (DSClass.classes[DSClass.count++] = &name)

#endif _CLASS_H_ 
