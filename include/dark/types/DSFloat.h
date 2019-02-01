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

method (DSFloat, ToString,        char*, (const DSFloat* const));
method (DSFloat, CompareTo,       int, (const DSFloat* const, const DSFloat* const));
method (DSFloat, IntValue,        int, (const DSFloat* const));
method (DSFloat, LongValue,       long, (const DSFloat* const));
method (DSFloat, FloatValue,      float, (const DSFloat* const));
method (DSFloat, DoubleValue,     double, (const DSFloat* const));
method (DSFloat, CharValue,       char, (const DSFloat* const));
method (DSFloat, ShortValue,      short, (const DSFloat* const));


/**
 * Float vtable with overrides
 */
vtable (DSFloat)
{
    const DSFloatToString             ToString;
    const DSObjectEquals              Equals;
    const DSObjectGetHashCode         GetHashCode;
    const DSObjectDispose             Dispose;
    const DSFloatCompareTo            CompareTo;
    const DSFloatIntValue             IntValue;
    const DSFloatLongValue            LongValue;
    const DSFloatFloatValue           FloatValue;
    const DSFloatDoubleValue          DoubleValue;
    const DSFloatCharValue            CharValue;
    const DSFloatShortValue           ShortValue;
};

#endif _DSFLOAT_H_
