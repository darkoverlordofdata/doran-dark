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

delegate (Number, New,              Number*, (Number*));
delegate (Number, ToString,        char*, (const Number* const));
delegate (Number, CompareTo,       int, (const Number* const, const Number* const));
delegate (Number, IntValue,        int, (const Number* const));
delegate (Number, LongValue,       long, (const Number* const));
delegate (Number, FloatValue,      float, (const Number* const));
delegate (Number, DoubleValue,     double, (const Number* const));
delegate (Number, CharValue,       char, (const Number* const));
delegate (Number, ShortValue,      short, (const Number* const));

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


static inline vptr(Number);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadNumber(Class base) 
{
    Class cls = createClass(base, Number);
    addMethod(cls, Number,      ToString);
    addMethod(cls, Object,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, Number,     CompareTo);
    addMethod(cls, Number,      IntValue);
    addMethod(cls, Number,     LongValue);
    addMethod(cls, Number,    FloatValue);
    addMethod(cls, Number,   DoubleValue);
    addMethod(cls, Number,     CharValue);
    addMethod(cls, Number,    ShortValue);

    return cls;
}

/**
 * Abstract class Number
 * Initialize the Number vtable
 * all methods are virtual
 */
method Number* New(Number* self)
{
    extends(Comparable);
    self->isa = objc_getClass("Number");
    return self;
}
/**
 * Compares two Number objects.
 *
 * @param   other  Short to be compared
 * @return  0 self == other
 *         +1 self < other
 *         -1 self > other
 */
method int CompareTo(const Number* self, const Number* const other) {
    return virtual(Number)->CompareTo(self, other);
}

/**
 * Returns the value of self value cast as an int
 */
method int IntValue(const Number* const self) {
    return virtual(Number)->IntValue(self);
}

/**
 * Returns the value of self value cast as a long
 */
method long LongValue(const Number* const self) {
    return virtual(Number)->LongValue(self);
}

/**
 * Returns the value of self value cast as a float
 */
method float FloatValue(const Number* const self) {
    return virtual(Number)->FloatValue(self);
}

/**
 * Returns the value of self value cast as a double
 */
method double DoubleValue(const Number* const self) {
    return virtual(Number)->DoubleValue(self);
}

/**
 * Returns the value of self value cast as a char
 */
method char CharValue(const Number* const self) {
    return virtual(Number)->CharValue(self);
}

/**
 * Returns the value of self value cast as a short
 */
method short ShortValue(const Number* const self) {
    return virtual(Number)->ShortValue(self);
}

method char* ToString(const Number* const self) {
    return virtual(Number)->ToString(self);
}
