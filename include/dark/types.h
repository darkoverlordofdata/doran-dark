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
#ifndef _TYPES_H
#define _TYPES_H
/**
 * lowest level internal core types
 */
static const int MajorVersion = 0; 
static const int MinorVersion = 0;
static const int BuildVersion = 1;
/**
 * the core ohject system:
 * 
 * this is the DaRKSTEP DSObject and DSClass
 */
#include "core.h"
#include "hashmap.h"
#include "DSLog.h"
#include "DSClass.h"
#include "DSObject.h"

/**
 * functional objects
 * 
 * some opaque helpers
 * Inspired by scala & haskell
 */
#include "Functional/Either.h"
#include "Functional/Option.h"
#include "Functional/Maybe.h"

/**
 * base framework
 * 
 * The Dark Overload stdlib
 */
#include "DSException.h"
#include "DSComparable.h"
#include "collections/DSArray.h"
#include "collections/DSMap.h"
#include "collections/DSList.h"
#include "types/DSNumber.h"
#include "types/DSBoolean.h"
#include "types/DSString.h"
#include "types/DSStringBuilder.h"
#include "types/DSChar.h"
#include "types/DSDouble.h"
#include "types/DSFloat.h"
#include "types/DSInteger.h"
#include "types/DSLong.h"
#include "types/DSShort.h"
/**
 *  MACRO $
 *      Wrap a primitive type in a DSObject*
 */
#define $(T) _Generic((T),                                              \
                                                                        \
        _Bool:              NewDSBoolean,                               \
        char:               NewDSChar,                                  \
        signed char:        NewDSChar,                                  \
        const char *:       NewDSString,                                \
        char *:             NewDSString,                                \
        short int:          NewDSShort,                                 \
        unsigned short int: NewDSShort,                                 \
        unsigned int:       NewDSInteger,                               \
        long int:           NewDSLong,                                  \
        unsigned long int:  NewDSLong,                                  \
        int:                NewDSInteger,                               \
        float:              NewDSFloat,                                 \
        double:             NewDSDouble,                                \
        default:            NewDSString)(T)



/**
 *  MACRO typeof
 *      return the typename of T
 */
#define typeof(T) \
    _Generic((T),        /* wrap a primitive type */      \
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
        DSMap *: "DSMap",                                       \
        DSList *: "DSList",                                             \
        DSClass : "DSClass",                                            \                                               
        default: "unknown")

        // Vec2 : "Vec2",                                                  \
        // Vec3 : "Vec3",                                                  \
        // Vec4 : "Vec4",                                                  \
        // Matrix : "Matrix",                                              \

#endif _TYPES_H
