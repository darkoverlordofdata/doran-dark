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
ivar (DSChar) 
{
    Class isa;
    char value;
};

DSChar* NewDSChar(const char value);
DSChar* DSChar_alloc();
DSChar* DSChar_init(DSChar* const this, const char value);

char*   overload ToString(const DSChar* const);
int     overload Compare(const char x, const char y);
int     overload CompareTo(const DSChar* const, const DSChar* const);
int     overload IntValue(const DSChar* const);
long    overload LongValue(const DSChar* const);
float   overload FloatValue(const DSChar* const);
double  overload DoubleValue(const DSChar* const);
char    overload CharValue(const DSChar* const);
short   overload ShortValue(const DSChar* const);


typedef char*   (*DSCharToString)       (const DSChar* const);
typedef int     (*DSCharCompareTo)      (const DSChar* const, const DSChar* const);
typedef int     (*DSCharIntValue)       (const DSChar* const);
typedef long    (*DSCharLongValue)      (const DSChar* const);
typedef float   (*DSCharFloatValue)     (const DSChar* const);
typedef double  (*DSCharDoubleValue)    (const DSChar* const);
typedef char    (*DSCharCharValue)      (const DSChar* const);
typedef short   (*DSCharShortValue)     (const DSChar* const);

/**
 * Char vtable with overrides
 */
vtable (DSChar)
{
    DSCharToString          ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    DSCharCompareTo         CompareTo;
    DSCharIntValue          IntValue;
    DSCharLongValue         LongValue;
    DSCharFloatValue        FloatValue;
    DSCharDoubleValue       DoubleValue;
    DSCharCharValue         CharValue;
    DSCharShortValue        ShortValue;
};

class (DSChar) {
    DSChar*(*Create) (char value);
};


#endif _DSCHAR_H_
