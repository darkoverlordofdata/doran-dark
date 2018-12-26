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
#include <gc.h>
// #include "tgc.h" 

// tgc_t gc;

void dark_free(TClass cls) 
{
    // printf("GC_FREE(%x)\n", (void*)cls);
    GC_FREE(cls);
    free(cls);
}

void* dark_malloc(size_t size)
{
    // void* ptr = calloc(1, size);
    void* ptr = GC_MALLOC(size);
    // printf("GC_MALLOC(%d) = %x\n", size, ptr);
    return ptr;
}

void* dark_realloc(void * old, size_t new_size)
{
    void* ptr = GC_REALLOC(old, new_size);
    return ptr;

}
void* dark_calloc(size_t num, size_t size)
{
    // void* ptr = calloc(num, size);
    void* ptr = GC_MALLOC(num * size);
    // printf("GC_MALLOC(%d * %d) = %x\n", num, size, ptr);
    return ptr;
}

/**
 *  start the garbage collector
 */
void __attribute__((constructor(101))) dark_gc_ctor()
{
    // printf("GC_INIT\n");
    GC_INIT();
}

void __attribute__((destructor)) dark_gc_dtor()
{
}

