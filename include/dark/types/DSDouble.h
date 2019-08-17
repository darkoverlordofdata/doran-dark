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

#define IsDSDouble(object) _Generic((object), DSDouble*: true, default: false)
#define AsDSDouble(object) _Generic((object),                          \
                            DSDouble*: (DSDouble *)object,             \
                            default: nullptr)

/**
 * Double instance variables
 */
type (DSDouble) 
{
    Class isa;
    double value;
};

def_method (DSDouble, ToString,        char*,    (const DSDouble* const));
def_method (DSDouble, CompareTo,       int,      (const DSDouble* const, const DSDouble* const));
def_method (DSDouble, IntValue,        int,      (const DSDouble* const));
def_method (DSDouble, LongValue,       long,     (const DSDouble* const));
def_method (DSDouble, FloatValue,      float,    (const DSDouble* const));
def_method (DSDouble, DoubleValue,     double,   (const DSDouble* const));
def_method (DSDouble, CharValue,       char,     (const DSDouble* const));
def_method (DSDouble, ShortValue,      short,    (const DSDouble* const));

/**
 * Double vtable with overrides
 */
vtable (DSDouble)
{
    const DSDoubleToString            ToString;
    const DSObjectEquals              Equals;
    const DSObjectGetHashCode         GetHashCode;
    const DSObjectDispose             Dispose;
    const DSDoubleCompareTo           CompareTo;
    const DSDoubleIntValue            IntValue;
    const DSDoubleLongValue           LongValue;
    const DSDoubleFloatValue          FloatValue;
    const DSDoubleDoubleValue         DoubleValue;
    const DSDoubleCharValue           CharValue;
    const DSDoubleShortValue          ShortValue;
};
vtable_ptr(DSDouble);
/**
 * Constructor
 * create a new DSDouble
 * 
 * @param value of double
 * 
 */
proc DSDouble* DSDouble_init(DSDouble* const this, const double value) {
    DSNumber_init(this);
    this->isa = objc_getClass("DSDouble");
    this->value = value;
    return this;
}

proc DSDouble* NewDSDouble(const double value) { 
    return DSDouble_init(alloc(DSDouble), value); 
}

/**
 * Returns a primitive double value parsed from input string. 
 */
proc double DSParseDouble(char const *const s) {
    errno = 0;
    char* endptr;
    double result = strtod(s, endptr);

    if (errno != 0)
        throw DSNumberFormatException(s, Source);

    if (s == endptr || *endptr != '\0')
        throw DSNumberFormatException(s, Source);

    return result;
}

/**
 * Compare two double primitives.
 * @param  x double to compare
 * @param  y double to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const double x, const double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two DSDouble objects.
 *
 * @param   other  DSDouble to be compared
 * @return same as DSDouble_Compare
 */
method int CompareTo(const DSDouble* const this, const DSDouble* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSDouble* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSDouble* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSDouble* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSDouble* const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSDouble* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSDouble* const this) {
    return (short)this->value;
}

method char* ToString(const DSDouble* const this) {
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}


class_bind( DSDouble );

class_override( ToString,         (DSDoubleToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSDoubleCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSDoubleIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSDoubleLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSDoubleFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSDoubleDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSDoubleCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSDoubleShortValue)ShortValue, "s@:v" );

class_member( value, sizeof( double ), "d" );

class_methodize


#endif _DSDOUBLE_H_
