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
#include <dark/io/DSInputStreamReader.h>
#include <dark/io/implementation/DSInputStreamReader.h>

overload DSInputStreamReader* DSInputStreamReader_init(DSInputStreamReader* this, DSInputStream* in) {
    DSObject_init(this);
    this->isa = getDSInputStreamReaderIsa();
    this->in = in;
    return this;
}

overload const char* ToString(const DSInputStreamReader* const this) {
    return "DSInputStreamReader";
}

overload int ReadOne(DSInputStreamReader* this) {
    return ReadOne(this->in);
}

overload int Read(DSInputStreamReader* this, IOBuff* cbuf, int offset, int length) {
    return Read(this->in, cbuf, offset, length);
}

overload long Skip(DSInputStreamReader* this, long n) {
    return Skip((DSReader*)this, n);
} 

overload void Close(DSInputStreamReader* this) {
    Close(this->in);
}

overload void Mark(DSInputStreamReader* this, int readLimit) {
    Mark((DSReader*)this, readLimit);
} 

overload bool MarkSupported(DSInputStreamReader* this) {
    return MarkSupported((DSReader*)this);
}

overload void Reset(DSInputStreamReader* this) {
    Reset((DSReader*)this);
}

overload bool Ready(DSInputStreamReader* this) {
    return Ready((DSReader*)this);
}
