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
#ifndef _DS_BUFFERED_READER_H_
#define _DS_BUFFERED_READER_H_
#include "../types.h"
#include "DSFileSystem.h"
#include "DSReader.h"

static const int INVALIDATED = -2;
static const int UNMARKED = -1;
const int defaultCharBufferSize;
const int defaultExpectedLineLength;

ivar (DSBufferedReader) {
    Class isa;
    DSReader* in;
    IOBuff cb;
    int nChars;
    int nextChar;
    int markedChar;
    int readAheadLimit;
    bool skipLF;
    bool markedSkipLF;
};

ctor (DSBufferedReader, DSReader*);
ctor (DSBufferedReader, DSReader*, int);

method (DSBufferedReader, ToString, const char*, (const DSBufferedReader* const) );
method (DSBufferedReader, ReadOne,         int,    (DSBufferedReader*) );
method (DSBufferedReader, Read,            int,    (DSBufferedReader*, IOBuff*, int, int) );
method (DSBufferedReader, Skip,            long,   (DSBufferedReader*, long) );
method (DSBufferedReader, Close,           void,   (DSBufferedReader*) );
method (DSBufferedReader, Mark,            void,   (DSBufferedReader*, int) );
method (DSBufferedReader, MarkSupported,   bool,   (DSBufferedReader*) );
method (DSBufferedReader, Reset,           void,   (DSBufferedReader*) );
method (DSBufferedReader, Ready,           bool,   (DSBufferedReader*) );
method (DSBufferedReader, ReadLine,        DSString*, (DSBufferedReader*, bool) );

DSString* overload ReadLine(DSBufferedReader* this);

vtable (DSBufferedReader) {
    const DSBufferedReaderToString      ToString;
    const DSObjectEquals                Equals;
    const DSObjectGetHashCode           GetHashCode;
    const DSObjectDispose               Dispose;
    const DSBufferedReaderReadOne       ReadOne;
    const DSBufferedReaderRead          Read;
    const DSBufferedReaderSkip          Skip;
    const DSBufferedReaderClose         Close;
    const DSBufferedReaderMark          Mark;
    const DSBufferedReaderMarkSupported MarkSupported;
    const DSBufferedReaderReset         Reset;
    const DSBufferedReaderReady         Ready;
    const DSBufferedReaderReadLine      ReadLine;
};

#endif _DS_BUFFERED_READER_H_