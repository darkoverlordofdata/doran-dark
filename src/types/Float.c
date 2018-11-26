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
#include <dark/types/Float.h>
/* 
 * Float implementation
 */
static Exception(NumberFormat);

/**
 * Returns a primitive float value parsed from input string. 
 */
float Float_ParseFloat(char* s)
{
    
    double d = Double_ParseDouble(s);
    if (d < FLOAT_MIN_VALUE || d > FLOAT_MAX_VALUE)
        return NumberFormatException(
            "Value out of range. Value:\"%s\"", s);
    return (float)d;
}

/**
 * Compare two float primitives.
 * @param  x float to compare
 * @param  y float to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
int Float_Compare(float x, float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as Float_Compare
 */
int Float_CompareTo(Float this, Float other) {
    return Float_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Float_IntValue(Float const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Float_LongValue(Float const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Float_DoubleValue(Float const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Float_FloatValue(Float const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Float_CharValue(Float const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Float_ShortValue(Float const this) {
    return (short)this->value;
}


char* Float_ToString(Float const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

/**
 * Initialize a new Float
 */
Float Float_Ctor(Float const this, float value)
{
    Number_Ctor(this);

    this->ToString      = Float_ToString;
    this->CompareTo     = Float_CompareTo;
    this->IntValue      = Float_IntValue; 
    this->LongValue     = Float_LongValue; 
    this->FloatValue    = Float_FloatValue; 
    this->DoubleValue   = Float_DoubleValue; 
    this->CharValue     = Float_CharValue; 
    this->ShortValue    = Float_ShortValue; 

    this->value = value;
    return this;
}

/**
 * new Float
 * 
 * create a new Float
 * 
 * @param value of float
 * 
 */
Float Float_New(float value)
{
    return Float_Ctor(new(Float), value);
}
