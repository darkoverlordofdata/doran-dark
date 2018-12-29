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
#include <dark/types/DSChar.h>
/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
DSChar* DSChar_Ctor(DSChar* const this, char value)
{
    DSNumber_Ctor(this);
    this->isa = isa(DSChar);
    this->value = value;
    return this;
}

DSChar* $DSChar(char value) { 
    return DSChar_Ctor(DSNew(DSChar), value); 
}

/**
 * Char Class Metadata
 */
DSDefine(DSChar, DSNumber, cls, {
    cls->ToString       = DSChar_ToString;
    cls->CompareTo      = DSChar_CompareTo;
    cls->IntValue       = DSChar_IntValue;
    cls->LongValue      = DSChar_LongValue; 
    cls->FloatValue     = DSChar_FloatValue; 
    cls->DoubleValue    = DSChar_DoubleValue;
    cls->CharValue      = DSChar_CharValue;
    cls->ShortValue     = DSChar_ShortValue; 
    cls->Create         = $DSChar;
});

/**
 * Compare two char primitives.
 * @param  x char to compare
 * @param  y char to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
int DSChar_Compare(char x, char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as DSChar_Compare
 */
int DSChar_CompareTo(DSChar* const this, DSChar* const other) {
    return DSChar_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int DSChar_IntValue(DSChar* const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long DSChar_LongValue(DSChar* const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float DSChar_FloatValue(DSChar* const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double DSChar_DoubleValue(DSChar* const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char DSChar_CharValue(DSChar* const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short DSChar_ShortValue(DSChar* const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
char* DSChar_ToString(DSChar* const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}


