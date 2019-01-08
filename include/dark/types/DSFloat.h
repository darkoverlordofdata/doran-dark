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
#ifndef _DSFLOAT_H_
#define _DSFLOAT_H_
#include "DSNumber.h"

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

#define IsDSFloat(x) (x->isa == &DSFloatClass)
#define AsDSFloat(x) (IsDSFloat(x) ? (DSFloat*)x : nullptr)

/**
 * Object class
 */
ivar (DSFloat) 
{
    Class isa;
    float value;
};

/**
 * Object metaclass
 */
vtable (DSFloat)
{
    char*   (*ToString)     (const DSFloat* const);
    bool    (*Equals)       (const DSObject* const, DSObject* const);
    int     (*GetHashCode)  (const DSObject* const);
    void    (*Dispose)      (DSObject* const);
    int     (*CompareTo)    (const DSComparable* const, const DSComparable* const);
    int     (*IntValue)     (const DSFloat* const);
    long    (*LongValue)    (const DSFloat* const);
    float   (*FloatValue)   (const DSFloat* const);
    double  (*DoubleValue)  (const DSFloat* const);
    char    (*CharValue)    (const DSFloat* const);
    short   (*ShortValue)   (const DSFloat* const);

};

class (DSFloat) {
    DSFloat*  (*Create) (float value);
};

DSFloat* NewDSFloat(const float value);
DSFloat* DSFloat_init(DSFloat* const this, const float value);
DSFloat* DSFloat_alloc();
int DSFloat_CompareTo(const DSFloat* const, const DSFloat* const);
int DSFloat_IntValue(const DSFloat* const);
long DSFloat_LongValue(const DSFloat* const);
float DSFloat_FloatValue(const DSFloat* const);
double DSFloat_DoubleValue(const DSFloat* const);
char DSFloat_CharValue(const DSFloat* const);
short DSFloat_ShortValue(const DSFloat* const);
char* DSFloat_ToString(const DSFloat* const);
#endif _DSFLOAT_H_
