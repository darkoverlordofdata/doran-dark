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

delegate (Short, New,           Short*, (Short*, const short));
delegate (Short, ToString,      char*, (const Short* const));
delegate (Short, CompareTo,     int, (const Short* const, const Short* const));
delegate (Short, IntValue,      int, (const Short* const));
delegate (Short, LongValue,     long, (const Short* const));
delegate (Short, FloatValue,    float, (const Short* const));
delegate (Short, DoubleValue,   double, (const Short* const));
delegate (Short, CharValue,     char, (const Short* const));
delegate (Short, ShortValue,    short, (const Short* const));


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

static inline vptr(Short);
/*
 *
 * Class Loader callback
 */
static inline Class objc_loadShort(Class base) 
{
    Class cls = createClass(base, Short);
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
method Short* New(Short* self, const short value)
{
    extends(Number);
    self->isa = objc_getClass("Short");
    self->value = value;
    return self;
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
method int Compare(const short x, const short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as Short_Compare
 */
method int CompareTo(const Short* self, const Short* other) {
    return Compare(self->value, other->value);
}

/**
 * Returns the value of self value cast as an int
 */
method int IntValue(const Short* const self) {
    return (int)self->value;
}

/**
 * Returns the value of self value cast as a long
 */
method long LongValue(const Short* const self) {
    return (long)self->value;
}

/**
 * Returns the value of self value cast as a float
 */
method float FloatValue(const Short* const self) {
    return (float)self->value;
}

/**
 * Returns the value of self value cast as a double
 */
method double DoubleValue(const Short* const self) {
    return (double)self->value;
}

/**
 * Returns the value of self value cast as a char
 */
method char CharValue(const Short* const self) {
    return (char)self->value;
}

/**
 * Returns the value of self value cast as a short
 */
method short ShortValue(const Short* const self) {
    return (short)self->value;
}


method char* ToString(const Short* const self)
{
    static char str[20];
    sprintf(str, "%d", self->value);
    return str;
}

