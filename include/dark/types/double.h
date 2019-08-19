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
#include <dark/types/number.h>

#define DOUBLE_MIN_VALUE  DBL_MIN
#define DOUBLE_MAX_VALUE  DBL_MAX
#define DOUBLE_BYTES      (sizeof(double))
#define DOUBLE_SIZE       (DOUBLE_BYTES * CHAR_BIT)
#define DOUBLE_TYPE       (TYPE_DOUBLE)

#define IsDouble(object) _Generic((object), Double*: true, default: false)
#define AsDouble(object) _Generic((object),                          \
                            Double*: (Double *)object,             \
                            default: nullptr)

/**
 * Double instance variables
 */
type (Double) 
{
    Class isa;
    double value;
};

interface (Double, ToString,        char*,    (const Double* const));
interface (Double, CompareTo,       int,      (const Double* const, const Double* const));
interface (Double, IntValue,        int,      (const Double* const));
interface (Double, LongValue,       long,     (const Double* const));
interface (Double, FloatValue,      float,    (const Double* const));
interface (Double, DoubleValue,     double,   (const Double* const));
interface (Double, CharValue,       char,     (const Double* const));
interface (Double, ShortValue,      short,    (const Double* const));

/**
 * Double vtable with overrides
 */
vtable (Double)
{
    const DoubleToString            ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const DoubleCompareTo           CompareTo;
    const DoubleIntValue            IntValue;
    const DoubleLongValue           LongValue;
    const DoubleFloatValue          FloatValue;
    const DoubleDoubleValue         DoubleValue;
    const DoubleCharValue           CharValue;
    const DoubleShortValue          ShortValue;
};

function vptr(Double);
/**
 * Class Loader callback
 */
function objc_loadDouble(Class super) 
{
    Class cls = createClass(super, Double);
    addMethod(cls,  Double,     ToString);
    addMethod(cls,  Object,       Equals);
    addMethod(cls,  Object,  GetHashCode);
    addMethod(cls,  Object,      Dispose);
    addMethod(cls,  Double,    CompareTo);
    addMethod(cls,  Double,     IntValue);
    addMethod(cls,  Double,    LongValue);
    addMethod(cls,  Double,   FloatValue);
    addMethod(cls,  Double,  DoubleValue);
    addMethod(cls,  Double,    CharValue);
    addMethod(cls,  Double,   ShortValue);
    return cls;
}

/**
 * Constructor
 * create a new Double
 * 
 * @param value of double
 * 
 */
function Double* Double_init(Double* const this, const double value) {
    Number_init(this);
    this->isa = objc_getClass("Double");
    this->value = value;
    return this;
}

function Double* NewDouble(const double value) { 
    return Double_init(alloc(Double), value); 
}

/**
 * Returns a primitive double value parsed from input string. 
 */
function double DSParseDouble(char const *const s) {
    errno = 0;
    char* endptr;
    double result = strtod(s, endptr);

    if (errno != 0)
        throw DSNumberFormatException(s, Source);

    if (s == endptr || *endptr != '\0')
        throw DSNumberFormatException(s, Source);

    return result;
}

/**
 * Compare two double primitives.
 * @param  x double to compare
 * @param  y double to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const double x, const double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Double objects.
 *
 * @param   other  Double to be compared
 * @return same as Double_Compare
 */
method int CompareTo(const Double* const this, const Double* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Double* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Double* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Double* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Double* const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Double* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Double* const this) {
    return (short)this->value;
}

method char* ToString(const Double* const this) {
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

