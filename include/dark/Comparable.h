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
#ifndef _COMPARABLE_H_
#define _COMPARABLE_H_
#include "Object.h"

typedef struct ComparableClass_t ComparableClass_t;
extern ComparableClass_t ComparableClass;

/**
 * Comparable Class
 */
class (Comparable)
{
    ComparableClass_t* isa;
};


/**
 * Comparable MetaClass
 */
typedef struct ComparableClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class   isa;
            Class   superclass;
            char*   name;
            char*   (*ToString) (Comparable const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
    int     (*CompareTo) (Comparable const, Comparable other);
};

int __attribute__((overloadable)) CompareTo(Comparable const, Comparable other);

#endif _COMPARABLE_H_
