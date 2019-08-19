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

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

#define IsLong(object) _Generic((object), Long*: true, default: false)
#define AsLong(object) _Generic((object),                             \
                            Long*: (Long *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
type (Long) 
{
    Class isa;
    long value;
};

interface (Long, ToString,        char*, (const Long* const));
interface (Long, CompareTo,       int, (const Long* const, const Long* const));
interface (Long, IntValue,        int, (const Long* const));
interface (Long, LongValue,       long, (const Long* const));
interface (Long, FloatValue,      float, (const Long* const));
interface (Long, DoubleValue,     double, (const Long* const));
interface (Long, CharValue,       char, (const Long* const));
interface (Long, ShortValue,      short, (const Long* const));


/**
 * Integer vtable with overrides
 */
vtable (Long)
{
    const LongToString           ToString;
    const ObjectEquals           Equals;
    const ObjectGetHashCode      GetHashCode;
    const ObjectDispose          Dispose;
    const LongCompareTo          CompareTo;
    const LongIntValue           IntValue;
    const LongLongValue          LongValue;
    const LongFloatValue         FloatValue;
    const LongDoubleValue        DoubleValue;
    const LongCharValue          CharValue;
    const LongShortValue         ShortValue;
};

function vptr(Long);
/** 
 * 
 * Class Loader callback
 */
function objc_loadLong(Class super) 
{
    Class cls = createClass(super, Long);
    addMethod(cls, LongToString,        ToString);
    addMethod(cls, ObjectEquals,        Equals);
    addMethod(cls, ObjectGetHashCode,   GetHashCode);
    addMethod(cls, ObjectDispose,       Dispose);
    addMethod(cls, LongCompareTo,       CompareTo);
    addMethod(cls, LongIntValue,        IntValue);
    addMethod(cls, LongLongValue,       LongValue);
    addMethod(cls, LongFloatValue,      FloatValue);
    addMethod(cls, LongDoubleValue,     DoubleValue);
    addMethod(cls, LongCharValue,       CharValue);
    addMethod(cls, LongShortValue,      ShortValue);
    return cls;
}


/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
function Long* Long_init(Long* const this, const long value)
{
    Number_init(this);
    this->isa = objc_getClass("Long");
    this->value = value;
    return this;
}

function Long* NewLong(const long value) { 
    return Long_init(alloc(Long), value); 
}

/**
 * Returns a primitive long value parsed from input string. 
 */
function long DSParseLong(const char* const s, const int radix)
{
    errno = 0;
    char* endptr;
    long result = strtol(s, &endptr, radix);

    if (errno != 0)
        throw DSNumberFormatException(s, radix, Source);

    if (s == endptr || *endptr != '\0')
        throw DSNumberFormatException(s, radix, Source);

    return result;
}

/**
 * Compare two long primitives.
 * @param  x long to compare
 * @param  y long to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const long x, const long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Long objects.
 *
 * @param   other  Long to be compared
 * @return same as Long_Compare
 */
method int CompareTo(const Long* const this, const Long* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Long* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Long* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Long* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Long* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Long* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Long* const this) {
    return (short)this->value;
}

method bool Equals(const Long* const this, const Long* const other)
{
    return this->value == other->value;
}

method char* ToString(const Long* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}
