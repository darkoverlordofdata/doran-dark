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
#ifndef _COLLECTION_H_
#define _COLLECTION_H_
#include "../Object.h"
/**
 * Base collection interface for sequential collections such as list and array
 */
typedef struct CollectionClass_t CollectionClass_t;
extern CollectionClass_t CollectionClass;

class (Collection)
{
    CollectionClass_t* isa;
};


/**
 * Object metaclass
 */
typedef struct CollectionClass_t
{
    union {
        Object_t base;
        struct 
        {
            Class   isa;
            Class   superclass;
            char*   name;
            char*   (*ToString) (Object const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
    int     (*Length) (Collection const);
    bool    (*IsEmpty) (Collection const);
    bool    (*Contains) (Collection const, Any value);
    void    (*Clear) (Collection const);
    bool    (*Add) (Collection const, Any value);
    bool    (*Remove) (Collection const, Any value);
};


/**
 * Collection API
 */
int overload Length(Collection const);
void overload Add(Collection const, Any item);

/**
 * AddAll
 * ToArray
*/
#endif _COLLECTION_H_
