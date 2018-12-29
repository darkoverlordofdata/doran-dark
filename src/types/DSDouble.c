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
/* 
 * Throws NumberFormatException:
 */
static DSException(NumberFormat);

/**
 * Constructor
 * create a new DSDouble
 * 
 * @param value of double
 * 
 */
DSDouble* DSDouble_Ctor(DSDouble* const this, double value)
{
    DSNumber_Ctor(this);
    this->isa = isa(DSDouble);
    this->value = value;
    return this;
}

/**
 * Returns a primitive double value parsed from input string. 
 */
double DSParseDouble(char const *const s)
{
    errno = 0;
    char* endptr;
    double result = strtod(s, endptr);

    if (errno != 0)
        return DSNumberFormatException(
            "Invalid input. Value:\"%s\"", s);

    if (s == endptr || *endptr != '\0')
        return DSNumberFormatException(
            "Invalid input. Value:\"%s\"", s);

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
int DSDouble_Compare(double x, double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two DSDouble objects.
 *
 * @param   other  DSDouble to be compared
 * @return same as DSDouble_Compare
 */
int DSDouble_CompareTo(DSDouble* const this, DSDouble* const other) {
    return DSDouble_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int DSDouble_IntValue(DSDouble* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long DSDouble_LongValue(DSDouble* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float DSDouble_FloatValue(DSDouble* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double DSDouble_DoubleValue(DSDouble* const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char DSDouble_CharValue(DSDouble* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short DSDouble_ShortValue(DSDouble* const this) {
    return (short)this->value;
}


char* DSDouble_ToString(DSDouble* const this) {
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

DSDouble* $DSDouble(double value) { 
    return DSDouble_Ctor(DSNew(DSDouble), value); 
}


/**
 * DSDouble Class Metadata
 */
DSDefine(DSDouble, DSNumber, cls, {
    cls->ToString       = DSDouble_ToString;
    cls->CompareTo      = DSDouble_CompareTo;
    cls->IntValue       = DSDouble_IntValue;
    cls->LongValue      = DSDouble_LongValue; 
    cls->FloatValue     = DSDouble_FloatValue; 
    cls->DoubleValue    = DSDouble_DoubleValue;
    cls->CharValue      = DSDouble_CharValue;
    cls->ShortValue     = DSDouble_ShortValue; 
    cls->Create         = $DSDouble;
});

