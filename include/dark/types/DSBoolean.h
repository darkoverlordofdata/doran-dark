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
#ifndef _DSBOOLEAN_H_
#define _DSBOOLEAN_H_
#include "../DSComparable.h"

#define BOOLEAN_BYTES      (sizeof(char))
#define BOOLEAN_SIZE       (BOOLEAN_BYTES * CHAR_BIT)
#define BOOLEAN_TYPE       (TYPE_BOOLEAN)

#define IsDSBoolean(x) (x->isa == &DSBooleanClass)
#define AsDSBoolean(x) (IsDSBoolean(x) ? (DSBoolean *)x : nullptr)

/**
 * DSBoolean class
 */
class (DSBoolean)
{
    struct DSBooleanClass* isa;
    bool value;
};


typedef bool    (*DSBooleanCompareTo)  (const DSBoolean* const, const DSBoolean* const);
typedef char*   (*DSBooleanToString)  (const DSBoolean* const);

/**
 * DSBoolean metaclass
 */
struct DSBooleanClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (const DSBoolean* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSBoolean*(*Create) (bool value);
    int     (*CompareTo) (const DSBoolean* const, const DSBoolean* const);

    bool    (*BoolValue) (const DSBoolean* const);
    int     (*Compare) (const bool, const bool);
    bool    (*ParseBool) (char const*);

    int  Bytes;
    int  Size;
    int  Type;
    DSBoolean* True;
    DSBoolean* False;
} DSBooleanClass;

bool BoolValue(const DSBoolean* const);
bool ParseBool(const char *const);

int overload Compare(bool, bool);
int DSBoolean_CompareTo(const DSBoolean* const, const DSBoolean* const);
char* overload ToString(const DSBoolean* const);
DSBoolean* DSBoolean_init(DSBoolean* this, bool value);

#endif // _DSBOOLEAN_H_
