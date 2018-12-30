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
#ifndef _DSLONG_H_
#define _DSLONG_H_
#include "DSNumber.h"

#define LONG_MIN_VALUE  LONG_MIN
#define LONG_MAX_VALUE  LONG_MAX
#define LONG_BYTES      (sizeof(long))
#define LONG_SIZE       (LONG_BYTES * CHAR_BIT)
#define LONG_TYPE       (TYPE_LONG)

#define IsDSLong(x) (x->isa == &DSLongClass)
#define AsDSLong(x) (IsDSLong(x) ? (DSLong*)x : nullptr)

/**
 * Object class
 */
class (DSLong) 
{
    struct DSLongClass * isa;
    long value;
};

/**
 * Object metaclass
 */
struct DSLongClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    info, instance_size;
    char*   (*ToString) (DSLong* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSLong*   (*Create) (long);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*IntValue) (DSLong* const);
    long    (*LongValue) (DSLong* const);
    float   (*FloatValue) (DSLong* const);
    double  (*DoubleValue) (DSLong* const);
    char    (*CharValue) (DSLong* const);
    short   (*ShortValue) (DSLong* const);

} DSLongClass;

long DSLong_ParseLong(char *const, int);
int DSLong_CompareTo(DSLong* const, DSLong* const);
int DSLong_IntValue(DSLong* const);
long DSLong_LongValue(DSLong* const);
float DSLong_FloatValue(DSLong* const);
double DSLong_DoubleValue(DSLong* const);
char DSLong_CharValue(DSLong* const);
short DSLong_ShortValue(DSLong* const);

#endif _DSLONG_H_
