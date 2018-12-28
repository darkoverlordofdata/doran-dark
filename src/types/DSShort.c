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
/* 
 * Throws NumberFormatException:
 */
static Exception(NumberFormat);

/**
 * Constructor
 * create a new Short
 * 
 * @param value of short
 * 
 */
DSShort* DSShort_Ctor(DSShort* const this, short value)
{
    DSNumber_Ctor(this);
    this->isa = isa(DSShort);
    this->value = value;
    return this;
}

/**
 * Returns a primitive short value parsed from input string. 
 */
short DSShort_ParseShort(char const *const s, int radix)
{
    long i = DSLong_ParseLong(s, radix);
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
short DSShort_Compare(short x, short y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Short objects.
 *
 * @param   other  Short to be compared
 * @return same as DSShort_Compare
 */
int DSShort_CompareTo(DSShort* this, DSShort* other) {
    return DSShort_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int DSShort_IntValue(DSShort* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long DSShort_LongValue(DSShort* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float DSShort_FloatValue(DSShort* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double DSShort_DoubleValue(DSShort* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char DSShort_CharValue(DSShort* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short DSShort_ShortValue(DSShort* const this) {
    return (short)this->value;
}


char* DSShort_ToString(DSShort* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

DSShort* $DSShort(short value) { 
    return DSShort_Ctor(new(DSShort), value); 
}


/**
 * Short Class Metadata
 */
register (DSShort)
{
    if (DSShortClass.isa == nullptr) {
        DSShortClass = (struct DSShortClass) {
            .isa            = &DSShortClass,
            .superclass     = &DSNumberClass,
            .name           = "DSShort",
            .Create         = $DSShort,
            .Equals         = DSObjectClass.Equals,
            .GetHashCode    = DSObjectClass.GetHashCode,
            .Dispose        = DSObjectClass.Dispose,
            .ReferenceEquals= DSObjectClass.ReferenceEquals,
            .InstanceEquals = DSObjectClass.InstanceEquals,
            .ToString       = DSShort_ToString,
            .CompareTo      = DSShort_CompareTo,
            .IntValue       = DSShort_IntValue, 
            .LongValue      = DSShort_LongValue, 
            .FloatValue     = DSShort_FloatValue, 
            .DoubleValue    = DSShort_DoubleValue, 
            .CharValue      = DSShort_CharValue, 
            .ShortValue     = DSShort_ShortValue, 

        };
        AddMetadata(DSShortClass);
    }
    return &DSShortClass;
}

