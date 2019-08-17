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
type (DSString) {
    Class isa;
    const char* value;
    int length;
};

method_proto (DSString, ToString,     char*, (const DSString* const));
method_proto (DSString, Equals,       bool, (const DSString* const, const DSString* const));
method_proto (DSString, CompareTo,    int, (const DSString* const this, const DSString* const other));
method_proto (DSString, Compare,      int, (const char* x, const char* y));
method_proto (DSString, CompareToIgnoreCase,   int, (const DSString* this, const DSString* other));
method_proto (DSString, Concat,       DSString*, (const DSString* this, const DSString* str));
method_proto (DSString, Concatc,      DSString*, (const DSString* this, const char* str));
method_proto (DSString, Contains,     bool, (const DSString* this, const DSString* str));
method_proto (DSString, CopyOf,       DSString*, (const DSString* this));
method_proto (DSString, EndsWith,     bool, (const DSString* this, const DSString* suffix););
method_proto (DSString, StartsWith,   bool, (const DSString* this, const DSString* prefix, const int offset));
method_proto (DSString, GetBytes,     char*, (const DSString* this));
method_proto (DSString, IndexOf,      int, (const DSString* this, const DSString* str, const int fromIndex));
method_proto (DSString, LastIndexOf,  int, (const DSString* this, const DSString* str, const int fromIndex));
method_proto (DSString, ToUpperCase,  DSString*, (const DSString* this));
method_proto (DSString, ToLowerCase,  DSString*, (const DSString* this));
method_proto (DSString, Trim,         DSString*, (const DSString* this));
method_proto (DSString, Length,       int, (const DSString* const));
method_proto (DSString, IsEmpty,      bool, (const DSString* const this));
method_proto (DSString, CharAt,       char, (const DSString* const this, const int index));
// method_proto (DSString, Substring,    DSString*, (const DSString* const this, const int index));
method_proto (DSString, Substring,    DSString*, (const DSString* const this, const int index, const int length));

method __attribute__((__format__ (__printf__, 1, 2)))
DSString*   Format(const char* format, ...);

/**
 * Object metaclass
 */
vtable (DSString) {
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

method DSString* StringJoin(int count, ...);

class_load( DSString );
class_override( ToString,         (DSStringToString)ToString, "$@:v" );
class_override( Equals,           (DSStringEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSStringCompareTo)CompareTo, "i@:@" );
class_method( Length,             (DSStringLength)Length, "i@:v" );
class_method( IsEmpty,            (DSStringIsEmpty)IsEmpty, "B@:v" );    
class_method( CharAt,             (DSStringCharAt)CharAt, "c@:i" );
class_method( CompareToIgnoreCase, (DSStringCompareToIgnoreCase)CompareToIgnoreCase, "@:" );    
class_method( Concat,             (DSStringConcat)Concat, "v@:$" );
class_method( Concatc,            (DSStringConcatc)Concatc, "v@:c" );
class_method( Contains,           (DSStringContains)Contains, "B@:$" );
class_method( CopyOf,             (DSStringCopyOf)CopyOf, "$@:v" );
class_method( EndsWith,           (DSStringEndsWith)EndsWith, "B@:$" );
class_method( StartsWith,         (DSStringStartsWith)StartsWith, "B@:$" );
class_method( GetBytes,           (DSStringGetBytes)GetBytes, "b@:*" );
class_method( IndexOf,            (DSStringIndexOf)IndexOf, "i@:$" );
class_method( LastIndexOf,        (DSStringLastIndexOf)LastIndexOf, "i@:$" );
class_method( ToLowerCase,        (DSStringToLowerCase)ToLowerCase, "$@:v" );
class_method( ToUpperCase,        (DSStringToUpperCase)ToUpperCase, "$@:v" );
class_method( Trim,               (DSStringTrim)Trim, "$@:v" );
class_method( Substring,          (DSStringSubstring)Substring, "$@:ii" );
class_member( value, sizeof( char* ), "*" );
class_member( length, sizeof( int ), "i" );

$DSString.Join = StringJoin;

class_fini



// function DSString* StringJoin(int count, ...);
/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
function DSString* DSString_init(DSString* const this, const char* value)
{
    DSComparable_init(this);
    this->isa = objc_getClass("DSString");
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

function DSString* NewDSString(const char* const str) {
    return DSString_init(alloc(DSString), str); 
}

function void GetChars(const DSString* this, char* dst, int dstBegin) {
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
method int Compare(const char* x, const char* y) {
    return strcmp(x, y);
}

/**
 * Compares two String objects.
 *
 * @param   other  String to be compared
 * @return same as String_Compare
 */
method int CompareTo(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value);
}

method bool Equals(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value) == 0;
}

method int CompareToIgnoreCase(const DSString* this, const DSString* str) {
    return strcmpi(this->value, str->value);
}

method DSString* Concatc(const DSString* this, const char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DScalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    DSString* result = NewDSString(str);
    return result;

}

method DSString* Concat(const DSString* this, const DSString* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DScalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    DSString* result = NewDSString(str);
    return result;
}

method bool Contains(const DSString* this, const DSString* s) {
    return _vptr(DSString)->IndexOf(this, s, 0) > -1;
}

method DSString* CopyOf(const DSString* this) {
    return NewDSString(this->value);
}

method bool EndsWith(const DSString* this, const DSString* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

method bool StartsWith(const DSString* this, const DSString* prefix, const int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

method char* GetBytes(const DSString* this) {
    return strdup(this->value);
}

method int IndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

method int LastIndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

method DSString* ToUpperCase(const DSString* this) {
    return NewDSString(strupr(this->value));
}

method DSString* ToLowerCase(const DSString* this) {
    return NewDSString(strlwr(this->value));
}

method DSString* Trim(const DSString* this) {
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

method DSString* Substring(const DSString* this, const int index, const int length) {
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

method DSString* Substring(const DSString* this, const int index) {
    int length = this->length - index;
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

method int Length(const DSString* const this) 
{
    return this->length;
}

method bool IsEmpty(const DSString* const this)
{
    return this->length == 0;
}

method char CharAt(const DSString* const this, const int index)
{
    // printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        throw DSIndexOutOfBoundsException(index, Source);
    return this->value[index];
}
 

method char* ToString(const DSString* const this)
{
    return this->value;
}

method __attribute__((__format__ (__printf__, 1, 2)))
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
method DSString* StringJoin(int count, ...)
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

#endif _DSSTRING_H_
