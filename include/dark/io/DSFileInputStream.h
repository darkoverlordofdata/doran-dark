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

IVAR (DSFileInputStream) {
    Class isa;
    FILE* fd;
    bool closed;
};

CTOR (DSFileInputStream, char*);
CTOR (DSFileInputStream, DSFile*);

METHOD (DSFileInputStream, ToString, const char*, (const DSFileInputStream* const) );
METHOD (DSFileInputStream, ReadOne,         int,    (DSFileInputStream*) );
METHOD (DSFileInputStream, Read,            int,    (DSFileInputStream*, IOBuff*, int, int) );
METHOD (DSFileInputStream, Skip,            long,   (DSFileInputStream*, long) );
METHOD (DSFileInputStream, Available,       int,    (DSFileInputStream*) );
METHOD (DSFileInputStream, Close,           void,   (DSFileInputStream*) );

VTABLE (DSFileInputStream) {
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

DEF_VPTR(DSFileInputStream);

static inline overload DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, char* name) {
    return DSFileInputStream_init(this, (name != nullptr ? NewDSFile(name) : nullptr));
}

static inline overload DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, DSFile* file) 
{
    DSObject_init(this);
    this->isa = objc_getClass("DSFileInputStream");
    auto name = file != nullptr ? GetPath(file) : nullptr;
    if (name == nullptr)
        throw DSNullPointerException(Source);
    if (IsInvalid(file))
        throw DSFileNotFoundException(name, Source);
    this->fd = fopen(name, "r");
    if (this->fd == nullptr) {
        DSLog("FileInputStream.FromFile Unable to Open %s\n", name);
        throw DSFileNotFoundException(name, Source);
    }
    return this;
}

static inline overload const char* ToString(const DSFileInputStream* const this) {
    return "DSFileInputStream";
}

static inline overload int ReadOne(DSFileInputStream* this) {
    return fgetc(this->fd);
}

static inline overload int Read(DSFileInputStream* this, IOBuff* buf, int offset, int len) {
    if (len <= 0)
        len = buf->len;
    if (buf->len <= 0 && len <= 0) 
        throw DSIndexOutOfBoundsException(len, Source);
    if (offset < 0 || buf->len - offset < len) 
        throw DSIndexOutOfBoundsException(offset, Source);

    char* bytes = DScalloc(1, len-offset);
    int nread = fread(bytes, 1, len-offset, this->fd);
    if (nread < 0) 
        nread = -1;
    else
        memcpy((char*)buf+offset, bytes, nread);
    return nread;
}

static inline overload long Skip(DSFileInputStream* this, long n)  {
    long i=0;
    for (; i<n; i++)
        if (ReadOne(this) < 0)
            return -1;
    return i;
}

static inline overload int Available(DSFileInputStream* this) {
    return 1;
}

static inline overload void Close(DSFileInputStream* this) {
    this->fd = nullptr;
}


VTABLE_BIND( DSFileInputStream );
VTABLE_OVERRIDE( ToString,        (DSFileInputStreamToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_METHOD( ReadOne,           (DSFileInputStreamReadOne)ReadOne, "i@:v" );
VTABLE_METHOD( Read,              (DSFileInputStreamRead)Read, "i@:^ii" );
VTABLE_METHOD( Skip,              (DSFileInputStreamSkip)Skip, "l@:l" );
VTABLE_METHOD( Close,             (DSFileInputStreamClose)Close, "v@:v" );
VTABLE_METHOD( Mark,              (DSInputStreamMark)Mark, "v@:i" );
VTABLE_METHOD( MarkSupported,     (DSInputStreamMarkSupported)MarkSupported, "v@:v" );
VTABLE_METHOD( Reset,             (DSInputStreamReset)Reset, "v@:v" );
VTABLE_METHOD( Available,         (DSFileInputStreamAvailable)Available, "B@:" );
VTABLE_METHODIZE;
#endif _DSFILE_INPUT_STREAM_H_