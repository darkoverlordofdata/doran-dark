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

#define IsDSDouble(x) (x->isa == &$DSDouble)
#define AsDSDouble(x) (IsDSDouble(x) ? (DSDouble*)x : nullptr)

/**
 * Double class
 */
Ivar (DSDouble) 
{
    Class isa;
    double value;
};

/**
 * Double metaclass
 */
VTable (DSDouble) {
    char*   (*ToString) (DSDouble* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    // bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    // bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSDouble* const);
    long    (*LongValue) (DSDouble* const);
    float   (*FloatValue) (DSDouble* const);
    double  (*DoubleValue) (DSDouble* const);
    char    (*CharValue) (DSDouble* const);
    short   (*ShortValue) (DSDouble* const);

};

Singleton ($DSDouble) {
    DSDouble* (*Create) (double value);
};


int DSDouble_CompareTo(DSDouble* const, DSDouble* const);
int DSDouble_IntValue(DSDouble* const);
long DSDouble_LongValue(DSDouble* const);
float DSDouble_FloatValue(DSDouble* const);
double DSDouble_DoubleValue(DSDouble* const);
char DSDouble_CharValue(DSDouble* const);
short DSDouble_ShortValue(DSDouble* const);
char* DSDouble_ToString(const DSDouble* const);
DSDouble* DSDouble_init(DSDouble* const this, double value);
DSDouble* DSDouble_alloc();
DSDouble* NewDSDouble(double value);

#endif _DSDOUBLE_H_
