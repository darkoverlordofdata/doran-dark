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
#include <stdio.h> 
#include <stdarg.h>
#include <math.h> 

/**
 * lowest level internal core types
 */
static const int MajorVersion = 0; 
static const int MinorVersion = 0;
static const int BuildVersion = 1;
/**
 * the core ohject system:
 * 
 * this is the DaRKSTEP Object and DSClass
 */
#include <dark/core.h>
#include <dark/polyfill.h>
#include <dark/core/class.h>
#include <dark/core/object.h>
#include <dark/printf.h>
#include <dark/classes.h>
/**
 * functional objects
 * 
 * some opaque helpers
 * Inspired by scala & haskell
 */
#include <dark/functional/either.h>
#include <dark/functional/option.h>
#include <dark/functional/maybe.h>

/**
 * base framework
 * 
 * The Dark Overload stdlib
 */
#include <dark/core/exception.h>
#include <dark/core/comparable.h>
#include <dark/collections/array.h>
#include <dark/collections/map.h>
#include <dark/collections/list.h>
#include <dark/types/number.h>
#include <dark/types/boolean.h>
#include <dark/types/string.h>
#include <dark/types/stringbuilder.h>
#include <dark/types/char.h>
#include <dark/types/double.h>
#include <dark/types/float.h>
#include <dark/types/integer.h>
#include <dark/types/long.h>
#include <dark/types/short.h>

static inline Boolean* NewBoolean(bool const value){
    return new(Boolean, value);
}
static inline Char* NewChar(char const value) {
    return new(Char, value);
}
static inline String* NewString(char* const value) {
    return new(String, value);
}

static inline Short* NewShort(short const value) {
    return new(Short, value);
}

static inline Integer* NewInteger(int const value) {
    return new(Integer, value);
}

static inline Long* NewLong(long const value) {
    return new(Long, value);
}

static inline Float* NewFloat(float const value) {
    return new(Float, value);
}

static inline Double* NewDouble(double const value) {
    return new(Double, value);
}
/**
 *  MACRO $
 *      Wrap a primitive type in a Object*
 */
#define $(T) _Generic((T),                                              \
                                                                        \
        _Bool:              NewBoolean,                                 \
        char:               NewChar,                                    \
        signed char:        NewChar,                                    \
        const char *:       NewString,                                  \
        char *:             NewString,                                  \
        short int:          NewShort,                                   \
        unsigned short int: NewShort,                                   \
        unsigned int:       NewInteger,                                 \
        long int:           NewLong,                                    \
        unsigned long int:  NewLong,                                    \
        int:                NewInteger,                                 \
        float:              NewFloat,                                   \
        double:             NewDouble,                                  \
        default:            NewString)(T)



/**
 *  MACRO typeof
 *      return the typename of T
 */
#define typeof(T) \
    _Generic((T),        /* wrap a primitive type */                    \
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
        Object *: "Object",                                             \
        Comparable * : "Comparable",                                    \
        Boolean *: "Boolean",                                           \
        Char *: "Char",                                                 \
        Double *: "Double",                                             \
        Float *: "Float",                                               \
        Integer *: "Integer",                                           \
        Long *: "Long",                                                 \
        Number *: "Number",                                             \
        Short *: "Short",                                               \
        String *: "String",                                             \
        StringBuilder *: "StringBuilder",                               \
        Array *: "Array",                                               \
        Map *: "Map",                                                   \
        List *: "List",                                                 \
        default: "unknown")


