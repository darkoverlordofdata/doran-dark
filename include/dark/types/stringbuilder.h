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
#include <string.h>
#include <dark/types/string.h>

#define IsStringBuilder(object) _Generic((object), StringBuilder*: true, default: false)
#define AsStringBuilder(object) _Generic((object),                    \
                            StringBuilder*: (StringBuilder *)object,\
                            default: nullptr)


type (StringFragment)
{
	StringFragment * next;
	int length;
	char* str;
};
/**
 * StringBuilder class
 */
type (StringBuilder) {
    Class isa;
	StringFragment* root;
	StringFragment* trunk;
	int length;
};

interface (StringBuilder, ToString,        char*, (const StringBuilder* const));

method 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(StringBuilder* sb, const char *format, ...);
typedef int (*StringBuilderAppendf)   (StringBuilder* sb, const char *format, ...);

interface (StringBuilder, Appendc, 	int, (StringBuilder* sb, const char c));
interface (StringBuilder, Append,	int, (StringBuilder* sb, const char *str));
interface (StringBuilder, Concat,	String*, (const StringBuilder* sb));
interface (StringBuilder, Reset,		void, (StringBuilder* sb));
interface (StringBuilder, Empty,		int, (const StringBuilder* sb));
interface (StringBuilder, Dispose,	void, (StringBuilder* const));

/**
 * StringBuilder metaclass
 */
vtable (StringBuilder) {
    const StringBuilderToString   ToString;
    const ObjectEquals            Equals;
    const ObjectGetHashCode       GetHashCode;
    const StringBuilderDispose    Dispose;
    const StringBuilderAppend     Append;
    const StringBuilderAppendc    Appendc;
    const StringBuilderAppendf    Appendf;
    const StringBuilderConcat     Concat;
    const StringBuilderEmpty      Empty;        
    const StringBuilderReset      Reset;
};

function vptr(StringBuilder);
/**
 * 
 * Class Loader callback
 */
function objc_loadStringBuilder(Class super) 
{
    Class cls = createClass(super, StringBuilder);
	addMethod(cls, StringBuilderToString, 	ToString);
	addMethod(cls, ObjectEquals, 			Equals);
	addMethod(cls, ObjectGetHashCode, 		GetHashCode);
	addMethod(cls, StringBuilderDispose, 	Dispose);
	addMethod(cls, StringBuilderAppend, 	Append);
	addMethod(cls, StringBuilderAppendc, 	Appendc);
	addMethod(cls, StringBuilderAppendf, 	Appendf);
	addMethod(cls, StringBuilderConcat, 	Concat);
	addMethod(cls, StringBuilderEmpty, 		Empty);
	addMethod(cls, StringBuilderReset, 		Reset);
    
    return cls;
}


/* 
 * Constructor
 * create a new StringBuilder
 * 
 */
function StringBuilder* StringBuilder_init(StringBuilder* const this)
{
    Object_init(this);
    this->isa = objc_getClass("StringBuilder"); 
	return this;
}

function StringBuilder* NewStringBuilder() { 
	return StringBuilder_init(alloc(StringBuilder)); 
}

/*
 * sb_empty returns non-zero if the given StringBuilder is empty.
 */
method int Empty(const StringBuilder* this)
{
	return (this->root == nullptr);
}


method int Appendc(StringBuilder* this, const char c)
{
	char str[2] = { c, 0 };
	auto x = get_vptr(StringBuilder)->Append(this, str);
	return x;
}
/*
 * sb_append adds a copy of the given string to a StringBuilder.
 */
method int Append(StringBuilder* this, const char *str)
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
method 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(StringBuilder* this, const char *format, ...)
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
method String* Concat(const StringBuilder* this)
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
	return NewString(buf);
}

/*
 * sb_reset resets the given StringBuilder, freeing all previously appended
 * strings.
 */
method void Reset(StringBuilder* this)
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
method void Dispose(StringBuilder* this)
{
	Reset(this);
}


method char* ToString(const StringBuilder* this)
{
	return Concat(this);
    // return "dark.StringBuilder";
}
