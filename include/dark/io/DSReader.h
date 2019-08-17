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


IVAR (DSReader) {
    Class isa;
    IOBuff skipBuffer;
};



CTOR (DSReader);
METHOD (DSReader, ToString, const char*, (const DSReader* const) );
METHOD (DSReader, ReadOne,         int,    (DSReader*) );
METHOD (DSReader, Read,            int,    (DSReader*, IOBuff*, int, int) );
METHOD (DSReader, Skip,            long,   (DSReader*, long) );
METHOD (DSReader, Close,           void,   (DSReader*) );
METHOD (DSReader, Mark,            void,   (DSReader*, int) );
METHOD (DSReader, MarkSupported,   bool,   (DSReader*) );
METHOD (DSReader, Reset,           void,   (DSReader*) );
METHOD (DSReader, Ready,           bool,   (DSReader*) );

VTABLE (DSReader) {
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

DEF_VPTR(DSReader);
/** Maximum skip-buffer size */
static const int maxSkipBufferSize = 8192;

static inline overload DSReader* DSReader_init(DSReader* this) {
    DSReader_init(this);
    this->isa = objc_getClass("DSReader");
    return this;
}

static inline overload const char* ToString(const DSReader* const this) {
    return "DSReader";
}

static inline overload int ReadOne(DSReader* this) {
    char cb[2];
    if (Read(this, &cb, 0, 1) == -1)
        return -1;
    else
        return (int)cb[0];
}

static inline overload int Read(DSReader* this, IOBuff* buf, int offset, int len) {
    return getVptr(DSReader)->Read(this, buf, offset, len);
}

static inline overload long Skip(DSReader* this, long n)  {

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

static inline overload bool Ready(DSReader* this) {
    return false;
}

static inline overload bool MarkSupported(DSReader* this) {
    return false;
}

static inline overload void Mark(DSReader* this, int readLimit) {
    throw DSNotSupportedException("Mark not supported", Source);
}

static inline overload void Reset(DSReader* this) {
    throw DSNotSupportedException("Reset not supported", Source);
}

static inline overload void Close(DSReader* this) {
    getVptr(DSReader)->Close(this);
}



VTABLE_BIND( DSReader );
VTABLE_OVERRIDE( ToString,        (DSReaderToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_METHOD( ReadOne,           (DSReaderReadOne)ReadOne, "i@:v" );
VTABLE_METHOD( Read,              (DSReaderRead)Read, "i@:^ii" );
VTABLE_METHOD( Skip,              (DSReaderSkip)Skip, "l@:l" );
VTABLE_METHOD( Close,             (DSReaderClose)Close, "v@:v" );
VTABLE_METHOD( Mark,              (DSReaderMark)Mark, "v@:i" );
VTABLE_METHOD( MarkSupported,     (DSReaderMarkSupported)MarkSupported, "v@:v" );
VTABLE_METHOD( Reset,             (DSReaderReset)Reset, "v@:v" );
VTABLE_METHOD( Ready,             (DSReaderReady)Ready, "B@:" );
VTABLE_METHODIZE;
#endif _DSREADER_H_