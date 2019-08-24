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

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

#define IsFloat(object) _Generic((object), Float*: true, default: false)
#define AsFloat(object) _Generic((object),                               \
                            Float*: (Float *)object,                  \
                            default: nullptr)


/**
 * Object class
 */
type (Float) 
{
    Class isa;
    float value;
};

delegate (Float, New,           Float*, (Float*, const float));
delegate (Float, ToString,      char*, (const Float* const));
delegate (Float, CompareTo,     int, (const Float* const, const Float* const));
delegate (Float, IntValue,      int, (const Float* const));
delegate (Float, LongValue,     long, (const Float* const));
delegate (Float, FloatValue,    float, (const Float* const));
delegate (Float, DoubleValue,   double, (const Float* const));
delegate (Float, CharValue,     char, (const Float* const));
delegate (Float, ShortValue,    short, (const Float* const));


/**
 * Float vtable with overrides
 */
vtable (Float)
{
    const FloatToString         ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const FloatCompareTo        CompareTo;
    const FloatIntValue         IntValue;
    const FloatLongValue        LongValue;
    const FloatFloatValue       FloatValue;
    const FloatDoubleValue      DoubleValue;
    const FloatCharValue        CharValue;
    const FloatShortValue       ShortValue;
};

static inline vptr(Float);
/** 
 * 
] * Class Loader callback
 */
static inline Class objc_loadFloat(Class super) 
{
    Class cls = createClass(super, Float);
    addMethod(cls, Object,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, Float,      CompareTo);
    addMethod(cls, Float,       IntValue);
    addMethod(cls, Float,      LongValue);
    addMethod(cls, Float,     FloatValue);
    addMethod(cls, Float,    DoubleValue);
    addMethod(cls, Float,      CharValue);
    addMethod(cls, Float,     ShortValue);
    return cls;
}

/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
method Float* New(Float* self, const float value)
{
    extends(Number);
    self->isa = objc_getClass("Float");
    self->value = value;
    return self;
}

/**
 * Returns a primitive float value parsed from input string. 
 */
static inline float DSParseFloat(const char* s)
{
    
    double d = DSParseDouble(s);
    if (d < FLOAT_MIN_VALUE || d > FLOAT_MAX_VALUE)
        throw DSNumberFormatException(s, Source);
    return (float)d;
}

/**
 * Compare two float primitives.
 * @param  x float to compare
 * @param  y float to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
method int Compare(const float x, const float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as Float_Compare
 */
method int CompareTo(const Float* self, const Float* other) {
    return Compare(self->value, other->value);
}

/**
 * Returns the value of self value cast as an int
 */
method int IntValue(const Float* const self) {
    return (int)self->value;
}

/**
 * Returns the value of self value cast as a long
 */
method long LongValue(const Float* const self) {
    return (long)self->value;
}

/**
 * Returns the value of self value cast as a double
 */
method double DoubleValue(const Float* const self) {
    return (double)self->value;
}

/**
 * Returns the value of self value cast as a float
 */
method float FloatValue(const Float* const self) {
    return (float)self->value;
}

/**
 * Returns the value of self value cast as a char
 */
method char CharValue(const Float* const self) {
    return (char)self->value;
}

/**
 * Returns the value of self value cast as a short
 */
method short ShortValue(const Float* const self) {
    return (short)self->value;
}


overload char* ToString(const Float* const self)
{
    static char str[20];
    sprintf(str, "%f", self->value);
    return str;
}

