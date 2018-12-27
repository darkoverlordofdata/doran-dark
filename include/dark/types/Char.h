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
#pragma once
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
    struct CharClass *isa;
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
            struct  Class *isa;
            struct  Class *superclass;
            char*   name;
            char*   (*ToString) (struct Char *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Char *  (*Create) (char value);
            int     (*CompareTo) (struct Comparable *const, struct Comparable *const);
            int     (*IntValue) (struct Char *const);
            long    (*LongValue) (struct Char *const);
            float   (*FloatValue) (struct Char *const);
            double  (*DoubleValue) (struct Char *const);
            char    (*CharValue) (struct Char *const);
            short   (*ShortValue) (struct Char *const);
        };
    };
};


int Char_CompareTo(struct Char *const, struct Char *const);
int Char_IntValue(struct Char *const);
long Char_LongValue(struct Char *const);
float Char_FloatValue(struct Char *const);
double Char_DoubleValue(struct Char *const);
char Char_CharValue(struct Char *const);
short Char_ShortValue(struct Char *const);
char* Char_ToString(struct Char *const);

#endif _CHAR_H_
