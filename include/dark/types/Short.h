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
#ifndef _SHORT_H_
#define _SHORT_H_
#include "Number.h"

#define SHORT_MIN_VALUE  SHRT_MIN
#define SHORT_MAX_VALUE  SHRT_MAX
#define SHORT_BYTES      (sizeof(short))
#define SHORT_SIZE       (SHORT_BYTES * CHAR_BIT)
#define SHORT_TYPE       (TYPE_SHORT)

#define IsShort(x) (x->isa == &Short)
#define AsShort(x) (IsShort(x) ? (struct Short *)x : nullptr)

/**
 * Object class
 */
class (Short) 
{
    struct ShortClass * isa;
    short value;
};

/**
 * Object metaclass
 */
struct ShortClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (struct Short *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Short * (*Create) (short value);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Short *const);
            long    (*LongValue) (struct Short *const);
            float   (*FloatValue) (struct Short *const);
            double  (*DoubleValue) (struct Short *const);
            char    (*CharValue) (struct Short *const);
            short   (*ShortValue) (struct Short *const);
        };
    };
};

short Short_ParseShort(char const *const s, int radix);
int Short_CompareTo(struct Short *const, struct Short *const);
int Short_IntValue(struct Short *const);
long Short_LongValue(struct Short *const);
float Short_FloatValue(struct Short *const);
double Short_DoubleValue(struct Short *const);
char Short_CharValue(struct Short *const);
short Short_ShortValue(struct Short *const);

#endif _SHORT_H_
