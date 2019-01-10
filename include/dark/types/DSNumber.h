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
#ifndef _DSNUMBER_H_
#define _DSNUMBER_H_
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../DSObject.h"
#include "../DSComparable.h"

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

#define IsDSNumber(object) _Generic((object), DSNumber*: true, default: false)
#define AsDSNumber(object) _Generic((object),                           \
                            DSNumber*: (DSNumber *)object,              \
                            default: nullptr)


/**
 * Object class
 */
ivar (DSNumber) {
    Class isa;
};

char*   overload ToString(const DSNumber* const);
int     overload CompareTo(const DSNumber* const, const DSNumber* const);
int     overload IntValue(const DSNumber* const);
long    overload LongValue(const DSNumber* const);
float   overload IntegerValue(const DSNumber* const);
double  overload DoubleValue(const DSNumber* const);
char    overload CharValue(const DSNumber* const);
short   overload ShortValue(const DSNumber* const);

// long    overload LongValue(const void* const);

typedef int     (*DSNumberCompareTo)  (const DSNumber* const, const DSNumber* const);
typedef char*   (*DSNumberToString)  (const DSNumber* const);
typedef int     (*DSNumberIntValue)  (const DSNumber* const);
typedef long    (*DSNumberLongValue)  (const DSNumber* const);
typedef float   (*DSNumberFloatValue)  (const DSNumber* const);
typedef double  (*DSNumberDoubleValue)  (const DSNumber* const);
typedef char    (*DSNumberCharValue)  (const DSNumber* const);
typedef short   (*DSNumberShortValue)  (const DSNumber* const);

/**
 * Object metaclass
 */
vtable (DSNumber) {
    char*   (*ToString)     (const DSNumber* const);
    bool    (*Equals)       (const DSObject* const, const DSObject* const);
    int     (*GetHashCode)  (const DSObject* const);
    void    (*Dispose)      (DSObject* const);
    int     (*CompareTo)    (const DSNumber* const, const DSNumber*);
    int     (*IntValue)     (const DSNumber* const);
    long    (*LongValue)    (const DSNumber* const);
    float   (*FloatValue)   (const DSNumber* const);
    double  (*DoubleValue)  (const DSNumber* const);
    char    (*CharValue)    (const DSNumber* const);
    short   (*ShortValue)   (const DSNumber* const);
    
};

class (DSNumber) {
    DSNumber* (*Create) ();
};


int overload CompareTo(const DSNumber* const, const DSNumber* const);
int overload IntValue(const DSNumber* const);
long overload LongValue(const DSNumber* const);
float overload FloatValue(const DSNumber* const);
double overload DoubleValue(const DSNumber* const);
char overload CharValue(const DSNumber* const);
short overload ShortValue(const DSNumber* const);
char* overload ToString(const DSNumber* const);

#endif _DSNUMBER_H_
