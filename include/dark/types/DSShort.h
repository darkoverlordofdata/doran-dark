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
#ifndef _DSSHORT_H_
#define _DSSHORT_H_
#include "DSNumber.h"

#define SHORT_MIN_VALUE  SHRT_MIN
#define SHORT_MAX_VALUE  SHRT_MAX
#define SHORT_BYTES      (sizeof(short))
#define SHORT_SIZE       (SHORT_BYTES * CHAR_BIT)
#define SHORT_TYPE       (TYPE_SHORT)

#define IsDSShort(object) _Generic((object), DSShort*: true, default: false)
#define AsDSShort(object) _Generic((object),                            \
                            DSShort*: (DSShort *)object,                \
                            default: nullptr)

/**
 * Object class
 */
type (DSShort) {
    Class isa;
    short value;
};

method_proto (DSShort, ToString,        char*, (const DSShort* const));
method_proto (DSShort, CompareTo,       int, (const DSShort* const, const DSShort* const));
method_proto (DSShort, IntValue,        int, (const DSShort* const));
method_proto (DSShort, LongValue,       long, (const DSShort* const));
method_proto (DSShort, FloatValue,      float, (const DSShort* const));
method_proto (DSShort, DoubleValue,     double, (const DSShort* const));
method_proto (DSShort, CharValue,       char, (const DSShort* const));
method_proto (DSShort, ShortValue,      short, (const DSShort* const));


/**
 * Integer vtable with overrides
 */
vtable (DSShort)
{
    const DSShortToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSShortCompareTo        CompareTo;
    const DSShortIntValue         IntValue;
    const DSShortLongValue        LongValue;
    const DSShortFloatValue       FloatValue;
    const DSShortDoubleValue      DoubleValue;
    const DSShortCharValue        CharValue;
    const DSShortShortValue       ShortValue;
};

class_load( DSShort );
class_override( ToString,         (DSShortToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSShortCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSShortIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSShortLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSShortFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSShortDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSShortCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSShortShortValue)ShortValue, "s@:v" );
class_member( value, sizeof( short ), "s" );
class_fini

/**
 * Constructor
 * create a new Short
 * 
 * @param value of short
 * 
 */
function DSShort* DSShort_init(DSShort* const this, const short value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSShort");
    this->value = value;
    return this;
}

function DSShort* NewDSShort(const short value) { 
    return DSShort_init(alloc(DSShort), value); 
}

/**
 * Returns a primitive short value parsed from input string. 
 */
function short DSParseShort(char const *const s, int const radix)
{
    long i = DSParseLong(s, radix);
    if (i < SHORT_MIN_VALUE || i > SHORT_MAX_VALUE)
        throw DSNumberFormatException(s, radix, Source);
    return (short)i;
}

/**
 * Compare two long primitives.
 * @param  x long to compare
 * @param  y long to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const short x, const short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as DSShort_Compare
 */
method int CompareTo(const DSShort* this, const DSShort* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSShort* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSShort* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSShort* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSShort* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSShort* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSShort* const this) {
    return (short)this->value;
}


method char* ToString(const DSShort* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}


#endif _DSSHORT_H_
