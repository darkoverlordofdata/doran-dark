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
IVAR (DSShort) {
    Class isa;
    short value;
};

METHOD (DSShort, ToString,        char*, (const DSShort* const));
METHOD (DSShort, CompareTo,       int, (const DSShort* const, const DSShort* const));
METHOD (DSShort, IntValue,        int, (const DSShort* const));
METHOD (DSShort, LongValue,       long, (const DSShort* const));
METHOD (DSShort, FloatValue,      float, (const DSShort* const));
METHOD (DSShort, DoubleValue,     double, (const DSShort* const));
METHOD (DSShort, CharValue,       char, (const DSShort* const));
METHOD (DSShort, ShortValue,      short, (const DSShort* const));


/**
 * Integer VTABLE with overrides
 */
VTABLE (DSShort)
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
DEF_VPTR(DSShort);
/**
 * Constructor
 * create a new Short
 * 
 * @param value of short
 * 
 */
static inline DSShort* DSShort_init(DSShort* const this, const short value)
{
    DSNumber_init(this);
    this->isa = objc_getClass("DSShort");
    this->value = value;
    return this;
}

static inline DSShort* NewDSShort(const short value) { 
    return DSShort_init(alloc(DSShort), value); 
}

/**
 * Returns a primitive short value parsed from input string. 
 */
static inline short DSParseShort(char const *const s, int const radix)
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
static inline overload int Compare(const short x, const short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as DSShort_Compare
 */
static inline overload int CompareTo(const DSShort* this, const DSShort* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
static inline overload int IntValue(const DSShort* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
static inline overload long LongValue(const DSShort* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
static inline overload float FloatValue(const DSShort* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
static inline overload double DoubleValue(const DSShort* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
static inline overload char CharValue(const DSShort* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
static inline overload short ShortValue(const DSShort* const this) {
    return (short)this->value;
}


static inline overload char* ToString(const DSShort* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}


VTABLE_BIND( DSShort );

VTABLE_OVERRIDE( ToString,         (DSShortToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,             (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,        (DSShortCompareTo)CompareTo, "i@:@" );
VTABLE_OVERRIDE( IntValue,         (DSShortIntValue)IntValue, "i@:v" );
VTABLE_OVERRIDE( LongValue,        (DSShortLongValue)LongValue, "l@:v" );
VTABLE_OVERRIDE( FloatValue,       (DSShortFloatValue)FloatValue, "f@:v" );
VTABLE_OVERRIDE( DoubleValue,      (DSShortDoubleValue)DoubleValue, "d@:v" );
VTABLE_OVERRIDE( CharValue,        (DSShortCharValue)CharValue, "c@:v" );
VTABLE_OVERRIDE( ShortValue,       (DSShortShortValue)ShortValue, "s@:v" );

VTABLE_IVAR( value, sizeof( short ), "s" );

VTABLE_METHODIZE


#endif _DSSHORT_H_
