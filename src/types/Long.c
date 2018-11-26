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
#include <dark/types/Long.h>
/* 
 * Long implementation
 */
static Exception(NumberFormat);


/**
 * Returns a primitive long value parsed from input string. 
 */
long Long_ParseLong(char* s, int radix)
{
    errno = 0;
    char* endptr;
    long result = strtol(s, endptr, radix);

    if (errno != 0)
        return NumberFormatException(
            "Invalid input. Value:\"%s\" Radix: %d", s, radix);

    if (s == endptr || *endptr != '\0')
        return NumberFormatException(
            "Invalid input. Value:\"%s\" Radix: %d", s, radix);

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
int Long_Compare(long x, long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Long objects.
 *
 * @param   other  Long to be compared
 * @return same as Long_Compare
 */
int Long_CompareTo(Long this, Long other) {
    return Long_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Long_IntValue(Long const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Long_LongValue(Long const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Long_FloatValue(Long const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Long_DoubleValue(Long const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Long_CharValue(Long const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Long_ShortValue(Long const this) {
    return (short)this->value;
}


char* Long_ToString(Long const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

/**
 * Initialize a new Long
 */
Long Long_Ctor(Long const this, long value)
{
    Number_Ctor(this);

    this->ToString      = Long_ToString;
    this->CompareTo     = Long_CompareTo;
    this->IntValue      = Long_IntValue; 
    this->LongValue     = Long_LongValue; 
    this->FloatValue    = Long_FloatValue; 
    this->DoubleValue   = Long_DoubleValue; 
    this->CharValue     = Long_CharValue; 
    this->ShortValue    = Long_ShortValue; 

    this->value = value;
    return this;
}

/**
 * new Long
 * 
 * create a new Long
 * 
 * @param value of long
 * 
 */
Long Long_New(long value)
{
    return Long_Ctor(new(Long), value);
}
