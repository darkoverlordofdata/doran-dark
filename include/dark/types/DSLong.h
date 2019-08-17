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
#ifndef _DSLONG_H_
#define _DSLONG_H_
#include "DSNumber.h"

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

#define IsDSLong(object) _Generic((object), DSLong*: true, default: false)
#define AsDSLong(object) _Generic((object),                             \
                            DSLong*: (DSLong *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
type (DSLong) 
{
    Class isa;
    long value;
};

def_method (DSLong, ToString,        char*, (const DSLong* const));
def_method (DSLong, CompareTo,       int, (const DSLong* const, const DSLong* const));
def_method (DSLong, IntValue,        int, (const DSLong* const));
def_method (DSLong, LongValue,       long, (const DSLong* const));
def_method (DSLong, FloatValue,      float, (const DSLong* const));
def_method (DSLong, DoubleValue,     double, (const DSLong* const));
def_method (DSLong, CharValue,       char, (const DSLong* const));
def_method (DSLong, ShortValue,      short, (const DSLong* const));


/**
 * Integer vtable with overrides
 */
vtable (DSLong)
{
    const DSLongToString           ToString;
    const DSObjectEquals           Equals;
    const DSObjectGetHashCode      GetHashCode;
    const DSObjectDispose          Dispose;
    const DSLongCompareTo          CompareTo;
    const DSLongIntValue           IntValue;
    const DSLongLongValue          LongValue;
    const DSLongFloatValue         FloatValue;
    const DSLongDoubleValue        DoubleValue;
    const DSLongCharValue          CharValue;
    const DSLongShortValue         ShortValue;
};
vtable_ptr(DSLong);
/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
proc DSLong* DSLong_init(DSLong* const this, const long value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSLong");
    this->value = value;
    return this;
}

proc DSLong* NewDSLong(const long value) { 
    return DSLong_init(alloc(DSLong), value); 
}

/**
 * Returns a primitive long value parsed from input string. 
 */
proc long DSParseLong(const char* const s, const int radix)
{
    errno = 0;
    char* endptr;
    long result = strtol(s, &endptr, radix);

    if (errno != 0)
        throw DSNumberFormatException(s, radix, Source);

    if (s == endptr || *endptr != '\0')
        throw DSNumberFormatException(s, radix, Source);

    return result;
}

/**
 * Compare two long primitives.
 * @param  x long to compare
 * @param  y long to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const long x, const long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Long objects.
 *
 * @param   other  Long to be compared
 * @return same as DSLong_Compare
 */
method int CompareTo(const DSLong* const this, const DSLong* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSLong* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSLong* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSLong* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSLong* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSLong* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSLong* const this) {
    return (short)this->value;
}

method bool Equals(const DSLong* const this, const DSLong* const other)
{
    return this->value == other->value;
}

method char* ToString(const DSLong* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

class_bind( DSLong );

class_override( ToString,         (DSLongToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSLongCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSLongIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSLongLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSLongFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSLongDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSLongCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSLongShortValue)ShortValue, "s@:v" );

class_member( value, sizeof( long ), "l" );

class_methodize


#endif _DSLONG_H_
