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

method (DSNumber, ToString,        char*, (const DSNumber* const));
method (DSNumber, CompareTo,       int, (const DSNumber* const, const DSNumber* const));
method (DSNumber, IntValue,        int, (const DSNumber* const));
method (DSNumber, LongValue,       long, (const DSNumber* const));
method (DSNumber, FloatValue,      float, (const DSNumber* const));
method (DSNumber, DoubleValue,     double, (const DSNumber* const));
method (DSNumber, CharValue,       char, (const DSNumber* const));
method (DSNumber, ShortValue,      short, (const DSNumber* const));

/**
 * Object metaclass
 */
vtable (DSNumber) {
    const DSNumberToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSNumberCompareTo        CompareTo;
    const DSNumberIntValue         IntValue;
    const DSNumberLongValue        LongValue;
    const DSNumberFloatValue       FloatValue;
    const DSNumberDoubleValue      DoubleValue;
    const DSNumberCharValue        CharValue;
    const DSNumberShortValue       ShortValue;
};

class (DSNumber) {
    DSNumber* (*Create) ();
};

#endif _DSNUMBER_H_
