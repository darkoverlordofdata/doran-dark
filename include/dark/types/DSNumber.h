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
#ifndef _DSNUMBER_H_
#define _DSNUMBER_H_
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../DSObject.h"
#include "../DSComparable.h"

#define NUMBER_MIN_RADIX 2
#define NUMBER_MAX_RADIX 36

#define IsDSNumber(x) (x->isa == &DSNumberClass)
#define AsDSNumber(x) (IsDSNumber(x) ? (DSNumber *)x : nullptr)

/**
 * Object class
 */
class (DSNumber) 
{
    struct DSNumberClass* isa;
};

/**
 * Object metaclass
 */
struct DSNumberClass
{
    union {
        struct DSObject base;
        struct 
        {
            struct  Class* isa;
            struct  Class* superclass;
            char*   name;
            char*   (*ToString) (DSNumber* const);
            bool    (*Equals) (DSObject* const, DSObject* const);
            int     (*GetHashCode) (DSObject* const);
            void    (*Dispose) (DSObject* const);
            bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
            bool    (*InstanceEquals) (DSObject* const, DSObject* const);
            DSNumber* (*Create) ();
            int     (*CompareTo) (DSComparable* const, DSComparable*);
        };
    };
    int     (*IntValue) (DSNumber* const);
    long    (*LongValue) (DSNumber* const);
    float   (*FloatValue) (DSNumber* const);
    double  (*DoubleValue) (DSNumber* const);
    char    (*CharValue) (DSNumber* const);
    short   (*ShortValue) (DSNumber* const);
    
} DSNumberClass;


int Number_CompareTo(DSNumber* const, DSNumber*);
bool Number_Equals(DSNumber* const, DSNumber*);
int Number_IntValue(DSNumber* const);
long LongValue(DSNumber* const);
float Number_FloatValue(DSNumber* const);
double Number_DoubleValue(DSNumber* const);
char Number_CharValue(DSNumber* const);
short Number_ShortValue(DSNumber* const);
int Number_Digit(char, int);

#endif _DSNUMBER_H_
