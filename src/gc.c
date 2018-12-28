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

/**
 * free the memory for this ptr
 */
// void DS_free(TClass cls) 
void DSFree(void* ptr) 
{
    GC_FREE(ptr);
}

/**
 * malloc size bytes
 */
void* DSMalloc(size_t size)
{
    void* ptr = GC_MALLOC(size);
    return ptr;
}

/**
 * realloc size bytes from old pointer
 */
void* DSRealloc(void * old, size_t new_size)
{
    void* ptr = GC_REALLOC(old, new_size);
    return ptr;

}

/**
 * malloc num * size bytes
 */
void* DSCalloc(size_t num, size_t size)
{
    void* ptr = GC_MALLOC(num * size);
    return ptr;
}

/**
 * Explicitly force a garbage collection.
 */
void DSCollect()
{
    GC_gcollect();
}

/**
 *  start the garbage collector
 */
void __attribute__((constructor(101))) DSGCStart()
{
    GC_INIT();
    GC_enable_incremental();
}

/**
 *  stop the garbage collector
 */
void __attribute__((destructor)) DSGCStop()
{
}

