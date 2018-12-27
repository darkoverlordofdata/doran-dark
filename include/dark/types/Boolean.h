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
#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_
#include "../Comparable.h"

#define BOOLEAN_BYTES      (sizeof(char))
#define BOOLEAN_SIZE       (BOOLEAN_BYTES * CHAR_BIT)
#define BOOLEAN_TYPE       (TYPE_BOOLEAN)

#define IsBoolean(x) (x->isa == &Boolean)
#define AsBoolean(x) (IsBoolean(x) ? (struct Boolean *)x : nullptr)

/**
 * Object class
 */
class (Boolean)
{
    struct BooleanClass * isa;
    bool value;
};

/**
 * Object metaclass
 */
struct BooleanClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class *isa;
            struct  Class *superclass;
            char*   name;
            char*   (*ToString) (const struct Boolean *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Boolean *(*Create) (bool value);
            int     (*CompareTo) (const struct Boolean *const, const struct Boolean *const);
        };
    };
    bool    (*BoolValue) (const struct Boolean *const);
    int     (*Compare) (const bool, const bool);
    bool    (*ParseBool) (char const*);

    int  Bytes;
    int  Size;
    int  Type;
    struct Boolean *True;
    struct Boolean *False;
};

bool BoolValue(const struct Boolean *const);
bool ParseBool(const char *const);

int overload Compare(bool, bool);
int overload CompareTo(const struct Boolean *const, const struct Boolean *const);
char* overload ToString(const struct Boolean *const);

#endif // _BOOLEAN_H_
