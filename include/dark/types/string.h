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
#include <string.h>
#include <dark/core/comparable.h>

#define STRING_TYPE       (TYPE_STRING)

#define IsString(object) _Generic((object), String*: true, default: false)
#define AsString(object) _Generic((object),                           \
                            String*: (String *)object,              \
                            default: nullptr)

/**
 * Object class
 */
type (String) {
    Class isa;
    const char* value;
    int length;
};

method_proto (String, ToString,     char*, (const String* const));
method_proto (String, Equals,       bool, (const String* const, const String* const));
method_proto (String, CompareTo,    int, (const String* const this, const String* const other));
method_proto (String, Compare,      int, (const char* x, const char* y));
method_proto (String, CompareToIgnoreCase,   int, (const String* this, const String* other));
method_proto (String, Concat,       String*, (const String* this, const String* str));
method_proto (String, Concatc,      String*, (const String* this, const char* str));
method_proto (String, Contains,     bool, (const String* this, const String* str));
method_proto (String, CopyOf,       String*, (const String* this));
method_proto (String, EndsWith,     bool, (const String* this, const String* suffix););
method_proto (String, StartsWith,   bool, (const String* this, const String* prefix, const int offset));
method_proto (String, GetBytes,     char*, (const String* this));
method_proto (String, IndexOf,      int, (const String* this, const String* str, const int fromIndex));
method_proto (String, LastIndexOf,  int, (const String* this, const String* str, const int fromIndex));
method_proto (String, ToUpperCase,  String*, (const String* this));
method_proto (String, ToLowerCase,  String*, (const String* this));
method_proto (String, Trim,         String*, (const String* this));
method_proto (String, Length,       int, (const String* const));
method_proto (String, IsEmpty,      bool, (const String* const this));
method_proto (String, CharAt,       char, (const String* const this, const int index));
// method_proto (String, Substring,    String*, (const String* const this, const int index));
method_proto (String, Substring,    String*, (const String* const this, const int index, const int length));

method __attribute__((__format__ (__printf__, 1, 2)))
String*   Format(const char* format, ...);

/**
 * Object metaclass
 */
vtable (String) {
    const StringToString              ToString;
    const StringEquals                Equals;
    const ObjectGetHashCode           GetHashCode;
    const ObjectDispose               Dispose;
    const StringCompareTo             CompareTo;
    const StringLength                Length;
    const StringIsEmpty               IsEmpty;
    const StringCharAt                CharAt;
    const StringCompareToIgnoreCase   CompareToIgnoreCase;
    const StringConcat                Concat;
    const StringConcatc               Concatc;
    const StringContains              Contains;
    const StringCopyOf                CopyOf;
    const StringEndsWith              EndsWith;
    const StringStartsWith            StartsWith;
    const StringGetBytes              GetBytes;
    const StringIndexOf               IndexOf;
    const StringLastIndexOf           LastIndexOf;
    const StringToUpperCase           ToUpperCase;
    const StringToLowerCase           ToLowerCase;
    const StringTrim                  Trim;
    const StringSubstring             Substring;
};

class (String) {
    String* (*Join) (int count, ...);
};

method String* StringJoin(int count, ...);

class_load( String );
class_override( ToString,           (StringToString)ToString, "$@:v" );
class_override( Equals,             (StringEquals)Equals, "B@:@@" );
class_method( GetHashCode,          (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,              (ObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,          (StringCompareTo)CompareTo, "i@:@" );
class_method( Length,               (StringLength)Length, "i@:v" );
class_method( IsEmpty,              (StringIsEmpty)IsEmpty, "B@:v" );    
class_method( CharAt,               (StringCharAt)CharAt, "c@:i" );
class_method( CompareToIgnoreCase,  (StringCompareToIgnoreCase)CompareToIgnoreCase, "@:" );    
class_method( Concat,               (StringConcat)Concat, "v@:$" );
class_method( Concatc,              (StringConcatc)Concatc, "v@:c" );
class_method( Contains,             (StringContains)Contains, "B@:$" );
class_method( CopyOf,               (StringCopyOf)CopyOf, "$@:v" );
class_method( EndsWith,             (StringEndsWith)EndsWith, "B@:$" );
class_method( StartsWith,           (StringStartsWith)StartsWith, "B@:$" );
class_method( GetBytes,             (StringGetBytes)GetBytes, "b@:*" );
class_method( IndexOf,              (StringIndexOf)IndexOf, "i@:$" );
class_method( LastIndexOf,          (StringLastIndexOf)LastIndexOf, "i@:$" );
class_method( ToLowerCase,          (StringToLowerCase)ToLowerCase, "$@:v" );
class_method( ToUpperCase,          (StringToUpperCase)ToUpperCase, "$@:v" );
class_method( Trim,                 (StringTrim)Trim, "$@:v" );
class_method( Substring,            (StringSubstring)Substring, "$@:ii" );
class_member( value,                sizeof( char* ), "*" );
class_member( length,               sizeof( int ), "i" );

$String.Join = StringJoin;

class_fini


// function String* StringJoin(int count, ...);
/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
function String* String_init(String* const this, const char* value)
{
    Comparable_init(this);
    this->isa = objc_getClass("String");
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

function String* NewString(const char* const str) {
    return String_init(alloc(String), str); 
}

function void GetChars(const String* this, char* dst, int dstBegin) {
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
method int CompareTo(const String* const this, const String* const other) {
    return Compare(this->value, other->value);
}

method bool Equals(const String* const this, const String* const other) {
    return Compare(this->value, other->value) == 0;
}

method int CompareToIgnoreCase(const String* this, const String* str) {
    return strcmpi(this->value, str->value);
}

method String* Concatc(const String* this, const char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DScalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    String* result = NewString(str);
    return result;

}

method String* Concat(const String* this, const String* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DScalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    String* result = NewString(str);
    return result;
}

method bool Contains(const String* this, const String* s) {
    return _vptr(String)->IndexOf(this, s, 0) > -1;
}

method String* CopyOf(const String* this) {
    return NewString(this->value);
}

method bool EndsWith(const String* this, const String* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

method bool StartsWith(const String* this, const String* prefix, const int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

method char* GetBytes(const String* this) {
    return strdup(this->value);
}

method int IndexOf(const String* this, const String* str, const int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

method int LastIndexOf(const String* this, const String* str, const int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

method String* ToUpperCase(const String* this) {
    return NewString(strupr(this->value));
}

method String* ToLowerCase(const String* this) {
    return NewString(strlwr(this->value));
}

method String* Trim(const String* this) {
    int len = this->length;
    int start = 0;
    while ((start < len) && (this->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (this->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < this->length)) 
        ? NewString(strndup(this->value+start, len-start))
        : this;    
}

method String* Substring(const String* this, const int index, const int length) {
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewString(result);
}

method String* Substring(const String* this, const int index) {
    int length = this->length - index;
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewString(result);
}

method int Length(const String* const this) 
{
    return this->length;
}

method bool IsEmpty(const String* const this)
{
    return this->length == 0;
}

method char CharAt(const String* const this, const int index)
{
    // printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        throw DSIndexOutOfBoundsException(index, Source);
    return this->value[index];
}
 

method char* ToString(const String* const this)
{
    return this->value;
}

method __attribute__((__format__ (__printf__, 1, 2)))
String* Format(const char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return NewString("");
    char* str = DScalloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return NewString(str);
}

/**
 * join strings
 * 
 * @param count of strings
 * @param ... list of String*'s
 * @returns all Strings concantenated together.
 */
method String* StringJoin(int count, ...)
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
        String* str = va_arg(args1, String*);
        size += Length(str);
    }
    va_end(args1);
    char* result = DScalloc((size+1),  sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        // String* str = va_arg(args2, String*);
        Object* str = va_arg(args2, Object*);
        strcat(result, ToString(str));
    }
    va_end(args2);
    return NewString(result);
}
