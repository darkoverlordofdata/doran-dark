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
#include <dark/types/DSLong.h>
/* 
 * Throws LongFormatException:
 */
static DSException(LongFormat);
begin_class(DSLong)

    method("ToString", DSLong_ToString, "$@:v");
    method("CompareTo", DSLong_CompareTo, "i@:@");
    method("IntValue", DSLong_IntValue, "i@:v");
    method("LongValue", DSLong_LongValue, "l@:v");
    method("FloatValue", DSLong_FloatValue, "f@:v");
    method("DoubleValue", DSLong_DoubleValue, "d@:v");
    method("CharValue", DSLong_CharValue, "c@:v");
    method("ShortValue", DSLong_ShortValue, "s@:v");

    ivar("value", sizeof(long), "l");

end_class

/**
 * Constructor
 * create a new Long
 * 
 * @param value of long
 * 
 */
DSLong* DSLong_init(DSLong* const this, long value)
{
    DSNumber_init(this);
    this->isa = ISA(DSLong);
    this->value = value;
    return this;
}

/**
 * Returns a primitive long value parsed from input string. 
 */
long DSParseLong(char* const s, int radix)
{
    errno = 0;
    char* endptr;
    long result = strtol(s, endptr, radix);

    if (errno != 0)
        return DSLongFormatException(
            "Invalid input. Value:\"%s\" Radix: %d", s, radix);

    if (s == endptr || *endptr != '\0')
        return DSLongFormatException(
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
int DSLong_Compare(long x, long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Long objects.
 *
 * @param   other  Long to be compared
 * @return same as DSLong_Compare
 */
int DSLong_CompareTo(DSLong* const this, DSLong* const other) {
    return DSLong_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int DSLong_IntValue(DSLong* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long DSLong_LongValue(DSLong* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float DSLong_FloatValue(DSLong* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double DSLong_DoubleValue(DSLong* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char DSLong_CharValue(DSLong* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short DSLong_ShortValue(DSLong* const this) {
    return (short)this->value;
}

bool DSLong_Equals(DSLong* const this, DSLong* const other)
{
    return this->value == other->value;
}

char* DSLong_ToString(const DSLong* const this)
{
    static char str[20];
    sprintf(str, "%d", this->value);
    return str;
}

DSLong* $DSLong(long value) { 
    printf("DSLong* Create(%d);\n", value);
    return DSLong_init(class_alloc(DSLong), value); 
}

/**
 * Long Class Metadata
 */
DSDefine(DSLong, DSNumber, cls, {
    cls->ToString       = DSLong_ToString;
    cls->CompareTo      = DSLong_CompareTo;
    cls->Equals         = DSLong_Equals;
    cls->IntValue       = DSLong_IntValue;
    cls->LongValue      = DSLong_LongValue; 
    cls->FloatValue     = DSLong_FloatValue; 
    cls->DoubleValue    = DSLong_DoubleValue;
    cls->CharValue      = DSLong_CharValue;
    cls->ShortValue     = DSLong_ShortValue; 
    cls->Create         = $DSLong;
});

