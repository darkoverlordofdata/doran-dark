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
#include <dark/core.h>
#include <dark/Class.h>
#include <stdlib.h>
// #include "tgc.h" 

// tgc_t gc;

struct Node {
    void * data;
    struct Node * next;
};

static struct Node * root = nullptr;

static void Push(struct Node **head, void* data)
{
    struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->next = (*head);
    newNode->data = data;
    (*head) = newNode;
}

static void Dump(struct Node *node, void(*func)(void*))
{
    while (node != nullptr)
    {
        (*func)(node->data);
        node = node->next;
    }
}
void dark_free(TClass cls) 
{
    free(cls);
}

void* dark_malloc(size_t size)
{
    // void* ptr = calloc(1, size);
    // Push(&root, &ptr);
    // return ptr;
    return calloc(1, size);
}

void* dark_calloc(size_t num, size_t size)
{
    // void* ptr = calloc(num, size);
    // Push(&root, &ptr);
    // return ptr;
    return calloc(num, size);
}

/**
 *  start the garbage collector
 */
void __attribute__((constructor(101))) dark_gc_ctor()
{
    // int argc;
    // tgc_start(&gc, &argc);    
}

void __attribute__((destructor)) dark_gc_dtor()
{
    // tgc_stop(&gc);    
}

