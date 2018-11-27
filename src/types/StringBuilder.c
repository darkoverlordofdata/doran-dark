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
 * StringBuilder implementation
 */

static Exception(IndexOutOfBounds);

/*
 * sb_empty returns non-zero if the given StringBuilder is empty.
 */
int StringBuilder_Empty(StringBuilder this)
{
	return (this->root == nullptr);
}

/*
 * sb_append adds a copy of the given string to a StringBuilder.
 */
int StringBuilder_Append(StringBuilder this, const char *str)
{
	int	length = 0;
	StringFragment frag = nullptr;

	if (nullptr == str || '\0' == *str)
		return this->length;

	length = strlen(str);
	frag = (StringFragment) malloc(sizeof(StringFragment_t) + (sizeof(char) * length));
	if (nullptr == frag)
		return SB_FAILURE;

	frag->next = nullptr;
	frag->length = length;
	memcpy((void*) &frag->str, (const void*) str, sizeof(char) * (length + 1));

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
int StringBuilder_Appendf(StringBuilder this, const char *format, ...)
{
	int rc = 0;
	char buf[SB_MAX_FRAG_LENGTH];
	va_list args;

	va_start (args, format);
	rc = vsnprintf(&buf[0], SB_MAX_FRAG_LENGTH, format, args);
	va_end(args);

	if (0 > rc)
		return SB_FAILURE;

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
char StringBuilder_Concat(StringBuilder this)
{
	char *buf = nullptr;
	char *c = nullptr;
	StringFragment	frag = nullptr;

	buf = (char *) malloc((this->length + 1) * sizeof(char));
	if (nullptr == buf)
		return nullptr;

	c = buf;
	for (frag = this->root; frag; frag = frag->next) {
		memcpy(c, frag->str, sizeof(char) * frag->length);
		c += frag->length;
	}

	*c = '\0';
	return buf;
}

/*
 * sb_reset resets the given StringBuilder, freeing all previously appended
 * strings.
 */
void StringBuilder_Reset(StringBuilder this)
{
	StringFragment frag = nullptr;
	StringFragment next = nullptr;

	frag = this->root;
	while(frag) {
		next = frag->next;
		free(frag);
		frag = next;
	}

	this->root = nullptr;
	this->trunk = nullptr;
	this->length = 0;
}

/*
 * sb_free frees the given StringBuilder and all of its appended strings.
 */
void StringBuilder_Dispose(StringBuilder this)
{
	StringBuilder_Reset(this);
	free(this);
}


char* StringBuilder_ToString(StringBuilder this)
{
    return "dark.StringBuilder";
}

StringBuilder StringBuilder_Ctor(StringBuilder const this)
{
    DObject_Ctor(this);

    this->Append    = StringBuilder_Append;
    this->Appendf   = StringBuilder_Appendf;
    this->Concat    = StringBuilder_Concat;
    this->Dispose   = StringBuilder_Dispose;
    this->Empty     = StringBuilder_Empty;
    this->Reset     = StringBuilder_Reset;

    return this;
}

StringBuilder StringBuilder_New()
{
    return StringBuilder_Ctor(new(StringBuilder));
}
