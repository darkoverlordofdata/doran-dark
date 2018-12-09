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
	StringFragment	next;
	int	            length;
	char*			str;
};

/**
 * Object class
 */
class (StringBuilder) 
{
    StringBuilderClass_t* isa;
	StringFragment	    root;
	StringFragment	    trunk;
	int					length;
};

/**
 * Object metaclass
 */
typedef struct StringBuilderClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class   isa;
            Class   superclass;
            char*   name;
            char*   (*ToString) (Object const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
            int     (*Empty) (StringBuilder const);
            int     (*Append) (StringBuilder const, char* str);
            int     (*Appendc) (StringBuilder const, char c);
            int     (*Appendf) (StringBuilder const, char* str, ...);
            String  (*Concat) (StringBuilder const);
            void    (*Reset) (StringBuilder const);
        };
    };
};


StringBuilder StringBuilder_New();
int StringBuilder_Empty(StringBuilder sb);
int StringBuilder_Appendc(StringBuilder sb, const char c);
int StringBuilder_Append(StringBuilder sb, const char *str);
__attribute__((__format__ (__printf__, 2, 3)))
int StringBuilder_Appendf(StringBuilder sb, const char *format, ...);
String StringBuilder_Concat(StringBuilder sb);
void StringBuilder_Reset(StringBuilder sb);
StringBuilder StringBuilder_Ctor(StringBuilder const this);

#endif _STRING_BUILDER_H_
