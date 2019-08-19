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
#include <dark/core/object.h>
#include <dark/types/string.h>

#define IsList(object) _Generic((object), List*: true, default: false)
#define AsList(object) _Generic((object),                             \
                            List*: (List *)object,                  \
                            default: nullptr)

typedef int (*List_Compare) (Object*, Object*);
typedef void (^List_Iterator) (Object*);

type (ListNode) {
    Object* data;
    ListNode* next;
};

type (List) {
    Class isa;
    Class typeOf;
    int length;
    ListNode* head;
};

ctor_proto (List);
ctor_proto (List, Class);
interface (List, ToString,   char*,      (const List* const) );
interface (List, Length,     int,        (List* const) );
interface (List, Add,        Either*,    (List* const, Object*) );
interface (List, Remove,     Object*,    (List* const) );
interface (List, Insert,     Either*,    (List* const, Object*, List_Compare) );
interface (List, Iterate,    void,       (List* const, List_Iterator) );

vtable (List) {
    const ListToString          ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const ListLength            Length;
    const ListAdd               Add;
    const ListRemove            Remove;
    const ListInsert            Insert;
    const ListIterate           Iterate;
};

function vptr(List);
/**
 * 
 * Class Loader callback
 */
function objc_loadList(Class super) 
{
    Class cls = createClass(super, List);
    addMethod(cls, ListToString, ToString);
    addMethod(cls, ObjectEquals, Equals);
    addMethod(cls, ObjectGetHashCode, GetHashCode);
    addMethod(cls, ObjectDispose, Dispose);
    addMethod(cls, ListLength, Length);
    addMethod(cls, ListAdd, Add);
    addMethod(cls, ListRemove, Remove);
    addMethod(cls, ListInsert, Insert);
    addMethod(cls, ListIterate, Iterate);
    
    return cls;
}

method List* List_init(List* const this)
{
    return List_init(this, nullptr);
}

method List* List_init(List* const this, Class typeOf)
{
    Object_init(this);
    this->isa = objc_getClass("List");
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
function ListNode* ListNode_init(ListNode* const this, Object* data, ListNode* next)
{
    this->data = data;
    this->next = next;
    return this;
}

function ListNode* NewListNode(Object* data, ListNode* next)
{
    return ListNode_init(alloc(List), data, next);
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
method Either* Insert(List* const this, Object* data, List_Compare comp)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return left(NewString("InvalidType"));

    if (this->head == nullptr) {
        this->head = NewListNode(data, nullptr);
        return right(NewString(1));
    }

    // Find spot in linked list to insert new node
    ListNode* prev = nullptr;
    ListNode* curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = NewListNode(data, this->head);
    else 
        prev->next = NewListNode(data, curr);

    this->length++;
    return right(NewString(1));
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
method Either* Add(List* const this, Object* data)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return left(NewString("InvalidType"));


    if (this->head == nullptr) {
        this->head = NewListNode(data, nullptr);
    }
    else { 
       this->head = NewListNode(data, this->head);
    }
    this->length++;
}

/**
 * Remove item at end of list
 */
method Object* Remove(List* const this)
{
    ListNode* head = this->head;

    Object* popped_data = head->data;
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
method void Iterate(List* const this, void (^iter)(Object*))
{
    for (ListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

/**
 * Free list
 */
method void Dispose(List* const this)
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
method int Length(List* const this)
{
    return this->length;
}

/**
 * ToString
 */
method char* ToString(const List* const this)
{
    return "dark.collections.List";
}

