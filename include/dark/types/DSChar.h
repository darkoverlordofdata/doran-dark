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
#ifndef _DSCHAR_H_
#define _DSCHAR_H_
#include "DSNumber.h"

#define CHAR_MIN_VALUE  CHAR_MIN
#define CHAR_MAX_VALUE  CHAR_MAX
#define CHAR_BYTES      (sizeof(char))
#define CHAR_SIZE       (CHAR_BYTES * CHAR_BIT)
#define CHAR_TYPE       (TYPE_CHAR)

#define IsDSChar(x) (x->isa == &DSCharClass)
#define AsDSChar(x) (IsDSChar(x) ? (DSChar* )x : nullptr)

/**
 * Char class
 */
class (DSChar) 
{
    struct DSCharClass *isa;
    char value;
};

/**
 * Char metaclass
 */
struct DSCharClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (DSChar* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSChar* (*Create) (char value);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSChar* const);
    long    (*LongValue) (DSChar* const);
    float   (*FloatValue) (DSChar* const);
    double  (*DoubleValue) (DSChar* const);
    char    (*CharValue) (DSChar* const);
    short   (*ShortValue) (DSChar* const);

} DSCharClass;


int DSChar_CompareTo(DSChar* const, DSChar* const);
int DSChar_IntValue(DSChar* const);
long DSChar_LongValue(DSChar* const);
float DSChar_FloatValue(DSChar* const);
double DSChar_DoubleValue(DSChar* const);
char DSChar_CharValue(DSChar* const);
short DSChar_ShortValue(DSChar* const);
char* DSChar_ToString(DSChar* const);
DSChar* $DSChar(char value);

#endif _DSCHAR_H_
