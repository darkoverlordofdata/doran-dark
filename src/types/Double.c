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
#include <dark/types/Double.h>
/* 
 * Throws NumberFormatException:
 */
static Exception(NumberFormat);

/**
 * Constructor
 * create a new Double
 * 
 * @param value of double
 * 
 */
TDouble Double_New(double value) {
    return Double_Ctor(new(Double), value);
}

/**
 * Initialize a new Double
 */
TDouble Double_Ctor(TDouble const this, double value)
{
    Number_Ctor(this);
    this->isa = isa(Double);
    this->value = value;
    return this;
}

/**
 * Returns a primitive double value parsed from input string. 
 */
double Double_ParseDouble(char* s)
{
    errno = 0;
    char* endptr;
    double result = strtod(s, endptr);

    if (errno != 0)
        return NumberFormatException(
            "Invalid input. Value:\"%s\"", s);

    if (s == endptr || *endptr != '\0')
        return NumberFormatException(
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
int Double_Compare(double x, double y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Double objects.
 *
 * @param   other  Double to be compared
 * @return same as Double_Compare
 */
int Double_CompareTo(TDouble this, TDouble other) {
    return Double_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Double_IntValue(TDouble const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Double_LongValue(TDouble const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Double_FloatValue(TDouble const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Double_DoubleValue(TDouble const this) {
    return this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Double_CharValue(TDouble const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Double_ShortValue(TDouble const this) {
    return (short)this->value;
}


char* Double_ToString(TDouble const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

/**
 * Double Class Metadata
 */
register (Double)
{
    if (Double.isa == nullptr) {
        Double = (struct DoubleClass) {
            .isa            = &Double,
            .superclass     = &Number,
            .name           = "Double",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .ToString       = Double_ToString,
            .CompareTo      = Double_CompareTo,
            .IntValue       = Double_IntValue, 
            .LongValue      = Double_LongValue, 
            .FloatValue     = Double_FloatValue, 
            .DoubleValue    = Double_DoubleValue, 
            .CharValue      = Double_CharValue, 
            .ShortValue     = Double_ShortValue, 
        };
        // AddMetadata(Double);
    }
    return &Double;
}

