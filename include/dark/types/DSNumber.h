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
#ifndef _DSNUMBER_H_
#define _DSNUMBER_H_
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../DSObject.h"
#include "../DSComparable.h"

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

#define IsDSNumber(object) _Generic((object), DSNumber*: true, default: false)
#define AsDSNumber(object) _Generic((object),                           \
                            DSNumber*: (DSNumber *)object,              \
                            default: nullptr)


/**
 * Object class
 */
IVAR (DSNumber) {
    Class isa;
};

METHOD (DSNumber, ToString,        char*, (const DSNumber* const));
METHOD (DSNumber, CompareTo,       int, (const DSNumber* const, const DSNumber* const));
METHOD (DSNumber, IntValue,        int, (const DSNumber* const));
METHOD (DSNumber, LongValue,       long, (const DSNumber* const));
METHOD (DSNumber, FloatValue,      float, (const DSNumber* const));
METHOD (DSNumber, DoubleValue,     double, (const DSNumber* const));
METHOD (DSNumber, CharValue,       char, (const DSNumber* const));
METHOD (DSNumber, ShortValue,      short, (const DSNumber* const));

/**
 * Object metaclass
 */
VTABLE (DSNumber) {
    const DSNumberToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSNumberCompareTo        CompareTo;
    const DSNumberIntValue         IntValue;
    const DSNumberLongValue        LongValue;
    const DSNumberFloatValue       FloatValue;
    const DSNumberDoubleValue      DoubleValue;
    const DSNumberCharValue        CharValue;
    const DSNumberShortValue       ShortValue;
};

class (DSNumber) {
    DSNumber* (*Create) ();
};

DEF_VPTR(DSNumber);
/**
 * Abstract class Number
 * Initialize the Number vtable
 * all methods are virtual
 */
static inline DSNumber* DSNumber_init(DSNumber* const this)
{
    DSComparable_init(this);
    this->isa = objc_getClass("DSNumber");
    return this;
}

/**
 * Compares two Number objects.
 *
 * @param   other  Short to be compared
 * @return  0 this == other
 *         +1 this < other
 *         -1 this > other
 */
static inline overload int CompareTo(const DSNumber* this, const DSNumber* const other) {
    return getVptr(DSNumber)->CompareTo(this, other);
}

/**
 * Returns the value of this value cast as an int
 */
static inline overload int IntValue(const DSNumber* const this) {
    return getVptr(DSNumber)->IntValue(this);
}

/**
 * Returns the value of this value cast as a long
 */
static inline overload long LongValue(const DSNumber* const this) {
    return getVptr(DSNumber)->LongValue(this);
}

/**
 * Returns the value of this value cast as a float
 */
static inline overload float FloatValue(const DSNumber* const this) {
    return getVptr(DSNumber)->FloatValue(this);
}

/**
 * Returns the value of this value cast as a double
 */
static inline overload double DoubleValue(const DSNumber* const this) {
    return getVptr(DSNumber)->DoubleValue(this);
}

/**
 * Returns the value of this value cast as a char
 */
static inline overload char CharValue(const DSNumber* const this) {
    return getVptr(DSNumber)->CharValue(this);
}

/**
 * Returns the value of this value cast as a short
 */
static inline overload short ShortValue(const DSNumber* const this) {
    return getVptr(DSNumber)->ShortValue(this);
}

static inline overload char* ToString(const DSNumber* const this) {
    return getVptr(DSNumber)->ToString(this);
}





VTABLE_BIND( DSNumber ); 

VTABLE_VIRTUAL( ToString,          (DSNumberToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,             (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_VIRTUAL( CompareTo,         (DSNumberCompareTo)CompareTo, "i@:@" );
VTABLE_VIRTUAL( IntValue,          (DSNumberIntValue)IntValue, "i@:v" );
VTABLE_VIRTUAL( LongValue,         (DSNumberLongValue)LongValue, "l@:v" );
VTABLE_VIRTUAL( FloatValue,        (DSNumberFloatValue)FloatValue, "f@:v" );
VTABLE_VIRTUAL( DoubleValue,       (DSNumberDoubleValue)DoubleValue, "d@:v" );
VTABLE_VIRTUAL( CharValue,         (DSNumberCharValue)CharValue, "c@:v" );
VTABLE_VIRTUAL( ShortValue,        (DSNumberShortValue)ShortValue, "s@:v" );

VTABLE_METHODIZE


#endif _DSNUMBER_H_
