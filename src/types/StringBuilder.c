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
#include <dark/types/StringBuilder.h>
/* 
 * Throws OutOfMemoryException:
 */
static Exception(OutOfMemory);

/* 
 * Constructor
 * create a new StringBuilder
 * 
 */
TStringBuilder StringBuilder_Ctor(TStringBuilder const this)
{
    Object_Ctor(this);
    this->isa = isa(StringBuilder);
	return this;
}


/*
 * sb_empty returns non-zero if the given StringBuilder is empty.
 */
int StringBuilder_Empty(TStringBuilder this)
{
	return (this->root == nullptr);
}


int StringBuilder_Appendc(TStringBuilder this, const char c)
{
	char str[2] = { c, 0 };
	return this->isa->Append(this, str);
}
/*
 * sb_append adds a copy of the given string to a StringBuilder.
 */
int StringBuilder_Append(TStringBuilder this, const char *str)
{
	int	length = 0;
	struct StringFragment * frag = nullptr;

	if (nullptr == str || '\0' == *str)
		return this->length;

	length = strlen(str);
	frag = (TStringFragment) dark_calloc(1, sizeof(struct StringFragment));
	if (nullptr == frag)
		return OutOfMemoryException("StringBuilder::Append");

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
__attribute__((__format__ (__printf__, 2, 3)))
int StringBuilder_Appendf(TStringBuilder this, const char *format, ...)
{
	const int MAX_FRAG_LENGTH = 4096;
	int len = 0;
	char buf[MAX_FRAG_LENGTH];
	va_list args;

	va_start(args, format);
	len = vsnprintf(&buf[0], MAX_FRAG_LENGTH, format, args);
	va_end(args);

	if (0 > len)
		return OutOfMemoryException("StringBuilder::Append");

	return StringBuilder_Append(this, buf);
}

/*
 * sb_concat returns a concatenation of strings that have been appended to the
 * StringBuilder. It is the callers responsibility to free the returned
 * reference.
 *
 * The StringBuilder is not modified by this function and can therefore continue
 * to be used.
 */
TString StringBuilder_Concat(TStringBuilder this)
{
	char *buf = nullptr;
	char *c = nullptr;
	struct StringFragment * frag = nullptr;

	buf = dark_calloc((this->length + 1), sizeof(char));
	if (nullptr == buf)
		return nullptr;

	c = buf;
	for (frag = this->root; frag; frag = frag->next) {
		memcpy(c, frag->str, sizeof(char) * frag->length);
		c += frag->length;
	}

	*c = '\0';
	return String.Create(buf);
}

/*
 * sb_reset resets the given StringBuilder, freeing all previously appended
 * strings.
 */
void StringBuilder_Reset(TStringBuilder this)
{
	struct StringFragment * frag = nullptr;
	struct StringFragment * next = nullptr;


	this->root = nullptr;
	this->trunk = nullptr;
	this->length = 0;
}

/*
 * sb_free frees the given StringBuilder and all of its appended strings.
 */
void StringBuilder_Dispose(TStringBuilder this)
{
	StringBuilder_Reset(this);
}


char* StringBuilder_ToString(TStringBuilder this)
{
    return "dark.StringBuilder";
}

static struct StringBuilder* Create() { 
	return StringBuilder_Ctor(new(StringBuilder)); 
}

/**
 * StringBuilder Class Metadata
 */
register (StringBuilder)
{
	if (StringBuilder.isa == nullptr) {
		StringBuilder = (struct StringBuilderClass) {
			.isa            = &StringBuilder,
			.superclass     = &Comparable,
			.name           = "StringBuilder",
			.Equals         = Object.Equals,
			.GetHashCode    = Object.GetHashCode,
			.Dispose        = Object.Dispose,
			.ReferenceEquals= Object.ReferenceEquals,
			.InstanceEquals = Object.InstanceEquals,
			.Append    		= StringBuilder_Append,
			.Appendc 		= StringBuilder_Appendc,
			.Appendf   		= StringBuilder_Appendf,
			.Concat    		= StringBuilder_Concat,
			.Dispose   		= StringBuilder_Dispose,
			.Empty     		= StringBuilder_Empty,
			.Reset     		= StringBuilder_Reset,
            .Create         = Create,
		};
        AddMetadata(StringBuilder);
	}
	return &StringBuilder;
}

