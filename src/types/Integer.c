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
 * Throws: NumberFormatException
 */
static Exception(NumberFormat);

/* 
 * Constructor
 * create a new Integer
 * 
 * @param value of int
 * 
 */
struct Integer * Integer_Ctor(struct Integer * const this, int value)
{
    Number_Ctor(this);
    this->isa = isa(Integer);
    this->value = value;
    return this;
}


/**
 * Returns a primitive integer value parsed from input string. 
 */
int Integer_ParseInt(char* const s, int radix) {
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
int Integer_CompareTo(struct Integer * this, struct Integer * other) {
    return Integer_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Integer_IntValue(struct Integer * const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Integer_LongValue(struct Integer * const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Integer_FloatValue(struct Integer * const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Integer_DoubleValue(struct Integer * const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Integer_CharValue(struct Integer * const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Integer_ShortValue(struct Integer * const this) {
    return (short)this->value;
}


char* Integer_ToString(struct Integer * const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

static struct Integer* Create(int value) { 
    return Integer_Ctor(new(Integer), value); 
}

/**
 * Integer Class Metadata
 */
register (Integer)
{
    if (Integer.isa == nullptr) {
        Integer = (struct IntegerClass) {
            .isa            = &Integer,
            .superclass     = &Number,
            .name           = "Integer",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .ToString       = Integer_ToString,
            .CompareTo      = Integer_CompareTo,
            .IntValue       = Integer_IntValue, 
            .LongValue      = Integer_LongValue, 
            .FloatValue     = Integer_FloatValue, 
            .DoubleValue    = Integer_DoubleValue, 
            .CharValue      = Integer_CharValue, 
            .ShortValue     = Integer_ShortValue, 
            .Create         = Create,
        };
        AddMetadata(Integer);
    }
    return &Integer;
}

