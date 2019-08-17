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
IVAR (DSInteger) 
{
    Class isa;
    int value;
};


METHOD (DSInteger, ToString,        char*, (const DSInteger* const));
METHOD (DSInteger, CompareTo,       int, (const DSInteger* const, const DSInteger* const));
METHOD (DSInteger, IntValue,        int, (const DSInteger* const));
METHOD (DSInteger, LongValue,       long, (const DSInteger* const));
METHOD (DSInteger, FloatValue,      float, (const DSInteger* const));
METHOD (DSInteger, DoubleValue,     double, (const DSInteger* const));
METHOD (DSInteger, CharValue,       char, (const DSInteger* const));
METHOD (DSInteger, ShortValue,      short, (const DSInteger* const));

/**
 * Integer VTABLE with overrides
 */
VTABLE (DSInteger)
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
DEF_VPTR(DSInteger);
/* 
 * Constructor
 * create a new Integer
 * 
 * @param value of int
 * 
 */
static inline DSInteger* DSInteger_init(DSInteger* const this, const int value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSInteger");
    this->value = value;
    return this;
}

static inline DSInteger* NewDSInteger(const int value) { 
    return DSInteger_init(alloc(DSInteger), value); 
}

/**
 * Returns a primitive integer value parsed from input string. 
 */
static inline int DSParseInt(const char* const s, const int radix) {
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
static inline overload int Compare(const int x, const int y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Integer objects.
 *
 * @param   other  Integer to be compared
 * @return same as DSInteger_Compare
 */
static inline overload int CompareTo(const DSInteger* this, const DSInteger* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
static inline overload int IntValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
static inline overload long LongValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
static inline overload float FloatValue(const DSInteger* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
static inline overload double DoubleValue(const DSInteger* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
static inline overload char CharValue(const DSInteger* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
static inline overload short ShortValue(const DSInteger* const this) {
    return (short)this->value;
}


static inline overload char* ToString(const DSInteger* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

VTABLE_BIND( DSInteger );

VTABLE_OVERRIDE( ToString,         (DSIntegerToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,             (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,        (DSIntegerCompareTo)CompareTo, "i@:@" );
VTABLE_OVERRIDE( IntValue,         (DSIntegerIntValue)IntValue, "i@:v" );
VTABLE_OVERRIDE( LongValue,        (DSIntegerLongValue)LongValue, "l@:v" );
VTABLE_OVERRIDE( FloatValue,       (DSIntegerFloatValue)FloatValue, "f@:v" );
VTABLE_OVERRIDE( DoubleValue,      (DSIntegerDoubleValue)DoubleValue, "d@:v" );
VTABLE_OVERRIDE( CharValue,        (DSIntegerCharValue)CharValue, "c@:v" );
VTABLE_OVERRIDE( ShortValue,       (DSIntegerShortValue)ShortValue, "s@:v" );

VTABLE_IVAR( value, sizeof( int ), "i" );

VTABLE_METHODIZE


#endif _DSINTEGER_H_
