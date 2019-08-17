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
IVAR (DSChar) {
    Class isa;
    char value;
};

METHOD (DSChar, ToString,        char*, (const DSChar* const));
METHOD (DSChar, CompareTo,       int, (const DSChar* const, const DSChar* const));
METHOD (DSChar, IntValue,        int, (const DSChar* const));
METHOD (DSChar, LongValue,       long, (const DSChar* const));
METHOD (DSChar, FloatValue,      float, (const DSChar* const));
METHOD (DSChar, DoubleValue,     double, (const DSChar* const));
METHOD (DSChar, CharValue,       char, (const DSChar* const));
METHOD (DSChar, ShortValue,      short, (const DSChar* const));

/**
 * Char VTABLE with overrides
 */
VTABLE (DSChar)
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
DEF_VPTR(DSChar);

/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
static inline DSChar* DSChar_init(DSChar* const this, const char value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSChar");
    this->value = value;
    return this;
}

static inline DSChar* NewDSChar(const char value) { 
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
static inline overload int Compare(const char x, const char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as DSChar_Compare
 */
static inline overload int CompareTo(const DSChar* const this, const DSChar* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
static inline overload int IntValue(const DSChar* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
static inline overload long LongValue(const DSChar* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
static inline overload float FloatValue(const DSChar* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
static inline overload double DoubleValue(const DSChar* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
static inline overload char CharValue(const DSChar* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
static inline overload short ShortValue(const DSChar* const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
static inline overload char* ToString(const DSChar* const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}



VTABLE_BIND( DSChar );
VTABLE_OVERRIDE( ToString,         (DSCharToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,             (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,        (DSCharCompareTo)CompareTo, "i@:@" );
VTABLE_OVERRIDE( IntValue,         (DSCharIntValue)IntValue, "i@:v" );
VTABLE_OVERRIDE( LongValue,        (DSCharLongValue)LongValue, "l@:v" );
VTABLE_OVERRIDE( FloatValue,       (DSCharFloatValue)FloatValue, "f@:v" );
VTABLE_OVERRIDE( DoubleValue,      (DSCharDoubleValue)DoubleValue, "d@:v" );
VTABLE_OVERRIDE( CharValue,        (DSCharCharValue)CharValue, "c@:v" );
VTABLE_OVERRIDE( ShortValue,       (DSCharShortValue)ShortValue, "s@:v" );

VTABLE_IVAR( value, sizeof( char ), "c" );

VTABLE_METHODIZE


#endif _DSCHAR_H_
