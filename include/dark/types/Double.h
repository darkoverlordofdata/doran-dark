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
    struct DoubleClass *isa;
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
            struct  Class *isa;
            struct  Class *superclass;
            char*   name;
            char*   (*ToString) (struct Double *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Double *(*Create) (double value);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Double *const);
            long    (*LongValue) (struct Double *const);
            float   (*FloatValue) (struct Double *const);
            double  (*DoubleValue) (struct Double *const);
            char    (*CharValue) (struct Double *const);
            short   (*ShortValue) (struct Double *const);
        };
    };
};


int Double_CompareTo(struct Double *const, struct Double *const);
int Double_IntValue(struct Double *const);
long Double_LongValue(struct Double *const);
float Double_FloatValue(struct Double *const);
double Double_DoubleValue(struct Double *const);
char Double_CharValue(struct Double *const);
short Double_ShortValue(struct Double *const);

#endif _DOUBLE_H_
