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
#include <dark/types/number.h>

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

#define IsFloat(object) _Generic((object), Float*: true, default: false)
#define AsFloat(object) _Generic((object),                               \
                            Float*: (Float *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
type (Float) 
{
    Class isa;
    float value;
};

method_proto (Float, ToString,        char*, (const Float* const));
method_proto (Float, CompareTo,       int, (const Float* const, const Float* const));
method_proto (Float, IntValue,        int, (const Float* const));
method_proto (Float, LongValue,       long, (const Float* const));
method_proto (Float, FloatValue,      float, (const Float* const));
method_proto (Float, DoubleValue,     double, (const Float* const));
method_proto (Float, CharValue,       char, (const Float* const));
method_proto (Float, ShortValue,      short, (const Float* const));


/**
 * Float vtable with overrides
 */
vtable (Float)
{
    const FloatToString         ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const FloatCompareTo        CompareTo;
    const FloatIntValue         IntValue;
    const FloatLongValue        LongValue;
    const FloatFloatValue       FloatValue;
    const FloatDoubleValue      DoubleValue;
    const FloatCharValue        CharValue;
    const FloatShortValue       ShortValue;
};

class_load( Float );
class_override( ToString,       (FloatToString)ToString, "$@:v" );
class_method( Equals,           (ObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,      (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,          (ObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,      (FloatCompareTo)CompareTo, "i@:@" );
class_override( IntValue,       (FloatIntValue)IntValue, "i@:v" );
class_override( LongValue,      (FloatLongValue)LongValue, "l@:v" );
class_override( FloatValue,     (FloatFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,    (FloatDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,      (FloatCharValue)CharValue, "c@:v" );
class_override( ShortValue,     (FloatShortValue)ShortValue, "s@:v" );
class_member( value,            sizeof( float ), "f" );
class_fini

/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
function Float* Float_init(Float* const this, const float value)
{
    Number_init(this);
    this->isa = objc_getClass("Float");
    this->value = value;
    return this;
}

function Float* NewFloat(const float value) { 
    return Float_init(alloc(Float), value); 
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
 * @return same as Float_Compare
 */
method int CompareTo(const Float* this, const Float* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Float* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Float* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Float* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Float* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Float* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Float* const this) {
    return (short)this->value;
}


overload char* ToString(const Float* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

