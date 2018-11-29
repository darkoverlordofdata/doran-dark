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
#ifndef _DOUBLE_H_
#define _DOUBLE_H_
#include "Number.h"

#define DOUBLE_MIN_VALUE  DBL_MIN
#define DOUBLE_MAX_VALUE  DBL_MAX
#define DOUBLE_BYTES      (sizeof(double))
#define DOUBLE_SIZE       (DOUBLE_BYTES * CHAR_BIT)
#define DOUBLE_TYPE       (TYPE_DOUBLE)

class (Double)
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
            int         (*CompareTo) (Double const, Double other);
            int         (*IntValue) (Double const);
            long        (*LongValue) (Double const);
            float       (*FloatValue) (Double const);
            double      (*DoubleValue) (Double const);
            char        (*CharValue) (Double const);
            short       (*ShortValue) (Double const);
        };
    };
    double            value;
};

int Double_CompareTo(Double const, Double other);
int Double_IntValue(Double const);
long Double_LongValue(Double const);
float Double_FloatValue(Double const);
double Double_DoubleValue(Double const);
char Double_CharValue(Double const);
short Double_ShortValue(Double const);
Double Double_New(double value);
Double Double_rcNew(double value);

#endif _DOUBLE_H_
