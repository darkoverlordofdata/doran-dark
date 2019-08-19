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



ctor_proto (Reader);
interface (Reader, ToString, const char*, (const Reader* const) );
interface (Reader, ReadOne,         int,    (Reader*) );
interface (Reader, Read,            int,    (Reader*, IOBuff*, int, int) );
interface (Reader, Skip,            long,   (Reader*, long) );
interface (Reader, Close,           void,   (Reader*) );
interface (Reader, Mark,            void,   (Reader*, int) );
interface (Reader, MarkSupported,   bool,   (Reader*) );
interface (Reader, Reset,           void,   (Reader*) );
interface (Reader, Ready,           bool,   (Reader*) );

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

function vptr(Reader);
/**
 * 
 * Class Loader callback
 */
function objc_loadReader(Class super) 
{
    Class cls = createClass(super, Reader);
    addMethod(cls, ReaderToString, ToString);
    addMethod(cls, ObjectEquals, Equals);
    addMethod(cls, ObjectGetHashCode, GetHashCode);
    addMethod(cls, ObjectDispose, Dispose);
    addMethod(cls, ReaderReadOne, ReadOne);
    addMethod(cls, ReaderRead, Read);
    addMethod(cls, ReaderSkip, Skip);
    addMethod(cls, ReaderClose, Close);
    addMethod(cls, ReaderMark, Mark);
    addMethod(cls, ReaderMarkSupported, MarkSupported);
    addMethod(cls, ReaderReset, Reset);
    addMethod(cls, ReaderReady, Ready);
    
    return cls;
}


/** Maximum skip-buffer size */
static const int maxSkipBufferSize = 8192;

method Reader* Reader_init(Reader* this) {
    Reader_init(this);
    this->isa = objc_getClass("Reader");
    return this;
}

method const char* ToString(const Reader* const this) {
    return "Reader";
}

method int ReadOne(Reader* this) {
    char cb[2];
    if (Read(this, &cb, 0, 1) == -1)
        return -1;
    else
        return (int)cb[0];
}

method int Read(Reader* this, IOBuff* buf, int offset, int len) {
    return get_vptr(Reader)->Read(this, buf, offset, len);
}

method long Skip(Reader* this, long n)  {

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

method bool Ready(Reader* this) {
    return false;
}

method bool MarkSupported(Reader* this) {
    return false;
}

method void Mark(Reader* this, int readLimit) {
    throw DSNotSupportedException("Mark not supported", Source);
}

method void Reset(Reader* this) {
    throw DSNotSupportedException("Reset not supported", Source);
}

method void Close(Reader* this) {
    get_vptr(Reader)->Close(this);
}

