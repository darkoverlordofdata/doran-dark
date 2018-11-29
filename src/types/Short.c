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
#include <dark/types/Short.h>
/* 
 * Short implementation
 */
static Exception(NumberFormat);


/**
 * Returns a primitive short value parsed from input string. 
 */
short Short_ParseShort(char* s, int radix)
{
    long i = Long_ParseLong(s, radix);
    if (i < SHORT_MIN_VALUE || i > SHORT_MAX_VALUE)
        return NumberFormatException(
            "Value out of range. Value:\"%s\" Radix: %d", s, radix);
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
short Short_Compare(short x, short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as Short_Compare
 */
int Short_CompareTo(Short this, Short other) {
    return Short_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Short_IntValue(Short const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Short_LongValue(Short const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Short_FloatValue(Short const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Short_DoubleValue(Short const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Short_CharValue(Short const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Short_ShortValue(Short const this) {
    return (short)this->value;
}


char* Short_ToString(Short const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

/**
 * Initialize a new Short
 */
Short Short_Ctor(Short const this, short value)
{
    Number_Ctor(this);

    this->ToString      = Short_ToString;
    this->CompareTo     = Short_CompareTo;
    this->IntValue      = Short_IntValue; 
    this->LongValue     = Short_LongValue; 
    this->FloatValue    = Short_FloatValue; 
    this->DoubleValue   = Short_DoubleValue; 
    this->CharValue     = Short_CharValue; 
    this->ShortValue    = Short_ShortValue; 

    this->value = value;
    return this;
}

/**
 * new Short
 * 
 * create a new Short
 * 
 * @param value of short
 * 
 */
Short Short_New(short value)
{
    return DObject_gc(Short_Ctor(new(Short), value));
}

Short Short_rcNew(short value)
{
    return Short_Ctor(rc_new(Short), value);
}