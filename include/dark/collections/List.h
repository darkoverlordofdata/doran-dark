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

typedef int (*List_Compare) (Any, Any);
typedef void (*List_Interator) (Any);

class (ListNode)
{
    Any data;
    ListNode next;
};

class (List)
{
    Class isa;
    int length;
    ListNode head;
};

typedef struct ListClass_t
{
    union {
        Collection_t base;
        struct {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (List const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (List const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
            int         (*Length)       (List const);
            bool        (*IsEmpty)      (List const);
            bool        (*Contains)     (List const, Any value);
            void        (*Clear)        (List const);
            void        (*Add)          (List const, Any value);
            Any         (*Remove)       (List const);

        };
    };
    int (*Insert) (List const, Any data, List_Compare func);
    void (*Iterate) (List const, List_Interator func);
};


/**
 * List API
 */
const char* overload ToString(List const);
void overload Dispose(List const);
int overload Length(List const);
bool overload IsEmpty(List const);
bool overload Contains(List const);
void overload Clear(List const);
void overload Add(List const, Any data);
Any overload Remove(List const);

int Insert(List const, Any data, List_Compare func);
void Iterate(List const, List_Interator func);
List List_New();
List List_Ctor(List const this);

#endif _LIST_H_ 
