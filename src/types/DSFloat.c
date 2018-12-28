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
#include <dark/types/DSFloat.h>
/* 
 * Throws NumberFormatException:
 */
static Exception(NumberFormat);

/**
 * Constructor
 * create a new Float
 * 
 * @param value of float
 * 
 */
DSFloat* DSFloat_Ctor(DSFloat* const this, float value)
{
    DSNumber_Ctor(this);
    this->isa = isa(DSFloat);
    this->value = value;
    return this;
}


/**
 * Returns a primitive float value parsed from input string. 
 */
float DSFloat_ParseFloat(char* s)
{
    
    double d = DSDouble_ParseDouble(s);
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
int DSFloat_Compare(float x, float y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Float objects.
 *
 * @param   other  Float to be compared
 * @return same as DSFloat_Compare
 */
int DSFloat_CompareTo(DSFloat* this, DSFloat* other) {
    return DSFloat_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int DSFloat_IntValue(DSFloat* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long DSFloat_LongValue(DSFloat* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double DSFloat_DoubleValue(DSFloat* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float DSFloat_FloatValue(DSFloat* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char DSFloat_CharValue(DSFloat* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short DSFloat_ShortValue(DSFloat* const this) {
    return (short)this->value;
}


char* DSFloat_ToString(DSFloat* const this)
{
    static char str[20];
    sprintf(str, "%f", this->value);
    return str;
}

DSFloat* $DSFloat(float value) { 
    return DSFloat_Ctor(new(DSFloat), value); 
}

/**
 * Float Class Metadata
 */
register (DSFloat)
{
    if (DSFloatClass.isa == nullptr) {
        DSFloatClass = (struct DSFloatClass) {
            .isa            = &DSFloatClass,
            .superclass     = &DSNumberClass,
            .name           = "DSFloat",
            .Create         = $DSFloat,
            .Equals         = DSObjectClass.Equals,
            .GetHashCode    = DSObjectClass.GetHashCode,
            .Dispose        = DSObjectClass.Dispose,
            .ReferenceEquals= DSObjectClass.ReferenceEquals,
            .InstanceEquals = DSObjectClass.InstanceEquals,
            .ToString       = DSFloat_ToString,
            .CompareTo      = DSFloat_CompareTo,
            .IntValue       = DSFloat_IntValue, 
            .LongValue      = DSFloat_LongValue, 
            .FloatValue     = DSFloat_FloatValue, 
            .DoubleValue    = DSFloat_DoubleValue, 
            .CharValue      = DSFloat_CharValue, 
            .ShortValue     = DSFloat_ShortValue, 
        };
        AddMetadata(DSFloatClass);
    }
    return &DSFloatClass;
}


