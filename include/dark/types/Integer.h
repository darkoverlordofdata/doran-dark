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
#ifndef _INTEGER_H_
#define _INTEGER_H_
#include "Number.h"


#define INTEGER_MIN_VALUE  INT_MIN
#define INTEGER_MAX_VALUE  INT_MAX
#define INTEGER_BYTES      (sizeof(int))
#define INTEGER_SIZE       (INTEGER_BYTES * CHAR_BIT)
#define INTEGER_TYPE       (TYPE_LONG)

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
            char*   (*ToString) (TInteger const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*IntValue) (TInteger const);
            long    (*LongValue) (TInteger const);
            float   (*FloatValue) (TInteger const);
            double  (*DoubleValue) (TInteger const);
            char    (*CharValue) (TInteger const);
            short   (*ShortValue) (TInteger const);
        };
    };
};

int Integer_ParseInt(char* s, int radix);
int Integer_CompareTo(TInteger const, TInteger other);
int Integer_IntValue(TInteger const);
long Integer_LongValue(TInteger const);
int Integer_IntegerValue(TInteger const);
double Integer_DoubleValue(TInteger const);
char Integer_CharValue(TInteger const);
short Integer_ShortValue(TInteger const);
TInteger Integer_New(int value);
TInteger Integer_Ctor(TInteger const this, int value);

#endif _INTEGER_H_
