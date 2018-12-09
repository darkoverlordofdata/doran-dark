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
#ifndef _SHORT_H_
#define _SHORT_H_
#include "Number.h"

#define SHORT_MIN_VALUE  SHRT_MIN
#define SHORT_MAX_VALUE  SHRT_MAX
#define SHORT_BYTES      (sizeof(short))
#define SHORT_SIZE       (SHORT_BYTES * CHAR_BIT)
#define SHORT_TYPE       (TYPE_SHORT)

/**
 * Object class
 */
class (Short) 
{
    ShortClass_t* isa;
    short        value;
};

/**
 * Object metaclass
 */
typedef struct ShortClass_t
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
            int     (*IntValue) (Short const);
            long    (*LongValue) (Short const);
            float   (*FloatValue) (Short const);
            double  (*DoubleValue) (Short const);
            char    (*CharValue) (Short const);
            short   (*ShortValue) (Short const);
        };
    };
};

short Short_ParseShort(char* s, int radix);
int Short_CompareTo(Short const, Short other);
int Short_IntValue(Short const);
long Short_LongValue(Short const);
float Short_FloatValue(Short const);
double Short_DoubleValue(Short const);
char Short_CharValue(Short const);
short Short_ShortValue(Short const);
Short Short_New(short value);
Short Short_Ctor(Short const this, short value);

#endif _SHORT_H_
