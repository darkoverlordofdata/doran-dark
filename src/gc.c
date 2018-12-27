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

#define USE_BOEHM 
#ifdef USE_BOEHM
#include <gc.h>
#else
#include <GC/gc.h>
// unforunately, tgc is too eager and crashes
// on the other hand, GC is GPL. 

// #include "tgc.h" 
// tgc_t gc;
#endif

/**
 * free the memory for this ptr
 */
// void darko_free(TClass cls) 
void darko_free(void* ptr) 
{
    #ifdef USE_BOEHM
    GC_FREE(ptr);
    #else
    GC_free(ptr);
    // tgc_free(&gc, ptr);
    #endif
}

/**
 * malloc size bytes
 */
void* darko_malloc(size_t size)
{
    #ifdef USE_BOEHM
    void* ptr = GC_MALLOC(size);
    #else
    void* ptr = GC_malloc(size);
    // void* ptr = tgc_calloc(&gc, 1, size);
    #endif
    return ptr;
}

/**
 * realloc size bytes from old pointer
 */
void* darko_realloc(void * old, size_t new_size)
{
    #ifdef USE_BOEHM
    void* ptr = GC_REALLOC(old, new_size);
    #else
    void* ptr = GC_realloc(old, new_size);
    // void* ptr = tgc_realloc(&gc, old, new_size);
    #endif
    return ptr;

}

/**
 * malloc num * size bytes
 */
void* darko_calloc(size_t num, size_t size)
{
    #ifdef USE_BOEHM
    void* ptr = GC_MALLOC(num * size);
    #else
    void* ptr = GC_malloc(num * size);
    // void* ptr = tgc_calloc(&gc, num, size);
    #endif
    return ptr;
}

/**
 * Explicitly force a garbage collection.
 */
void darko_gc()
{
    #ifdef USE_BOEHM
    GC_gcollect();
    #else
    GC_gcollect();
    #endif
}

/**
 *  start the garbage collector
 */
void __attribute__((constructor(101))) darko_gc_ctor()
{
    #ifdef USE_BOEHM
    GC_INIT();
    GC_enable_incremental();
    #else
    // int argc;
    // tgc_start(&gc, &argc);
    GC_init();
    #endif
}

/**
 *  stop the garbage collector
 */
void __attribute__((destructor)) darko_gc_dtor()
{
    #ifdef USE_BOEHM
    #else
    // tgc_stop(&gc);
    #endif

}

