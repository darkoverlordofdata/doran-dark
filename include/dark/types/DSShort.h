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
    char*   (*ToString) (DSShort* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    // bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    // bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSShort* const);
    long    (*LongValue) (DSShort* const);
    float   (*FloatValue) (DSShort* const);
    double  (*DoubleValue) (DSShort* const);
    char    (*CharValue) (DSShort* const);
    short   (*ShortValue) (DSShort* const);

};

class (DSShort) {
    DSShort*  (*Create) (short value);
};

short DSShort_ParseShort(char const *const s, int);
int DSShort_CompareTo(DSShort* const, DSShort* const);
int DSShort_IntValue(DSShort* const);
long DSShort_LongValue(DSShort* const);
float DSShort_FloatValue(DSShort* const);
double DSShort_DoubleValue(DSShort* const);
char DSShort_CharValue(DSShort* const);
short DSShort_ShortValue(DSShort* const);
char* DSShort_ToString(const DSShort* const);
DSShort* DSShort_init(DSShort* const this, short value);
DSShort* DSShort_alloc();
DSShort* NewDSShort(short value);

#endif _DSSHORT_H_
