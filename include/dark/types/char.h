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

#define CHAR_MIN_VALUE  CHAR_MIN
#define CHAR_MAX_VALUE  CHAR_MAX
#define CHAR_BYTES      (sizeof(char))
#define CHAR_SIZE       (CHAR_BYTES * CHAR_BIT)
#define CHAR_TYPE       (TYPE_CHAR)

#define IsChar(object) _Generic((object), Char*: true, default: false)
#define AsChar(object) _Generic((object),                             \
                            Char*: (Char *)object,                  \
                            default: nullptr)

/**
 * Char instance variables
 */
type (Char) {
    Class isa;
    char value;
};

delegate (Char, New,            Char*, (Char*, const char value));
delegate (Char, ToString,       char*, (const Char* const));
delegate (Char, CompareTo,      int, (const Char* const, const Char* const));
delegate (Char, IntValue,       int, (const Char* const));
delegate (Char, LongValue,      long, (const Char* const));
delegate (Char, FloatValue,     float, (const Char* const));
delegate (Char, DoubleValue,    double, (const Char* const));
delegate (Char, CharValue,      char, (const Char* const));
delegate (Char, ShortValue,     short, (const Char* const));

/**
 * Char vtable with overrides
 */
vtable (Char)
{
    const CharToString          ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const CharCompareTo         CompareTo;
    const CharIntValue          IntValue;
    const CharLongValue         LongValue;
    const CharFloatValue        FloatValue;
    const CharDoubleValue       DoubleValue;
    const CharCharValue         CharValue;
    const CharShortValue        ShortValue;
};

static inline vptr(Char);
/**
 * Class Loader callback
 */
static inline Class ClassLoadChar(Class base) 
{
    Class cls = createClass(base, Char);

    addMethod(cls, Char,   ToString);
    addMethod(cls, Char,   ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Char,   CompareTo);
    addMethod(cls, Char,   IntValue);
    addMethod(cls, Char,   LongValue);
    addMethod(cls, Char,   FloatValue);
    addMethod(cls, Char,   DoubleValue);
    addMethod(cls, Char,   CharValue);
    addMethod(cls, Char,   ShortValue);
    return cls;
}


/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
method Char* New(Char* self, const char value)
{
    extends(Number);
    set_isa(Char);
    self->value = value;
    return self;
}

/**
 * Compare two char primitives.
 * @param  x char to compare
 * @param  y char to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const char x, const char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as Char_Compare
 */
method int CompareTo(const Char* const self, const Char* const other) {
    return Compare(self->value, other->value);
}

/**
 * Returns the value of self value cast as an int
 */
method int IntValue(const Char* const self) {
    return (int)self->value;
}

/**
 * Returns the value of self value cast as a long
 */
method long LongValue(const Char* const self) {
    return (long)self->value;
}

/**
 * Returns the value of self value cast as a float
 */
method float FloatValue(const Char* const self) {
    return (float)self->value;
}

/**
 * Returns the value of self value cast as a double
 */
method double DoubleValue(const Char* const self) {
    return (double)self->value;
}

/**
 * Returns the value of self value cast as a char
 */
method char CharValue(const Char* const self) {
    return (char)self->value;
}

/**
 * Returns the value of self value cast as a short
 */
method short ShortValue(const Char* const self) {
    return (short)self->value;
}


/**
 * Returns the string value of self Char
 */
method char* ToString(const Char* const self)
{
    static char str[2];
    sprintf(str, "%c", self->value);
    return str;
}

