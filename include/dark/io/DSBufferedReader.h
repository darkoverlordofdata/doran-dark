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
#ifndef _DS_BUFFERED_READER_H_
#define _DS_BUFFERED_READER_H_
#include "../types.h"
#include "DSFileSystem.h"
#include "DSReader.h"

static const int INVALIDATED = -2;
static const int UNMARKED = -1;
static const int defaultCharBufferSize = 8192;
static const int defaultExpectedLineLength = 80;

IVAR (DSBufferedReader) {
    Class isa;
    DSReader* in;
    IOBuff cb;
    int nChars;
    int nextChar;
    int markedChar;
    int readAheadLimit;
    bool skipLF;
    bool markedSkipLF;
};

CTOR (DSBufferedReader, DSReader*);
CTOR (DSBufferedReader, DSReader*, int);

METHOD (DSBufferedReader, ToString, const char*, (const DSBufferedReader* const) );
METHOD (DSBufferedReader, ReadOne,         int,    (DSBufferedReader*) );
METHOD (DSBufferedReader, Read,            int,    (DSBufferedReader*, IOBuff*, int, int) );
METHOD (DSBufferedReader, Skip,            long,   (DSBufferedReader*, long) );
METHOD (DSBufferedReader, Close,           void,   (DSBufferedReader*) );
METHOD (DSBufferedReader, Mark,            void,   (DSBufferedReader*, int) );
METHOD (DSBufferedReader, MarkSupported,   bool,   (DSBufferedReader*) );
METHOD (DSBufferedReader, Reset,           void,   (DSBufferedReader*) );
METHOD (DSBufferedReader, Ready,           bool,   (DSBufferedReader*) );
METHOD (DSBufferedReader, ReadLine,        DSString*, (DSBufferedReader*, bool) );

VTABLE (DSBufferedReader) {
    const DSBufferedReaderToString      ToString;
    const DSObjectEquals                Equals;
    const DSObjectGetHashCode           GetHashCode;
    const DSObjectDispose               Dispose;
    const DSBufferedReaderReadOne       ReadOne;
    const DSBufferedReaderRead          Read;
    const DSBufferedReaderSkip          Skip;
    const DSBufferedReaderClose         Close;
    const DSBufferedReaderMark          Mark;
    const DSBufferedReaderMarkSupported MarkSupported;
    const DSBufferedReaderReset         Reset;
    const DSBufferedReaderReady         Ready;
    const DSBufferedReaderReadLine      ReadLine;
};

DEF_VPTR(DSBufferedReader);

static inline overload DSBufferedReader* DSBufferedReader_init(DSBufferedReader* const this, DSReader* in) {
    DSBufferedReader_init(this, in, defaultCharBufferSize);
}

static inline overload DSBufferedReader* DSBufferedReader_init(DSBufferedReader* const this, DSReader* in, int sz) {
    DSReader_init(this);
    this->isa = objc_getClass("DSBufferedReader");
    this->markedChar = UNMARKED;
    this->readAheadLimit = 0;
    this->skipLF = false;
    this->markedSkipLF = false;
    if (sz <= 0) throw DSIllegalArgumentException("Buffer size <= 0", Source);
    this->in = in;
    this->cb.buff = DScalloc(1, sz);
    this->cb.len = sz;
    this->nextChar = 0;
    this->nChars = 0;
    return this;
}

static inline void EnsureOpen(const DSBufferedReader* const this) {
    if (this->in == nullptr) throw DSIllegalArgumentException("Stream closed", Source);
}

static inline void Fill(DSBufferedReader* const this) {
    int dst;
    if (this->markedChar <= UNMARKED) {
        dst = 0;
    } else {
        int delta = this->nextChar - this->markedChar;
        if (delta >= this->readAheadLimit) {
            /* Gone past read-ahead limit: Invalidate mark */
            this->markedChar = INVALIDATED;
            this->readAheadLimit = 0;
            dst = 0;
        } else {
            if (this->readAheadLimit <= this->cb.len) {
                memcpy(&this->cb, &this->cb+this->markedChar, delta);
                this->markedChar = 0;
                dst = delta;
            } else {
                char* ncb = DScalloc(1, this->readAheadLimit);
                memcpy(ncb, &this->cb+this->markedChar, delta);
                this->cb.buff = ncb;
                this->markedChar = 0;
                dst = delta;
            }
            this->nextChar = this->nChars = delta;
        }

    }
    int n = 0;
    do {
        n = Read(this->in, &this->cb, dst, this->cb.len - dst);
    } while (n == 0);
    if (n > 0) {
        this->nChars = dst + n;
        this->nextChar = dst;
    }
 }

static inline overload const char* ToString(const DSBufferedReader* const this) {
    return "DSBufferedReader";
}

static inline overload int ReadOne(DSBufferedReader* this) {
    EnsureOpen(this);
    for (;;) {
        if (this->nextChar >= this->nChars) {
            Fill(this);
            if (this->nextChar >= this->nChars)
                return -1;
        }
        if (this->skipLF) {
            this->skipLF = false;
            if (this->cb.buff[this->nextChar] == '\n') {
                this->nextChar++;
                continue;
            }
        }
        return this->cb.buff[this->nextChar++];
    }
}

static inline overload static int Read1(DSBufferedReader* this, IOBuff* cbuf, int off, int len) {
    if (this->nextChar >= this->nChars) {
        /* If the requested length is at least as large as the buffer, and
            if there is no mark/reset activity, and if line feeds are not
            being skipped, do not bother to copy the characters into the
            local buffer.  In this way buffered streams will cascade
            harmlessly. */
        if (len >= this->cb.len && this->markedChar <= UNMARKED && !this->skipLF) {
            return Read(this->in, &cbuf, off, len);
        }
        Fill(this);
    }
    if (this->nextChar >= this->nChars) return -1;
    if (this->skipLF) {
        this->skipLF = false;
        if (this->cb.buff[this->nextChar] == '\n') {
            this->nextChar++;
            if (this->nextChar >= this->nChars)
                Fill(this);
            if (this->nextChar >= this->nChars)
                return -1;
        }
    }
    int n = (int)Min(len, this->nChars - this->nextChar);
    memcpy(&cbuf+off, &this->cb+this->nextChar, n);
    this->nextChar += n;
    return n;

}

static inline overload int Read(DSBufferedReader* this, IOBuff* cbuf, int off, int len) {
    if (len==0) len = cbuf->len-off;
    EnsureOpen(this);
    if ((off < 0) || (off > cbuf->len) || (len < 0) ||
        ((off + len) > cbuf->len) || ((off + len) < 0)) {
        throw DSIndexOutOfBoundsException(off, Source);
    } else if (len == 0) {
        return 0;
    }

    int n = Read1(this, cbuf, off, len);
    if (n <= 0) return n;
    while ((n < len) && Ready(this->in)) {
        int n1 = Read1(this, cbuf, off + n, len - n);
        if (n1 <= 0) break;
        n += n1;
    }
    return n;
}

static inline overload DSString* ReadLine(DSBufferedReader* this) {
    ReadLine(this, false);
}

static inline overload DSString* ReadLine(DSBufferedReader* this, bool ignoreLF) {
    DSStringBuilder* s = nullptr;
    int startChar;

    EnsureOpen(this);
    bool omitLF = ignoreLF || this->skipLF;

    for (;;) {

        if (this->nextChar >= this->nChars)
            Fill(this);
        if (this->nextChar >= this->nChars) { /* EOF */
            if (s != nullptr && s->length > 0)
                return Concat(s);
            else
                return nullptr;
        }
        bool eol = false;
        char c = 0;
        int i;

        /* Skip a leftover '\n', if necessary */
        if (omitLF && (this->cb.buff[this->nextChar] == '\n'))
            this->nextChar++;
        this->skipLF = false;
        omitLF = false;

    // charLoop:
        for (i = this->nextChar; i < this->nChars; i++) {
            c = this->cb.buff[i];
            if ((c == '\n') || (c == '\r')) {
                eol = true;
                break; // charLoop;
            }
        }

        startChar = this->nextChar;
        this->nextChar = i;

        if (eol) {
            DSString* str;
            if (s == nullptr) {
                str = $(strndup(&this->cb.buff[startChar], i-startChar));
            } else {
                Append(s, strndup(&this->cb.buff[startChar], i-startChar));
                str = Concat(s);
            }
            this->nextChar++;
            if (c == '\r') {
                this->skipLF = true;
            }
            return str;
        }

        if (s == nullptr)
            s = new (DSStringBuilder);
        Append(s, strndup(&this->cb.buff[startChar], i-startChar));
    }
}

static inline overload long Skip(DSBufferedReader* this, long n)  {
    if (n < 0L) {
        throw DSIllegalArgumentException("skip value is negative", Source);
    }
    EnsureOpen(this);
    long r = n;
    while (r > 0) {
        if (this->nextChar >= this->nChars)
            Fill(this);
        if (this->nextChar >= this->nChars) /* EOF */
            break;
        if (this->skipLF) {
            this->skipLF = false;
            if (this->cb.buff[this->nextChar] == '\n') {
                this->nextChar++;
            }
        }
        long d = this->nChars - this->nextChar;
        if (r <= d) {
            this->nextChar += (int)r;
            r = 0;
            break;
        }
        else {
            r -= d;
            this->nextChar = this->nChars;
        }
    }
    return n - r;
}

static inline overload bool Ready(DSBufferedReader* this) {
    EnsureOpen(this);

    /*
        * If newline needs to be skipped and the next char to be read
        * is a newline character, then just skip it right away.
        */
    if (this->skipLF) {
        /* Note that in.ready() will return true if and only if the next
            * read on the stream will not block.
            */
        if (this->nextChar >= this->nChars && Ready(this->in)) {
            Fill(this);
        }
        if (this->nextChar < this->nChars) {
            if (this->cb.buff[this->nextChar] == '\n')
                this->nextChar++;
            this->skipLF = false;
        }
    }
    return (this->nextChar < this->nChars) || Ready(this->in);
}

static inline overload bool MarkSupported(DSBufferedReader* this) {
    return true;
}

static inline overload void Mark(DSBufferedReader* this, int readAheadLimit) {
    if (readAheadLimit < 0) {
        throw DSIllegalArgumentException("Read-ahead limit < 0", Source);
    }
    EnsureOpen(this);
    this->readAheadLimit = readAheadLimit;
    this->markedChar = this->nextChar;
    this->markedSkipLF = this->skipLF;
}

static inline overload void Reset(DSBufferedReader* this) {
    EnsureOpen(this);
    if (this->markedChar < 0)
        throw DSIllegalArgumentException((this->markedChar == INVALIDATED)
                                ? "Mark invalid"
                                : "Stream not marked", Source);
    this->nextChar = this->markedChar;
    this->skipLF = this->markedSkipLF;
}

static inline overload void Close(DSBufferedReader* this) {
    if (this->in == nullptr)
        return;
    try {
        Close(this->in);
    } finally {
        this->in = nullptr;
        this->cb.buff = nullptr;
    }
}


VTABLE_BIND( DSBufferedReader );
VTABLE_OVERRIDE( ToString,        (DSBufferedReaderToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_METHOD( ReadOne,           (DSBufferedReaderReadOne)ReadOne, "i@:v" );
VTABLE_METHOD( Read,              (DSBufferedReaderRead)Read, "i@:^ii" );
VTABLE_METHOD( Skip,              (DSBufferedReaderSkip)Skip, "l@:l" );
VTABLE_METHOD( Close,             (DSBufferedReaderClose)Close, "v@:v" );
VTABLE_METHOD( Mark,              (DSBufferedReaderMark)Mark, "v@:i" );
VTABLE_METHOD( MarkSupported,     (DSBufferedReaderMarkSupported)MarkSupported, "v@:v" );
VTABLE_METHOD( Reset,             (DSBufferedReaderReset)Reset, "v@:v" );
VTABLE_METHOD( Ready,             (DSBufferedReaderReady)Ready, "B@:" );
VTABLE_METHOD( ReadLine,          (DSBufferedReaderReadLine)ReadLine, "$@:B" );
VTABLE_METHODIZE;
#endif _DS_BUFFERED_READER_H_