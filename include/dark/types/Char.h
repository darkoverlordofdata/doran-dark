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
#ifndef _CHAR_H_
#define _CHAR_H_
#include "Number.h"

#define CHAR_MIN_VALUE  CHAR_MIN
#define CHAR_MAX_VALUE  CHAR_MAX
#define CHAR_BYTES      (sizeof(char))
#define CHAR_SIZE       (CHAR_BYTES * CHAR_BIT)
#define CHAR_TYPE       (TYPE_CHAR)

class (Char)
{
    union {
        Number_t _;
        struct 
        {
            retained
            char*       (*ToString) (DObject const);
            bool        (*Equals) (DObject const, DObject const);
            int         (*GetHashCode) (DObject const);
            void        (*Dispose) (DObject const);
            int         (*CompareTo) (Char const, Char other);
            int         (*IntValue) (Char const);
            long        (*LongValue) (Char const);
            float       (*FloatValue) (Char const);
            double      (*DoubleValue) (Char const);
            char        (*CharValue) (Char const);
            short       (*ShortValue) (Char const);
        };
    };
    char            value;
};

int Char_CompareTo(Char const, Char other);
int Char_IntValue(Char const);
long Char_LongValue(Char const);
float Char_FloatValue(Char const);
double Char_DoubleValue(Char const);
char Char_CharValue(Char const);
short Char_ShortValue(Char const);
Char Char_New(char value);

#endif _CHAR_H_
