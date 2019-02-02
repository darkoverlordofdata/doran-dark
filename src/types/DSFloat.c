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
#include <dark/types/DSFloat.h>
#include <dark/types/implementation/DSFloat.h>
/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
DSFloat* NewDSFloat(const float value) { 
    return DSFloat_init(alloc(DSFloat), value); 
}

DSFloat* DSFloat_init(DSFloat* const this, const float value)
{
    DSNumber_init(this);
    this->isa = getDSFloatIsa();
    this->value = value;
    return this;
}

/**
 * Returns a primitive float value parsed from input string. 
 */
float DSParseFloat(const char* s)
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
overload int Compare(const float x, const float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as DSFloat_Compare
 */
overload int CompareTo(const DSFloat* this, const DSFloat* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
overload int IntValue(const DSFloat* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
overload long LongValue(const DSFloat* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
overload double DoubleValue(const DSFloat* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
overload float FloatValue(const DSFloat* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
overload char CharValue(const DSFloat* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
overload short ShortValue(const DSFloat* const this) {
    return (short)this->value;
}


overload char* ToString(const DSFloat* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}
