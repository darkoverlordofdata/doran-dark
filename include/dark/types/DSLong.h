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
#ifndef _DSLONG_H_
#define _DSLONG_H_
#include "DSNumber.h"

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

#define IsDSLong(object) _Generic((object), DSLong*: true, default: false)
#define AsDSLong(object) _Generic((object),                             \
                            DSLong*: (DSLong *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
ivar (DSLong) 
{
    Class isa;
    long value;
};

DSLong* NewDSLong(long const value);
DSLong* DSLong_init(DSLong* const this, const long value);
DSLong* DSLong_alloc();

char*   overload ToString(const DSLong* const);
int     overload CompareTo(const DSLong* const, const DSLong* const);
int     overload IntValue(const DSLong* const);
long    overload LongValue(const DSLong* const);
float   overload IntegerValue(const DSLong* const);
double  overload DoubleValue(const DSLong* const);
char    overload CharValue(const DSLong* const);
short   overload ShortValue(const DSLong* const);

typedef char*   (*DSLongToString)       (const DSLong* const);
typedef int     (*DSLongCompareTo)      (const DSLong* const, const DSLong* const);
typedef int     (*DSLongIntValue)       (const DSLong* const);
typedef long    (*DSLongLongValue)      (const DSLong* const);
typedef float   (*DSLongFloatValue)     (const DSLong* const);
typedef double  (*DSLongDoubleValue)    (const DSLong* const);
typedef char    (*DSLongCharValue)      (const DSLong* const);
typedef short   (*DSLongShortValue)     (const DSLong* const);

/**
 * Integer vtable with overrides
 */
vtable (DSLong)
{
    DSLongToString           ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    DSLongCompareTo          CompareTo;
    DSLongIntValue           IntValue;
    DSLongLongValue          LongValue;
    DSLongFloatValue         IntegerValue;
    DSLongDoubleValue        DoubleValue;
    DSLongCharValue          CharValue;
    DSLongShortValue         ShortValue;
};




class (DSLong) {
    DSLong*   (*Create) (long);
};


#endif _DSLONG_H_
