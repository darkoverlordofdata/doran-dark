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
            char*   (*ToString) (TCollection const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TCollection   (*Create) ();
        };
    };
    int     (*Length) (TCollection const);
    bool    (*IsEmpty) (TCollection const);
    bool    (*Contains) (TCollection const, Any value);
    void    (*Clear) (TCollection const);
    bool    (*Add) (TCollection const, Any value);
    bool    (*Remove) (TCollection const, Any value);
};


/**
 * Collection API
 */
int overload Length(TCollection const);
void overload Add(TCollection const, Any item);
TCollection Collection_Ctor(TCollection const this);

/**
 * AddAll
 * ToArray
*/
#endif DARK_COLLECTION_H_
