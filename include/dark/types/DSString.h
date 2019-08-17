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
#ifndef _DSSTRING_H_
#define _DSSTRING_H_
#include <string.h>
#include "../DSComparable.h"

#define STRING_TYPE       (TYPE_STRING)

#define IsDSString(object) _Generic((object), DSString*: true, default: false)
#define AsDSString(object) _Generic((object),                           \
                            DSString*: (DSString *)object,              \
                            default: nullptr)

/**
 * Object class
 */
IVAR (DSString) {
    Class isa;
    const char* value;
    int length;
};

METHOD (DSString, ToString,     char*, (const DSString* const));
METHOD (DSString, Equals,       bool, (const DSString* const, const DSString* const));
METHOD (DSString, CompareTo,    int, (const DSString* const this, const DSString* const other));
METHOD (DSString, Compare,      int, (const char* x, const char* y));
METHOD (DSString, CompareToIgnoreCase,   int, (const DSString* this, const DSString* other));
METHOD (DSString, Concat,       DSString*, (const DSString* this, const DSString* str));
METHOD (DSString, Concatc,      DSString*, (const DSString* this, const char* str));
METHOD (DSString, Contains,     bool, (const DSString* this, const DSString* str));
METHOD (DSString, CopyOf,       DSString*, (const DSString* this));
METHOD (DSString, EndsWith,     bool, (const DSString* this, const DSString* suffix););
METHOD (DSString, StartsWith,   bool, (const DSString* this, const DSString* prefix, const int offset));
METHOD (DSString, GetBytes,     char*, (const DSString* this));
METHOD (DSString, IndexOf,      int, (const DSString* this, const DSString* str, const int fromIndex));
METHOD (DSString, LastIndexOf,  int, (const DSString* this, const DSString* str, const int fromIndex));
METHOD (DSString, ToUpperCase,  DSString*, (const DSString* this));
METHOD (DSString, ToLowerCase,  DSString*, (const DSString* this));
METHOD (DSString, Trim,         DSString*, (const DSString* this));
METHOD (DSString, Length,       int, (const DSString* const));
METHOD (DSString, IsEmpty,      bool, (const DSString* const this));
METHOD (DSString, CharAt,       char, (const DSString* const this, const int index));
// METHOD (DSString, Substring,    DSString*, (const DSString* const this, const int index));
METHOD (DSString, Substring,    DSString*, (const DSString* const this, const int index, const int length));

static inline overload __attribute__((__format__ (__printf__, 1, 2)))
DSString*   Format(const char* format, ...);

/**
 * Object metaclass
 */
VTABLE (DSString) {
    const DSStringToString              ToString;
    const DSStringEquals                Equals;
    const DSObjectGetHashCode           GetHashCode;
    const DSObjectDispose               Dispose;
    const DSStringCompareTo             CompareTo;
    const DSStringLength                Length;
    const DSStringIsEmpty               IsEmpty;
    const DSStringCharAt                CharAt;
    const DSStringCompareToIgnoreCase   CompareToIgnoreCase;
    const DSStringConcat                Concat;
    const DSStringConcatc               Concatc;
    const DSStringContains              Contains;
    const DSStringCopyOf                CopyOf;
    const DSStringEndsWith              EndsWith;
    const DSStringStartsWith            StartsWith;
    const DSStringGetBytes              GetBytes;
    const DSStringIndexOf               IndexOf;
    const DSStringLastIndexOf           LastIndexOf;
    const DSStringToUpperCase           ToUpperCase;
    const DSStringToLowerCase           ToLowerCase;
    const DSStringTrim                  Trim;
    const DSStringSubstring             Substring;
};

class (DSString) {
    DSString* (*Join) (int count, ...);
};

DEF_VPTR(DSString);


// static inline DSString* StringJoin(int count, ...);
/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
static inline DSString* DSString_init(DSString* const this, const char* value)
{
    DSComparable_init(this);
    this->isa = objc_getClass("DSString");
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

static inline DSString* NewDSString(const char* const str) {
    return DSString_init(alloc(DSString), str); 
}

static inline void GetChars(const DSString* this, char* dst, int dstBegin) {
    memcpy(dst+dstBegin, this->value, this->length);
}

/**
 * Compare two primitive character strings
 *
 * @param  x string to compare
 * @param  y string to compare
 * @return  0 x == y
 *         +1 x is true
 *         -1 y is true
 */
static inline overload int Compare(const char* x, const char* y) {
    return strcmp(x, y);
}

/**
 * Compares two String objects.
 *
 * @param   other  String to be compared
 * @return same as String_Compare
 */
static inline overload int CompareTo(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value);
}

static inline overload bool Equals(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value) == 0;
}

static inline overload int CompareToIgnoreCase(const DSString* this, const DSString* str) {
    return strcmpi(this->value, str->value);
}

static inline overload DSString* Concatc(const DSString* this, const char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DScalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    DSString* result = NewDSString(str);
    return result;

}

static inline overload DSString* Concat(const DSString* this, const DSString* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DScalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    DSString* result = NewDSString(str);
    return result;
}

static inline overload bool Contains(const DSString* this, const DSString* s) {
    return getVptr(DSString)->IndexOf(this, s, 0) > -1;
}

static inline overload DSString* CopyOf(const DSString* this) {
    return NewDSString(this->value);
}

static inline overload bool EndsWith(const DSString* this, const DSString* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

static inline overload bool StartsWith(const DSString* this, const DSString* prefix, const int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

static inline overload char* GetBytes(const DSString* this) {
    return strdup(this->value);
}

static inline overload int IndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

static inline overload int LastIndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

static inline overload DSString* ToUpperCase(const DSString* this) {
    return NewDSString(strupr(this->value));
}

static inline overload DSString* ToLowerCase(const DSString* this) {
    return NewDSString(strlwr(this->value));
}

static inline overload DSString* Trim(const DSString* this) {
    int len = this->length;
    int start = 0;
    while ((start < len) && (this->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (this->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < this->length)) 
        ? NewDSString(strndup(this->value+start, len-start))
        : this;    
}

static inline overload DSString* Substring(const DSString* this, const int index, const int length) {
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

static inline overload DSString* Substring(const DSString* this, const int index) {
    int length = this->length - index;
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

static inline overload int Length(const DSString* const this) 
{
    return this->length;
}

static inline overload bool IsEmpty(const DSString* const this)
{
    return this->length == 0;
}

static inline overload char CharAt(const DSString* const this, const int index)
{
    // printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        throw DSIndexOutOfBoundsException(index, Source);
    return this->value[index];
}
 

static inline overload char* ToString(const DSString* const this)
{
    return this->value;
}

static inline overload __attribute__((__format__ (__printf__, 1, 2)))
DSString* Format(const char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return NewDSString("");
    char* str = DScalloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return NewDSString(str);
}

/**
 * join strings
 * 
 * @param count of strings
 * @param ... list of DSString*'s
 * @returns all DSStrings concantenated together.
 */
static inline overload DSString* StringJoin(int count, ...)
{
    int size = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);  

    /**
     * Caclulate length of the result string
     */
    for (int i = 0; i < count; ++i) {
        DSString* str = va_arg(args1, DSString*);
        size += Length(str);
    }
    va_end(args1);
    char* result = DScalloc((size+1),  sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        // DSString* str = va_arg(args2, DSString*);
        DSObject* str = va_arg(args2, DSObject*);
        strcat(result, ToString(str));
    }
    va_end(args2);
    return NewDSString(result);
}



VTABLE_BIND( DSString );

VTABLE_OVERRIDE( ToString,         (DSStringToString)ToString, "$@:v" );
VTABLE_OVERRIDE( Equals,           (DSStringEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,        (DSStringCompareTo)CompareTo, "i@:@" );
VTABLE_METHOD( Length,             (DSStringLength)Length, "i@:v" );
VTABLE_METHOD( IsEmpty,            (DSStringIsEmpty)IsEmpty, "B@:v" );    
VTABLE_METHOD( CharAt,             (DSStringCharAt)CharAt, "c@:i" );
VTABLE_METHOD( CompareToIgnoreCase, (DSStringCompareToIgnoreCase)CompareToIgnoreCase, "@:" );    
VTABLE_METHOD( Concat,             (DSStringConcat)Concat, "v@:$" );
VTABLE_METHOD( Concatc,            (DSStringConcatc)Concatc, "v@:c" );
VTABLE_METHOD( Contains,           (DSStringContains)Contains, "B@:$" );
VTABLE_METHOD( CopyOf,             (DSStringCopyOf)CopyOf, "$@:v" );
VTABLE_METHOD( EndsWith,           (DSStringEndsWith)EndsWith, "B@:$" );
VTABLE_METHOD( StartsWith,         (DSStringStartsWith)StartsWith, "B@:$" );
VTABLE_METHOD( GetBytes,           (DSStringGetBytes)GetBytes, "b@:*" );
VTABLE_METHOD( IndexOf,            (DSStringIndexOf)IndexOf, "i@:$" );
VTABLE_METHOD( LastIndexOf,        (DSStringLastIndexOf)LastIndexOf, "i@:$" );
VTABLE_METHOD( ToLowerCase,        (DSStringToLowerCase)ToLowerCase, "$@:v" );
VTABLE_METHOD( ToUpperCase,        (DSStringToUpperCase)ToUpperCase, "$@:v" );
VTABLE_METHOD( Trim,               (DSStringTrim)Trim, "$@:v" );
VTABLE_METHOD( Substring,          (DSStringSubstring)Substring, "$@:ii" );

VTABLE_IVAR( value, sizeof( char* ), "*" );
VTABLE_IVAR( length, sizeof( int ), "i" );

$DSString.Join = StringJoin;

VTABLE_METHODIZE



#endif _DSSTRING_H_
