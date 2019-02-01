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

method (DSShort, ToString,        char*, (const DSShort* const));
method (DSShort, CompareTo,       int, (const DSShort* const, const DSShort* const));
method (DSShort, IntValue,        int, (const DSShort* const));
method (DSShort, LongValue,       long, (const DSShort* const));
method (DSShort, FloatValue,      float, (const DSShort* const));
method (DSShort, DoubleValue,     double, (const DSShort* const));
method (DSShort, CharValue,       char, (const DSShort* const));
method (DSShort, ShortValue,      short, (const DSShort* const));


/**
 * Integer vtable with overrides
 */
vtable (DSShort)
{
    const DSShortToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSShortCompareTo        CompareTo;
    const DSShortIntValue         IntValue;
    const DSShortLongValue        LongValue;
    const DSShortFloatValue       FloatValue;
    const DSShortDoubleValue      DoubleValue;
    const DSShortCharValue        CharValue;
    const DSShortShortValue       ShortValue;
};

#endif _DSSHORT_H_
