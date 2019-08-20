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

#define SHORT_MIN_VALUE  SHRT_MIN
#define SHORT_MAX_VALUE  SHRT_MAX
#define SHORT_BYTES      (sizeof(short))
#define SHORT_SIZE       (SHORT_BYTES * CHAR_BIT)
#define SHORT_TYPE       (TYPE_SHORT)

#define IsShort(object) _Generic((object), Short*: true, default: false)
#define AsShort(object) _Generic((object),                            \
                            Short*: (Short *)object,                \
                            default: nullptr)

/**
 * Object class
 */
type (Short) {
    Class isa;
    short value;
};

interface (Short, ToString,        char*, (const Short* const));
interface (Short, CompareTo,       int, (const Short* const, const Short* const));
interface (Short, IntValue,        int, (const Short* const));
interface (Short, LongValue,       long, (const Short* const));
interface (Short, FloatValue,      float, (const Short* const));
interface (Short, DoubleValue,     double, (const Short* const));
interface (Short, CharValue,       char, (const Short* const));
interface (Short, ShortValue,      short, (const Short* const));


/**
 * Integer vtable with overrides
 */
vtable (Short)
{
    const ShortToString         ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const ShortCompareTo        CompareTo;
    const ShortIntValue         IntValue;
    const ShortLongValue        LongValue;
    const ShortFloatValue       FloatValue;
    const ShortDoubleValue      DoubleValue;
    const ShortCharValue        CharValue;
    const ShortShortValue       ShortValue;
};

function vptr(Short);
/*
 *
 * Class Loader callback
 */
function objc_loadShort(Class super) 
{
    Class cls = createClass(super, Short);
    addMethod(cls, Short,       ToString);
    addMethod(cls, Object,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, Short,      CompareTo);
    addMethod(cls, Short,       IntValue);
    addMethod(cls, Short,      LongValue);
    addMethod(cls, Short,     FloatValue);
    addMethod(cls, Short,    DoubleValue);
    addMethod(cls, Short,      CharValue);
    addMethod(cls, Short,     ShortValue);
    
    return cls;
}

/**
 * Constructor
 * create a new Short
 * 
 * @param value of short
 * 
 */
function Short* Short_init(Short* const this, const short value)
{
    Number_init(this);
    this->isa = objc_getClass("Short");
    this->value = value;
    return this;
}

function Short* NewShort(const short value) { 
    return Short_init(alloc(Short), value); 
}

/**
 * Returns a primitive short value parsed from input string. 
 */
function short DSParseShort(char const *const s, int const radix)
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
method int Compare(const short x, const short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as Short_Compare
 */
method int CompareTo(const Short* this, const Short* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method int IntValue(const Short* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
method long LongValue(const Short* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
method float FloatValue(const Short* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
method double DoubleValue(const Short* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
method char CharValue(const Short* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
method short ShortValue(const Short* const this) {
    return (short)this->value;
}


method char* ToString(const Short* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

