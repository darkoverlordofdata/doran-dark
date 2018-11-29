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
#include <dark/types/Integer.h>
/* 
 * Integer implementation
 */

/**
 * Returns a primitive integer value parsed from input string. 
 */
int Integer_ParseInt(char* s, int radix) {
    long i = Long_ParseLong(s, radix);
    if (i < INTEGER_MIN_VALUE || i > INTEGER_MAX_VALUE)
        return NumberFormatException(
            "Value out of range. Value:\"%s\" Radix: %d", s, radix);
    return (int)i;
}

/**
 * Compare two int primitives.
 * @param  x int to compare
 * @param  y int to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
int Integer_Compare(int x, int y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Integer objects.
 *
 * @param   other  Integer to be compared
 * @return same as Integer_Compare
 */
int Integer_CompareTo(Integer this, Integer other) {
    return Integer_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Integer_IntValue(Integer const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Integer_LongValue(Integer const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Integer_FloatValue(Integer const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Integer_DoubleValue(Integer const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Integer_CharValue(Integer const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Integer_ShortValue(Integer const this) {
    return (short)this->value;
}


char* Integer_ToString(Integer const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

/**
 * Initialize a new Integer
 */
Integer Integer_Ctor(Integer const this, int value)
{
    Number_Ctor(this);

    this->ToString      = Integer_ToString;
    this->CompareTo     = Integer_CompareTo;
    this->IntValue      = Integer_IntValue; 
    this->LongValue     = Integer_LongValue; 
    this->FloatValue    = Integer_FloatValue; 
    this->DoubleValue   = Integer_DoubleValue; 
    this->CharValue     = Integer_CharValue; 
    this->ShortValue    = Integer_ShortValue; 

    this->value = value;
    return this;
}

/**
 * new Integer
 * 
 * create a new Integer
 * 
 * @param value of int
 * 
 */
Integer Integer_New(int value)
{
    return DObject_gc(Integer_Ctor(new(Integer), value));
}

Integer Integer_rcNew(int value)
{
    return Integer_Ctor(rc_new(Integer), value);
}
