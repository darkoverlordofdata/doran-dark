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
#ifndef _DOUBLE_H_
#define _DOUBLE_H_
#include "Number.h"

#define DOUBLE_MIN_VALUE  DBL_MIN
#define DOUBLE_MAX_VALUE  DBL_MAX
#define DOUBLE_BYTES      (sizeof(double))
#define DOUBLE_SIZE       (DOUBLE_BYTES * CHAR_BIT)
#define DOUBLE_TYPE       (TYPE_DOUBLE)

#define IsDouble(x) (x->isa == &Double)
#define AsDouble(x) (IsDouble(x) ? (struct Double *)x : nullptr)

/**
 * Double class
 */
class (Double) 
{
    struct DoubleClass * isa;
    double value;
};

/**
 * Double metaclass
 */
struct DoubleClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TDouble const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TDouble (*Create) (double value);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*IntValue) (TDouble const);
            long    (*LongValue) (TDouble const);
            float   (*FloatValue) (TDouble const);
            double  (*DoubleValue) (TDouble const);
            char    (*CharValue) (TDouble const);
            short   (*ShortValue) (TDouble const);
        };
    };
};


int Double_CompareTo(TDouble const, TDouble other);
int Double_IntValue(TDouble const);
long Double_LongValue(TDouble const);
float Double_FloatValue(TDouble const);
double Double_DoubleValue(TDouble const);
char Double_CharValue(TDouble const);
short Double_ShortValue(TDouble const);
TDouble Double_New(double value);
TDouble Double_Ctor(TDouble const this, double value);

#endif _DOUBLE_H_
