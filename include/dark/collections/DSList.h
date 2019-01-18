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

ivar (DSListNode) {
    DSObject* data;
    DSListNode* next;
};

ivar (DSList) {
    Class isa;
    int length;
    Class typeOf;
    DSListNode* head;
};

/**
 * List API
 */
DSList* DSList_alloc();
DSList* overload DSList_init(DSList* const this);
DSList* overload DSList_init(DSList* const this, Class typeOf);
DSList* NewDSList();

method (DSList, ToString,   char*,      (const DSList* const) );
method (DSList, Length,     int,        (DSList* const) );
method (DSList, IsEmpty,    bool,       (DSList* const) );
method (DSList, Contains,   bool,       (DSList* const, DSObject*) );
method (DSList, Clear,      void,       (DSList* const) );
method (DSList, Add,        Either*,    (DSList* const, DSObject*) );
method (DSList, Remove,     DSObject*,  (DSList* const) );
method (DSList, Insert,     Either*,    (DSList* const, DSObject*, DSList_Compare) );
method (DSList, Iterate,    void,       (DSList* const, DSList_Iterator) );


vtable (DSList) {
    const DSListToString          ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSListLength            Length;
    const DSListIsEmpty           IsEmpty;
    const DSListContains          Contains;
    const DSListClear             Clear;
    const DSListAdd               Add;
    const DSListRemove            Remove;
    const DSListInsert            Insert;
    const DSListIterate           Iterate;
};

class (DSList) {
    DSList*   (*Create) ();
};


#endif _DSLIST_H_ 
