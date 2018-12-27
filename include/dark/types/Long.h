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
#ifndef _LONG_H_
#define _LONG_H_
#include "Number.h"

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

#define IsLong(x) (x->isa == &Long)
#define AsLong(x) (IsLong(x) ? (struct Long *)x : nullptr)

/**
 * Object class
 */
class (Long) 
{
    struct LongClass * isa;
    long value;
};

/**
 * Object metaclass
 */
struct LongClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (struct Long *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Long *  (*Create) (long);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Long *const);
            long    (*LongValue) (struct Long *const);
            float   (*FloatValue) (struct Long *const);
            double  (*DoubleValue) (struct Long *const);
            char    (*CharValue) (struct Long *const);
            short   (*ShortValue) (struct Long *const);
        };
    };
};

long Long_ParseLong(char *const, int);
int Long_CompareTo(struct Long *const, struct Long *const);
int Long_IntValue(struct Long *const);
long Long_LongValue(struct Long *const);
float Long_FloatValue(struct Long *const);
double Long_DoubleValue(struct Long *const);
char Long_CharValue(struct Long *const);
short Long_ShortValue(struct Long *const);

#endif _LONG_H_
