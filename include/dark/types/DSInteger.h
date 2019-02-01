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

method (DSInteger, ToString,        char*, (const DSInteger* const));
method (DSInteger, CompareTo,       int, (const DSInteger* const, const DSInteger* const));
method (DSInteger, IntValue,        int, (const DSInteger* const));
method (DSInteger, LongValue,       long, (const DSInteger* const));
method (DSInteger, FloatValue,      float, (const DSInteger* const));
method (DSInteger, DoubleValue,     double, (const DSInteger* const));
method (DSInteger, CharValue,       char, (const DSInteger* const));
method (DSInteger, ShortValue,      short, (const DSInteger* const));

/**
 * Integer vtable with overrides
 */
vtable (DSInteger)
{
    const DSIntegerToString           ToString;
    const DSObjectEquals              Equals;
    const DSObjectGetHashCode         GetHashCode;
    const DSObjectDispose             Dispose;
    const DSIntegerCompareTo          CompareTo;
    const DSIntegerIntValue           IntValue;
    const DSIntegerLongValue          LongValue;
    const DSIntegerFloatValue         FloatValue;
    const DSIntegerDoubleValue        DoubleValue;
    const DSIntegerCharValue          CharValue;
    const DSIntegerShortValue         ShortValue;
};

#endif _DSINTEGER_H_
