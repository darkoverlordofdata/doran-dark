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

type (DSInputStreamReader) {
    Class isa;
    DSInputStream* in;
};

def_ctor (DSInputStreamReader, DSInputStream*);
def_method (DSInputStreamReader, ToString, const char*, (const DSInputStreamReader* const) );
def_method (DSInputStreamReader, ReadOne,         int,    (DSInputStreamReader*) );
def_method (DSInputStreamReader, Read,            int,    (DSInputStreamReader*, IOBuff*, int, int) );
def_method (DSInputStreamReader, Skip,            long,   (DSInputStreamReader*, long) );
def_method (DSInputStreamReader, Close,           void,   (DSInputStreamReader*) );
def_method (DSInputStreamReader, Mark,            void,   (DSInputStreamReader*, int) );
def_method (DSInputStreamReader, MarkSupported,   bool,   (DSInputStreamReader*) );
def_method (DSInputStreamReader, Reset,           void,   (DSInputStreamReader*) );
def_method (DSInputStreamReader, Ready,           bool,   (DSInputStreamReader*) );

vtable (DSInputStreamReader) {
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

vtable_ptr(DSInputStreamReader);
method DSInputStreamReader* DSInputStreamReader_init(DSInputStreamReader* this, DSInputStream* in) {
    DSObject_init(this);
    this->isa = objc_getClass("DSInputStreamReader");
    this->in = in;
    return this;
}

method const char* ToString(const DSInputStreamReader* const this) {
    return "DSInputStreamReader";
}

method int ReadOne(DSInputStreamReader* this) {
    return ReadOne(this->in);
}

method int Read(DSInputStreamReader* this, IOBuff* cbuf, int offset, int length) {
    return Read(this->in, cbuf, offset, length);
}

method long Skip(DSInputStreamReader* this, long n) {
    return Skip((DSReader*)this, n);
} 

method void Close(DSInputStreamReader* this) {
    Close(this->in);
}

method void Mark(DSInputStreamReader* this, int readLimit) {
    Mark((DSReader*)this, readLimit);
} 

method bool MarkSupported(DSInputStreamReader* this) {
    return MarkSupported((DSReader*)this);
}

method void Reset(DSInputStreamReader* this) {
    Reset((DSReader*)this);
}

method bool Ready(DSInputStreamReader* this) {
    return Ready((DSReader*)this);
}


class_bind( DSInputStreamReader );
class_override( ToString,        (DSInputStreamReaderToString)ToString, "$@:v" );
class_method( Equals,            (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (DSInputStreamReaderReadOne)ReadOne, "i@:v" );
class_method( Read,              (DSInputStreamReaderRead)Read, "i@:^ii" );
class_method( Skip,              (DSReaderSkip)Skip, "l@:l" );
class_method( Close,             (DSInputStreamReaderClose)Close, "v@:v" );
class_method( Mark,              (DSReaderMark)Mark, "v@:i" );
class_method( MarkSupported,     (DSReaderMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (DSReaderReset)Reset, "v@:v" );
class_method( Ready,             (DSReaderReady)Ready, "B@:" );
class_methodize;
#endif _DS_INPUT_STREAM_READER_H_