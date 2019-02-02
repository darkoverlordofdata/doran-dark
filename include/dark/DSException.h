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
    NumberFormatException,
    NullPointerException,
    FileNotFoundException,
    NotSupportedException,
    IllegalArgumentException
} DSExceptionType;

#define $AbstractMethodException    "AbstractMethodException %s %s"
#define $InvalidTypeException       "InvalidTypeException: expecting %s %s"
#define $IndexOutOfBoundsException  "IndexOutOfBoundsException at index %d %s"
#define $OutOfMemoryException       "OutOfMemoryException %s %s"
#define $NumberFormatException2     "NumberFormatException Invalid input. Value:\"%s\" %s"
#define $NumberFormatException3     "NumberFormatException Invalid input. Value:\"%s\", Radix: %d %s"
#define $NullPointerException       "NullPointerException"
#define $FileNotFoundException      "FileNotFoundException: %s"  
#define $NotSupportedException      "NotSupportedException: %s"
#define $IllegalArgumentException   "IllegalArgumentException: %s"

#define AT "in %s method %s at line %d"
#define Source DSsprintf(AT, __FILENAME__, __func__, __LINE__)

ivar (DSException) {
    Class isa;
    DSExceptionType type;
    const char *msg;
};

// overload DSException* NewDSException(DSExceptionType, char*);
DSException* NewDSException(DSExceptionType type, char* msg);

ctor (DSException, DSExceptionType, char*);
method (DSException, ToString, const char*, (const DSException* const) );

vtable (DSException) {
    const DSExceptionToString     ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
};

define_exception_type(DSException*);
extern struct exception_context the_exception_context[1];
/** 
 * Builtin Exceptions
 * 
 * Exceptions can be thrown or passed in Either*
 */
static inline DSException* DSInvalidTypeException(const char* name, const char* source) {
    return NewDSException(InvalidTypeException, DSsprintf($InvalidTypeException, 
        name, source));
}

static inline DSException* DSAbstractMethodException(const char* name, const char* source) {
    return NewDSException(AbstractMethodException, DSsprintf($AbstractMethodException, 
        name, source));
}

static inline DSException* DSIndexOutOfBoundsException(const int index, const char* source) {
    return NewDSException(IndexOutOfBoundsException, DSsprintf($IndexOutOfBoundsException, 
        index, source));
}

static inline DSException* DSOutOfMemoryException(const char* name, const char* source) {
    return NewDSException(OutOfMemoryException, DSsprintf($OutOfMemoryException, 
        name, source));
}

static inline DSException* overload DSNumberFormatException(const char* raw, const char* source) {
    return NewDSException(NumberFormatException, DSsprintf($NumberFormatException2, 
        raw, source));
}

static inline DSException* overload DSNumberFormatException(const char* raw, const int radix, const char* source) {
    return NewDSException(NumberFormatException, DSsprintf($NumberFormatException3, 
        raw, radix, source));
}

static inline DSException* DSNullPointerException(const char* source) {
    return NewDSException(NullPointerException, DSsprintf($NullPointerException, source));
}

static inline DSException* DSFileNotFoundException(const char* name, const char* source) {
    return NewDSException(FileNotFoundException, DSsprintf($FileNotFoundException, name, source));
}

static inline DSException* DSNotSupportedException(const char* str, const char* source) {
    return NewDSException(NotSupportedException, DSsprintf($NotSupportedException, str, source));
}

static inline DSException* DSIllegalArgumentException(const char* str, const char* source) {
    return NewDSException(IllegalArgumentException, DSsprintf($IllegalArgumentException, str, source));
}

#endif _DSEXCEPTION_H_