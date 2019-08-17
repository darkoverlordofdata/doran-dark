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
#include <dark/io/DSFileInputStream.h>
#include <dark/io/implementation/DSFileInputStream.h>

overload DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, char* name) {
    return DSFileInputStream_init(this, (name != nullptr ? NewDSFile(name) : nullptr));
}

overload DSFileInputStream* DSFileInputStream_init(DSFileInputStream* const this, DSFile* file) 
{
    DSObject_init(this);
    this->isa = getDSFileInputStreamIsa();
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

overload const char* ToString(const DSFileInputStream* const this) {
    return "DSFileInputStream";
}

overload int ReadOne(DSFileInputStream* this) {
    return fgetc(this->fd);
}

overload int Read(DSFileInputStream* this, IOBuff* buf, int offset, int len) {
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

overload long Skip(DSFileInputStream* this, long n)  {
    long i=0;
    for (; i<n; i++)
        if (ReadOne(this) < 0)
            return -1;
    return i;
}

overload int Available(DSFileInputStream* this) {
    return 1;
}

overload void Close(DSFileInputStream* this) {
    this->fd = nullptr;
}

