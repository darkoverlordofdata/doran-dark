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
#ifndef _DS_INPUT_STREAM_READER_H_
#define _DS_INPUT_STREAM_READER_H_
#include "../types.h"
#include "DSFileSystem.h"
#include "DSReader.h"
#include "DSInputStream.h"

IVAR (DSInputStreamReader) {
    Class isa;
    DSInputStream* in;
};

CTOR (DSInputStreamReader, DSInputStream*);
METHOD (DSInputStreamReader, ToString, const char*, (const DSInputStreamReader* const) );
METHOD (DSInputStreamReader, ReadOne,         int,    (DSInputStreamReader*) );
METHOD (DSInputStreamReader, Read,            int,    (DSInputStreamReader*, IOBuff*, int, int) );
METHOD (DSInputStreamReader, Skip,            long,   (DSInputStreamReader*, long) );
METHOD (DSInputStreamReader, Close,           void,   (DSInputStreamReader*) );
METHOD (DSInputStreamReader, Mark,            void,   (DSInputStreamReader*, int) );
METHOD (DSInputStreamReader, MarkSupported,   bool,   (DSInputStreamReader*) );
METHOD (DSInputStreamReader, Reset,           void,   (DSInputStreamReader*) );
METHOD (DSInputStreamReader, Ready,           bool,   (DSInputStreamReader*) );

VTABLE (DSInputStreamReader) {
    const DSInputStreamReaderToString       ToString;
    const DSObjectEquals                    Equals;
    const DSObjectGetHashCode               GetHashCode;
    const DSObjectDispose                   Dispose;
    const DSInputStreamReaderReadOne        ReadOne;
    const DSInputStreamReaderRead           Read;
    const DSInputStreamReaderSkip           Skip;
    const DSInputStreamReaderClose          Close;
    const DSInputStreamReaderMark           Mark;
    const DSInputStreamReaderMarkSupported  MarkSupported;
    const DSInputStreamReaderReset          Reset;
    const DSInputStreamReaderReady          Ready;
};

DEF_VPTR(DSInputStreamReader);
static inline overload DSInputStreamReader* DSInputStreamReader_init(DSInputStreamReader* this, DSInputStream* in) {
    DSObject_init(this);
    this->isa = objc_getClass("DSInputStreamReader");
    this->in = in;
    return this;
}

static inline overload const char* ToString(const DSInputStreamReader* const this) {
    return "DSInputStreamReader";
}

static inline overload int ReadOne(DSInputStreamReader* this) {
    return ReadOne(this->in);
}

static inline overload int Read(DSInputStreamReader* this, IOBuff* cbuf, int offset, int length) {
    return Read(this->in, cbuf, offset, length);
}

static inline overload long Skip(DSInputStreamReader* this, long n) {
    return Skip((DSReader*)this, n);
} 

static inline overload void Close(DSInputStreamReader* this) {
    Close(this->in);
}

static inline overload void Mark(DSInputStreamReader* this, int readLimit) {
    Mark((DSReader*)this, readLimit);
} 

static inline overload bool MarkSupported(DSInputStreamReader* this) {
    return MarkSupported((DSReader*)this);
}

static inline overload void Reset(DSInputStreamReader* this) {
    Reset((DSReader*)this);
}

static inline overload bool Ready(DSInputStreamReader* this) {
    return Ready((DSReader*)this);
}


VTABLE_BIND( DSInputStreamReader );
VTABLE_OVERRIDE( ToString,        (DSInputStreamReaderToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_METHOD( ReadOne,           (DSInputStreamReaderReadOne)ReadOne, "i@:v" );
VTABLE_METHOD( Read,              (DSInputStreamReaderRead)Read, "i@:^ii" );
VTABLE_METHOD( Skip,              (DSReaderSkip)Skip, "l@:l" );
VTABLE_METHOD( Close,             (DSInputStreamReaderClose)Close, "v@:v" );
VTABLE_METHOD( Mark,              (DSReaderMark)Mark, "v@:i" );
VTABLE_METHOD( MarkSupported,     (DSReaderMarkSupported)MarkSupported, "v@:v" );
VTABLE_METHOD( Reset,             (DSReaderReset)Reset, "v@:v" );
VTABLE_METHOD( Ready,             (DSReaderReady)Ready, "B@:" );
VTABLE_METHODIZE;
#endif _DS_INPUT_STREAM_READER_H_