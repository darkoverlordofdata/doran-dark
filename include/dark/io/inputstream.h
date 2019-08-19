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

interface (InputStream, ToString, const char*, (const InputStream* const) );
interface (InputStream, ReadOne,         int,    (InputStream*) );
interface (InputStream, Read,            int,    (InputStream*, IOBuff*, int, int) );
interface (InputStream, Skip,            long,   (InputStream*, long) );
interface (InputStream, Available,       int,    (InputStream*) );
interface (InputStream, Close,           void,   (InputStream*) );
interface (InputStream, Mark,            void,   (InputStream*, int) );
interface (InputStream, MarkSupported,   bool,   (InputStream*) );
interface (InputStream, Reset,           void,   (InputStream*) );

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

function vptr(InputStream);
/**
 * 
 * Class Loader callback
 */
function objc_loadInputStream(Class super) 
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
    get_vptr(InputStream)->Close(this);
}

method void Mark(InputStream* this, int readlimit)
{
    get_vptr(InputStream)->Mark(this, readlimit);
}

method bool MarkSupported(InputStream* this)
{
    return false;
}

method void Reset(InputStream* this)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}

