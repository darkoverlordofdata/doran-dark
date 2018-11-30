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

class (Integer)
{
    union {
        Number_t _;
        struct 
        {
            REFCOUNT
            char*       (*ToString)(DObject const);
            bool        (*Equals)(DObject const, DObject const);
            int         (*GetHashCode)(DObject const);
            void        (*Dispose) (DObject const);
            int         (*CompareTo) (Integer const, Integer other);
            int         (*IntValue) (Integer const);
            long        (*LongValue) (Integer const);
            float       (*FloatValue) (Integer const);
            double      (*DoubleValue) (Integer const);
            char        (*CharValue) (Integer const);
            short       (*ShortValue) (Integer const);
        };
    };
    int            value;
};

int Integer_ParseInt(char* s, int radix);
int Integer_CompareTo(Integer const, Integer other);
int Integer_IntValue(Integer const);
long Integer_LongValue(Integer const);
float Integer_FloatValue(Integer const);
double Integer_DoubleValue(Integer const);
char Integer_CharValue(Integer const);
short Integer_ShortValue(Integer const);
Integer Integer_New(int value);
Integer Integer_rcNew(int value);

#endif _INTEGER_H_
