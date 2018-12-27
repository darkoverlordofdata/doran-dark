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
#ifndef DARK_COLLECTION_H_
#define DARK_COLLECTION_H_
#include "../Object.h"

#define IsCollection(x) (x->isa == &Collection)
#define AsCollection(x) (IsCollection(x) ? (struct Collision *)x : nullptr)

/**
 * Base collection interface for sequential collections such as list and array
 */
class (Collection)
{
    struct CollectionClass * isa;
};


/**
 * Object metaclass
 */
struct CollectionClass
{
    union {
        struct Object base;
        struct 
        {
            struct Class * isa;
            struct Class * superclass;
            char* name;
            char*   (*ToString) (struct Collection *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const , struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct Collection * (*Create) ();
        };
    };
    int     (*Length) (struct Collection *const);
    bool    (*IsEmpty) (struct Collection *const);
    bool    (*Contains) (struct Collection *const, Any);
    void    (*Clear) (struct Collection *const);
    bool    (*Add) (struct Collection *const, Any);
    bool    (*Remove) (struct Collection *const, Any);
};


/**
 * Collection API
 */
int overload Length(struct Collection *const);
void overload Add(struct Collection *const, Any);
struct Collection *Collection_Ctor(struct Collection *const);

/**
 * AddAll
 * ToArray
*/
#endif DARK_COLLECTION_H_
