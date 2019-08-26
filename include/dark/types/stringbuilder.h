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

delegate (StringBuilder, New,     	StringBuilder*, (StringBuilder*));
delegate (StringBuilder, ToString,  char*, (const StringBuilder* const));

method 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(StringBuilder* sb, const char *format, ...);
typedef int (*StringBuilderAppendf)   (StringBuilder* sb, const char *format, ...);

delegate (StringBuilder, Appendc, 	int, (StringBuilder* sb, const char c));
delegate (StringBuilder, Append,	int, (StringBuilder* sb, const char *str));
delegate (StringBuilder, Concat,	String*, (const StringBuilder* sb));
delegate (StringBuilder, Reset,		void, (StringBuilder* sb));
delegate (StringBuilder, Empty,		int, (const StringBuilder* sb));
delegate (StringBuilder, Dispose,	void, (StringBuilder* const));

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

static inline vptr(StringBuilder);
/**
 * 
 * Class Loader callback
 */
static inline Class ClassLoadStringBuilder(Class base) 
{
    Class cls = createClass(base, StringBuilder);
	addMethod(cls, StringBuilder, 	ToString);
	addMethod(cls, Object, 			Equals);
	addMethod(cls, Object, 		GetHashCode);
	addMethod(cls, StringBuilder, 	Dispose);
	addMethod(cls, StringBuilder, 	Append);
	addMethod(cls, StringBuilder, 	Appendc);
	addMethod(cls, StringBuilder, 	Appendf);
	addMethod(cls, StringBuilder, 	Concat);
	addMethod(cls, StringBuilder, 	Empty);
	addMethod(cls, StringBuilder, 	Reset);
    
    return cls;
}


/* 
 * Constructor
 * create a new StringBuilder
 * 
 */
method StringBuilder* New(StringBuilder* self)
{
    extends(Object);
    set_isa(StringBuilder); 
	return self;
}

/*
 * sb_empty returns non-zero if the given StringBuilder is empty.
 */
method int Empty(const StringBuilder* self)
{
	return (self->root == nullptr);
}


method int Appendc(StringBuilder* self, const char c)
{
	char str[2] = { c, 0 };
	auto x = virtual(StringBuilder)->Append(self, str);
	return x;
}
/*
 * sb_append adds a copy of the given string to a StringBuilder.
 */
method int Append(StringBuilder* self, const char *str)
{
	int	length = 0;
	struct StringFragment * frag = nullptr;

	if (nullptr == str || '\0' == *str)
		return self->length;

	length = strlen(str);
	frag = (StringFragment*) DScalloc(1, sizeof(struct StringFragment));
	if (nullptr == frag)
		throw DSOutOfMemoryException("StringBuilder::Append", Source);

	frag->next = nullptr;
	frag->length = length;
	frag->str = strdup(str);

	self->length += length;
	if (nullptr == self->root)
		self->root = frag;
	else
		self->trunk->next = frag;

	self->trunk = frag;
	return self->length;
}

/*
 * sb_appendf adds a copy of the given formatted string to a StringBuilder.
 */
method 
__attribute__((__format__ (__printf__, 2, 3)))
int Appendf(StringBuilder* self, const char *format, ...)
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

	return Append(self, buf);
}

/*
 * sb_concat returns a concatenation of strings that have been appended to the
 * StringBuilder. It is the callers responsibility to free the returned
 * reference.
 *
 * The StringBuilder is not modified by self function and can therefore continue
 * to be used.
 */
method String* Concat(const StringBuilder* self)
{
	char *buf = nullptr;
	char *c = nullptr;
	StringFragment* frag = nullptr;

	buf = DScalloc((self->length + 1), sizeof(char));
	if (nullptr == buf)
		return nullptr;

	c = buf;
	for (frag = self->root; frag; frag = frag->next) {
		memcpy(c, frag->str, sizeof(char) * frag->length);
		c += frag->length;
	}

	*c = '\0';
	return new(String, buf);
}

/*
 * sb_reset resets the given StringBuilder, freeing all previously appended
 * strings.
 */
method void Reset(StringBuilder* self)
{
	StringFragment* frag = nullptr;
	StringFragment* next = nullptr;


	self->root = nullptr;
	self->trunk = nullptr;
	self->length = 0;
}

/*
 * sb_free frees the given StringBuilder and all of its appended strings.
 */
method void Dispose(StringBuilder* self)
{
	Reset(self);
}


method char* ToString(const StringBuilder* self)
{
	return Concat(self);
    // return "dark.StringBuilder";
}
