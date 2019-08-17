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
#ifndef _DSINPUT_STREAM_H_
#define _DSINPUT_STREAM_H_
#include "../types.h"
#include "DSFileSystem.h"

#define MAX_SKIP_BUFFER_SIZE 2048

IVAR (DSInputStream) {
    Class isa;
};

METHOD (DSInputStream, ToString, const char*, (const DSInputStream* const) );
METHOD (DSInputStream, ReadOne,         int,    (DSInputStream*) );
METHOD (DSInputStream, Read,            int,    (DSInputStream*, IOBuff*, int, int) );
METHOD (DSInputStream, Skip,            long,   (DSInputStream*, long) );
METHOD (DSInputStream, Available,       int,    (DSInputStream*) );
METHOD (DSInputStream, Close,           void,   (DSInputStream*) );
METHOD (DSInputStream, Mark,            void,   (DSInputStream*, int) );
METHOD (DSInputStream, MarkSupported,   bool,   (DSInputStream*) );
METHOD (DSInputStream, Reset,           void,   (DSInputStream*) );

VTABLE (DSInputStream) {
    const DSInputStreamToString     ToString;
    const DSObjectEquals            Equals;
    const DSObjectGetHashCode       GetHashCode;
    const DSObjectDispose           Dispose;
    const DSInputStreamReadOne      ReadOne;
    const DSInputStreamRead         Read;
    const DSInputStreamSkip         Skip;
    const DSInputStreamClose        Close;
    const DSInputStreamMark         Mark;
    const DSInputStreamMarkSupported MarkSupported;
    const DSInputStreamReset        Reset;
    const DSInputStreamAvailable    Available;
};

DEF_VPTR(DSInputStream);

static inline overload DSInputStream* DSInputStream_init(DSInputStream* const this) 
{
    DSObject_init(this);
    this->isa = objc_getClass("DSInputStream");
    return this;
}

static inline overload const char* ToString(const DSInputStream* const this) {
    return "DSInputStream";
}

static inline overload int ReadOne(DSInputStream* this)
{
    return -1;
}

static inline overload int Read(DSInputStream* this, IOBuff* b, int off, int len)
{
    if (b == nullptr)
        throw DSNullPointerException(Source);
    else if (off < 0 || len < 0 || len > b->len - off)
        throw DSIndexOutOfBoundsException(off, Source);
    else if (len == 0) {
        len = b->len;
        if (len == 0) return 0;
    }

    int c = ReadOne(this);
    if (c == -1) return -1;
    b->buff[off] = (char)c;

    int i = 1;
    for (; i<len; i++) {
        c = ReadOne(this);
        if (c == -1) break;
        b->buff[off + i] = (char)c;
    }
    return i;
}

static inline overload long Skip(DSInputStream* this, long n) 
{
    long remaining = n;
    int nr;

    if (n <= 0) return 0;

    int size = Min(MAX_SKIP_BUFFER_SIZE, remaining);
    IOBuff skipBuffer;
    skipBuffer.buff = DSmalloc(size);
    skipBuffer.len = size;

    while (remaining > 0) {
        nr = Read(this, &skipBuffer, 0, Min(size, remaining));
        if (nr < 0) break;
        remaining = nr;
    }
    return n - remaining;
}

static inline overload int Available(DSInputStream* this)
{
    return 0;
}

static inline overload void Close(DSInputStream* this)
{
    getVptr(DSInputStream)->Close(this);
}

static inline overload void Mark(DSInputStream* this, int readlimit)
{
    getVptr(DSInputStream)->Mark(this, readlimit);
}

static inline overload bool MarkSupported(DSInputStream* this)
{
    return false;
}

static inline overload void Reset(DSInputStream* this)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}




VTABLE_BIND( DSInputStream );

VTABLE_OVERRIDE( ToString,        (DSInputStreamToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_METHOD( ReadOne,           (DSInputStreamReadOne)ReadOne, "i@:v" );
VTABLE_METHOD( Read,              (DSInputStreamRead)Read, "i@:^ii" );
VTABLE_METHOD( Skip,              (DSInputStreamSkip)Skip, "l@:l" );
VTABLE_METHOD( Close,             (DSInputStreamClose)Close, "v@:v" );
VTABLE_METHOD( Mark,              (DSInputStreamMark)Mark, "v@:i" );
VTABLE_METHOD( MarkSupported,     (DSInputStreamMarkSupported)MarkSupported, "v@:v" );
VTABLE_METHOD( Reset,             (DSInputStreamReset)Reset, "v@:v" );
VTABLE_METHOD( Available,         (DSInputStreamAvailable)Available, "B@:" );
VTABLE_METHODIZE;
#endif _DSINPUT_STREAM_H_