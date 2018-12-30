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
#include <dark/collections/DSList.h>
/**
 * Constructor
 */
DSList* DSList_init(DSList* const this)
{
    DSCollection_init(this);
    this->isa = ISA(DSList);
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
DSListNode* DSListNode_init(DSListNode* const this, Any data, DSListNode* next)
{
    this->data = data;
    this->next = next;
    return this;
}

DSListNode* DSListNode_New(Any data, DSListNode* next)
{
    return DSListNode_init(class_alloc(DSList), data, next);
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
int Insert(DSList* const this, Any data, int (*comp)(Any, Any))
{
    if (this->head == nullptr) {
        this->head = DSListNode_New(data, nullptr);
        return 1;
    }

    // Find spot in linked list to insert new node
    DSListNode* prev = nullptr;
    DSListNode* curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = DSListNode_New(data, this->head);
    else 
        prev->next = DSListNode_New(data, curr);

    this->length++;
    return 1;
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
void overload Add(DSList* const this, Any data)
{
    if (this->head == nullptr) {
        this->head = DSListNode_New(data, nullptr);
    }
    else { 
       this->head = DSListNode_New(data, this->head);
    }
    this->length++;
}

/**
 * Remove item at end of list
 */
Any overload Remove(DSList* const this)
{
    DSListNode* head = this->head;

    Any popped_data = head->data;
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
void overload ForEach(DSList* const this, void (^iter)(Any))
{
    for (DSListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

/**
 * Free list
 */
void overload Dispose(DSList* const this)
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
int overload Length(DSList* const this)
{
    return this->length;
}

/**
 * ToString
 */
char* overload ToString(DSList* const this)
{
    return "dark.collections.List";
}

DSList* $DSList() { 
    return DSList_init(class_alloc(DSList)); 
}

/**
 * List Class Metadata
 */
DSDefine(DSList, DSCollection, cls, {
    cls->Create         = $DSList;
    cls->ToString       = ToString;
    cls->Dispose        = Dispose;
    cls->Length         = Length;
    cls->Iterate        = ForEach;
    cls->Insert         = Insert;
    cls->Add            = Add;
    cls->Remove         = Remove;
});
