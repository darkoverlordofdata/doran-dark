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


ivar (DSReader) {
    Class isa;
    IOBuff skipBuffer;
};



ctor (DSReader);
method (DSReader, ToString, const char*, (const DSReader* const) );
method (DSReader, ReadOne,         int,    (DSReader*) );
method (DSReader, Read,            int,    (DSReader*, IOBuff*, int, int) );
method (DSReader, Skip,            long,   (DSReader*, long) );
method (DSReader, Close,           void,   (DSReader*) );
method (DSReader, Mark,            void,   (DSReader*, int) );
method (DSReader, MarkSupported,   bool,   (DSReader*) );
method (DSReader, Reset,           void,   (DSReader*) );
method (DSReader, Ready,           bool,   (DSReader*) );

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

#endif _DSREADER_H_