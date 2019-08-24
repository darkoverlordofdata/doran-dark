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

static const int INVALIDATED = -2;
static const int UNMARKED = -1;
static const int defaultCharBufferSize = 8192;
static const int defaultExpectedLineLength = 80;

type (BufferedReader) {
    Class isa;
    Reader* in;
    IOBuff cb;
    int nChars;
    int nextChar;
    int markedChar;
    int readAheadLimit;
    bool skipLF;
    bool markedSkipLF;
};

delegate (BufferedReader, New,          BufferedReader*, (BufferedReader*, Reader*, int));
delegate (BufferedReader, ToString,     const char*, (const BufferedReader* const) );
delegate (BufferedReader, ReadOne,      int,    (BufferedReader*) );
delegate (BufferedReader, Read,         int,    (BufferedReader*, IOBuff*, int, int) );
delegate (BufferedReader, Skip,         long,   (BufferedReader*, long) );
delegate (BufferedReader, Close,        void,   (BufferedReader*) );
delegate (BufferedReader, Mark,         void,   (BufferedReader*, int) );
delegate (BufferedReader, MarkSupported,bool,   (BufferedReader*) );
delegate (BufferedReader, Reset,        void,   (BufferedReader*) );
delegate (BufferedReader, Ready,        bool,   (BufferedReader*) );
delegate (BufferedReader, ReadLine,     String*, (BufferedReader*, bool) );

vtable (BufferedReader) {
    const BufferedReaderToString      ToString;
    const ObjectEquals                Equals;
    const ObjectGetHashCode           GetHashCode;
    const ObjectDispose               Dispose;
    const BufferedReaderReadOne       ReadOne;
    const BufferedReaderRead          Read;
    const BufferedReaderSkip          Skip;
    const BufferedReaderClose         Close;
    const BufferedReaderMark          Mark;
    const BufferedReaderMarkSupported MarkSupported;
    const BufferedReaderReset         Reset;
    const BufferedReaderReady         Ready;
    const BufferedReaderReadLine      ReadLine;
};

static inline vptr(BufferedReader);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadBufferedReader(Class super) 
{
    Class cls = createClass(super, BufferedReader);
    addMethod(cls, BufferedReader, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, BufferedReader, ReadOne);
    addMethod(cls, BufferedReader, Read);
    addMethod(cls, BufferedReader, Skip);
    addMethod(cls, BufferedReader, Close);
    addMethod(cls, BufferedReader, Mark);
    addMethod(cls, BufferedReader, MarkSupported);
    addMethod(cls, BufferedReader, Reset);
    addMethod(cls, BufferedReader, Ready);
    addMethod(cls, BufferedReader, ReadLine);
    
    return cls;
}



method BufferedReader* New(BufferedReader* self, Reader* in, int sz) {
    extends(Reader);
    self->isa = objc_getClass("BufferedReader");
    self->markedChar = UNMARKED;
    self->readAheadLimit = 0;
    self->skipLF = false;
    self->markedSkipLF = false;
    if (sz <= 0) throw DSIllegalArgumentException("Buffer size <= 0", Source);
    self->in = in;
    self->cb.buff = DScalloc(1, sz);
    self->cb.len = sz;
    self->nextChar = 0;
    self->nChars = 0;
    return self;
}

method BufferedReader* New(BufferedReader* self, Reader* in) {
    New(self, in, defaultCharBufferSize);
}


static inline void EnsureOpen(const BufferedReader* const self) {
    if (self->in == nullptr) throw DSIllegalArgumentException("Stream closed", Source);
}

static inline void Fill(BufferedReader* const self) {
    int dst;
    if (self->markedChar <= UNMARKED) {
        dst = 0;
    } else {
        int delta = self->nextChar - self->markedChar;
        if (delta >= self->readAheadLimit) {
            /* Gone past read-ahead limit: Invalidate mark */
            self->markedChar = INVALIDATED;
            self->readAheadLimit = 0;
            dst = 0;
        } else {
            if (self->readAheadLimit <= self->cb.len) {
                memcpy(&self->cb, &self->cb+self->markedChar, delta);
                self->markedChar = 0;
                dst = delta;
            } else {
                char* ncb = DScalloc(1, self->readAheadLimit);
                memcpy(ncb, &self->cb+self->markedChar, delta);
                self->cb.buff = ncb;
                self->markedChar = 0;
                dst = delta;
            }
            self->nextChar = self->nChars = delta;
        }

    }
    int n = 0;
    do {
        n = Read(self->in, &self->cb, dst, self->cb.len - dst);
    } while (n == 0);
    if (n > 0) {
        self->nChars = dst + n;
        self->nextChar = dst;
    }
 }

method const char* ToString(const BufferedReader* const self) {
    return "BufferedReader";
}

method int ReadOne(BufferedReader* self) {
    EnsureOpen(self);
    for (;;) {
        if (self->nextChar >= self->nChars) {
            Fill(self);
            if (self->nextChar >= self->nChars)
                return -1;
        }
        if (self->skipLF) {
            self->skipLF = false;
            if (self->cb.buff[self->nextChar] == '\n') {
                self->nextChar++;
                continue;
            }
        }
        return self->cb.buff[self->nextChar++];
    }
}

method static int Read1(BufferedReader* self, IOBuff* cbuf, int off, int len) {
    if (self->nextChar >= self->nChars) {
        /* If the requested length is at least as large as the buffer, and
            if there is no mark/reset activity, and if line feeds are not
            being skipped, do not bother to copy the characters into the
            local buffer.  In self way buffered streams will cascade
            harmlessly. */
        if (len >= self->cb.len && self->markedChar <= UNMARKED && !self->skipLF) {
            return Read(self->in, &cbuf, off, len);
        }
        Fill(self);
    }
    if (self->nextChar >= self->nChars) return -1;
    if (self->skipLF) {
        self->skipLF = false;
        if (self->cb.buff[self->nextChar] == '\n') {
            self->nextChar++;
            if (self->nextChar >= self->nChars)
                Fill(self);
            if (self->nextChar >= self->nChars)
                return -1;
        }
    }
    int n = (int)Min(len, self->nChars - self->nextChar);
    memcpy(&cbuf+off, &self->cb+self->nextChar, n);
    self->nextChar += n;
    return n;

}

method int Read(BufferedReader* self, IOBuff* cbuf, int off, int len) {
    if (len==0) len = cbuf->len-off;
    EnsureOpen(self);
    if ((off < 0) || (off > cbuf->len) || (len < 0) ||
        ((off + len) > cbuf->len) || ((off + len) < 0)) {
        throw DSIndexOutOfBoundsException(off, Source);
    } else if (len == 0) {
        return 0;
    }

    int n = Read1(self, cbuf, off, len);
    if (n <= 0) return n;
    while ((n < len) && Ready(self->in)) {
        int n1 = Read1(self, cbuf, off + n, len - n);
        if (n1 <= 0) break;
        n += n1;
    }
    return n;
}

method String* ReadLine(BufferedReader* self) {
    ReadLine(self, false);
}

method String* ReadLine(BufferedReader* self, bool ignoreLF) {
    StringBuilder* s = nullptr;
    int startChar;

    EnsureOpen(self);
    bool omitLF = ignoreLF || self->skipLF;

    for (;;) {

        if (self->nextChar >= self->nChars)
            Fill(self);
        if (self->nextChar >= self->nChars) { /* EOF */
            if (s != nullptr && s->length > 0)
                return Concat(s);
            else
                return nullptr;
        }
        bool eol = false;
        char c = 0;
        int i;

        /* Skip a leftover '\n', if necessary */
        if (omitLF && (self->cb.buff[self->nextChar] == '\n'))
            self->nextChar++;
        self->skipLF = false;
        omitLF = false;

    // charLoop:
        for (i = self->nextChar; i < self->nChars; i++) {
            c = self->cb.buff[i];
            if ((c == '\n') || (c == '\r')) {
                eol = true;
                break; // charLoop;
            }
        }

        startChar = self->nextChar;
        self->nextChar = i;

        if (eol) {
            String* str;
            if (s == nullptr) {
                str = new(String, strndup(&self->cb.buff[startChar], i-startChar));
            } else {
                Append(s, strndup(&self->cb.buff[startChar], i-startChar));
                str = Concat(s);
            }
            self->nextChar++;
            if (c == '\r') {
                self->skipLF = true;
            }
            return str;
        }

        if (s == nullptr)
            s = new (StringBuilder);
        Append(s, strndup(&self->cb.buff[startChar], i-startChar));
    }
}

method long Skip(BufferedReader* self, long n)  {
    if (n < 0L) {
        throw DSIllegalArgumentException("skip value is negative", Source);
    }
    EnsureOpen(self);
    long r = n;
    while (r > 0) {
        if (self->nextChar >= self->nChars)
            Fill(self);
        if (self->nextChar >= self->nChars) /* EOF */
            break;
        if (self->skipLF) {
            self->skipLF = false;
            if (self->cb.buff[self->nextChar] == '\n') {
                self->nextChar++;
            }
        }
        long d = self->nChars - self->nextChar;
        if (r <= d) {
            self->nextChar += (int)r;
            r = 0;
            break;
        }
        else {
            r -= d;
            self->nextChar = self->nChars;
        }
    }
    return n - r;
}

method bool Ready(BufferedReader* self) {
    EnsureOpen(self);

    /*
        * If newline needs to be skipped and the next char to be read
        * is a newline character, then just skip it right away.
        */
    if (self->skipLF) {
        /* Note that in.ready() will return true if and only if the next
            * read on the stream will not block.
            */
        if (self->nextChar >= self->nChars && Ready(self->in)) {
            Fill(self);
        }
        if (self->nextChar < self->nChars) {
            if (self->cb.buff[self->nextChar] == '\n')
                self->nextChar++;
            self->skipLF = false;
        }
    }
    return (self->nextChar < self->nChars) || Ready(self->in);
}

method bool MarkSupported(BufferedReader* self) {
    return true;
}

method void Mark(BufferedReader* self, int readAheadLimit) {
    if (readAheadLimit < 0) {
        throw DSIllegalArgumentException("Read-ahead limit < 0", Source);
    }
    EnsureOpen(self);
    self->readAheadLimit = readAheadLimit;
    self->markedChar = self->nextChar;
    self->markedSkipLF = self->skipLF;
}

method void Reset(BufferedReader* self) {
    EnsureOpen(self);
    if (self->markedChar < 0)
        throw DSIllegalArgumentException((self->markedChar == INVALIDATED)
                                ? "Mark invalid"
                                : "Stream not marked", Source);
    self->nextChar = self->markedChar;
    self->skipLF = self->markedSkipLF;
}

method void Close(BufferedReader* self) {
    if (self->in == nullptr)
        return;
    try {
        Close(self->in);
    } finally {
        self->in = nullptr;
        self->cb.buff = nullptr;
    }
}
