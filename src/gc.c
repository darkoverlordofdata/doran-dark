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
#include <stdlib.h>
#include "tgc.h"
// #include <gc.h>
static tgc_t gc;

void* dark_malloc(size_t nbytes) {
    return tgc_calloc(&gc, 1, nbytes);
    // return calloc(1, nbytes);
    // return GC_malloc(nbytes);
}

/**
 *  start the garbage collector
 */
void __attribute__((constructor)) dark_gc_ctor()
{
    int argc;
    tgc_start(&gc, &argc);    
    // GC_INIT();
}

void __attribute__((destructor)) dark_gc_dtor()
{
    tgc_stop(&gc);    
}

