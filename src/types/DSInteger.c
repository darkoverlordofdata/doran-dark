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
#include <dark/types/DSInteger.h>
#include "private/DSInteger.h"
/* 
 * throws: NumberFormatException
 */
// static DSException(NumberFormat);
/* 
 * Constructor
 * create a new Integer
 * 
 * @param value of int
 * 
 */

DSInteger* NewDSInteger(const int value) { 
    return DSInteger_init(alloc(DSInteger), value); 
}

DSInteger* DSInteger_init(DSInteger* const this, const int value)
{
    DSNumber_init(this);
    this->isa = getDSIntegerIsa();
    this->value = value;
    return this;
}

/**
 * Returns a primitive integer value parsed from input string. 
 */
int DSParseInt(const char* const s, const int radix) {
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
int overload Compare(const int x, const int y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Integer objects.
 *
 * @param   other  Integer to be compared
 * @return same as DSInteger_Compare
 */
int overload CompareTo(const DSInteger* this, const DSInteger* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long overload LongValue(const DSInteger* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float overload FloatValue(const DSInteger* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double overload DoubleValue(const DSInteger* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char overload CharValue(const DSInteger* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short overload ShortValue(const DSInteger* const this) {
    return (short)this->value;
}


char* overload ToString(const DSInteger* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}
