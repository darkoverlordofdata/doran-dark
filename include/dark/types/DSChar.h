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
#ifndef _DSCHAR_H_
#define _DSCHAR_H_
#include "DSNumber.h"

#define CHAR_MIN_VALUE  CHAR_MIN
#define CHAR_MAX_VALUE  CHAR_MAX
#define CHAR_BYTES      (sizeof(char))
#define CHAR_SIZE       (CHAR_BYTES * CHAR_BIT)
#define CHAR_TYPE       (TYPE_CHAR)

#define IsDSChar(object) _Generic((object), DSChar*: true, default: false)
#define AsDSChar(object) _Generic((object),                             \
                            DSChar*: (DSChar *)object,                  \
                            default: nullptr)

/**
 * Char instance variables
 */
ivar (DSChar) {
    Class isa;
    char value;
};

DSChar* NewDSChar(const char value);
DSChar* DSChar_alloc();
DSChar* DSChar_init(DSChar* const this, const char value);

int     overload Compare(const char x, const char y);

method (DSChar, ToString,        char*, (const DSChar* const));
method (DSChar, CompareTo,       int, (const DSChar* const, const DSChar* const));
method (DSChar, IntValue,        int, (const DSChar* const));
method (DSChar, LongValue,       long, (const DSChar* const));
method (DSChar, FloatValue,      float, (const DSChar* const));
method (DSChar, DoubleValue,     double, (const DSChar* const));
method (DSChar, CharValue,       char, (const DSChar* const));
method (DSChar, ShortValue,      short, (const DSChar* const));

/**
 * Char vtable with overrides
 */
vtable (DSChar)
{
    const DSCharToString          ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSCharCompareTo         CompareTo;
    const DSCharIntValue          IntValue;
    const DSCharLongValue         LongValue;
    const DSCharFloatValue        FloatValue;
    const DSCharDoubleValue       DoubleValue;
    const DSCharCharValue         CharValue;
    const DSCharShortValue        ShortValue;
};

#endif _DSCHAR_H_
