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
#include <dark/io/DSReader.h>
#include <dark/io/private/DSReader.h>

/** Maximum skip-buffer size */
static const int maxSkipBufferSize = 8192;

overload DSReader* DSReader_init(DSReader* this) {
    DSReader_init(this);
    this->isa = getDSReaderIsa();
    return this;
}

overload const char* ToString(const DSReader* const this) {
    return "DSReader";
}

overload int ReadOne(DSReader* this) {
    char cb[2];
    if (Read(this, &cb, 0, 1) == -1)
        return -1;
    else
        return (int)cb[0];
}

overload int Read(DSReader* this, IOBuff* buf, int offset, int len) {
    return _vptr(this)->Read(this, buf, offset, len);
}

overload long Skip(DSReader* this, long n)  {

    if (n < 0L)
        throw DSIllegalArgumentException("skip value is negative", Source);
    int nn = (int)Min(n, maxSkipBufferSize);
    if ((this->skipBuffer.buff == nullptr) || (this->skipBuffer.len < nn))
        this->skipBuffer.buff = DScalloc(1, nn);
    long r = n;
    while (r > 0) {
        int nc = Read(this, &this->skipBuffer, 0, (int)Min(r, nn));
        if (nc == -1)
            break;
        r -= nc;
    }
    return n - r;
}

overload bool Ready(DSReader* this) {
    return false;
}

overload bool MarkSupported(DSReader* this) {
    return false;
}

overload void Mark(DSReader* this, int readLimit) {
    throw DSNotSupportedException("Mark not supported", Source);
}

overload void Reset(DSReader* this) {
    throw DSNotSupportedException("Reset not supported", Source);
}

overload void Close(DSReader* this) {
    _vptr(this)->Close(this);
}

