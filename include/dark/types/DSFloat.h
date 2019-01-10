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

#define IsDSFloat(object) _Generic((object), DSFloat*: true, default: false)
#define AsDSFloat(object) _Generic((object),                               \
                            DSFloat*: (DSFloat *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
ivar (DSFloat) 
{
    Class isa;
    float value;
};

DSFloat* NewDSFloat(float const value);
DSFloat* DSFloat_init(DSFloat* const this, const float value);
DSFloat* DSFloat_alloc();

char*   overload ToString(const DSFloat* const);
int     overload CompareTo(const DSFloat* const, const DSFloat* const);
int     overload IntValue(const DSFloat* const);
long    overload LongValue(const DSFloat* const);
float   overload FloatValue(const DSFloat* const);
double  overload DoubleValue(const DSFloat* const);
char    overload CharValue(const DSFloat* const);
short   overload ShortValue(const DSFloat* const);

typedef char*   (*DSFloatToString)       (const DSFloat* const);
typedef int     (*DSFloatCompareTo)      (const DSFloat* const, const DSFloat* const);
typedef int     (*DSFloatIntValue)       (const DSFloat* const);
typedef long    (*DSFloatLongValue)      (const DSFloat* const);
typedef float   (*DSFloatFloatValue)     (const DSFloat* const);
typedef double  (*DSFloatDoubleValue)    (const DSFloat* const);
typedef char    (*DSFloatCharValue)      (const DSFloat* const);
typedef short   (*DSFloatShortValue)     (const DSFloat* const);

/**
 * Float vtable with overrides
 */
vtable (DSFloat)
{
    DSFloatToString             ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    DSFloatCompareTo            CompareTo;
    DSFloatIntValue             IntValue;
    DSFloatLongValue            LongValue;
    DSFloatFloatValue           FloatValue;
    DSFloatDoubleValue          DoubleValue;
    DSFloatCharValue            CharValue;
    DSFloatShortValue           ShortValue;
};


class (DSFloat) {
    DSFloat*  (*Create) (float value);
};

#endif _DSFLOAT_H_
