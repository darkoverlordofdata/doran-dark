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
#include <dark/types/DSLong.h>
#include <dark/types/implementation/DSLong.h>
/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
DSLong* NewDSLong(const long value) { 
    return DSLong_init(alloc(DSLong), value); 
}

DSLong* DSLong_init(DSLong* const this, const long value)
{
    DSNumber_init(this);
    this->isa = getDSLongIsa();
    this->value = value;
    return this;
}

/**
 * Returns a primitive long value parsed from input string. 
 */
long DSParseLong(const char* const s, const int radix)
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
overload int Compare(const long x, const long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Long objects.
 *
 * @param   other  Long to be compared
 * @return same as DSLong_Compare
 */
overload int CompareTo(const DSLong* const this, const DSLong* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
overload int IntValue(const DSLong* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
overload long LongValue(const DSLong* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
overload float FloatValue(const DSLong* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
overload double DoubleValue(const DSLong* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
overload char CharValue(const DSLong* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
overload short ShortValue(const DSLong* const this) {
    return (short)this->value;
}

overload bool Equals(const DSLong* const this, const DSLong* const other)
{
    return this->value == other->value;
}

overload char* ToString(const DSLong* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}
