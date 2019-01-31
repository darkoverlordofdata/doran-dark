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
#ifndef _DSFILE_INPUT_STREAM_H_
#define _DSFILE_INPUT_STREAM_H_
#include "../types.h"
#include "DSFile.h"
#include "DSInputStream.h"

ivar (DSFileInputStream) {
    Class isa;
    FILE* fd;
    bool closed;
};

ctor (DSFileInputStream, char*);
ctor (DSFileInputStream, DSFile*);

method (DSFileInputStream, ToString, const char*, (const DSFileInputStream* const) );
method (DSFileInputStream, ReadOne,         int,    (DSFileInputStream*) );
method (DSFileInputStream, Read,            int,    (DSFileInputStream*, IOBuff*, int, int) );
method (DSFileInputStream, Skip,            long,   (DSFileInputStream*, long) );
method (DSFileInputStream, Available,       int,    (DSFileInputStream*) );
method (DSFileInputStream, Close,           void,   (DSFileInputStream*) );
// method (DSFileInputStream, Mark,            void,   (DSFileInputStream*, int) );
// method (DSFileInputStream, MarkSupported,   bool,   (DSFileInputStream*) );
// method (DSFileInputStream, Reset,           void,   (DSFileInputStream*) );

vtable (DSFileInputStream) {
    const DSFileInputStreamToString     ToString;
    const DSObjectEquals                Equals;
    const DSObjectGetHashCode           GetHashCode;
    const DSObjectDispose               Dispose;
    const DSFileInputStreamReadOne      ReadOne;
    const DSFileInputStreamRead         Read;
    const DSFileInputStreamSkip         Skip;
    const DSFileInputStreamClose        Close;
    const DSInputStreamMark             Mark;
    const DSInputStreamMarkSupported    MarkSupported;
    const DSInputStreamReset            Reset;
    const DSFileInputStreamAvailable    Available;
};

#endif _DSFILE_INPUT_STREAM_H_