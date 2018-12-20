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
#pragma once
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../Object.h"
#include "../Comparable.h"

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

#define IsNumber(x) (x->isa == &Number)
#define AsNumber(x) (IsNumber(x) ? (struct Number *)x : nullptr)

/**
 * Object class
 */
class (Number) 
{
    struct NumberClass * isa;
};

/**
 * Object metaclass
 */
struct NumberClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class *isa;
            struct  Class *superclass;
            char*   name;
            char*   (*ToString) (TNumber const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TNumber (*Create) ();
            int     (*CompareTo) (TComparable const, TComparable other);
        };
    };
    int     (*IntValue) (TNumber const);
    long    (*LongValue) (TNumber const);
    float   (*FloatValue) (TNumber const);
    double  (*DoubleValue) (TNumber const);
    char    (*CharValue) (TNumber const);
    short   (*ShortValue) (TNumber const);
};


int Number_CompareTo(TNumber const, TNumber other);
bool Number_Equals(TNumber const, TNumber other);
int Number_IntValue(TNumber const);
long LongValue(TNumber const);
float Number_FloatValue(TNumber const);
double Number_DoubleValue(TNumber const);
char Number_CharValue(TNumber const);
short Number_ShortValue(TNumber const);
int Number_Digit(char ch, int radix);

#endif _NUMBER_H_
