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


int Number_CompareTo(Number this, Number other) {
    return this->CompareTo(this, other);
}
static short abstract_CompareTo(Number const this, Number other) {
    printf("abstract_CompareTo\n");
    return 0;
}

/**
 * Returns the value of this {@code Number} as an {@code int} after
 * a narrowing primitive conversion.
 */
int Number_IntValue(Number const this) {
    return this->IntValue(this);
}
static short abstract_IntValue(Number const this) {
    printf("abstract_IntValue\n");
    return 0;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code long} value.
 */
long Number_LongValue(Number const this) {
    printf("virtual_LongValue\n");
    return this->LongValue(this);
}
static short abstract_LongValue(Number const this) {
    printf("abstract_LongValue\n");
    return 0;
}

/**
 * Returns the value of this {@code Number} as a {@code float} after
 * a widening primitive conversion.
 */
float Number_FloatValue(Number const this) {
    return this->FloatValue(this);
}
static short abstract_FloatValue(Number const this) {
    printf("abstract_FloatValue\n");
    return 0;
}

/**
 * Returns the value of this {@code Number} as a {@code double}
 * after a widening primitive conversion.
 */
double Number_DoubleValue(Number const this) {
    return this->DoubleValue(this);
}
static short abstract_DoubleValue(Number const this) {
    printf("abstract_DoubleValue\n");
    return 0;
}

/**
 * Returns the value of this {@code Number} as a {@code byte} after
 * a narrowing primitive conversion.
 */
char Number_CharValue(Number const this) {
    return this->CharValue(this);
}
static short abstract_CharValue(Number const this) {
    printf("abstract_CharValue\n");
    return 0;
}

/**
 * Returns the value of this {@code Number} as a {@code short} after
 * a narrowing primitive conversion.
 */
short Number_ShortValue(Number const this) {
    return this->ShortValue(this);
}
static short abstract_ShortValue(Number const this) {
    printf("abstract_ShortValue\n");
    return 0;
}


char* Number_ToString(Number const this) {
    return this->ToString(this);
}
static char* abstract_ToString(Number const this) {
    return "Dark.Number";
}

/**
 * Initialize a new Number
 */
Number Number_Ctor(Number const this)
{
    Comparable_Ctor(this);

    this->ToString      = &abstract_ToString;
    this->CompareTo     = &abstract_CompareTo;
    this->IntValue      = &abstract_IntValue; 
    this->LongValue     = &abstract_LongValue; 
    this->FloatValue    = &abstract_FloatValue; 
    this->DoubleValue   = &abstract_DoubleValue; 
    this->CharValue     = &abstract_CharValue; 
    this->ShortValue    = &abstract_ShortValue; 

    return this;
}

