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
#include <dark/Foundation.h>
#include <Block.h>

void Describe(char* desc, void (^lambda)());
void It(char* desc, void (^lambda)());
int Summary();

int TestCountInc();
int TestFailInc();
int TestPassInc();

/**
 *  MACRO Expect
 *      this is done as a macro so we can display the
 *      actual source file location for each failure.
 *  
 *      'test' must be an expression that resolves to true or false
 */
#define Expect(test)                                                    \
({                                                                      \
    if (!(test)) {                                                      \
        DSLog(" failed (%s:%i)", __FILENAME__, __LINE__);               \
	    TestPassInc();                                                  \
    } else {                                                            \
        DSLog(" passed");                                               \
	    TestFailInc();                                                  \
    }                                                                   \
    TestCountInc();                                                     \
})

#endif _DARKUNIT_H_
