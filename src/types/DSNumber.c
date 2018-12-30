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

/**
 * Abstract Number
 * Initialize a new Number
 */
DSNumber* DSNumber_init(DSNumber* const this)
{
    DSComparable_init(this);
    this->isa = ISA(DSNumber);
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
int DSNumber_CompareTo(DSNumber* this, DSNumber* other) {
    return this->isa->CompareTo(this, other);
}
static short Abstract_CompareTo(DSNumber* const this, DSNumber* other) {
    return DSAbstractMethodException("Number_CompareTo");
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(DSNumber* const this) {
    return this->isa->IntValue(this);
}
static int Abstract_IntValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_IntValue");
}

/**
 * Returns the value of this value cast as an long
 */
long LongValue(DSNumber* const this) {
    return this->isa->LongValue(this);
}
static long Abstract_LongValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_LongValue");
}

/**
 * Returns the value of this value cast as an float
 */
float overload FloatValue(DSNumber* const this) {
    return this->isa->FloatValue(this);
}
static float Abstract_FloatValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_FloatValue");
}

/**
 * Returns the value of this value cast as an double
 */
double overload DoubleValue(DSNumber* const this) {
    return this->isa->DoubleValue(this);
}
static double Abstract_DoubleValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_DoubleValue");
}

/**
 * Returns the value of this value cast as an char
 */
char overload CharValue(DSNumber* const this) {
    return this->isa->CharValue(this);
}
static char Abstract_CharValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_CharValue");
}

/**
 * Returns the value of this value cast as an short
 */
short overload ShortValue(DSNumber* const this) {
    return this->isa->ShortValue(this);
}
static short Abstract_ShortValue(DSNumber* const this) {
    return DSAbstractMethodException("Number_ShortValue");
}


char* overload ToString(DSNumber* const this) {
    return this->isa->ToString(this);
}
static char* Virtual_ToString(DSNumber* const this) {
    return "dark.Number";
}

bool Number_Equals(DSNumber* const this, DSNumber* const other) {
    return this->isa->Equals(this, other);
}
static bool Virtual_Equals(DSObject* const this, DSObject* const other) {
    return true;
}

/**
 * DSNumber Class Metadata
 */
DSDefine(DSNumber, DSObject, cls, {
    cls->CompareTo      = DSNumber_CompareTo;
    cls->CompareTo      = DSNumber_CompareTo;
    cls->ToString       = Virtual_ToString;
    cls->Equals         = Virtual_Equals;
    cls->CompareTo      = Abstract_CompareTo;
    cls->IntValue       = Abstract_IntValue; 
    cls->LongValue      = Abstract_LongValue; 
    cls->FloatValue     = Abstract_FloatValue; 
    cls->DoubleValue    = Abstract_DoubleValue; 
    cls->CharValue      = Abstract_CharValue; 
    cls->ShortValue     = Abstract_ShortValue;
});

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

