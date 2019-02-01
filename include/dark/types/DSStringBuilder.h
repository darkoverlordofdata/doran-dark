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

ivar (StringFragment)
{
	StringFragment * next;
	int length;
	char* str;
};

#define IsDSStringBuilder(object) _Generic((object), DSStringBuilder*: true, default: false)
#define AsDSStringBuilder(object) _Generic((object),                    \
                            DSStringBuilder*: (DSStringBuilder *)object,\
                            default: nullptr)


/**
 * StringBuilder class
 */
ivar (DSStringBuilder) {
    Class isa;
	StringFragment* root;
	StringFragment* trunk;
	int length;
};

DSStringBuilder* NewDSStringBuilder();
DSStringBuilder* DSStringBuilder_init(DSStringBuilder* const this);
DSStringBuilder* DSStringBuilder_alloc();

method (DSStringBuilder, ToString,        char*, (const DSStringBuilder* const));


__attribute__((__format__ (__printf__, 2, 3)))
int         overload Appendf(DSStringBuilder* sb, const char *format, ...);
int         overload Appendc(DSStringBuilder* sb, const char c);
int         overload Append(DSStringBuilder* sb, const char *str);
DSString*   overload Concat(const DSStringBuilder* sb);
void        overload Reset(DSStringBuilder* sb);
int         overload Empty(const DSStringBuilder* sb);
void        overload Dispose(DSStringBuilder* const);

typedef void        (*DSStringBuilderDispose)   (DSStringBuilder* const);
typedef int         (*DSStringBuilderAppendf)   (DSStringBuilder* sb, const char *format, ...);
typedef int         (*DSStringBuilderAppendc)   (DSStringBuilder* sb, const char c);
typedef int         (*DSStringBuilderAppend)    (DSStringBuilder* sb, const char *str);
typedef DSString*   (*DSStringBuilderConcat)    (const DSStringBuilder* sb);
typedef void        (*DSStringBuilderReset)     (DSStringBuilder* sb);
typedef int         (*DSStringBuilderEmpty)     (const DSStringBuilder* sb);


/**
 * StringBuilder metaclass
 */
vtable (DSStringBuilder) {
    const DSStringBuilderToString   ToString;
    const DSObjectEquals            Equals;
    const DSObjectGetHashCode       GetHashCode;
    const DSStringBuilderDispose    Dispose;
    const DSStringBuilderAppend     Append;
    const DSStringBuilderAppendc    Appendc;
    const DSStringBuilderAppendf    Appendf;
    const DSStringBuilderConcat     Concat;
    const DSStringBuilderEmpty      Empty;        
    const DSStringBuilderReset      Reset;
};

#endif _DSSTRING_BUILDER_H_
