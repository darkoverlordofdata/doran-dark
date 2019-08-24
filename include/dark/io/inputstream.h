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

delegate (InputStream, New,         InputStream*, (InputStream*) );
delegate (InputStream, ToString, const char*, (const InputStream* const) );
delegate (InputStream, ReadOne,         int,    (InputStream*) );
delegate (InputStream, Read,            int,    (InputStream*, IOBuff*, int, int) );
delegate (InputStream, Skip,            long,   (InputStream*, long) );
delegate (InputStream, Available,       int,    (InputStream*) );
delegate (InputStream, Close,           void,   (InputStream*) );
delegate (InputStream, Mark,            void,   (InputStream*, int) );
delegate (InputStream, MarkSupported,   bool,   (InputStream*) );
delegate (InputStream, Reset,           void,   (InputStream*) );

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

static inline vptr(InputStream);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadInputStream(Class super) 
{
    Class cls = createClass(super, InputStream);
    addMethod(cls, InputStream, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, InputStream, ReadOne);
    addMethod(cls, InputStream, Read);
    addMethod(cls, InputStream, Skip);
    addMethod(cls, InputStream, Close);
    addMethod(cls, InputStream, Mark);
    addMethod(cls, InputStream, MarkSupported);
    addMethod(cls, InputStream, Reset);
    addMethod(cls, InputStream, Available);
    
    return cls;
}


method InputStream* New(InputStream* self) 
{
    extends(Object);
    self->isa = objc_getClass("InputStream");
    return self;
}

method const char* ToString(const InputStream* const self) {
    return "InputStream";
}

method int ReadOne(InputStream* self)
{
    return -1;
}

method int Read(InputStream* self, IOBuff* b, int off, int len)
{
    if (b == nullptr)
        throw DSNullPointerException(Source);
    else if (off < 0 || len < 0 || len > b->len - off)
        throw DSIndexOutOfBoundsException(off, Source);
    else if (len == 0) {
        len = b->len;
        if (len == 0) return 0;
    }

    int c = ReadOne(self);
    if (c == -1) return -1;
    b->buff[off] = (char)c;

    int i = 1;
    for (; i<len; i++) {
        c = ReadOne(self);
        if (c == -1) break;
        b->buff[off + i] = (char)c;
    }
    return i;
}

method long Skip(InputStream* self, long n) 
{
    long remaining = n;
    int nr;

    if (n <= 0) return 0;

    int size = Min(MAX_SKIP_BUFFER_SIZE, remaining);
    IOBuff skipBuffer;
    skipBuffer.buff = DSmalloc(size);
    skipBuffer.len = size;

    while (remaining > 0) {
        nr = Read(self, &skipBuffer, 0, Min(size, remaining));
        if (nr < 0) break;
        remaining = nr;
    }
    return n - remaining;
}

method int Available(InputStream* self)
{
    return 0;
}

method void Close(InputStream* self)
{
    virtual(InputStream)->Close(self);
}

method void Mark(InputStream* self, int readlimit)
{
    virtual(InputStream)->Mark(self, readlimit);
}

method bool MarkSupported(InputStream* self)
{
    return false;
}

method void Reset(InputStream* self)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}

