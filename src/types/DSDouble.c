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
#include <dark/types/DSDouble.h>
#include <dark/types/private/DSDouble.h>
/* 
 * throws NumberFormatException:
 */
// static DSException(NumberFormat);

/**
 * Constructor
 * create a new DSDouble
 * 
 * @param value of double
 * 
 */
DSDouble* NewDSDouble(const double value) { 
    return DSDouble_init(alloc(DSDouble), value); 
}

DSDouble* DSDouble_init(DSDouble* const this, const double value) {
    DSNumber_init(this);
    this->isa = getDSDoubleIsa();
    this->value = value;
    return this;
}

/**
 * Returns a primitive double value parsed from input string. 
 */
double DSParseDouble(char const *const s) {
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
int overload Compare(const double x, const double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two DSDouble objects.
 *
 * @param   other  DSDouble to be compared
 * @return same as DSDouble_Compare
 */
int overload CompareTo(const DSDouble* const this, const DSDouble* const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(const DSDouble* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long overload LongValue(const DSDouble* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float overload FloatValue(const DSDouble* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double overload DoubleValue(const DSDouble* const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char overload CharValue(const DSDouble* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short overload ShortValue(const DSDouble* const this) {
    return (short)this->value;
}

char* overload ToString(const DSDouble* const this) {
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

