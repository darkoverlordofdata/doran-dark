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
#ifndef _INTEGER_H_
#define _INTEGER_H_
#include "Number.h"


#define INTEGER_MIN_VALUE  INT_MIN
#define INTEGER_MAX_VALUE  INT_MAX
#define INTEGER_BYTES      (sizeof(int))
#define INTEGER_SIZE       (INTEGER_BYTES * CHAR_BIT)
#define INTEGER_TYPE       (TYPE_LONG)

#define IsInteger(x) (x->isa == &Integer)
#define AsInteger(x) (IsInteger(x) ? (struct Integer *)x : nullptr)

/**
 * Object class
 */
class (Integer) 
{
    struct IntegerClass* isa;
    int        value;
};

/**
 * Object metaclass
 */
struct IntegerClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (struct Integer *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            TInteger(*Create) (int value);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Integer *const);
            long    (*LongValue) (struct Integer *const);
            float   (*FloatValue) (struct Integer *const);
            double  (*DoubleValue) (struct Integer *const);
            char    (*CharValue) (struct Integer *const);
            short   (*ShortValue) (struct Integer *const);
        };
    };
};

int Integer_ParseInt(char *const, int);
int Integer_CompareTo(struct Integer *const, struct Integer *const);
int Integer_IntValue(struct Integer *const);
long Integer_LongValue(struct Integer *const);
int Integer_IntegerValue(struct Integer *const);
double Integer_DoubleValue(struct Integer *const);
char Integer_CharValue(struct Integer *const);
short Integer_ShortValue(struct Integer *const);

#endif _INTEGER_H_
