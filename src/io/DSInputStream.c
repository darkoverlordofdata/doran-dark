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
#include <dark/io/DSInputStream.h>
#include <dark/io/private/DSInputStream.h>

overload DSInputStream* DSInputStream_init(DSInputStream* const this) 
{
    DSObject_init(this);
    this->isa = getDSInputStreamIsa();
    return this;
}

overload const char* ToString(const DSInputStream* const this) {
    return "DSInputStream";
}

overload int ReadOne(DSInputStream* this)
{
    return -1;
}

overload int Read(DSInputStream* this, IOBuff* b, int off, int len)
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

overload long Skip(DSInputStream* this, long n) 
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

overload int Available(DSInputStream* this)
{
    return 0;
}

overload void Close(DSInputStream* this)
{
    _vptr(this)->Close(this);
}

overload void Mark(DSInputStream* this, int readlimit)
{
    _vptr(this)->Mark(this, readlimit);
}

overload bool MarkSupported(DSInputStream* this)
{
    return false;
}

overload void Reset(DSInputStream* this)
{
    throw DSNotSupportedException("mark/reset not supported", Source);
}


