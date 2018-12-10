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
#ifndef _LIST_H_
#define _LIST_H_
#include "Collection.h"

#define IsList(x) (x->isa == &List)
#define AsList(x) (IsList(x) ? (struct List *)x : nullptr)

typedef int (*List_Compare) (Any, Any);
typedef void (^List_Interator) (Any);

class (ListNode)
{
    Any data;
    struct ListNode * next;
};

class (List)
{
    struct ListClass * isa;
    int length;
    struct ListNode * head;
};

struct ListClass
{
    union {
        struct Collection base;
        struct {
            struct Class * isa;
            struct Class * superclass;
            char* name;
            char*   (*ToString) (TList const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TList   (*Create) ();
            int     (*Length)       (TList const);
            bool    (*IsEmpty)      (TList const);
            bool    (*Contains)     (TList const, Any value);
            void    (*Clear)        (TList const);
            void    (*Add)          (TList const, Any value);
            Any     (*Remove)       (TList const);

        };
    };
    int (*Insert) (TList const, Any data, List_Compare func);
    void (*Iterate) (TList const, List_Interator func);
};


/**
 * List API
 */
char* overload ToString(TList const);
void overload Dispose(TList const);
int overload Length(TList const);
bool overload IsEmpty(TList const);
bool overload Contains(TList const);
void overload Clear(TList const);
void overload Add(TList const, Any data);
Any overload Remove(TList const);

int Insert(TList const, Any data, List_Compare func);
void overload ForEach(TList const, List_Interator func);
TList List_New();
TList List_Ctor(TList const this);

#endif _LIST_H_ 
