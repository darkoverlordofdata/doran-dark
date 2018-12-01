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
static short Abstract_CompareTo(Number const this, Number other) {
    return AbstractMethodException("Number_CompareTo");
}

/**
 * Returns the value of this value cast as an int
 */
int Number_IntValue(Number const this) {
    return this->IntValue(this);
}
static int Abstract_IntValue(Number const this) {
    return AbstractMethodException("Number_IntValue");
}

/**
 * Returns the value of this value cast as an long
 */
long Number_LongValue(Number const this) {
    return this->LongValue(this);
}
static long Abstract_LongValue(Number const this) {
    return AbstractMethodException("Number_LongValue");
}

/**
 * Returns the value of this value cast as an float
 */
float Number_FloatValue(Number const this) {
    return this->FloatValue(this);
}
static float Abstract_FloatValue(Number const this) {
    return AbstractMethodException("Number_FloatValue");
}

/**
 * Returns the value of this value cast as an double
 */
double Number_DoubleValue(Number const this) {
    return this->DoubleValue(this);
}
static double Abstract_DoubleValue(Number const this) {
    return AbstractMethodException("Number_DoubleValue");
}

/**
 * Returns the value of this value cast as an char
 */
char Number_CharValue(Number const this) {
    return this->CharValue(this);
}
static char Abstract_CharValue(Number const this) {
    return AbstractMethodException("Number_CharValue");
}

/**
 * Returns the value of this value cast as an short
 */
short Number_ShortValue(Number const this) {
    return this->ShortValue(this);
}
static short Abstract_ShortValue(Number const this) {
    return AbstractMethodException("Number_ShortValue");
}


char* Number_ToString(Number const this) {
    return this->ToString(this);
}
static char* Virtual_ToString(Number const this) {
    return "dark.Number";
}

/**
 * Initialize a new Number
 */
Number Number_Ctor(Number const this)
{
    Comparable_Ctor(this);

    this->ToString      = &Virtual_ToString;
    this->CompareTo     = &Abstract_CompareTo;
    this->IntValue      = &Abstract_IntValue; 
    this->LongValue     = &Abstract_LongValue; 
    this->FloatValue    = &Abstract_FloatValue; 
    this->DoubleValue   = &Abstract_DoubleValue; 
    this->CharValue     = &Abstract_CharValue; 
    this->ShortValue    = &Abstract_ShortValue; 

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

