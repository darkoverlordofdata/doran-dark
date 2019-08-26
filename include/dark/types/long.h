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

delegate (Long, New,        Long*, (Long*, const long));
delegate (Long, ToString,   char*, (const Long* const));
delegate (Long, CompareTo,  int, (const Long* const, const Long* const));
delegate (Long, IntValue,   int, (const Long* const));
delegate (Long, LongValue,  long, (const Long* const));
delegate (Long, FloatValue, float, (const Long* const));
delegate (Long, DoubleValue,double, (const Long* const));
delegate (Long, CharValue,  char, (const Long* const));
delegate (Long, ShortValue, short, (const Long* const));


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

static inline vptr(Long);
/** 
 * 
 * Class Loader callback
 */
static inline Class ClassLoadLong(Class base) 
{
    Class cls = createClass(base, Long);
    addMethod(cls, Long,        ToString);
    addMethod(cls, Object,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, Long,       CompareTo);
    addMethod(cls, Long,        IntValue);
    addMethod(cls, Long,       LongValue);
    addMethod(cls, Long,      FloatValue);
    addMethod(cls, Long,     DoubleValue);
    addMethod(cls, Long,       CharValue);
    addMethod(cls, Long,      ShortValue);
    return cls;
}


/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
method Long* New(Long* self, const long value)
{
    extends(Number);
    set_isa(Long);
    self->value = value;
    return self;
}

/**
 * Returns a primitive long value parsed from input string. 
 */
static inline long DSParseLong(const char* const s, const int radix)
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
method int CompareTo(const Long* const self, const Long* const other) {
    return Compare(self->value, other->value);
}

/**
 * Returns the value of self value cast as an int
 */
method int IntValue(const Long* const self) {
    return (int)self->value;
}

/**
 * Returns the value of self value cast as a long
 */
method long LongValue(const Long* const self) {
    return (long)self->value;
}

/**
 * Returns the value of self value cast as a float
 */
method float FloatValue(const Long* const self) {
    return (float)self->value;
}

/**
 * Returns the value of self value cast as a double
 */
method double DoubleValue(const Long* const self) {
    return (double)self->value;
}

/**
 * Returns the value of self value cast as a char
 */
method char CharValue(const Long* const self) {
    return (char)self->value;
}

/**
 * Returns the value of self value cast as a short
 */
method short ShortValue(const Long* const self) {
    return (short)self->value;
}

method bool Equals(const Long* const self, const Long* const other)
{
    return self->value == other->value;
}

method char* ToString(const Long* const self)
{
    static char str[20];
    sprintf(str, "%d", self->value);
    return str;
}
