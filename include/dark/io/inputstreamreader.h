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

delegate (InputStreamReader, New,           InputStreamReader*, (InputStreamReader*, const InputStream*) );
delegate (InputStreamReader, ToString,      const char*, (const InputStreamReader* const) );
delegate (InputStreamReader, ReadOne,       int,    (InputStreamReader*) );
delegate (InputStreamReader, Read,          int,    (InputStreamReader*, IOBuff*, int, int) );
delegate (InputStreamReader, Skip,          long,   (InputStreamReader*, long) );
delegate (InputStreamReader, Close,         void,   (InputStreamReader*) );
delegate (InputStreamReader, Mark,          void,   (InputStreamReader*, int) );
delegate (InputStreamReader, MarkSupported, bool,   (InputStreamReader*) );
delegate (InputStreamReader, Reset,         void,   (InputStreamReader*) );
delegate (InputStreamReader, Ready,         bool,   (InputStreamReader*) );

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
function Class objc_loadInputStreamReader(Class super) 
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


method InputStreamReader* New(InputStreamReader* self, InputStream* in) {
    extends((Object*)self);
    self->isa = objc_getClass("InputStreamReader");
    self->in = in;
    return self;
}


method const char* ToString(const InputStreamReader* const self) {
    return "InputStreamReader";
}

method int ReadOne(InputStreamReader* self) {
    return ReadOne(self->in);
}

method int Read(InputStreamReader* self, IOBuff* cbuf, int offset, int length) {
    return Read(self->in, cbuf, offset, length);
}

method long Skip(InputStreamReader* self, long n) {
    return Skip((Reader*)self, n);
} 

method void Close(InputStreamReader* self) {
    Close(self->in);
}

method void Mark(InputStreamReader* self, int readLimit) {
    Mark((Reader*)self, readLimit);
} 

method bool MarkSupported(InputStreamReader* self) {
    return MarkSupported((Reader*)self);
}

method void Reset(InputStreamReader* self) {
    Reset((Reader*)self);
}

method bool Ready(InputStreamReader* self) {
    return Ready((Reader*)self);
}


