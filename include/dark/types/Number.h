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
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../DObject.h"
#include "../Comparable.h"

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

class (Number)
{
    union {
        Comparable_t _;
        struct 
        {
            retained
            char*       (*ToString)(DObject const);
            bool        (*Equals)(DObject const, DObject const);
            int         (*GetHashCode)(DObject const);
            void        (*Dispose) (DObject const);
            int         (*CompareTo) (Comparable const, DObject other);
        };
    };
    int             (*IntValue) (Number const);
    long            (*LongValue) (Number const);
    float           (*FloatValue) (Number const);
    double          (*DoubleValue) (Number const);
    char            (*CharValue) (Number const);
    short           (*ShortValue) (Number const);
};


int Number_CompareTo(Number const, Number other);
int Number_IntValue(Number const);
long Number_LongValue(Number const);
float Number_FloatValue(Number const);
double Number_DoubleValue(Number const);
char Number_CharValue(Number const);
short Number_ShortValue(Number const);
int Number_Digit(char ch, int radix);

#endif _NUMBER_H_
