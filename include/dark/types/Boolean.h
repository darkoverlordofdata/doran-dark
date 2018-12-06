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
#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_
#include "../Comparable.h"

#define BOOLEAN_BYTES      (sizeof(char))
#define BOOLEAN_SIZE       (BOOLEAN_BYTES * CHAR_BIT)
#define BOOLEAN_TYPE       (TYPE_BOOLEAN)

typedef struct BooleanClass_t BooleanClass_t;
extern BooleanClass_t BooleanClass;


/**
 * Object class
 */
class (Boolean)
{
    BooleanClass_t* isa;
    bool value;
};


/**
 * Object metaclass
 */
typedef struct BooleanClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class isa;
            Class superclass;
            char* name;
            char*   (*ToString) (Boolean const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
            int     (*CompareTo) (Boolean const, Boolean other);
        };
    };
    bool    (*BoolValue) (Boolean const);
    int     (*Compare) (bool x, bool y);
    bool    (*ParseBool) (char* s);

    int const Bytes;
    int const Size;
    int const Type;
    Boolean True;
    Boolean False;
};

bool BoolValue(Boolean const);
bool ParseBool(char* s);

int overload Compare(bool x, bool y);
char* overload ToString(Boolean const this);
int overload CompareTo(Boolean const, Boolean other);
Boolean Boolean_New(bool value);

#endif _BOOLEAN_H_
