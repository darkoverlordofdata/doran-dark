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
            char*   (*ToString) (TShort const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*IntValue) (TShort const);
            long    (*LongValue) (TShort const);
            float   (*FloatValue) (TShort const);
            double  (*DoubleValue) (TShort const);
            char    (*CharValue) (TShort const);
            short   (*ShortValue) (TShort const);
        };
    };
};

short Short_ParseShort(char* s, int radix);
int Short_CompareTo(TShort const, TShort other);
int Short_IntValue(TShort const);
long Short_LongValue(TShort const);
float Short_FloatValue(TShort const);
double Short_DoubleValue(TShort const);
char Short_CharValue(TShort const);
short Short_ShortValue(TShort const);
TShort Short_New(short value);
TShort Short_Ctor(TShort const this, short value);

#endif _SHORT_H_
