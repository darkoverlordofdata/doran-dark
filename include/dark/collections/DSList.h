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
#include <dark/DSObject.h>
#include <dark/types/DSString.h>
// #include "DSCollection.h"

#define IsDSList(object) _Generic((object), DSList*: true, default: false)
#define AsDSList(object) _Generic((object),                             \
                            DSList*: (DSList *)object,                  \
                            default: nullptr)

typedef int (*DSList_Compare) (DSObject*, DSObject*);
typedef void (^DSList_Iterator) (DSObject*);

type (DSListNode) {
    DSObject* data;
    DSListNode* next;
};

type (DSList) {
    Class isa;
    Class typeOf;
    int length;
    DSListNode* head;
};

def_ctor (DSList);
def_ctor (DSList, Class);
def_method (DSList, ToString,   char*,      (const DSList* const) );
def_method (DSList, Length,     int,        (DSList* const) );
def_method (DSList, Add,        Either*,    (DSList* const, DSObject*) );
def_method (DSList, Remove,     DSObject*,  (DSList* const) );
def_method (DSList, Insert,     Either*,    (DSList* const, DSObject*, DSList_Compare) );
def_method (DSList, Iterate,    void,       (DSList* const, DSList_Iterator) );

vtable (DSList) {
    const DSListToString          ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSListLength            Length;
    const DSListAdd               Add;
    const DSListRemove            Remove;
    const DSListInsert            Insert;
    const DSListIterate           Iterate;
};

vtable_ptr(DSList);
method DSList* DSList_init(DSList* const this)
{
    return DSList_init(this, nullptr);
}

method DSList* DSList_init(DSList* const this, Class typeOf)
{
    DSObject_init(this);
    this->isa = objc_getClass("DSList");
    this->typeOf = typeOf;
    this->head = nullptr;

    return this;
}

/**
 * Create new ListNode
 * 
 * @param data to add
 * @param next node in list
 * 
 */
proc DSListNode* DSListNode_init(DSListNode* const this, DSObject* data, DSListNode* next)
{
    this->data = data;
    this->next = next;
    return this;
}

proc DSListNode* NewDSListNode(DSObject* data, DSListNode* next)
{
    return DSListNode_init(alloc(DSList), data, next);
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
method Either* Insert(DSList* const this, DSObject* data, DSList_Compare comp)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return Left(NewDSString("InvalidType"));

    if (this->head == nullptr) {
        this->head = NewDSListNode(data, nullptr);
        return Right(NewDSString(1));
    }

    // Find spot in linked list to insert new node
    DSListNode* prev = nullptr;
    DSListNode* curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = NewDSListNode(data, this->head);
    else 
        prev->next = NewDSListNode(data, curr);

    this->length++;
    return Right(NewDSString(1));
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
method Either* Add(DSList* const this, DSObject* data)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return Left(NewDSString("InvalidType"));


    if (this->head == nullptr) {
        this->head = NewDSListNode(data, nullptr);
    }
    else { 
       this->head = NewDSListNode(data, this->head);
    }
    this->length++;
}

/**
 * Remove item at end of list
 */
method DSObject* Remove(DSList* const this)
{
    DSListNode* head = this->head;

    DSObject* popped_data = head->data;
    this->head = head->next;

    // delete(head);
    this->length--;
    return popped_data;
}

/**
 * Iterate over list
 * 
 * @param iter function to call for each iteration
 * 
 */
method void Iterate(DSList* const this, void (^iter)(DSObject*))
{
    for (DSListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

/**
 * Free list
 */
method void Dispose(DSList* const this)
{
    // ListNode curr = this->head;
    // ListNode next;

    // while (curr != nullptr) {
    //     delete(curr->data);
    //     next = curr->next;
    //     delete(curr);
    //     curr = next;
    // }
}

/**
 * Number of items in vector
 */
method int Length(DSList* const this)
{
    return this->length;
}

/**
 * ToString
 */
method char* ToString(const DSList* const this)
{
    return "dark.collections.List";
}



class_bind(DSList)

class_method(ToString,           (DSListToString)ToString, "@@:v");
class_method(Equals,             (DSObjectEquals)Equals, "B@:@@");
class_method(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
class_method(Dispose,            (DSObjectDispose)Dispose, "v@:v");
class_method(Length,             (DSListLength)Length, "i@:v");
class_method(Add,                (DSListAdd)Add, "@@:*");
class_method(Remove,             (DSListRemove)Remove, "i@:*");
class_method(Insert,             (DSListInsert)Insert, "i@:*@");
class_method(Iterate,            (DSListIterate)Iterate, "i@:@@");

class_member(typeof, sizeof(id), "@");
class_member(length, sizeof(int), "i");
class_member(head, sizeof(void*), "^");

class_methodize;

#endif _DSLIST_H_ 
