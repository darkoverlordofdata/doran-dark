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

#define IsChar(x) (x->isa == &Char)
#define AsChar(x) (IsChar(x) ? (struct Char *)x : nullptr)

/**
 * Char class
 */
class (Char) 
{
    struct CharClass * isa;
    char value;
};

/**
 * Char metaclass
 */
struct CharClass
{
    union {
        struct NumberClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TChar const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TChar   (*Create) (char value);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*IntValue) (TChar const);
            long    (*LongValue) (TChar const);
            float   (*FloatValue) (TChar const);
            double  (*DoubleValue) (TChar const);
            char    (*CharValue) (TChar const);
            short   (*ShortValue) (TChar const);
        };
    };
};


int Char_CompareTo(TChar const, TChar other);
int Char_IntValue(TChar const);
long Char_LongValue(TChar const);
float Char_FloatValue(TChar const);
double Char_DoubleValue(TChar const);
char Char_CharValue(TChar const);
short Char_ShortValue(TChar const);
TChar Char_New(char value);
TChar Char_Ctor(TChar const this, char value);

#endif _CHAR_H_
