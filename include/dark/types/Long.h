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



class (Long)
{
    union {
        Number_t _;
        struct 
        {
            int         RefCount;
            char*       (*ToString) (DObject const);
            bool        (*Equals) (DObject const, DObject const);
            int         (*GetHashCode) (DObject const);
            void        (*Dispose) (DObject const);
            int         (*CompareTo) (Long const, Long other);
            int         (*IntValue) (Long const);
            long        (*LongValue) (Long const);
            float       (*FloatValue) (Long const);
            double      (*DoubleValue) (Long const);
            char        (*CharValue) (Long const);
            short       (*ShortValue) (Long const);
        };
    };
    long                value;
};

long Long_ParseLong(char* s, int radix);
int Long_CompareTo(Long const, Long other);
int Long_IntValue(Long const);
long Long_LongValue(Long const);
float Long_FloatValue(Long const);
double Long_DoubleValue(Long const);
char Long_CharValue(Long const);
short Long_ShortValue(Long const);
Long Long_New(long value);
Long Long_rcNew(long value);

#endif _LONG_H_
