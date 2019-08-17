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
#ifndef _DSCHAR_H_
#define _DSCHAR_H_
#include "DSNumber.h"

#define CHAR_MIN_VALUE  CHAR_MIN
#define CHAR_MAX_VALUE  CHAR_MAX
#define CHAR_BYTES      (sizeof(char))
#define CHAR_SIZE       (CHAR_BYTES * CHAR_BIT)
#define CHAR_TYPE       (TYPE_CHAR)

#define IsDSChar(object) _Generic((object), DSChar*: true, default: false)
#define AsDSChar(object) _Generic((object),                             \
                            DSChar*: (DSChar *)object,                  \
                            default: nullptr)

/**
 * Char instance variables
 */
type (DSChar) {
    Class isa;
    char value;
};

method_proto (DSChar, ToString,        char*, (const DSChar* const));
method_proto (DSChar, CompareTo,       int, (const DSChar* const, const DSChar* const));
method_proto (DSChar, IntValue,        int, (const DSChar* const));
method_proto (DSChar, LongValue,       long, (const DSChar* const));
method_proto (DSChar, FloatValue,      float, (const DSChar* const));
method_proto (DSChar, DoubleValue,     double, (const DSChar* const));
method_proto (DSChar, CharValue,       char, (const DSChar* const));
method_proto (DSChar, ShortValue,      short, (const DSChar* const));

/**
 * Char vtable with overrides
 */
vtable (DSChar)
{
    const DSCharToString          ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSCharCompareTo         CompareTo;
    const DSCharIntValue          IntValue;
    const DSCharLongValue         LongValue;
    const DSCharFloatValue        FloatValue;
    const DSCharDoubleValue       DoubleValue;
    const DSCharCharValue         CharValue;
    const DSCharShortValue        ShortValue;
};
class_bind( DSChar );
class_override( ToString,         (DSCharToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSCharCompareTo)CompareTo, "i@:@" );
class_override( IntValue,         (DSCharIntValue)IntValue, "i@:v" );
class_override( LongValue,        (DSCharLongValue)LongValue, "l@:v" );
class_override( FloatValue,       (DSCharFloatValue)FloatValue, "f@:v" );
class_override( DoubleValue,      (DSCharDoubleValue)DoubleValue, "d@:v" );
class_override( CharValue,        (DSCharCharValue)CharValue, "c@:v" );
class_override( ShortValue,       (DSCharShortValue)ShortValue, "s@:v" );

class_member( value, sizeof( char ), "c" );

class_methodize;



/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
function DSChar* DSChar_init(DSChar* const this, const char value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSChar");
    this->value = value;
    return this;
}

function DSChar* NewDSChar(const char value) { 
    return DSChar_init(alloc(DSChar), value); 
}

/**
 * Compare two char primitives.
 * @param  x char to compare
 * @param  y char to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const char x, const char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as DSChar_Compare
 */
method int CompareTo(const DSChar* const this, const DSChar* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSChar* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSChar* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSChar* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSChar* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSChar* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSChar* const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
method char* ToString(const DSChar* const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}

#endif _DSCHAR_H_
