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

type (DSFileInputStream) {
    Class isa;
    FILE* fd;
    bool closed;
};

def_ctor (DSFileInputStream, char*);
def_ctor (DSFileInputStream, DSFile*);

def_method (DSFileInputStream, ToString, const char*, (const DSFileInputStream* const) );
def_method (DSFileInputStream, ReadOne,         int,    (DSFileInputStream*) );
def_method (DSFileInputStream, Read,            int,    (DSFileInputStream*, IOBuff*, int, int) );
def_method (DSFileInputStream, Skip,            long,   (DSFileInputStream*, long) );
def_method (DSFileInputStream, Available,       int,    (DSFileInputStream*) );
def_method (DSFileInputStream, Close,           void,   (DSFileInputStream*) );

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

vtable_ptr(DSFileInputStream);

method DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, char* name) {
    return DSFileInputStream_init(this, (name != nullptr ? NewDSFile(name) : nullptr));
}

method DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, DSFile* file) 
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

method const char* ToString(const DSFileInputStream* const this) {
    return "DSFileInputStream";
}

method int ReadOne(DSFileInputStream* this) {
    return fgetc(this->fd);
}

method int Read(DSFileInputStream* this, IOBuff* buf, int offset, int len) {
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

method long Skip(DSFileInputStream* this, long n)  {
    long i=0;
    for (; i<n; i++)
        if (ReadOne(this) < 0)
            return -1;
    return i;
}

method int Available(DSFileInputStream* this) {
    return 1;
}

method void Close(DSFileInputStream* this) {
    this->fd = nullptr;
}


class_bind( DSFileInputStream );
class_override( ToString,        (DSFileInputStreamToString)ToString, "$@:v" );
class_method( Equals,            (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (DSFileInputStreamReadOne)ReadOne, "i@:v" );
class_method( Read,              (DSFileInputStreamRead)Read, "i@:^ii" );
class_method( Skip,              (DSFileInputStreamSkip)Skip, "l@:l" );
class_method( Close,             (DSFileInputStreamClose)Close, "v@:v" );
class_method( Mark,              (DSInputStreamMark)Mark, "v@:i" );
class_method( MarkSupported,     (DSInputStreamMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (DSInputStreamReset)Reset, "v@:v" );
class_method( Available,         (DSFileInputStreamAvailable)Available, "B@:" );
class_methodize;
#endif _DSFILE_INPUT_STREAM_H_