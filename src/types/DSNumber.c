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
#include <dark/types/DSNumber.h>
/* 
 * Throws DSAbstractMethodException:
 */
static DSException(AbstractMethod);
$implementation(DSNumber); 

$method(ToString,   DSNumber_ToString, "$@:v");
$method(CompareTo,  DSNumber_CompareTo, "i@:@");
$method(IntValue,   DSNumber_IntValue, "i@:v");
$method(LongValue,  DSNumber_LongValue, "l@:v");
$method(FloatValue, DSNumber_FloatValue, "f@:v");
$method(DoubleValue, DSNumber_DoubleValue, "d@:v");
$method(CharValue,  DSNumber_CharValue, "c@:v");
$method(ShortValue, DSNumber_ShortValue, "s@:v");

$end;

/**
 * Abstract Number
 * Initialize a new Number
 */
DSNumber* DSNumber_init(DSNumber* const this)
{
    DSComparable_init(this);
    this->isa = objc_getClass("DSNumber");
    return this;
}

/**
 * Compares two Number objects.
 *
 * @param   other  Short to be compared
 * @return  0 this == other
 *         +1 this < other
 *         -1 this > other
 */
int overload CompareTo(DSNumber* this, DSNumber* other) {
    return DSNumberVTable.CompareTo(this, other);
}
int DSNumber_CompareTo(DSNumber* const this, DSNumber* other) {
    return DSAbstractMethodException("Number_CompareTo");
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(DSNumber* const this) {
    return DSNumberVTable.IntValue(this);
}
int DSNumber_IntValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_IntValue");
}

/**
 * Returns the value of this value cast as an long
 */
long LongValue(DSNumber* const this) {
    return DSNumberVTable.LongValue(this);
}
long DSNumber_LongValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_LongValue");
}

/**
 * Returns the value of this value cast as an float
 */
float overload FloatValue(DSNumber* const this) {
    return DSNumberVTable.FloatValue(this);
}
float DSNumber_FloatValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_FloatValue");
}

/**
 * Returns the value of this value cast as an double
 */
double overload DoubleValue(DSNumber* const this) {
    return DSNumberVTable.DoubleValue(this);
}
double DSNumber_DoubleValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_DoubleValue");
}

/**
 * Returns the value of this value cast as an char
 */
char overload CharValue(DSNumber* const this) {
    return DSNumberVTable.CharValue(this);
}
char DSNumber_CharValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_CharValue");
}

/**
 * Returns the value of this value cast as an short
 */
short overload ShortValue(DSNumber* const this) {
    return DSNumberVTable.ShortValue(this);
}
short DSNumber_ShortValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_ShortValue");
}


char* overload ToString(const DSNumber* const this) {
    return DSNumberVTable.ToString(this);
}
char* DSNumber_ToString(const DSNumber* const this) {
    return "dark.Number";
}

bool overload Equals(DSNumber* const this, DSNumber* const other) {
    return DSNumberVTable.Equals(this, other);
}
bool DSNumber_Equals(DSNumber* const this, DSNumber* const other) {
    return true;
}


/**
 * char table for radix up to 36
 */
int Number_Digit(char ch, int radix) 
{
    static const char Digits [] = 
    {
        '0' , '1' , '2' , '3' , '4' , '5' ,
        '6' , '7' , '8' , '9' , 'a' , 'b' ,
        'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
        'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
        'o' , 'p' , 'q' , 'r' , 's' , 't' ,
        'u' , 'v' , 'w' , 'x' , 'y' , 'z'
    };
    
    for (int i=0; i<radix; i++)
        if (ch == Digits[i])
            return i;
            
    return -1;
}

