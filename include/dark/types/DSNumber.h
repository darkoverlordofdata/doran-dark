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
type (DSNumber) {
    Class isa;
};

method_proto (DSNumber, ToString,        char*, (const DSNumber* const));
method_proto (DSNumber, CompareTo,       int, (const DSNumber* const, const DSNumber* const));
method_proto (DSNumber, IntValue,        int, (const DSNumber* const));
method_proto (DSNumber, LongValue,       long, (const DSNumber* const));
method_proto (DSNumber, FloatValue,      float, (const DSNumber* const));
method_proto (DSNumber, DoubleValue,     double, (const DSNumber* const));
method_proto (DSNumber, CharValue,       char, (const DSNumber* const));
method_proto (DSNumber, ShortValue,      short, (const DSNumber* const));

/**
 * Object metaclass
 */
vtable (DSNumber) {
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

class_load( DSNumber ); 
vtable_virtual( ToString,          (DSNumberToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
vtable_virtual( CompareTo,         (DSNumberCompareTo)CompareTo, "i@:@" );
vtable_virtual( IntValue,          (DSNumberIntValue)IntValue, "i@:v" );
vtable_virtual( LongValue,         (DSNumberLongValue)LongValue, "l@:v" );
vtable_virtual( FloatValue,        (DSNumberFloatValue)FloatValue, "f@:v" );
vtable_virtual( DoubleValue,       (DSNumberDoubleValue)DoubleValue, "d@:v" );
vtable_virtual( CharValue,         (DSNumberCharValue)CharValue, "c@:v" );
vtable_virtual( ShortValue,        (DSNumberShortValue)ShortValue, "s@:v" );
class_fini

/**
 * Abstract class Number
 * Initialize the Number vtable
 * all methods are virtual
 */
function DSNumber* DSNumber_init(DSNumber* const this)
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
method int CompareTo(const DSNumber* this, const DSNumber* const other) {
    return _vptr(DSNumber)->CompareTo(this, other);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const DSNumber* const this) {
    return _vptr(DSNumber)->IntValue(this);
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const DSNumber* const this) {
    return _vptr(DSNumber)->LongValue(this);
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const DSNumber* const this) {
    return _vptr(DSNumber)->FloatValue(this);
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const DSNumber* const this) {
    return _vptr(DSNumber)->DoubleValue(this);
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const DSNumber* const this) {
    return _vptr(DSNumber)->CharValue(this);
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const DSNumber* const this) {
    return _vptr(DSNumber)->ShortValue(this);
}

method char* ToString(const DSNumber* const this) {
    return _vptr(DSNumber)->ToString(this);
}


#endif _DSNUMBER_H_
