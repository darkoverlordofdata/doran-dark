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
method_proto (Reader, ToString, const char*, (const Reader* const) );
method_proto (Reader, ReadOne,         int,    (Reader*) );
method_proto (Reader, Read,            int,    (Reader*, IOBuff*, int, int) );
method_proto (Reader, Skip,            long,   (Reader*, long) );
method_proto (Reader, Close,           void,   (Reader*) );
method_proto (Reader, Mark,            void,   (Reader*, int) );
method_proto (Reader, MarkSupported,   bool,   (Reader*) );
method_proto (Reader, Reset,           void,   (Reader*) );
method_proto (Reader, Ready,           bool,   (Reader*) );

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

class_load( Reader );
class_override( ToString,        (ReaderToString)ToString, "$@:v" );
class_method( Equals,            (ObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (ObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (ReaderReadOne)ReadOne, "i@:v" );
class_method( Read,              (ReaderRead)Read, "i@:^ii" );
class_method( Skip,              (ReaderSkip)Skip, "l@:l" );
class_method( Close,             (ReaderClose)Close, "v@:v" );
class_method( Mark,              (ReaderMark)Mark, "v@:i" );
class_method( MarkSupported,     (ReaderMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (ReaderReset)Reset, "v@:v" );
class_method( Ready,             (ReaderReady)Ready, "B@:" );
class_fini;

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
    return _vptr(Reader)->Read(this, buf, offset, len);
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
    _vptr(Reader)->Close(this);
}

