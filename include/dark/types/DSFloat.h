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
class (DSFloat) 
{
    struct DSFloatClass* isa;
    float value;
};

/**
 * Object metaclass
 */
struct DSFloatClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (DSFloat* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSFloat*  (*Create) (float value);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSFloat* const);
    long    (*LongValue) (DSFloat* const);
    float   (*FloatValue) (DSFloat* const);
    double  (*DoubleValue) (DSFloat* const);
    char    (*CharValue) (DSFloat* const);
    short   (*ShortValue) (DSFloat* const);

} DSFloatClass;


int DSFloat_CompareTo(DSFloat* const, DSFloat* const);
int DSFloat_IntValue(DSFloat* const);
long DSFloat_LongValue(DSFloat* const);
float DSFloat_FloatValue(DSFloat* const);
float DSFloat_FloatValue(DSFloat* const);
char DSFloat_CharValue(DSFloat* const);
short DSFloat_ShortValue(DSFloat* const);

#endif _DSFLOAT_H_
