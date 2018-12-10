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
#ifndef _STRING_BUILDER_H_
#define _STRING_BUILDER_H_
#include <string.h>
#include "String.h"

class (StringFragment)
{
	struct StringFragment * next;
	int length;
	char* str;
};

#define IsStringBuilder(x) (x->isa == &StringBuilder)
#define AsStringBuilder(x) (IsStringBuilder(x) ? (struct StringBuilder *)x : nullptr)


/**
 * Object class
 */
class (StringBuilder) 
{
    struct StringBuilderClass * isa;
	struct StringFragment * root;
	struct StringFragment * trunk;
	int length;
};

/**
 * Object metaclass
 */
struct StringBuilderClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TStringBuilder const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TStringBuilder(*Create) ();
            int     (*Empty) (TStringBuilder const);
            int     (*Append) (TStringBuilder const, char* str);
            int     (*Appendc) (TStringBuilder const, char c);
            int     (*Appendf) (TStringBuilder const, char* str, ...);
            TString (*Concat) (TStringBuilder const);
            void    (*Reset) (TStringBuilder const);
        };
    };
};


TStringBuilder StringBuilder_New();
int StringBuilder_Empty(TStringBuilder sb);
int StringBuilder_Appendc(TStringBuilder sb, const char c);
int StringBuilder_Append(TStringBuilder sb, const char *str);
__attribute__((__format__ (__printf__, 2, 3)))
int StringBuilder_Appendf(TStringBuilder sb, const char *format, ...);
TString StringBuilder_Concat(TStringBuilder sb);
void StringBuilder_Reset(TStringBuilder sb);
TStringBuilder StringBuilder_Ctor(TStringBuilder const this);

#endif _STRING_BUILDER_H_
