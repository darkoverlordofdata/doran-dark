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
#include <limits.h>
#include <float.h>
#include <math.h>
#include <dark/core/object.h>
#include <dark/core/comparable.h>

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

#define IsNumber(object) _Generic((object), Number*: true, default: false)
#define AsNumber(object) _Generic((object),                           \
                            Number*: (Number *)object,              \
                            default: nullptr)


/**
 * Object class
 */
type (Number) {
    Class isa;
};

interface (Number, ToString,        char*, (const Number* const));
interface (Number, CompareTo,       int, (const Number* const, const Number* const));
interface (Number, IntValue,        int, (const Number* const));
interface (Number, LongValue,       long, (const Number* const));
interface (Number, FloatValue,      float, (const Number* const));
interface (Number, DoubleValue,     double, (const Number* const));
interface (Number, CharValue,       char, (const Number* const));
interface (Number, ShortValue,      short, (const Number* const));

/**
 * Object metaclass
 */
vtable (Number) {
    const NumberToString         ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const NumberCompareTo        CompareTo;
    const NumberIntValue         IntValue;
    const NumberLongValue        LongValue;
    const NumberFloatValue       FloatValue;
    const NumberDoubleValue      DoubleValue;
    const NumberCharValue        CharValue;
    const NumberShortValue       ShortValue;
};

class (Number) {
    Number* (*Create) ();
};


function vptr(Number);
/**
 * 
 * Class Loader callback
 */
function objc_loadNumber(Class super) 
{
    Class cls = createClass(super, Number);
    addMethod(cls, NumberToString,      ToString);
    addMethod(cls, ObjectEquals,        Equals);
    addMethod(cls, ObjectGetHashCode,   GetHashCode);
    addMethod(cls, ObjectDispose,       Dispose);
    addMethod(cls, NumberCompareTo,     CompareTo);
    addMethod(cls, NumberIntValue,      IntValue);
    addMethod(cls, NumberLongValue,     LongValue);
    addMethod(cls, NumberFloatValue,    FloatValue);
    addMethod(cls, NumberDoubleValue,   DoubleValue);
    addMethod(cls, NumberCharValue,     CharValue);
    addMethod(cls, NumberShortValue,    ShortValue);

    return cls;
}

/**
 * Abstract class Number
 * Initialize the Number vtable
 * all methods are virtual
 */
function Number* Number_init(Number* const this)
{
    Comparable_init(this);
    this->isa = objc_getClass("Number");
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
method int CompareTo(const Number* this, const Number* const other) {
    return get_vptr(Number)->CompareTo(this, other);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Number* const this) {
    return get_vptr(Number)->IntValue(this);
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Number* const this) {
    return get_vptr(Number)->LongValue(this);
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Number* const this) {
    return get_vptr(Number)->FloatValue(this);
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Number* const this) {
    return get_vptr(Number)->DoubleValue(this);
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Number* const this) {
    return get_vptr(Number)->CharValue(this);
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Number* const this) {
    return get_vptr(Number)->ShortValue(this);
}

method char* ToString(const Number* const this) {
    return get_vptr(Number)->ToString(this);
}
