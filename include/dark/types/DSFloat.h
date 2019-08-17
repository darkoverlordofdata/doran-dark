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
IVAR (DSFloat) 
{
    Class isa;
    float value;
};

METHOD (DSFloat, ToString,        char*, (const DSFloat* const));
METHOD (DSFloat, CompareTo,       int, (const DSFloat* const, const DSFloat* const));
METHOD (DSFloat, IntValue,        int, (const DSFloat* const));
METHOD (DSFloat, LongValue,       long, (const DSFloat* const));
METHOD (DSFloat, FloatValue,      float, (const DSFloat* const));
METHOD (DSFloat, DoubleValue,     double, (const DSFloat* const));
METHOD (DSFloat, CharValue,       char, (const DSFloat* const));
METHOD (DSFloat, ShortValue,      short, (const DSFloat* const));


/**
 * Float VTABLE with overrides
 */
VTABLE (DSFloat)
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
DEF_VPTR(DSFloat);
/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
static inline DSFloat* DSFloat_init(DSFloat* const this, const float value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSFloat");
    this->value = value;
    return this;
}

static inline DSFloat* NewDSFloat(const float value) { 
    return DSFloat_init(alloc(DSFloat), value); 
}

/**
 * Returns a primitive float value parsed from input string. 
 */
static inline float DSParseFloat(const char* s)
{
    
    double d = DSParseDouble(s);
    if (d < FLOAT_MIN_VALUE || d > FLOAT_MAX_VALUE)
        throw DSNumberFormatException(s, Source);
    return (float)d;
}

/**
 * Compare two float primitives.
 * @param  x float to compare
 * @param  y float to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
static inline overload int Compare(const float x, const float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as DSFloat_Compare
 */
static inline overload int CompareTo(const DSFloat* this, const DSFloat* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
static inline overload int IntValue(const DSFloat* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
static inline overload long LongValue(const DSFloat* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
static inline overload double DoubleValue(const DSFloat* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
static inline overload float FloatValue(const DSFloat* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
static inline overload char CharValue(const DSFloat* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
static inline overload short ShortValue(const DSFloat* const this) {
    return (short)this->value;
}


overload char* ToString(const DSFloat* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

VTABLE_BIND( DSFloat );

VTABLE_OVERRIDE( ToString,         (DSFloatToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,             (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,        (DSFloatCompareTo)CompareTo, "i@:@" );
VTABLE_OVERRIDE( IntValue,         (DSFloatIntValue)IntValue, "i@:v" );
VTABLE_OVERRIDE( LongValue,        (DSFloatLongValue)LongValue, "l@:v" );
VTABLE_OVERRIDE( FloatValue,       (DSFloatFloatValue)FloatValue, "f@:v" );
VTABLE_OVERRIDE( DoubleValue,      (DSFloatDoubleValue)DoubleValue, "d@:v" );
VTABLE_OVERRIDE( CharValue,        (DSFloatCharValue)CharValue, "c@:v" );
VTABLE_OVERRIDE( ShortValue,       (DSFloatShortValue)ShortValue, "s@:v" );

VTABLE_IVAR( value, sizeof( float ), "f" );

VTABLE_METHODIZE


#endif _DSFLOAT_H_
