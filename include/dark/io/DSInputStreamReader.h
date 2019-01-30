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

ivar (DSInputStreamReader) {
    Class isa;
    DSInputStream* in;
};

ctor (DSInputStreamReader, DSInputStream*);
method (DSInputStreamReader, ToString, const char*, (const DSInputStreamReader* const) );
method (DSInputStreamReader, ReadOne,         int,    (DSInputStreamReader*) );
method (DSInputStreamReader, Read,            int,    (DSInputStreamReader*, IOBuff*, int, int) );
method (DSInputStreamReader, Skip,            long,   (DSInputStreamReader*, long) );
method (DSInputStreamReader, Close,           void,   (DSInputStreamReader*) );
method (DSInputStreamReader, Mark,            void,   (DSInputStreamReader*, int) );
method (DSInputStreamReader, MarkSupported,   bool,   (DSInputStreamReader*) );
method (DSInputStreamReader, Reset,           void,   (DSInputStreamReader*) );
method (DSInputStreamReader, Ready,           bool,   (DSInputStreamReader*) );

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

#endif _DS_INPUT_STREAM_READER_H_