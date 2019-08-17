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
type (DSFloat) 
{
    Class isa;
    float value;
};

method_proto (DSFloat, ToString,        char*, (const DSFloat* const));
method_proto (DSFloat, CompareTo,       int, (const DSFloat* const, const DSFloat* const));
method_proto (DSFloat, IntValue,        int, (const DSFloat* const));
method_proto (DSFloat, LongValue,       long, (const DSFloat* const));
method_proto (DSFloat, FloatValue,      float, (const DSFloat* const));
method_proto (DSFloat, DoubleValue,     double, (const DSFloat* const));
method_proto (DSFloat, CharValue,       char, (const DSFloat* const));
method_proto (DSFloat, ShortValue,      short, (const DSFloat* const));


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

class_load( DSFloat );
class_override( ToString,         (DSFloatToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSFloatCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSFloatIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSFloatLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSFloatFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSFloatDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSFloatCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSFloatShortValue)ShortValue, "s@:v" );
class_member( value, sizeof( float ), "f" );
class_fini

/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
function DSFloat* DSFloat_init(DSFloat* const this, const float value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSFloat");
    this->value = value;
    return this;
}

function DSFloat* NewDSFloat(const float value) { 
    return DSFloat_init(alloc(DSFloat), value); 
}

/**
 * Returns a primitive float value parsed from input string. 
 */
function float DSParseFloat(const char* s)
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
method int Compare(const float x, const float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as DSFloat_Compare
 */
method int CompareTo(const DSFloat* this, const DSFloat* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSFloat* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSFloat* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSFloat* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSFloat* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSFloat* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSFloat* const this) {
    return (short)this->value;
}


overload char* ToString(const DSFloat* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}


#endif _DSFLOAT_H_
