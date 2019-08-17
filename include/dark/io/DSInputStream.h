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

type (DSInputStream) {
    Class isa;
};

def_method (DSInputStream, ToString, const char*, (const DSInputStream* const) );
def_method (DSInputStream, ReadOne,         int,    (DSInputStream*) );
def_method (DSInputStream, Read,            int,    (DSInputStream*, IOBuff*, int, int) );
def_method (DSInputStream, Skip,            long,   (DSInputStream*, long) );
def_method (DSInputStream, Available,       int,    (DSInputStream*) );
def_method (DSInputStream, Close,           void,   (DSInputStream*) );
def_method (DSInputStream, Mark,            void,   (DSInputStream*, int) );
def_method (DSInputStream, MarkSupported,   bool,   (DSInputStream*) );
def_method (DSInputStream, Reset,           void,   (DSInputStream*) );

vtable (DSInputStream) {
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

vtable_ptr(DSInputStream);

method DSInputStream* DSInputStream_init(DSInputStream* const this) 
{
    DSObject_init(this);
    this->isa = objc_getClass("DSInputStream");
    return this;
}

method const char* ToString(const DSInputStream* const this) {
    return "DSInputStream";
}

method int ReadOne(DSInputStream* this)
{
    return -1;
}

method int Read(DSInputStream* this, IOBuff* b, int off, int len)
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

method long Skip(DSInputStream* this, long n) 
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

method int Available(DSInputStream* this)
{
    return 0;
}

method void Close(DSInputStream* this)
{
    get_vptr(DSInputStream)->Close(this);
}

method void Mark(DSInputStream* this, int readlimit)
{
    get_vptr(DSInputStream)->Mark(this, readlimit);
}

method bool MarkSupported(DSInputStream* this)
{
    return false;
}

method void Reset(DSInputStream* this)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}




class_bind( DSInputStream );

class_override( ToString,        (DSInputStreamToString)ToString, "$@:v" );
class_method( Equals,            (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (DSInputStreamReadOne)ReadOne, "i@:v" );
class_method( Read,              (DSInputStreamRead)Read, "i@:^ii" );
class_method( Skip,              (DSInputStreamSkip)Skip, "l@:l" );
class_method( Close,             (DSInputStreamClose)Close, "v@:v" );
class_method( Mark,              (DSInputStreamMark)Mark, "v@:i" );
class_method( MarkSupported,     (DSInputStreamMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (DSInputStreamReset)Reset, "v@:v" );
class_method( Available,         (DSInputStreamAvailable)Available, "B@:" );
class_methodize;
#endif _DSINPUT_STREAM_H_