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
#ifndef _LONG_H_
#define _LONG_H_
#include "Number.h"

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

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
            char*   (*ToString) (TLong const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*IntValue) (TLong const);
            long    (*LongValue) (TLong const);
            float   (*FloatValue) (TLong const);
            double  (*DoubleValue) (TLong const);
            char    (*CharValue) (TLong const);
            short   (*ShortValue) (TLong const);
        };
    };
};

long Long_ParseLong(char* s, int radix);
int Long_CompareTo(TLong const, TLong other);
int Long_IntValue(TLong const);
long Long_LongValue(TLong const);
float Long_FloatValue(TLong const);
double Long_DoubleValue(TLong const);
char Long_CharValue(TLong const);
short Long_ShortValue(TLong const);
TLong Long_New(long value);
TLong Long_Ctor(TLong const this, long value);

#endif _LONG_H_
