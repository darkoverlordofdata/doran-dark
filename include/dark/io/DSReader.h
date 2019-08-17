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
#ifndef _DSREADER_H_
#define _DSREADER_H_
#include "../types.h"
#include "DSFileSystem.h"


type (DSReader) {
    Class isa;
    IOBuff skipBuffer;
};



def_ctor (DSReader);
def_method (DSReader, ToString, const char*, (const DSReader* const) );
def_method (DSReader, ReadOne,         int,    (DSReader*) );
def_method (DSReader, Read,            int,    (DSReader*, IOBuff*, int, int) );
def_method (DSReader, Skip,            long,   (DSReader*, long) );
def_method (DSReader, Close,           void,   (DSReader*) );
def_method (DSReader, Mark,            void,   (DSReader*, int) );
def_method (DSReader, MarkSupported,   bool,   (DSReader*) );
def_method (DSReader, Reset,           void,   (DSReader*) );
def_method (DSReader, Ready,           bool,   (DSReader*) );

vtable (DSReader) {
    const DSReaderToString      ToString;
    const DSObjectEquals        Equals;
    const DSObjectGetHashCode   GetHashCode;
    const DSObjectDispose       Dispose;
    const DSReaderReadOne       ReadOne;
    const DSReaderRead          Read;
    const DSReaderSkip          Skip;
    const DSReaderClose         Close;
    const DSReaderMark          Mark;
    const DSReaderMarkSupported MarkSupported;
    const DSReaderReset         Reset;
    const DSReaderReady         Ready;
};

vtable_ptr(DSReader);
/** Maximum skip-buffer size */
static const int maxSkipBufferSize = 8192;

method DSReader* DSReader_init(DSReader* this) {
    DSReader_init(this);
    this->isa = objc_getClass("DSReader");
    return this;
}

method const char* ToString(const DSReader* const this) {
    return "DSReader";
}

method int ReadOne(DSReader* this) {
    char cb[2];
    if (Read(this, &cb, 0, 1) == -1)
        return -1;
    else
        return (int)cb[0];
}

method int Read(DSReader* this, IOBuff* buf, int offset, int len) {
    return get_vptr(DSReader)->Read(this, buf, offset, len);
}

method long Skip(DSReader* this, long n)  {

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

method bool Ready(DSReader* this) {
    return false;
}

method bool MarkSupported(DSReader* this) {
    return false;
}

method void Mark(DSReader* this, int readLimit) {
    throw DSNotSupportedException("Mark not supported", Source);
}

method void Reset(DSReader* this) {
    throw DSNotSupportedException("Reset not supported", Source);
}

method void Close(DSReader* this) {
    get_vptr(DSReader)->Close(this);
}



class_bind( DSReader );
class_override( ToString,        (DSReaderToString)ToString, "$@:v" );
class_method( Equals,            (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (DSReaderReadOne)ReadOne, "i@:v" );
class_method( Read,              (DSReaderRead)Read, "i@:^ii" );
class_method( Skip,              (DSReaderSkip)Skip, "l@:l" );
class_method( Close,             (DSReaderClose)Close, "v@:v" );
class_method( Mark,              (DSReaderMark)Mark, "v@:i" );
class_method( MarkSupported,     (DSReaderMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (DSReaderReset)Reset, "v@:v" );
class_method( Ready,             (DSReaderReady)Ready, "B@:" );
class_methodize;
#endif _DSREADER_H_