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
#ifndef _DSINTEGER_H_
#define _DSINTEGER_H_
#include "DSNumber.h"
#include "DSLong.h"


#define INTEGER_MIN_VALUE  INT_MIN
#define INTEGER_MAX_VALUE  INT_MAX
#define INTEGER_BYTES      (sizeof(int))
#define INTEGER_SIZE       (INTEGER_BYTES * CHAR_BIT)
#define INTEGER_TYPE       (TYPE_LONG)

#define IsDSInteger(object) _Generic((object), DSInteger*: true, default: false)
#define AsDSInteger(object) _Generic((object),                          \
                            DSInteger*: (DSInteger *)object,            \
                            default: nullptr)

/**
 * Object class
 */
ivar (DSInteger) 
{
    Class isa;
    int value;
};


DSInteger* NewDSInteger(int const value);
DSInteger* DSInteger_init(DSInteger* const this, const int value);
DSInteger* DSInteger_alloc();

char*   overload ToString(const DSInteger* const);
int     overload CompareTo(const DSInteger* const, const DSInteger* const);
int     overload IntValue(const DSInteger* const);
long    overload LongValue(const DSInteger* const);
float   overload IntegerValue(const DSInteger* const);
double  overload DoubleValue(const DSInteger* const);
char    overload CharValue(const DSInteger* const);
short   overload ShortValue(const DSInteger* const);

typedef char*   (*DSIntegerToString)       (const DSInteger* const);
typedef int     (*DSIntegerCompareTo)      (const DSInteger* const, const DSInteger* const);
typedef int     (*DSIntegerIntValue)       (const DSInteger* const);
typedef long    (*DSIntegerLongValue)      (const DSInteger* const);
typedef float   (*DSIntegerFloatValue)     (const DSInteger* const);
typedef double  (*DSIntegerDoubleValue)    (const DSInteger* const);
typedef char    (*DSIntegerCharValue)      (const DSInteger* const);
typedef short   (*DSIntegerShortValue)     (const DSInteger* const);

/**
 * Integer vtable with overrides
 */
vtable (DSInteger)
{
    DSIntegerToString           ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    DSIntegerCompareTo          CompareTo;
    DSIntegerIntValue           IntValue;
    DSIntegerLongValue          LongValue;
    DSIntegerFloatValue         IntegerValue;
    DSIntegerDoubleValue        DoubleValue;
    DSIntegerCharValue          CharValue;
    DSIntegerShortValue         ShortValue;
};

class (DSInteger) {
    DSInteger*(*Create) (int value);
};


#endif _DSINTEGER_H_
