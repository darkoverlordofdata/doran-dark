/*
 * Copyright 2017 Ryan Armstrong <ryan@cavaliercoder.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * C String Builder - https://github.com/cavaliercoder/c-stringbuilder
 *
 * sb.c is a simple, non-thread safe String Builder that makes use of a
 * dynamically-allocated linked-list to enable linear time appending and
 * concatenation.
 */
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
#pragma once
#ifndef _DSSTRING_BUILDER_H_
#define _DSSTRING_BUILDER_H_
#include <string.h>
#include "DSString.h"

class (StringFragment)
{
	StringFragment * next;
	int length;
	char* str;
};

#define IsDSStringBuilder(x) (x->isa == &DSStringBuilderClass)
#define AsDSStringBuilder(x) (IsDSStringBuilder(x) ? (DSStringBuilder *)x : nullptr)


/**
 * StringBuilder class
 */
class (DSStringBuilder) 
{
    struct DSStringBuilderClass* isa;
	StringFragment* root;
	StringFragment* trunk;
	int length;
};

/**
 * StringBuilder metaclass
 */
struct DSStringBuilderClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    char*   (*ToString) (DSStringBuilder* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    DSStringBuilder*(*Create) ();
    int     (*Empty) (DSStringBuilder* const);
    int     (*Append) (DSStringBuilder* const, char* str);
    int     (*Appendc) (DSStringBuilder* const, char c);
    int     (*Appendf) (DSStringBuilder* const, char* str, ...);
    DSString* (*Concat) (DSStringBuilder* const);
    void    (*Reset) (DSStringBuilder* const);

} DSStringBuilderClass;

__attribute__((__format__ (__printf__, 2, 3)))
int StringBuilder_Appendf(DSStringBuilder* sb, const char *format, ...);
int StringBuilder_Appendc(DSStringBuilder* sb, const char c);
int StringBuilder_Append(DSStringBuilder* sb, const char *str);
DSString* StringBuilder_Concat(DSStringBuilder* sb);
void StringBuilder_Reset(DSStringBuilder* sb);
int StringBuilder_Empty(DSStringBuilder* sb);

#endif _DSSTRING_BUILDER_H_
