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

method (DSLong, ToString,        char*, (const DSLong* const));
method (DSLong, CompareTo,       int, (const DSLong* const, const DSLong* const));
method (DSLong, IntValue,        int, (const DSLong* const));
method (DSLong, LongValue,       long, (const DSLong* const));
method (DSLong, FloatValue,      float, (const DSLong* const));
method (DSLong, DoubleValue,     double, (const DSLong* const));
method (DSLong, CharValue,       char, (const DSLong* const));
method (DSLong, ShortValue,      short, (const DSLong* const));


/**
 * Integer vtable with overrides
 */
vtable (DSLong)
{
    const DSLongToString           ToString;
    const DSObjectEquals           Equals;
    const DSObjectGetHashCode      GetHashCode;
    const DSObjectDispose          Dispose;
    const DSLongCompareTo          CompareTo;
    const DSLongIntValue           IntValue;
    const DSLongLongValue          LongValue;
    const DSLongFloatValue         FloatValue;
    const DSLongDoubleValue        DoubleValue;
    const DSLongCharValue          CharValue;
    const DSLongShortValue         ShortValue;
};

#endif _DSLONG_H_
