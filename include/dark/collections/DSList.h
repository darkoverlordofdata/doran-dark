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
#ifndef _DSLIST_H_
#define _DSLIST_H_
#include "DSCollection.h"

#define IsDSList(x) (x->isa == &DSListClass)
#define AsDSList(x) (IsDSList(x) ? (DSList*)x : nullptr)

typedef int (*DSList_Compare) (Any, Any);
typedef void (^DSList_Interator) (Any);

class (DSListNode)
{
    Any data;
    DSListNode* next;
};

class (DSList)
{
    struct DSListClass* isa;
    int length;
    DSListNode* head;
};

struct DSListClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    long    info, instance_size;
    char*   (*ToString) (DSList* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSList*   (*Create) ();
    int     (*Length)       (DSList* const);
    bool    (*IsEmpty)      (DSList* const);
    bool    (*Contains)     (DSList* const, Any);
    void    (*Clear)        (DSList* const);
    void    (*Add)          (DSList* const, Any);
    Any     (*Remove)       (DSList* const);

    int (*Insert) (DSList* const, Any, DSList_Compare);
    void (*Iterate) (DSList* const, DSList_Interator);
    
} DSListClass;


/**
 * List API
 */
char* overload ToString(DSList* const);
void overload Dispose(DSList* const);
int overload Length(DSList* const);
bool overload IsEmpty(DSList* const);
bool overload Contains(DSList* const);
void overload Clear(DSList* const);
void overload Add(DSList* const, Any);
Any overload Remove(DSList* const);

int Insert(DSList* const, Any, DSList_Compare);
void overload ForEach(DSList* const, DSList_Interator);

#endif _DSLIST_H_ 
