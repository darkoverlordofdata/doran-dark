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
#include <dark/types/DSShort.h>
#include "private/DSShort.h"
/* 
 * Throws NumberFormatException:
 */
// static DSException(NumberFormat);
/**
 * Constructor
 * create a new Short
 * 
 * @param value of short
 * 
 */
DSShort* NewDSShort(const short value) { 
    return DSShort_init(objc_getClass("DSShort"), value); 
}

DSShort* DSShort_init(DSShort* const this, const short value)
{
    DSNumber_init(this);
    this->isa = getDSShortIsa();
    this->value = value;
    return this;
}

DSShort* DSShort_alloc() {
    return DSMalloc(getDSShortSize());
}


/**
 * Returns a primitive short value parsed from input string. 
 */
short DSParseShort(char const *const s, int const radix)
{
    long i = DSParseLong(s, radix);
    if (i < SHORT_MIN_VALUE || i > SHORT_MAX_VALUE)
        Throw DSNumberFormatException(s, radix);
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
short overload Compare(const short x, const short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as DSShort_Compare
 */
int overload CompareTo(const DSShort* this, const DSShort* other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(const DSShort* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long overload LongValue(const DSShort* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float overload FloatValue(const DSShort* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double overload DoubleValue(const DSShort* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char overload CharValue(const DSShort* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short overload ShortValue(const DSShort* const this) {
    return (short)this->value;
}


char* overload ToString(const DSShort* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

