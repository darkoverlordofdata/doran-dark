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
#include <dark/cexcept.h>
#include <dark/core/object.h>

#define IsException(object) _Generic((object), Exception*: true, default: false)
#define AsException(object) _Generic((object),                        \
                            Exception*: (Exception *)object,        \
                            default: nullptr)

typedef enum ExceptionType {
    AbstractMethodException, 
    InvalidTypeException, 
    IndexOutOfBoundsException, 
    OutOfMemoryException,
    NumberFormatException,
    NullPointerException,
    FileNotFoundException,
    NotSupportedException,
    IllegalArgumentException
} ExceptionType;

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

type (Exception) 
{
    Class isa;
    ExceptionType type;
    const char *msg;
};

ctor_proto (Exception, ExceptionType, char*);
interface (Exception, ToString, const char*, (const Exception* const) );

vtable (Exception) 
{
    const ExceptionToString     ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
};

function vptr(Exception);

function Class objc_loadException(Class super) 
{
    Class cls = createClass(super, Exception);
    addMethod(cls, Exception,  ToString);
    addMethod(cls, Object,     Equals);
    addMethod(cls, Object,     GetHashCode);
    addMethod(cls, Object,     Dispose);
    return cls;
}

define_exception_type(Exception*);

/** 
 * Exceptions 
 */
struct exception_context the_exception_context[1];

/**
 * Returns the string value of this Exception
 */
method const char* ToString(const Exception* const this) {
    return this->msg;
}

function Exception* NewException(ExceptionType type, char* msg) {
    Exception* this = alloc(Exception);
    return Exception_init(this, type, msg);
}

method Exception* Exception_init(Exception* this, ExceptionType type, char* msg) {
    Object_init(this);
    this->isa = objc_getClass("Exception");
    this->type = type;
    this->msg = msg;
    return this;
}

// extern struct exception_context the_exception_context[1];
/** 
 * Builtin Exceptions
 * 
 * Exceptions can be thrown or passed in Either*
 */
method Exception* DSInvalidTypeException(const char* name, const char* source) {
    return NewException(InvalidTypeException, DSsprintf($InvalidTypeException, 
        name, source));
}

method Exception* DSAbstractMethodException(const char* name, const char* source) {
    return NewException(AbstractMethodException, DSsprintf($AbstractMethodException, 
        name, source));
}

method Exception* DSIndexOutOfBoundsException(const int index, const char* source) {
    return NewException(IndexOutOfBoundsException, DSsprintf($IndexOutOfBoundsException, 
        index, source));
}

method Exception* DSOutOfMemoryException(const char* name, const char* source) {
    return NewException(OutOfMemoryException, DSsprintf($OutOfMemoryException, 
        name, source));
}

method Exception* DSNumberFormatException(const char* raw, const char* source) {
    return NewException(NumberFormatException, DSsprintf($NumberFormatException2, 
        raw, source));
}

method Exception* DSNumberFormatException(const char* raw, const int radix, const char* source) {
    return NewException(NumberFormatException, DSsprintf($NumberFormatException3, 
        raw, radix, source));
}

method Exception* DSNullPointerException(const char* source) {
    return NewException(NullPointerException, DSsprintf($NullPointerException, source));
}

method Exception* DSFileNotFoundException(const char* name, const char* source) {
    return NewException(FileNotFoundException, DSsprintf($FileNotFoundException, name, source));
}

method Exception* DSNotSupportedException(const char* str, const char* source) {
    return NewException(NotSupportedException, DSsprintf($NotSupportedException, str, source));
}

method Exception* DSIllegalArgumentException(const char* str, const char* source) {
    return NewException(IllegalArgumentException, DSsprintf($IllegalArgumentException, str, source));
}


