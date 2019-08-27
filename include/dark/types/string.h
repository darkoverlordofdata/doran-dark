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

delegate (String, New,          String*, (String*, const char*));
delegate (String, ToString,     char*, (const String* const));
delegate (String, Dispose,      void, (const String* const));
delegate (String, Equals,       bool, (const String* const, const String* const));
delegate (String, CompareTo,    int, (const String* const self, const String* const other));
delegate (String, Compare,      int, (const char* x, const char* y));
delegate (String, CompareToIgnoreCase,   int, (const String* self, const String* other));
delegate (String, Concat,       String*, (const String* self, const String* str));
delegate (String, Concatc,      String*, (const String* self, const char* str));
delegate (String, Contains,     bool, (const String* self, const String* str));
delegate (String, CopyOf,       String*, (const String* self));
delegate (String, EndsWith,     bool, (const String* self, const String* suffix););
delegate (String, StartsWith,   bool, (const String* self, const String* prefix, const int offset));
delegate (String, GetBytes,     char*, (const String* self));
delegate (String, IndexOf,      int, (const String* self, const String* str, const int fromIndex));
delegate (String, LastIndexOf,  int, (const String* self, const String* str, const int fromIndex));
delegate (String, ToUpperCase,  String*, (const String* self));
delegate (String, ToLowerCase,  String*, (const String* self));
delegate (String, Trim,         String*, (const String* self));
delegate (String, Length,       int, (const String* const));
delegate (String, IsEmpty,      bool, (const String* const self));
delegate (String, CharAt,       char, (const String* const self, const int index));
// delegate (String, Substring,    String*, (const String* const self, const int index));
delegate (String, Substring,    String*, (const String* const self, const int index, const int length));

method __attribute__((__format__ (__printf__, 1, 2)))
String*   Format(const char* format, ...);

/**
 * Object metaclass
 */
vtable (String) {
    const StringToString              ToString;
    const StringEquals                Equals;
    const ObjectGetHashCode           GetHashCode;
    const StringDispose               Dispose;
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


static inline vptr(String);

/**
 * 
 * Class Loader callback
 */
static inline Class ClassLoadString(Class base) 
{
    Class cls = createClass(base, String);
    addMethod(cls, String,      ToString);
    addMethod(cls, String,        Equals);
    addMethod(cls, Object,   GetHashCode);
    addMethod(cls, Object,       Dispose);
    addMethod(cls, String,     CompareTo);
    addMethod(cls, String,        Length);
    addMethod(cls, String,       IsEmpty);    
    addMethod(cls, String,        CharAt);
    addMethod(cls, String, CompareToIgnoreCase);    
    addMethod(cls, String,        Concat);
    addMethod(cls, String,       Concatc);
    addMethod(cls, String,      Contains);
    addMethod(cls, String,        CopyOf);
    addMethod(cls, String,      EndsWith);
    addMethod(cls, String,    StartsWith);
    addMethod(cls, String,      GetBytes);
    addMethod(cls, String,       IndexOf);
    addMethod(cls, String,   LastIndexOf);
    addMethod(cls, String,   ToLowerCase);
    addMethod(cls, String,   ToUpperCase);
    addMethod(cls, String,          Trim);
    addMethod(cls, String,     Substring);

    $String.Join = StringJoin;
    return cls;
}



// static inline String* StringJoin(int count, ...);
/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
method String* New(String* self, const char* value)
{
    extends(Comparable);
    self->isa = isa(String);
    self->value = strdup(value);
    self->length = strlen(value);
    return self;
}


method void Dispose(String* self) {
    Dispose((Object*)self);
}
static inline void GetChars(const String* self, char* dst, int dstBegin) {
    memcpy(dst+dstBegin, self->value, self->length);
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
method int CompareTo(const String* const self, const String* const other) {
    return Compare(self->value, other->value);
}

method bool Equals(const String* const self, const String* const other) {
    return Compare(self->value, other->value) == 0;
}

method int CompareToIgnoreCase(const String* self, const String* str) {
    return strcmpi(self->value, str->value);
}

method String* Concatc(const String* self, const char* other) {
    int length = strlen(other);
    if (length == 0) return self;
    int len = self->length;
    char* str = DScalloc((len+length+1), sizeof(char));
    strncpy(str, self->value, len);
    strncpy(str+len, other, length);
    String* result = new(String, str);
    return result;

}

method String* Concat(const String* self, const String* other) {
    if (other->length == 0)
        return self;

    int len = self->length;
    char* str = DScalloc((len+other->length+1), sizeof(char));
    strncpy(str, self->value, len);
    strncpy(str+len, other->value, other->length);
    String* result = new(String, str);
    return result;
}

method bool Contains(const String* self, const String* s) {
    return virtual(String)->IndexOf(self, s, 0) > -1;
}

method String* CopyOf(const String* self) {
    return new(String, self->value);
}

method bool EndsWith(const String* self, const String* suffix) {
    char* offset = self->value + self->length - suffix->length;
    return !strcmp(offset, suffix);
}

method bool StartsWith(const String* self, const String* prefix, const int offset) {
    char* c = strstr(self->value+offset, prefix->value);
    return c == (self->value+offset) ? true : false;
}

method char* GetBytes(const String* self) {
    return strdup(self->value);
}

method int IndexOf(const String* self, const String* str, const int offset) {
    char* c = strstr(self->value+offset, str->value);
    return c == nullptr ? 0 : c - self->value;
}

method int LastIndexOf(const String* self, const String* str, const int offset) {
    char* c = strrstr(self->value+offset, str->value);
    return c == nullptr ? 0 : c - self->value;
}

method String* ToUpperCase(const String* self) {
    return new(String, strupr(self->value));
}

method String* ToLowerCase(const String* self) {
    return new(String, strlwr(self->value));
}

method String* Trim(const String* self) {
    int len = self->length;
    int start = 0;
    while ((start < len) && (self->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (self->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < self->length)) 
        ? new(String, strndup(self->value+start, len-start))
        : self;    
}

method String* Substring(const String* self, const int index, const int length) {
    char* result = DSmalloc(length+1);
    strncpy(result, self->value+index, length);
    result[length] = '\0';
    return new(String, result);
}

method String* Substring(const String* self, const int index) {
    int length = self->length - index;
    char* result = DSmalloc(length+1);
    strncpy(result, self->value+index, length);
    result[length] = '\0';
    return new(String, result);
}

method int Length(const String* const self) 
{
    return self->length;
}

method bool IsEmpty(const String* const self)
{
    return self->length == 0;
}

method char CharAt(const String* const self, const int index)
{
    // printf("string %d,%d %s\n", index, self->length, self->value);
    if (index < 0 || index >= self->length)
        throw DSIndexOutOfBoundsException(index, Source);
    return self->value[index];
}
 

method char* ToString(const String* const self)
{
    return self->value;
}

method __attribute__((__format__ (__printf__, 1, 2)))
String* Format(const char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return new(String, "");
    char* str = DScalloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return new(String, str);
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
    return new(String, result);
}
