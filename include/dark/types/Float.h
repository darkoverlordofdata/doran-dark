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
#ifndef _FLOAT_H_
#define _FLOAT_H_
#include "Number.h"

#define FLOAT_MIN_VALUE  FLT_MIN
#define FLOAT_MAX_VALUE  FLT_MAX
#define FLOAT_BYTES      (sizeof(float))
#define FLOAT_SIZE       (FLOAT_BYTES * CHAR_BIT)
#define FLOAT_TYPE       (TYPE_FLOAT)

/**
 * Object class
 */
class (Float) 
{
    FloatClass_t* isa;
    float        value;
};

/**
 * Object metaclass
 */
typedef struct FloatClass_t
{
    union {
        NumberClass_t base;
        struct 
        {
            Class isa;
            Class superclass;
            char* name;
            char*   (*ToString) (Object const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
            int     (*CompareTo) (Comparable const, Comparable other);
            int     (*IntValue) (Float const);
            long    (*LongValue) (Float const);
            float   (*FloatValue) (Float const);
            double  (*DoubleValue) (Float const);
            char    (*CharValue) (Float const);
            short   (*ShortValue) (Float const);
        };
    };
};


int Float_CompareTo(Float const, Float other);
int Float_IntValue(Float const);
long Float_LongValue(Float const);
float Float_FloatValue(Float const);
float Float_FloatValue(Float const);
char Float_CharValue(Float const);
short Float_ShortValue(Float const);
Float Float_New(float value);

#endif _FLOAT_H_
