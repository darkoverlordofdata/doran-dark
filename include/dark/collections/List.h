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
#include "../DObject.h"

class (ListNode)
{
    Any data;
    ListNode next;
};

class (List)
{
    union {
        DObject_t _;
        struct 
        {
            retained
            char*       (*ToString)(DObject const);
            bool        (*Equals)(DObject const, DObject const);
            int         (*GetHashCode)(DObject const);
            void        (*Dispose) (DObject const);
        };
    };
    ListNode head;

    /* List_add_inorder: Add to sorted linked list */
    int (*Add) (List const, Any data, int (*comp)(Any, Any));

    /* List_push: Add to head of list */
    void (*Push) (List const, Any data);

    /* List_pop: remove and return head of linked list */
    void (*Pop) (List const);

    /* List_print: print linked list */
    void (*Iterate) (List const, void (*iter)(Any data));
};


/**
 * List API
 */
int List_Add(List const, Any data, int (*comp)(Any, Any));
void List_Push(List const, Any data);
Any List_Pop(List const);
void List_Iterate(List const, void (*iter)(Any));
void List_Dispose(List const);
const char* List_ToString(List const);
List List_New();

#endif _LIST_H_ 
