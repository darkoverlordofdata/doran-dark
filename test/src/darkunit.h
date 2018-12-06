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
#ifndef _DARKUNIT_H_
#define _DARKUNIT_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <Block.h>
/**
 * Inspired by [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html)
 * 
 * Compiler/linker flags needed to enable c99 lambda's:
 * 
 *  -LC:/msys64/mingw64/bin
 *  -lBlocksRuntime -fblocks
 * 
 */
typedef struct test_stats {
    int total;
    int failed;
    int passed;
} test_stats;
test_stats tests;

void Describe(char* desc, void (^lambda)());

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define error(MSG, ...) { \
    printf("[ERROR] (%s:%s:%i) ", __FILENAME__, __func__, __LINE__); \
    printf(MSG, ##__VA_ARGS__); }

#define It(desc, test) do { \
    printf("%s - ", desc); \
    int r=test(); \
    tests.total++; \
    if (r) tests.failed++; \
    else tests.passed++; \
} while(0)

#define Expect(test) do { \
    if (!(test)) { \
        printf(" failed (%s:%i)\n", __FILENAME__, __LINE__); \
        return 1; \
    } else { \
        printf(" passed \n"); \
        return 0; \
    } \
} while(0)


#endif _DARKUNIT_H_
