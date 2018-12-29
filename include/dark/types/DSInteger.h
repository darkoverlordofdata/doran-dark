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
#ifndef _DSINTEGER_H_
#define _DSINTEGER_H_
#include "DSNumber.h"
#include "DSLong.h"


#define INTEGER_MIN_VALUE  INT_MIN
#define INTEGER_MAX_VALUE  INT_MAX
#define INTEGER_BYTES      (sizeof(int))
#define INTEGER_SIZE       (INTEGER_BYTES * CHAR_BIT)
#define INTEGER_TYPE       (TYPE_LONG)

#define IsDSInteger(x) (x->isa == &DSIntegerClass)
#define AsDSInteger(x) (IsDSInteger(x) ? (DSInteger*)x : nullptr)

/**
 * Object class
 */
class (DSInteger) 
{
    struct DSIntegerClass *isa;
    int value;
};

/**
 * Object metaclass
 */
struct DSIntegerClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    char*   (*ToString) (DSInteger* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSInteger*(*Create) (int value);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSInteger* const);
    long    (*LongValue) (DSInteger* const);
    float   (*FloatValue) (DSInteger* const);
    double  (*DoubleValue) (DSInteger* const);
    char    (*CharValue) (DSInteger* const);
    short   (*ShortValue) (DSInteger* const);

} DSIntegerClass;

int DSInteger_ParseInt(char *const, int);
int DSInteger_CompareTo(DSInteger* const, DSInteger* const);
int DSInteger_IntValue(DSInteger* const);
long DSInteger_LongValue(DSInteger* const);
int DSInteger_IntegerValue(DSInteger* const);
double DSInteger_DoubleValue(DSInteger* const);
char DSInteger_CharValue(DSInteger* const);
short DSInteger_ShortValue(DSInteger* const);

#endif _DSINTEGER_H_
