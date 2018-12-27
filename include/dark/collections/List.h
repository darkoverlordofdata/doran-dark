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
#ifndef DARK_LIST_H_
#define DARK_LIST_H_
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
            char*   (*ToString) (struct List *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            struct List *  (*Create) ();
            int     (*Length)       (struct List *const);
            bool    (*IsEmpty)      (struct List *const);
            bool    (*Contains)     (struct List *const, Any);
            void    (*Clear)        (struct List *const);
            void    (*Add)          (struct List *const, Any);
            Any     (*Remove)       (struct List *const);

        };
    };
    int (*Insert) (struct List *const, Any, List_Compare);
    void (*Iterate) (struct List *const, List_Interator);
};


/**
 * List API
 */
char* overload ToString(struct List *const);
void overload Dispose(struct List *const);
int overload Length(struct List *const);
bool overload IsEmpty(struct List *const);
bool overload Contains(struct List *const);
void overload Clear(struct List *const);
void overload Add(struct List *const, Any);
Any overload Remove(struct List *const);

int Insert(struct List *const, Any, List_Compare);
void overload ForEach(struct List *const, List_Interator);

#endif DARK_LIST_H_ 
