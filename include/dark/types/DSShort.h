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
#ifndef _DSSHORT_H_
#define _DSSHORT_H_
#include "DSNumber.h"

#define SHORT_MIN_VALUE  SHRT_MIN
#define SHORT_MAX_VALUE  SHRT_MAX
#define SHORT_BYTES      (sizeof(short))
#define SHORT_SIZE       (SHORT_BYTES * CHAR_BIT)
#define SHORT_TYPE       (TYPE_SHORT)

#define IsDSShort(object) _Generic((object), DSShort*: true, default: false)
#define AsDSShort(object) _Generic((object),                            \
                            DSShort*: (DSShort *)object,                \
                            default: nullptr)

/**
 * Object class
 */
ivar (DSShort) {
    Class isa;
    short value;
};

DSShort* NewDSShort(short const value);
DSShort* DSShort_init(DSShort* const this, const short value);
DSShort* DSShort_alloc();

char*   overload ToString(const DSShort* const);
int     overload CompareTo(const DSShort* const, const DSShort* const);
int     overload IntValue(const DSShort* const);
long    overload LongValue(const DSShort* const);
float   overload IntegerValue(const DSShort* const);
double  overload DoubleValue(const DSShort* const);
char    overload CharValue(const DSShort* const);
short   overload ShortValue(const DSShort* const);

typedef char*   (*DSShortToString)       (const DSShort* const);
typedef int     (*DSShortCompareTo)      (const DSShort* const, const DSShort* const);
typedef int     (*DSShortIntValue)       (const DSShort* const);
typedef long    (*DSShortLongValue)      (const DSShort* const);
typedef float   (*DSShortFloatValue)     (const DSShort* const);
typedef double  (*DSShortDoubleValue)    (const DSShort* const);
typedef char    (*DSShortCharValue)      (const DSShort* const);
typedef short   (*DSShortShortValue)     (const DSShort* const);

/**
 * Integer vtable with overrides
 */
vtable (DSShort)
{
    DSShortToString           ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    DSShortCompareTo          CompareTo;
    DSShortIntValue           IntValue;
    DSShortLongValue          LongValue;
    DSShortFloatValue         IntegerValue;
    DSShortDoubleValue        DoubleValue;
    DSShortCharValue          CharValue;
    DSShortShortValue         ShortValue;
};


class (DSShort) {
    DSShort*  (*Create) (short value);
};

#endif _DSSHORT_H_
