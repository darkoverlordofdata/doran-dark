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
#include <dark/types/Number.h>

/* 
 * Abstract Number
 */
static Exception(AbstractMethod);


/**
 * Compares two Number objects.
 *
 * @param   other  Short to be compared
 * @return  0 this == other
 *         +1 this < other
 *         -1 this > other
 */
int Number_CompareTo(Number this, Number other) {
    return this->CompareTo(this, other);
}
static short abstract_CompareTo(Number const this, Number other) {
    return AbstractMethodException("Number_CompareTo");
}

/**
 * Returns the value of this value cast as an int
 */
int Number_IntValue(Number const this) {
    return this->IntValue(this);
}
static int abstract_IntValue(Number const this) {
    return AbstractMethodException("Number_IntValue");
}

/**
 * Returns the value of this value cast as an long
 */
long Number_LongValue(Number const this) {
    return this->LongValue(this);
}
static long abstract_LongValue(Number const this) {
    return AbstractMethodException("Number_LongValue");
}

/**
 * Returns the value of this value cast as an float
 */
float Number_FloatValue(Number const this) {
    return this->FloatValue(this);
}
static float abstract_FloatValue(Number const this) {
    return AbstractMethodException("Number_FloatValue");
}

/**
 * Returns the value of this value cast as an double
 */
double Number_DoubleValue(Number const this) {
    return this->DoubleValue(this);
}
static double abstract_DoubleValue(Number const this) {
    return AbstractMethodException("Number_DoubleValue");
}

/**
 * Returns the value of this value cast as an char
 */
char Number_CharValue(Number const this) {
    return this->CharValue(this);
}
static char abstract_CharValue(Number const this) {
    return AbstractMethodException("Number_CharValue");
}

/**
 * Returns the value of this value cast as an short
 */
short Number_ShortValue(Number const this) {
    return this->ShortValue(this);
}
static short abstract_ShortValue(Number const this) {
    return AbstractMethodException("Number_ShortValue");
}


char* Number_ToString(Number const this) {
    return this->ToString(this);
}
static char* virtual_ToString(Number const this) {
    return "dark.Number";
}

/**
 * Initialize a new Number
 */
Number Number_Ctor(Number const this)
{
    Comparable_Ctor(this);

    this->ToString      = virtual_ToString;
    this->CompareTo     = abstract_CompareTo;
    this->IntValue      = abstract_IntValue; 
    this->LongValue     = abstract_LongValue; 
    this->FloatValue    = abstract_FloatValue; 
    this->DoubleValue   = abstract_DoubleValue; 
    this->CharValue     = abstract_CharValue; 
    this->ShortValue    = abstract_ShortValue; 

    return this;
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

