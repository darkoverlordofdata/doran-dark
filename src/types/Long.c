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
 * Throws LongFormatException:
 */
static Exception(LongFormat);

/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
TLong Long_Ctor(TLong const this, long value)
{
    Number_Ctor(this);
    this->isa = isa(Long);
    this->value = value;
    return this;
}

/**
 * Returns a primitive long value parsed from input string. 
 */
long Long_ParseLong(char* s, int radix)
{
    errno = 0;
    char* endptr;
    long result = strtol(s, endptr, radix);

    if (errno != 0)
        return LongFormatException(
            "Invalid input. Value:\"%s\" Radix: %d", s, radix);

    if (s == endptr || *endptr != '\0')
        return LongFormatException(
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
int Long_CompareTo(TLong this, TLong other) {
    return Long_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Long_IntValue(TLong const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Long_LongValue(TLong const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Long_FloatValue(TLong const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Long_DoubleValue(TLong const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Long_CharValue(TLong const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Long_ShortValue(TLong const this) {
    return (short)this->value;
}

bool Long_Equals(TLong const this, TLong const other)
{
    return this->value == other->value;
}

char* Long_ToString(TLong const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

static struct Long* Create(long value) { 
    return Long_Ctor(new(Long), value); 
}

/**
 * Long Class Metadata
 */
register (Long)
{
    if (Long.isa == nullptr) {
        Long = (struct LongClass) {
            .isa            = &Long,
            .superclass     = &Number,
            .name           = "Long",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .Equals         = Long_Equals,
            .ToString       = Long_ToString,
            .CompareTo      = Long_CompareTo,
            .IntValue       = Long_IntValue, 
            .LongValue      = Long_LongValue, 
            .FloatValue     = Long_FloatValue, 
            .DoubleValue    = Long_DoubleValue, 
            .CharValue      = Long_CharValue, 
            .ShortValue     = Long_ShortValue, 
            .Create         = Create,
        };
        AddMetadata(Long);
    }
    return &Long;
}

