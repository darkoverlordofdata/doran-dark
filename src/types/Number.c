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
 * Throws AbstractMethodException:
 */
static Exception(AbstractMethod);

/**
 * Abstract Number
 * Initialize a new Number
 */
struct Number * Number_Ctor(struct Number * const this)
{
    Comparable_Ctor(this);
    this->isa = isa(Number);
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
int Number_CompareTo(struct Number * this, struct Number * other) {
    return this->isa->CompareTo(this, other);
}
static short Abstract_CompareTo(struct Number * const this, struct Number * other) {
    return AbstractMethodException("Number_CompareTo");
}

/**
 * Returns the value of this value cast as an int
 */
int overload IntValue(struct Number * const this) {
    return this->isa->IntValue(this);
}
static int Abstract_IntValue(struct Number * const this) {
    return AbstractMethodException("Number_IntValue");
}

/**
 * Returns the value of this value cast as an long
 */
long LongValue(struct Number * const this) {
    return this->isa->LongValue(this);
}
static long Abstract_LongValue(struct Number * const this) {
    return AbstractMethodException("Number_LongValue");
}

/**
 * Returns the value of this value cast as an float
 */
float overload FloatValue(struct Number * const this) {
    return this->isa->FloatValue(this);
}
static float Abstract_FloatValue(struct Number * const this) {
    return AbstractMethodException("Number_FloatValue");
}

/**
 * Returns the value of this value cast as an double
 */
double overload DoubleValue(struct Number * const this) {
    return this->isa->DoubleValue(this);
}
static double Abstract_DoubleValue(struct Number * const this) {
    return AbstractMethodException("Number_DoubleValue");
}

/**
 * Returns the value of this value cast as an char
 */
char overload CharValue(struct Number * const this) {
    return this->isa->CharValue(this);
}
static char Abstract_CharValue(struct Number * const this) {
    return AbstractMethodException("Number_CharValue");
}

/**
 * Returns the value of this value cast as an short
 */
short overload ShortValue(struct Number * const this) {
    return this->isa->ShortValue(this);
}
static short Abstract_ShortValue(struct Number * const this) {
    return AbstractMethodException("Number_ShortValue");
}


char* overload ToString(struct Number * const this) {
    return this->isa->ToString(this);
}
static char* Virtual_ToString(struct Number * const this) {
    return "dark.Number";
}

bool Number_Equals(struct Number * const this, struct Number * const other) {
    return this->isa->Equals(this, other);
}
static char* Virtual_Equals(struct Number * const this, struct Number * const other) {
    return true;
}

/**
 * Number Class Metadata
 */
register (Number)
{
    if (Number.isa == nullptr) {
        Number = (struct NumberClass) {
            .isa            = &Number,
            .superclass     = &Comparable,
            .name           = "Number",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .CompareTo      = Number_CompareTo,
            .ToString       = Virtual_ToString,
            .Equals         = Virtual_Equals,
            .CompareTo      = Abstract_CompareTo,
            .IntValue       = Abstract_IntValue, 
            .LongValue      = Abstract_LongValue, 
            .FloatValue     = Abstract_FloatValue, 
            .DoubleValue    = Abstract_DoubleValue, 
            .CharValue      = Abstract_CharValue, 
            .ShortValue     = Abstract_ShortValue 
        };
        AddMetadata(Number);
    }
    return &Number;
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

