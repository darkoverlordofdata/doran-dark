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
#include <dark/types/DSString.h>
#include <dark/types/implementation/DSString.h>
/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
DSString* NewDSString(const char* const str) {
    return DSString_init(alloc(DSString), str); 
}

DSString* DSString_init(DSString* const this, const char* value)
{
    DSComparable_init(this);
    this->isa = getDSStringIsa();
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

void overload GetChars(const DSString* this, char* dst, int dstBegin) {
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
overload int Compare(const char* x, const char* y) {
    return strcmp(x, y);
}

/**
 * Compares two String objects.
 *
 * @param   other  String to be compared
 * @return same as String_Compare
 */
overload int CompareTo(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value);
}

overload bool Equals(const DSString* const this, const DSString* const other) {
    return Compare(this->value, other->value) == 0;
}

overload int CompareToIgnoreCase(const DSString* this, const DSString* str) {
    return strcmpi(this->value, str->value);
}

overload DSString* Concatc(const DSString* this, const char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DScalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    DSString* result = NewDSString(str);
    return result;

}

overload DSString* Concat(const DSString* this, const DSString* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DScalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    DSString* result = NewDSString(str);
    return result;
}

overload bool Contains(const DSString* this, const DSString* s) {
    return _vptr(this)->IndexOf(this, s, 0) > -1;
}

overload DSString* CopyOf(const DSString* this) {
    return NewDSString(this->value);
}

overload bool EndsWith(const DSString* this, const DSString* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

overload bool StartsWith(const DSString* this, const DSString* prefix, const int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

overload char* GetBytes(const DSString* this) {
    return strdup(this->value);
}

overload int IndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

overload int LastIndexOf(const DSString* this, const DSString* str, const int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

overload DSString* ToUpperCase(const DSString* this) {
    return NewDSString(strupr(this->value));
}

overload DSString* ToLowerCase(const DSString* this) {
    return NewDSString(strlwr(this->value));
}

overload DSString* Trim(const DSString* this) {
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

overload DSString* Substring(const DSString* this, const int index, const int length) {
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

overload DSString* Substring(const DSString* this, const int index) {
    int length = this->length - index;
    char* result = DSmalloc(length+1);
    strncpy(result, this->value+index, length);
    result[length] = '\0';
    return NewDSString(result);
}

overload int Length(const DSString* const this) 
{
    return this->length;
}

overload bool IsEmpty(const DSString* const this)
{
    return this->length == 0;
}

overload char CharAt(const DSString* const this, const int index)
{
    // printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        throw DSIndexOutOfBoundsException(index, Source);
    return this->value[index];
}
 

overload char* ToString(const DSString* const this)
{
    return this->value;
}

__attribute__((__format__ (__printf__, 1, 2)))
overload DSString* Format(const char* format, ...) {
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
DSString* StringJoin(int count, ...)
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

