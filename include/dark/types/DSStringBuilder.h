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

IVAR (StringFragment)
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
IVAR (DSStringBuilder) {
    Class isa;
	StringFragment* root;
	StringFragment* trunk;
	int length;
};

METHOD (DSStringBuilder, ToString,        char*, (const DSStringBuilder* const));

static inline overload 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(DSStringBuilder* sb, const char *format, ...);
typedef int (*DSStringBuilderAppendf)   (DSStringBuilder* sb, const char *format, ...);

METHOD (DSStringBuilder, Appendc, 	int, (DSStringBuilder* sb, const char c));
METHOD (DSStringBuilder, Append,	int, (DSStringBuilder* sb, const char *str));
METHOD (DSStringBuilder, Concat,	DSString*, (const DSStringBuilder* sb));
METHOD (DSStringBuilder, Reset,		void, (DSStringBuilder* sb));
METHOD (DSStringBuilder, Empty,		int, (const DSStringBuilder* sb));
METHOD (DSStringBuilder, Dispose,	void, (DSStringBuilder* const));

/**
 * StringBuilder metaclass
 */
VTABLE (DSStringBuilder) {
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

DEF_VPTR(DSStringBuilder);

/* 
 * Constructor
 * create a new StringBuilder
 * 
 */
static inline DSStringBuilder* DSStringBuilder_init(DSStringBuilder* const this)
{
    DSObject_init(this);
    this->isa = objc_getClass("DSStringBuilder"); 
	return this;
}

static inline DSStringBuilder* NewDSStringBuilder() { 
	return DSStringBuilder_init(alloc(DSStringBuilder)); 
}

/*
 * sb_empty returns non-zero if the given StringBuilder is empty.
 */
static inline overload int Empty(const DSStringBuilder* this)
{
	return (this->root == nullptr);
}


static inline overload int Appendc(DSStringBuilder* this, const char c)
{
	char str[2] = { c, 0 };
	auto x = getVptr(DSStringBuilder)->Append(this, str);
	return x;
}
/*
 * sb_append adds a copy of the given string to a StringBuilder.
 */
static inline overload int Append(DSStringBuilder* this, const char *str)
{
	int	length = 0;
	struct StringFragment * frag = nullptr;

	if (nullptr == str || '\0' == *str)
		return this->length;

	length = strlen(str);
	frag = (StringFragment*) DScalloc(1, sizeof(struct StringFragment));
	if (nullptr == frag)
		throw DSOutOfMemoryException("StringBuilder::Append", Source);

	frag->next = nullptr;
	frag->length = length;
	frag->str = strdup(str);

	this->length += length;
	if (nullptr == this->root)
		this->root = frag;
	else
		this->trunk->next = frag;

	this->trunk = frag;
	return this->length;
}

/*
 * sb_appendf adds a copy of the given formatted string to a StringBuilder.
 */
static inline overload 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(DSStringBuilder* this, const char *format, ...)
{
	const int MAX_FRAG_LENGTH = 4096;
	int len = 0;
	char buf[MAX_FRAG_LENGTH];
	va_list args;

	va_start(args, format);
	len = vsnprintf(&buf[0], MAX_FRAG_LENGTH, format, args);
	va_end(args);

	if (0 > len)
		throw DSOutOfMemoryException("StringBuilder::Append", Source);

	return Append(this, buf);
}

/*
 * sb_concat returns a concatenation of strings that have been appended to the
 * StringBuilder. It is the callers responsibility to free the returned
 * reference.
 *
 * The StringBuilder is not modified by this function and can therefore continue
 * to be used.
 */
static inline overload DSString* Concat(const DSStringBuilder* this)
{
	char *buf = nullptr;
	char *c = nullptr;
	StringFragment* frag = nullptr;

	buf = DScalloc((this->length + 1), sizeof(char));
	if (nullptr == buf)
		return nullptr;

	c = buf;
	for (frag = this->root; frag; frag = frag->next) {
		memcpy(c, frag->str, sizeof(char) * frag->length);
		c += frag->length;
	}

	*c = '\0';
	return NewDSString(buf);
}

/*
 * sb_reset resets the given StringBuilder, freeing all previously appended
 * strings.
 */
static inline overload void Reset(DSStringBuilder* this)
{
	StringFragment* frag = nullptr;
	StringFragment* next = nullptr;


	this->root = nullptr;
	this->trunk = nullptr;
	this->length = 0;
}

/*
 * sb_free frees the given StringBuilder and all of its appended strings.
 */
static inline overload void Dispose(DSStringBuilder* this)
{
	Reset(this);
}


static inline overload char* ToString(const DSStringBuilder* this)
{
	return Concat(this);
    // return "dark.StringBuilder";
}




VTABLE_BIND( DSStringBuilder );

VTABLE_METHOD( ToString, 		    (DSStringBuilderToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_OVERRIDE( Dispose, 		(DSStringBuilderDispose)Dispose, "v@:v" );
VTABLE_METHOD( Append,			(DSStringBuilderAppend)Append, "i@:v" );
VTABLE_METHOD( Appendc, 			(DSStringBuilderAppendc)Appendc, "i@:c" );
VTABLE_METHOD( Appendf, 			(DSStringBuilderAppendf)Appendf, "i@:c." );
VTABLE_METHOD( Concat, 			(DSStringBuilderConcat)Concat, "$@:v" );
VTABLE_METHOD( Empty, 			(DSStringBuilderEmpty)Empty, "B@:v" );
VTABLE_METHOD( Reset, 			(DSStringBuilderReset)Reset, "v@:v" );

VTABLE_IVAR( root, sizeof( id ), "^" );
VTABLE_IVAR( trunk, sizeof( id ), "^" );
VTABLE_IVAR( length, sizeof( int ), "i" );

VTABLE_METHODIZE


#endif _DSSTRING_BUILDER_H_
