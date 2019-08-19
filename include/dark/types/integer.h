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
#include <dark/types/long.h>


#define INTEGER_MIN_VALUE  INT_MIN
#define INTEGER_MAX_VALUE  INT_MAX
#define INTEGER_BYTES      (sizeof(int))
#define INTEGER_SIZE       (INTEGER_BYTES * CHAR_BIT)
#define INTEGER_TYPE       (TYPE_LONG)

#define IsInteger(object) _Generic((object), Integer*: true, default: false)
#define AsInteger(object) _Generic((object),                          \
                            Integer*: (Integer *)object,            \
                            default: nullptr)

/**
 * Object class
 */
type (Integer) 
{
    Class isa;
    int value;
};


interface (Integer, ToString,        char*, (const Integer* const));
interface (Integer, CompareTo,       int, (const Integer* const, const Integer* const));
interface (Integer, IntValue,        int, (const Integer* const));
interface (Integer, LongValue,       long, (const Integer* const));
interface (Integer, FloatValue,      float, (const Integer* const));
interface (Integer, DoubleValue,     double, (const Integer* const));
interface (Integer, CharValue,       char, (const Integer* const));
interface (Integer, ShortValue,      short, (const Integer* const));

/**
 * Integer vtable with overrides
 */
vtable (Integer)
{
    const IntegerToString           ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const IntegerCompareTo          CompareTo;
    const IntegerIntValue           IntValue;
    const IntegerLongValue          LongValue;
    const IntegerFloatValue         FloatValue;
    const IntegerDoubleValue        DoubleValue;
    const IntegerCharValue          CharValue;
    const IntegerShortValue         ShortValue;
};

function vptr(Integer);
/**
 * Class Loader callback
 */
function objc_loadInteger(Class super) 
{
    Class cls = createClass(super, Integer);
    addMethod(cls, Integer,     ToString);
    addMethod(cls, Object,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, Integer,    CompareTo);
    addMethod(cls, Integer,     IntValue);
    addMethod(cls, Integer,    LongValue);
    addMethod(cls, Integer,   FloatValue);
    addMethod(cls, Integer,  DoubleValue);
    addMethod(cls, Integer,    CharValue);
    addMethod(cls, Integer,   ShortValue);
    return cls;
}

/* 
 * Constructor
 * create a new Integer
 * 
 * @param value of int
 * 
 */
function Integer* Integer_init(Integer* const this, const int value)
{
    Number_init(this);
    this->isa = objc_getClass("Integer");
    this->value = value;
    return this;
}

function Integer* NewInteger(const int value) { 
    return Integer_init(alloc(Integer), value); 
}

/**
 * Returns a primitive integer value parsed from input string. 
 */
function int DSParseInt(const char* const s, const int radix) {
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
method int Compare(const int x, const int y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Integer objects.
 *
 * @param   other  Integer to be compared
 * @return same as Integer_Compare
 */
method int CompareTo(const Integer* this, const Integer* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Integer* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Integer* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Integer* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Integer* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Integer* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Integer* const this) {
    return (short)this->value;
}


method char* ToString(const Integer* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}
