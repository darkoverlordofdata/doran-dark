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

#define IsDSInteger(x) (x->isa == &$DSInteger)
#define AsDSInteger(x) (IsDSInteger(x) ? (DSInteger*)x : nullptr)

/**
 * Object class
 */
ivar (DSInteger) 
{
    Class isa;
    int value;
};

/**
 * Object metaclass
 */
vtable (DSInteger) {
    char*   (*ToString)     (const DSInteger* const);
    bool    (*Equals)       (const DSObject* const, DSObject* const);
    int     (*GetHashCode)  (const DSObject* const);
    void    (*Dispose)      (DSObject* const);
    int     (*CompareTo)    (const DSComparable* const, const DSComparable* const);
    int     (*IntValue)     (const DSInteger* const);
    long    (*LongValue)    (const DSInteger* const);
    float   (*FloatValue)   (const DSInteger* const);
    double  (*DoubleValue)  (const DSInteger* const);
    char    (*CharValue)    (const DSInteger* const);
    short   (*ShortValue)   (const DSInteger* const);

};

class (DSInteger) {
    DSInteger*(*Create) (int value);
};

DSInteger* NewDSInteger(const int value);
DSInteger* DSInteger_init(DSInteger* const this, const int value);
DSInteger* DSInteger_alloc();
int DSInteger_ParseInt(const char *const, const int);
int DSInteger_CompareTo(const DSInteger* const, const DSInteger* const);
int DSInteger_IntValue(const DSInteger* const);
long DSInteger_LongValue(const DSInteger* const);
float DSInteger_FloatValue(const DSInteger* const);
double DSInteger_DoubleValue(const DSInteger* const);
char DSInteger_CharValue(const DSInteger* const);
short DSInteger_ShortValue(const DSInteger* const);
char* DSInteger_ToString(const DSInteger* const);

#endif _DSINTEGER_H_
