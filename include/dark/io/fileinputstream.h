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

delegate (FileInputStream, New,         const FileInputStream*, (FileInputStream*, const char*) );
delegate (FileInputStream, ToString,    const char*, (const FileInputStream* const) );
delegate (FileInputStream, ReadOne,     int,    (FileInputStream*) );
delegate (FileInputStream, Read,        int,    (FileInputStream*, IOBuff*, int, int) );
delegate (FileInputStream, Skip,        long,   (FileInputStream*, long) );
delegate (FileInputStream, Available,   int,    (FileInputStream*) );
delegate (FileInputStream, Close,       void,   (FileInputStream*) );

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

function vptr(FileInputStream);
/**
 * 
 * Class Loader callback
 */
function Class objc_loadFileInputStream(Class super) 
{
    Class cls = createClass(super, FileInputStream);
    addMethod(cls, FileInputStream, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, FileInputStream, ReadOne);
    addMethod(cls, FileInputStream, Read);
    addMethod(cls, FileInputStream, Skip);
    addMethod(cls, FileInputStream, Close);
    addMethod(cls, InputStream, Mark);
    addMethod(cls, InputStream, MarkSupported);
    addMethod(cls, InputStream, Reset);
    addMethod(cls, FileInputStream, Available);
    
    return cls;
}


method FileInputStream* New(FileInputStream* self, File* file) 
{
    extends((Object*)self);
    self->isa = objc_getClass("FileInputStream");
    auto name = file != nullptr ? GetPath(file) : nullptr;
    if (name == nullptr)
        throw DSNullPointerException(Source);
    if (IsInvalid(file))
        throw DSFileNotFoundException(name, Source);
    self->fd = fopen(name, "r");
    if (self->fd == nullptr) {
        Log("FileInputStream.FromFile Unable to Open %s\n", name);
        throw DSFileNotFoundException(name, Source);
    }
    return self;
}

// method FileInputStream* New(FileInputStream* self, char* name) {
//     return New(self, (name != nullptr ? new(File(name)) : nullptr));
// }


method const char* ToString(const FileInputStream* const self) {
    return "FileInputStream";
}

method int ReadOne(FileInputStream* self) {
    return fgetc(self->fd);
}

method int Read(FileInputStream* self, IOBuff* buf, int offset, int len) {
    if (len <= 0)
        len = buf->len;
    if (buf->len <= 0 && len <= 0) 
        throw DSIndexOutOfBoundsException(len, Source);
    if (offset < 0 || buf->len - offset < len) 
        throw DSIndexOutOfBoundsException(offset, Source);

    char* bytes = (char*)DScalloc(1, len-offset);
    int nread = fread(bytes, 1, len-offset, self->fd);
    if (nread < 0) 
        nread = -1;
    else
        memcpy((char*)buf+offset, bytes, nread);
    return nread;
}

method long Skip(FileInputStream* self, long n)  {
    long i=0;
    for (; i<n; i++)
        if (ReadOne(self) < 0)
            return -1;
    return i;
}

method int Available(FileInputStream* self) {
    return 1;
}

method void Close(FileInputStream* self) {
    self->fd = nullptr;
}
