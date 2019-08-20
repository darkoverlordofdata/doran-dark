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
#include <dark/io/filesystem.h>
#include <dark/io/reader.h>
#include <dark/io/inputstream.h>

type (InputStreamReader) {
    Class isa;
    InputStream* in;
};

ctor (InputStreamReader, InputStream*);
interface (InputStreamReader, ToString, const char*, (const InputStreamReader* const) );
interface (InputStreamReader, ReadOne,         int,    (InputStreamReader*) );
interface (InputStreamReader, Read,            int,    (InputStreamReader*, IOBuff*, int, int) );
interface (InputStreamReader, Skip,            long,   (InputStreamReader*, long) );
interface (InputStreamReader, Close,           void,   (InputStreamReader*) );
interface (InputStreamReader, Mark,            void,   (InputStreamReader*, int) );
interface (InputStreamReader, MarkSupported,   bool,   (InputStreamReader*) );
interface (InputStreamReader, Reset,           void,   (InputStreamReader*) );
interface (InputStreamReader, Ready,           bool,   (InputStreamReader*) );

vtable (InputStreamReader) {
    const InputStreamReaderToString       ToString;
    const ObjectEquals                    Equals;
    const ObjectGetHashCode               GetHashCode;
    const ObjectDispose                   Dispose;
    const InputStreamReaderReadOne        ReadOne;
    const InputStreamReaderRead           Read;
    const InputStreamReaderSkip           Skip;
    const InputStreamReaderClose          Close;
    const InputStreamReaderMark           Mark;
    const InputStreamReaderMarkSupported  MarkSupported;
    const InputStreamReaderReset          Reset;
    const InputStreamReaderReady          Ready;
};

function vptr(InputStreamReader);
/**
 * 
 * Class Loader callback
 */
function objc_loadInputStreamReader(Class super) 
{
    Class cls = createClass(super, InputStreamReader);
    addMethod(cls, InputStreamReader, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, InputStreamReader, ReadOne);
    addMethod(cls, InputStreamReader, Read);
    addMethod(cls, Reader, Skip);
    addMethod(cls, InputStreamReader, Close);
    addMethod(cls, Reader, Mark);
    addMethod(cls, Reader, MarkSupported);
    addMethod(cls, Reader, Reset);
    addMethod(cls, Reader, Ready);
    
    return cls;
}



method InputStreamReader* InputStreamReader_init(InputStreamReader* this, InputStream* in) {
    Object_init(this);
    this->isa = objc_getClass("InputStreamReader");
    this->in = in;
    return this;
}

method const char* ToString(const InputStreamReader* const this) {
    return "InputStreamReader";
}

method int ReadOne(InputStreamReader* this) {
    return ReadOne(this->in);
}

method int Read(InputStreamReader* this, IOBuff* cbuf, int offset, int length) {
    return Read(this->in, cbuf, offset, length);
}

method long Skip(InputStreamReader* this, long n) {
    return Skip((Reader*)this, n);
} 

method void Close(InputStreamReader* this) {
    Close(this->in);
}

method void Mark(InputStreamReader* this, int readLimit) {
    Mark((Reader*)this, readLimit);
} 

method bool MarkSupported(InputStreamReader* this) {
    return MarkSupported((Reader*)this);
}

method void Reset(InputStreamReader* this) {
    Reset((Reader*)this);
}

method bool Ready(InputStreamReader* this) {
    return Ready((Reader*)this);
}


