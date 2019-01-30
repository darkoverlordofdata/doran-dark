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
#ifndef _DSEXCEPTION_H_
#define _DSEXCEPTION_H_
#include "cexcept.h"
#include "DSObject.h"

#define IsDSException(object) _Generic((object), DSException*: true, default: false)
#define AsDSException(object) _Generic((object),                        \
                            DSException*: (DSException *)object,        \
                            default: nullptr)

typedef enum DSExceptionType {
    AbstractMethodException, 
    InvalidTypeException, 
    IndexOutOfBoundsException, 
    OutOfMemoryException,
    NumberFormatException
} DSExceptionType;

ivar (DSException) {
    Class isa;
    DSExceptionType type;
    const char *msg;
};

DSException* NewDSException(DSExceptionType type, char* msg);
DSException* DSException_init(DSException* this, DSExceptionType type, char* msg);

char*   overload ToString(const DSException* const);

typedef char*   (*DSExceptionToString)    (const DSException* const);

vtable (DSException) {
    const DSExceptionToString     ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
};

class (DSException) {
    DSException* (*Create)(DSExceptionType type, char* msg);
};

/** 
 * Exceptions
 * 
 * Exceptions can be thrown or passed in Either*
 */
define_exception_type(DSException*);
extern struct exception_context the_exception_context[1];

#define AT "in %s method %s at line %d"
#define Source DSsprintf(AT, __FILENAME__, __func__, __LINE__)

static inline DSException* DSInvalidTypeException(const char* name, const char* source) {
    return DSException_init(alloc(DSException), InvalidTypeException, 
        DSsprintf("InvalidTypeException: expecting %s %s", name, source));
}

static inline DSException* DSAbstractMethodException(const char* name, const char* source) {
    return DSException_init(alloc(DSException), AbstractMethodException, 
        DSsprintf("AbstractMethodException %s %s", name, source));
}

static inline DSException* DSIndexOutOfBoundsException(const int index, const char* source) {
    return DSException_init(alloc(DSException), IndexOutOfBoundsException, 
        DSsprintf("IndexOutOfBoundsException at index %d %s", index, source));
}

static inline DSException* DSOutOfMemoryException(const char* name, const char* source) {
    return DSException_init(alloc(DSException), OutOfMemoryException,
        DSsprintf("OutOfMemoryException %s %s", name, source));
}

static inline DSException* overload DSNumberFormatException(const char* raw, const char* source) {
    return DSException_init(alloc(DSException), NumberFormatException,
        DSsprintf("NumberFormatException Invalid input. Value:\"%s\" %s", raw, source));
}

static inline DSException* overload DSNumberFormatException(const char* raw, const int radix, const char* source) {
    return DSException_init(alloc(DSException), NumberFormatException,
        DSsprintf("NumberFormatException Invalid input. Value:\"%s\", Radix: %d %s", raw, radix, source));
}


#endif _DSEXCEPTION_H_