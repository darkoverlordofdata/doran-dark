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
#include <dark/List.h>
/* 
 * Generic Linked List implementation
 */

/**
 * Create new ListNode
 * 
 * @param data to add
 * @param next node in list
 * 
 */
ListNode ListNode_Ctor(ListNode const this, Any data, ListNode next)
{
    this->data = data;
    this->next = next;
    return this;
}

ListNode ListNode_New(Any data, ListNode next)
{
    return ListNode_Ctor(new(List), data, next);
}

/**
 * Add to list in sorted order
 * 
 * @param data to insert
 * @param comp function to compare for insertion
 * 
 */
int List_Add(List const this, Any data, int (*comp)(Any, Any))
{
    if (this->head == nullptr) {
        this->head = ListNode_New(data, nullptr);
        return 1;
    }

    // Find spot in linked list to insert new node
    ListNode prev = nullptr;
    ListNode curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = ListNode_New(data, this->head);
    else 
        prev->next = ListNode_New(data, curr);

    return 1;
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
void List_Push(List const this, Any data)
{
    if (this->head == nullptr)
       this->head = ListNode_New(data, nullptr);
    else 
       this->head = ListNode_New(data, this->head);
}

/**
 * Remove item at end of list
 */
Any List_Pop(List const this)
{
    ListNode head = this->head;

    Any popped_data = head->data;
    this->head = head->next;

    free(head);

    return popped_data;
}

/**
 * Iterate over list
 * 
 * @param iter function to call for each iteration
 * 
 */
void List_Iterate(List const this, void (*iter)(Any))
{
    for (ListNode curr = this->head; curr != nullptr; curr = curr->next)
        iter(curr->data);
}

/**
 * Free list
 */
void List_Dispose(List const this)
{
    ListNode curr = this->head;
    ListNode next;

    while (curr != nullptr) {
        free(curr->data);
        next = curr->next;
        free(curr);
        curr = next;
    }
}

/**
 * ToString
 */
const char* List_ToString(List const this)
{
    return "Dark.List";
}
/**
 * Constructor
 */
List List_Ctor(List const this)
{
    Object_Ctor(this);

    this->ToString      = &List_ToString;
    this->Iterate       = &List_Iterate;
    this->Add           = &List_Add;
    this->Push          = &List_Push;
    this->Pop           = &List_Pop;
    this->Dispose       = &List_Dispose;

    this->head = nullptr;

    return this;
}

List List_New()
{
    return List_Ctor(new(List));
}

