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
#include <dark/types/DSNumber.h>
#include <dark/types/implementation/DSNumber.h>
/**
 * Abstract class Number
 * Initialize the Number vtable
 * all methods are virtual
 */
DSNumber* DSNumber_init(DSNumber* const this)
{
    DSComparable_init(this);
    this->isa = getDSNumberIsa();
    return this;
}

/**
 * Compares two Number objects.
 *
 * @param   other  Short to be compared
 * @return  0 this == other
 *         +1 this < other
 *         -1 this > other
 */
int overload CompareTo(const DSNumber* this, const DSNumber* const other) {
    return _vptr(this)->CompareTo(this, other);
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(const DSNumber* const this) {
    return _vptr(this)->IntValue(this);
}

/**
 * Returns the value of this value cast as a long
 */
long overload LongValue(const DSNumber* const this) {
    return _vptr(this)->LongValue(this);
}

/**
 * Returns the value of this value cast as a float
 */
float overload FloatValue(const DSNumber* const this) {
    return _vptr(this)->FloatValue(this);
}

/**
 * Returns the value of this value cast as a double
 */
double overload DoubleValue(const DSNumber* const this) {
    return _vptr(this)->DoubleValue(this);
}

/**
 * Returns the value of this value cast as a char
 */
char overload CharValue(const DSNumber* const this) {
    return _vptr(this)->CharValue(this);
}

/**
 * Returns the value of this value cast as a short
 */
short overload ShortValue(const DSNumber* const this) {
    return _vptr(this)->ShortValue(this);
}

char* overload ToString(const DSNumber* const this) {
    return _vptr(this)->ToString(this);
}



