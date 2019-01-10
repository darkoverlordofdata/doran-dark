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
#ifndef _DSDOUBLE_H_
#define _DSDOUBLE_H_
#include "DSNumber.h"

#define DOUBLE_MIN_VALUE  DBL_MIN
#define DOUBLE_MAX_VALUE  DBL_MAX
#define DOUBLE_BYTES      (sizeof(double))
#define DOUBLE_SIZE       (DOUBLE_BYTES * CHAR_BIT)
#define DOUBLE_TYPE       (TYPE_DOUBLE)

#define IsDSDouble(object) _Generic((object), DSDouble*: true, default: false)
#define AsDSDouble(object) _Generic((object),                          \
                            DSDouble*: (DSDouble *)object,             \
                            default: nullptr)

/**
 * Double instance variables
 */
ivar (DSDouble) 
{
    Class isa;
    double value;
};

DSDouble* NewDSDouble(double const value);
DSDouble* DSDouble_init(DSDouble* const this, const double value);
DSDouble* DSDouble_alloc();

char*   overload ToString(const DSDouble* const);
int     overload CompareTo(const DSDouble* const, const DSDouble* const);
int     overload IntValue(const DSDouble* const);
long    overload LongValue(const DSDouble* const);
float   overload FloatValue(const DSDouble* const);
double  overload DoubleValue(const DSDouble* const);
char    overload CharValue(const DSDouble* const);
short   overload ShortValue(const DSDouble* const);

typedef char*   (*DSDoubleToString)       (const DSDouble* const);
typedef int     (*DSDoubleCompareTo)      (const DSDouble* const, const DSDouble* const);
typedef int     (*DSDoubleIntValue)       (const DSDouble* const);
typedef long    (*DSDoubleLongValue)      (const DSDouble* const);
typedef float   (*DSDoubleFloatValue)     (const DSDouble* const);
typedef double  (*DSDoubleDoubleValue)    (const DSDouble* const);
typedef char    (*DSDoubleCharValue)      (const DSDouble* const);
typedef short   (*DSDoubleShortValue)     (const DSDouble* const);

/**
 * Double vtable with overrides
 */
vtable (DSDouble)
{
    DSDoubleToString            ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    DSDoubleCompareTo           CompareTo;
    DSDoubleIntValue            IntValue;
    DSDoubleLongValue           LongValue;
    DSDoubleFloatValue          FloatValue;
    DSDoubleDoubleValue         DoubleValue;
    DSDoubleCharValue           CharValue;
    DSDoubleShortValue          ShortValue;
};

/**
 * Double class methods & vars
 */
class (DSDouble) {
    DSDouble* (*Create) (double value);
};



#endif _DSDOUBLE_H_
