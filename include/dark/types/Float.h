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
#ifndef _FLOAT_H_
#define _FLOAT_H_
#include "Number.h"

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

#define IsFloat(x) (x->isa == &Float)
#define AsFloat(x) (IsFloat(x) ? (struct Float *)x : nullptr)

/**
 * Object class
 */
class (Float) 
{
    struct FloatClass * isa;
    float value;
};

/**
 * Object metaclass
 */
struct FloatClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (struct Float *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Float * (*Create) (float value);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Float *const);
            long    (*LongValue) (struct Float *const);
            float   (*FloatValue) (struct Float *const);
            double  (*DoubleValue) (struct Float *const);
            char    (*CharValue) (struct Float *const);
            short   (*ShortValue) (struct Float *const);
        };
    };
};


int Float_CompareTo(struct Float *const, struct Float *const);
int Float_IntValue(struct Float *const);
long Float_LongValue(struct Float *const);
float Float_FloatValue(struct Float *const);
float Float_FloatValue(struct Float *const);
char Float_CharValue(struct Float *const);
short Float_ShortValue(struct Float *const);

#endif _FLOAT_H_
