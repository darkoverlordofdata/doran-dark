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
#include <dark/collections/List.h>
/**
 * Constructor
 */
TList List_New() {
    return List_Ctor(new(List));
}

TList List_Ctor(TList const this)
{
    Collection_Ctor(this);
    this->isa = isa(List);
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
TListNode ListNode_Ctor(TListNode const this, Any data, TListNode next)
{
    this->data = data;
    this->next = next;
    return this;
}

TListNode ListNode_New(Any data, TListNode next)
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
int Insert(TList const this, Any data, int (*comp)(Any, Any))
{
    if (this->head == nullptr) {
        this->head = ListNode_New(data, nullptr);
        return 1;
    }

    // Find spot in linked list to insert new node
    TListNode prev = nullptr;
    TListNode curr = this->head;
    while (curr != nullptr && curr->data != nullptr && comp(curr->data, data) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) 
        this->head = ListNode_New(data, this->head);
    else 
        prev->next = ListNode_New(data, curr);

    this->length++;
    return 1;
}

/**
 * Add to end of list
 * 
 * @param data to insert
 * 
 */
void overload Add(TList const this, Any data)
{
    if (this->head == nullptr) {
        // this->head = ListNode_New(data, nullptr);
    }
    else { 
    //    this->head = ListNode_New(data, this->head);
    }
    this->length++;
}

/**
 * Remove item at end of list
 */
Any overload Remove(TList const this)
{
    TListNode head = this->head;

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
void Iterate(TList const this, void (*iter)(Any))
{
    for (TListNode curr = this->head; curr != nullptr; curr = curr->next)
        iter(curr->data);
}

/**
 * Free list
 */
void overload Dispose(TList const this)
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
int overload Length(TList const this)
{
    return this->length;
}


/**
 * ToString
 */
char* overload ToString(TList const this)
{
    return "dark.collections.List";
}

/**
 * List Class Metadata
 */
register (List)
{
    if (List.isa == nullptr) {
        List = (struct ListClass) {
            .isa            = &List,
            .superclass     = &Collection,
            .name           = "List",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .ToString       = ToString,
            .Dispose        = Dispose,
            .Length         = Length,
            .Iterate        = Iterate,
            .Insert         = Insert,
            .Add            = Add,
            .Remove         = Remove,
        };
        // AddMetadata(List);
    }
    return &List;
}


