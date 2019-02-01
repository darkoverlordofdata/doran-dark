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
#include <dark/Foundation.h>
#include <dark/collections/implementation/DSList.h>
/**
 * Constructor
 */
overload DSList* DSList_init(DSList* const this)
{
    return DSList_init(this, nullptr);
}

overload DSList* DSList_init(DSList* const this, Class typeOf)
{
    DSObject_init(this);
    this->isa = getDSListIsa();
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
DSListNode* DSListNode_init(DSListNode* const this, DSObject* data, DSListNode* next)
{
    this->data = data;
    this->next = next;
    return this;
}

DSListNode* NewDSListNode(DSObject* data, DSListNode* next)
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
overload Either* Insert(DSList* const this, DSObject* data, DSList_Compare comp)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return Left($("InvalidType"));

    if (this->head == nullptr) {
        this->head = NewDSListNode(data, nullptr);
        return Right($(1));
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
    return Right($(1));
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
overload Either* Add(DSList* const this, DSObject* data)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, data)) 
        return Left($("InvalidType"));


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
overload DSObject* Remove(DSList* const this)
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
overload void Iterate(DSList* const this, void (^iter)(DSObject*))
{
    for (DSListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

/**
 * Free list
 */
overload void Dispose(DSList* const this)
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
overload int Length(DSList* const this)
{
    return this->length;
}

/**
 * ToString
 */
overload char* ToString(const DSList* const this)
{
    return "dark.collections.List";
}

