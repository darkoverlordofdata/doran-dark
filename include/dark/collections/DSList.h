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
#include "../DSObject.h"
// #include "DSCollection.h"

#define IsDSList(object) _Generic((object), DSList*: true, default: false)
#define AsDSList(object) _Generic((object),                             \
                            DSList*: (DSList *)object,                  \
                            default: nullptr)

typedef int (*DSList_Compare) (DSObject*, DSObject*);
typedef void (^DSList_Iterator) (DSObject*);

ivar (DSListNode)
{
    DSObject* data;
    DSListNode* next;
};

ivar (DSList) {
    Class isa;
    int length;
    DSListNode* head;
};

/** Interface */
typedef char*   (*DSListToString)   (const DSList* const);
typedef void    (*DSListDispose)    (DSList* const);
typedef int     (*DSListLength)     (const DSList* const);
typedef int     (*DSListForEach)    (DSList* const, DSList_Iterator, DSObject*);
typedef void    (*DSListInsert)     (DSList* const, DSObject*, DSList_Compare);
typedef void    (*DSListAdd)        (DSList* const, DSObject*);
typedef DSObject*     (*DSListRemove)     (const DSList* const);

vtable (DSList) {
    char*   (*ToString)     (const DSList* const);
    bool    (*Equals)       (DSObject* const, DSObject* const);
    int     (*GetHashCode)  (DSObject* const);
    void    (*Dispose)      (DSObject* const);
    int     (*Length)       (const DSList* const);
    bool    (*IsEmpty)      (DSList* const);
    bool    (*Contains)     (DSList* const, DSObject*);
    void    (*Clear)        (DSList* const);
    void    (*Add)          (DSList* const, DSObject*);
    DSObject*     (*Remove)       (DSList* const);
    int     (*Insert)       (DSList* const, DSObject*, DSList_Compare);
    void    (*Iterate)      (DSList* const, DSList_Iterator);
    
};

class (DSList) {
    DSList*   (*Create) ();
};


/**
 * List API
 */
char* overload ToString(const DSList* const);
void overload Dispose(DSList* const);
int overload Length(const DSList* const);
bool overload IsEmpty(DSList* const);
bool overload Contains(DSList* const);
void overload Clear(DSList* const);
void overload Add(DSList* const, DSObject*);
DSObject* overload Remove(DSList* const);

int Insert(DSList* const, DSObject*, DSList_Compare);
void overload ForEach(DSList* const, DSList_Iterator);
DSList* DSList_alloc();
DSList* DSList_init(DSList* const this);
DSList* NewDSList();

#endif _DSLIST_H_ 
