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
#include <dark/types.h>
#include <dark/io/file.h>
#include <dark/io/inputstream.h>

type (FileInputStream) {
    Class isa;
    FILE* fd;
    bool closed;
};

ctor_proto (FileInputStream, char*);
ctor_proto (FileInputStream, File*);

method_proto (FileInputStream, ToString, const char*, (const FileInputStream* const) );
method_proto (FileInputStream, ReadOne,         int,    (FileInputStream*) );
method_proto (FileInputStream, Read,            int,    (FileInputStream*, IOBuff*, int, int) );
method_proto (FileInputStream, Skip,            long,   (FileInputStream*, long) );
method_proto (FileInputStream, Available,       int,    (FileInputStream*) );
method_proto (FileInputStream, Close,           void,   (FileInputStream*) );

vtable (FileInputStream) {
    const FileInputStreamToString     ToString;
    const ObjectEquals                Equals;
    const ObjectGetHashCode           GetHashCode;
    const ObjectDispose               Dispose;
    const FileInputStreamReadOne      ReadOne;
    const FileInputStreamRead         Read;
    const FileInputStreamSkip         Skip;
    const FileInputStreamClose        Close;
    const InputStreamMark             Mark;
    const InputStreamMarkSupported    MarkSupported;
    const InputStreamReset            Reset;
    const FileInputStreamAvailable    Available;
};

class_load( FileInputStream );
class_override( ToString,        (FileInputStreamToString)ToString, "$@:v" );
class_method( Equals,            (ObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (ObjectDispose)Dispose, "v@:v" );
class_method( ReadOne,           (FileInputStreamReadOne)ReadOne, "i@:v" );
class_method( Read,              (FileInputStreamRead)Read, "i@:^ii" );
class_method( Skip,              (FileInputStreamSkip)Skip, "l@:l" );
class_method( Close,             (FileInputStreamClose)Close, "v@:v" );
class_method( Mark,              (InputStreamMark)Mark, "v@:i" );
class_method( MarkSupported,     (InputStreamMarkSupported)MarkSupported, "v@:v" );
class_method( Reset,             (InputStreamReset)Reset, "v@:v" );
class_method( Available,         (FileInputStreamAvailable)Available, "B@:" );
class_fini;

method FileInputStream* FileInputStream_init(FileInputStream* const this, char* name) {
    return FileInputStream_init(this, (name != nullptr ? NewFile(name) : nullptr));
}

method FileInputStream* FileInputStream_init(FileInputStream* const this, File* file) 
{
    Object_init(this);
    this->isa = objc_getClass("FileInputStream");
    auto name = file != nullptr ? GetPath(file) : nullptr;
    if (name == nullptr)
        throw DSNullPointerException(Source);
    if (IsInvalid(file))
        throw DSFileNotFoundException(name, Source);
    this->fd = fopen(name, "r");
    if (this->fd == nullptr) {
        Log("FileInputStream.FromFile Unable to Open %s\n", name);
        throw DSFileNotFoundException(name, Source);
    }
    return this;
}

method const char* ToString(const FileInputStream* const this) {
    return "FileInputStream";
}

method int ReadOne(FileInputStream* this) {
    return fgetc(this->fd);
}

method int Read(FileInputStream* this, IOBuff* buf, int offset, int len) {
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

method long Skip(FileInputStream* this, long n)  {
    long i=0;
    for (; i<n; i++)
        if (ReadOne(this) < 0)
            return -1;
    return i;
}

method int Available(FileInputStream* this) {
    return 1;
}

method void Close(FileInputStream* this) {
    this->fd = nullptr;
}
