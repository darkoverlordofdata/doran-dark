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

#define IsDSInteger(object) _Generic((object), DSInteger*: true, default: false)
#define AsDSInteger(object) _Generic((object),                          \
                            DSInteger*: (DSInteger *)object,            \
                            default: nullptr)

/**
 * Object class
 */
type (DSInteger) 
{
    Class isa;
    int value;
};


method_proto (DSInteger, ToString,        char*, (const DSInteger* const));
method_proto (DSInteger, CompareTo,       int, (const DSInteger* const, const DSInteger* const));
method_proto (DSInteger, IntValue,        int, (const DSInteger* const));
method_proto (DSInteger, LongValue,       long, (const DSInteger* const));
method_proto (DSInteger, FloatValue,      float, (const DSInteger* const));
method_proto (DSInteger, DoubleValue,     double, (const DSInteger* const));
method_proto (DSInteger, CharValue,       char, (const DSInteger* const));
method_proto (DSInteger, ShortValue,      short, (const DSInteger* const));

/**
 * Integer vtable with overrides
 */
vtable (DSInteger)
{
    const DSIntegerToString           ToString;
    const DSObjectEquals              Equals;
    const DSObjectGetHashCode         GetHashCode;
    const DSObjectDispose             Dispose;
    const DSIntegerCompareTo          CompareTo;
    const DSIntegerIntValue           IntValue;
    const DSIntegerLongValue          LongValue;
    const DSIntegerFloatValue         FloatValue;
    const DSIntegerDoubleValue        DoubleValue;
    const DSIntegerCharValue          CharValue;
    const DSIntegerShortValue         ShortValue;
};

class_load( DSInteger );
class_override( ToString,         (DSIntegerToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSIntegerCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSIntegerIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSIntegerLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSIntegerFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSIntegerDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSIntegerCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSIntegerShortValue)ShortValue, "s@:v" );
class_member( value, sizeof( int ), "i" );
class_fini

/* 
 * Constructor
 * create a new Integer
 * 
 * @param value of int
 * 
 */
function DSInteger* DSInteger_init(DSInteger* const this, const int value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSInteger");
    this->value = value;
    return this;
}

function DSInteger* NewDSInteger(const int value) { 
    return DSInteger_init(alloc(DSInteger), value); 
}

/**
 * Returns a primitive integer value parsed from input string. 
 */
function int DSParseInt(const char* const s, const int radix) {
    long i = DSParseLong(s, radix);
    if (i < INTEGER_MIN_VALUE || i > INTEGER_MAX_VALUE)
        throw DSNumberFormatException(s, radix, Source);
    return (int)i;
}

/**
 * Compare two int primitives.
 * @param  x int to compare
 * @param  y int to compare
 * @return  0 x == y
 *        +1 x < y
 *        -1 x > y
 */
method int Compare(const int x, const int y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Integer objects.
 *
 * @param   other  Integer to be compared
 * @return same as DSInteger_Compare
 */
method int CompareTo(const DSInteger* this, const DSInteger* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSInteger* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSInteger* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSInteger* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSInteger* const this) {
    return (short)this->value;
}


method char* ToString(const DSInteger* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}


#endif _DSINTEGER_H_
