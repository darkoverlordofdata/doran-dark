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


type (Reader) {
    Class isa;
    IOBuff skipBuffer;
};

delegate (Reader, New,          Reader*, (Reader*) );
delegate (Reader, ToString,     const char*, (const Reader* const) );
delegate (Reader, ReadOne,      int,    (Reader*) );
delegate (Reader, Read,         int,    (Reader*, IOBuff*, int, int) );
delegate (Reader, Skip,         long,   (Reader*, long) );
delegate (Reader, Close,        void,   (Reader*) );
delegate (Reader, Mark,         void,   (Reader*, int) );
delegate (Reader, MarkSupported,bool,   (Reader*) );
delegate (Reader, Reset,        void,   (Reader*) );
delegate (Reader, Ready,        bool,   (Reader*) );

vtable (Reader) {
    const ReaderToString      ToString;
    const ObjectEquals        Equals;
    const ObjectGetHashCode   GetHashCode;
    const ObjectDispose       Dispose;
    const ReaderReadOne       ReadOne;
    const ReaderRead          Read;
    const ReaderSkip          Skip;
    const ReaderClose         Close;
    const ReaderMark          Mark;
    const ReaderMarkSupported MarkSupported;
    const ReaderReset         Reset;
    const ReaderReady         Ready;
};

static inline vptr(Reader);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadReader(Class base) 
{
    Class cls = createClass(base, Reader);
    addMethod(cls, Reader, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Reader, ReadOne);
    addMethod(cls, Reader, Read);
    addMethod(cls, Reader, Skip);
    addMethod(cls, Reader, Close);
    addMethod(cls, Reader, Mark);
    addMethod(cls, Reader, MarkSupported);
    addMethod(cls, Reader, Reset);
    addMethod(cls, Reader, Ready);
    
    return cls;
}


/** Maximum skip-buffer size */
static const int maxSkipBufferSize = 8192;

method Reader* New(Reader* self) {
    extends(Object);
    self->isa = objc_getClass("Reader");
    return self;
}

method const char* ToString(const Reader* const self) {
    return "Reader";
}

method int ReadOne(Reader* self) {
    char cb[2];
    if (Read(self, &cb, 0, 1) == -1)
        return -1;
    else
        return (int)cb[0];
}

method int Read(Reader* self, IOBuff* buf, int offset, int len) {
    return virtual(Reader)->Read(self, buf, offset, len);
}

method long Skip(Reader* self, long n)  {

    if (n < 0L)
        throw DSIllegalArgumentException("skip value is negative", Source);
    int nn = (int)Min(n, maxSkipBufferSize);
    if ((self->skipBuffer.buff == nullptr) || (self->skipBuffer.len < nn))
        self->skipBuffer.buff = DScalloc(1, nn);
    long r = n;
    while (r > 0) {
        int nc = Read(self, &self->skipBuffer, 0, (int)Min(r, nn));
        if (nc == -1)
            break;
        r -= nc;
    }
    return n - r;
}

method bool Ready(Reader* self) {
    return false;
}

method bool MarkSupported(Reader* self) {
    return false;
}

method void Mark(Reader* self, int readLimit) {
    throw DSNotSupportedException("Mark not supported", Source);
}

method void Reset(Reader* self) {
    throw DSNotSupportedException("Reset not supported", Source);
}

method void Close(Reader* self) {
    virtual(Reader)->Close(self);
}

