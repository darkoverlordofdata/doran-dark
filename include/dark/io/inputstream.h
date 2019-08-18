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
#include <dark/types.h>
#include <dark/io/filesystem.h>

#define MAX_SKIP_BUFFER_SIZE 2048

type (InputStream) {
    Class isa;
};

method_proto (InputStream, ToString, const char*, (const InputStream* const) );
method_proto (InputStream, ReadOne,         int,    (InputStream*) );
method_proto (InputStream, Read,            int,    (InputStream*, IOBuff*, int, int) );
method_proto (InputStream, Skip,            long,   (InputStream*, long) );
method_proto (InputStream, Available,       int,    (InputStream*) );
method_proto (InputStream, Close,           void,   (InputStream*) );
method_proto (InputStream, Mark,            void,   (InputStream*, int) );
method_proto (InputStream, MarkSupported,   bool,   (InputStream*) );
method_proto (InputStream, Reset,           void,   (InputStream*) );

vtable (InputStream) {
    const InputStreamToString     ToString;
    const ObjectEquals            Equals;
    const ObjectGetHashCode       GetHashCode;
    const ObjectDispose           Dispose;
    const InputStreamReadOne      ReadOne;
    const InputStreamRead         Read;
    const InputStreamSkip         Skip;
    const InputStreamClose        Close;
    const InputStreamMark         Mark;
    const InputStreamMarkSupported MarkSupported;
    const InputStreamReset        Reset;
    const InputStreamAvailable    Available;
};

class_load( InputStream );
class_override( ToString,        (InputStreamToString)ToString, "$@:v" );
class_method( Equals,            (ObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (ObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (InputStreamReadOne)ReadOne, "i@:v" );
class_method( Read,              (InputStreamRead)Read, "i@:^ii" );
class_method( Skip,              (InputStreamSkip)Skip, "l@:l" );
class_method( Close,             (InputStreamClose)Close, "v@:v" );
class_method( Mark,              (InputStreamMark)Mark, "v@:i" );
class_method( MarkSupported,     (InputStreamMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (InputStreamReset)Reset, "v@:v" );
class_method( Available,         (InputStreamAvailable)Available, "B@:" );
class_fini;

method InputStream* InputStream_init(InputStream* const this) 
{
    Object_init(this);
    this->isa = objc_getClass("InputStream");
    return this;
}

method const char* ToString(const InputStream* const this) {
    return "InputStream";
}

method int ReadOne(InputStream* this)
{
    return -1;
}

method int Read(InputStream* this, IOBuff* b, int off, int len)
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

method long Skip(InputStream* this, long n) 
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

method int Available(InputStream* this)
{
    return 0;
}

method void Close(InputStream* this)
{
    _vptr(InputStream)->Close(this);
}

method void Mark(InputStream* this, int readlimit)
{
    _vptr(InputStream)->Mark(this, readlimit);
}

method bool MarkSupported(InputStream* this)
{
    return false;
}

method void Reset(InputStream* this)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}

