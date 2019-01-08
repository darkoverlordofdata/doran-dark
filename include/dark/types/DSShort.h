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

#define IsDSShort(x) (x->isa == &$DSShort)
#define AsDSShort(x) (IsDSShort(x) ? (DSShort*)x : nullptr)

/**
 * Object class
 */
ivar (DSShort) {
    Class isa;
    short value;
};

/**
 * Object metaclass
 */
vtable (DSShort) {
    char*   (*ToString) (const DSShort* const);
    bool    (*Equals) (const DSObject* const, DSObject* const);
    int     (*GetHashCode) (const DSObject* const);
    void    (*Dispose) (const DSObject* const);
    int     (*CompareTo) (const DSComparable* const, const DSComparable* const);
    int     (*IntValue) (const DSShort* const);
    long    (*LongValue) (const DSShort* const);
    float   (*FloatValue) (const DSShort* const);
    double  (*DoubleValue) (const DSShort* const);
    char    (*CharValue) (const DSShort* const);
    short   (*ShortValue) (const DSShort* const);

};

class (DSShort) {
    DSShort*  (*Create) (short value);
};

DSShort* NewDSShort(short const value);
DSShort* DSShort_init(DSShort* const this, const short value);
DSShort* DSShort_alloc();
short DSShort_ParseShort(char const *const, const int);
int DSShort_CompareTo(const DSShort* const, const DSShort* const);
int DSShort_IntValue(const DSShort* const);
long DSShort_LongValue(const DSShort* const);
float DSShort_FloatValue(const DSShort* const);
double DSShort_DoubleValue(const DSShort* const);
char DSShort_CharValue(const DSShort* const);
short DSShort_ShortValue(const DSShort* const);
char* DSShort_ToString(const DSShort* const);

#endif _DSSHORT_H_
