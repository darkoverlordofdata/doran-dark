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
#include <dark/types/String.h>
/* 
 * Throws IndexOutOfBoundsException:
 */
static Exception(IndexOutOfBounds);

/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
TString String_New(char* value) {
    return String_Ctor(new(String), value);
}

TString String_Ctor(TString const this, char* value)
{
    Comparable_Ctor(this);
    this->isa = isa(String);
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

void String_GetChars(TString this, char* dst, int dstBegin) {
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
int String_Compare(char* x, char* y) {
    return strcmp(x, y);
}

/**
 * Compares two String objects.
 *
 * @param   other  String to be compared
 * @return same as String_Compare
 */
int String_CompareTo(TString this, TString other) {
    return String_Compare(this->value, other->value);
}

int String_CompareToIgnoreCase(TString this, TString str) {
    return strcmpi(this->value, str->value);
}

TString String_Concatc(TString this, char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = dark_calloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    TString result = String_New(str);
    return result;

}

TString String_Concat(TString this, TString other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = dark_calloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    TString result = String_New(str);
    return result;
}

bool String_Contains(TString this, TString s) {
    return this->isa->IndexOf(this, s, 0) > -1;
}

TString String_CopyOf(TString this) {
    return String_New(this->value);
}

bool String_EndsWith(TString this, TString suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

bool String_StartsWith(TString this, TString prefix, int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

char* String_GetBytes(TString this) {
    return strdup(this->value);
}

int String_IndexOf(TString this, TString str, int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

int String_LastIndexOf(TString this, TString str, int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

TString String_ToUpperCase(TString this) {
    return String_New(strupr(this->value));
}

TString String_ToLowerCase(TString this) {
    return String_New(strlwr(this->value));
}

TString String_Trim(TString this) {
    int len = this->length;
    int start = 0;
    while ((start < len) && (this->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (this->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < this->length)) 
        ? String_New(strndup(this->value+start, len-start))
        : this;    
}

int overload Length(TString const this) 
{
    return this->length;
}

bool String_IsEmpty(TString const this)
{
    return this->length == 0;
}

char String_CharAt(TString const this, int index)
{
    printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        return IndexOutOfBoundsException("at index %d", index);
    return this->value[index];
}
 

char* String_ToString(TString const this)
{
    return this->value;
}

void String_Dispose(TString const this)
{
}

/**
 * String Class Metadata
 */
register (String)
{
    if (String.isa == nullptr) {
        String = (struct StringClass) {
            .isa            = &String,
            .superclass     = &Comparable,
            .name           = "String",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .ToString       = String_ToString,
            .Dispose        = String_Dispose,
            .CompareTo      = String_CompareTo,
            .Length         = Length,
            .IsEmpty        = String_IsEmpty,
            .CharAt         = String_CharAt,
            .CompareToIgnoreCase = String_CompareToIgnoreCase,
            .Concat         = String_Concat,
            .Concatc        = String_Concatc,
            .Contains       = String_Contains,
            .CopyOf         = String_CopyOf,
            .EndsWith       = String_EndsWith,
            .StartsWith     = String_StartsWith,
            .GetBytes       = String_GetBytes,
            .IndexOf        = String_IndexOf,
            .LastIndexOf    = String_LastIndexOf,
            .ToLowerCase    = String_ToLowerCase,
            .ToUpperCase    = String_ToUpperCase,
            .Trim           = String_Trim,
            .Create         = String_New,
        };
        AddMetadata(String);
    }
    return &String;
}

__attribute__((__format__ (__printf__, 1, 2)))
TString String_Format(char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return String_New("");
    char* str = dark_calloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return String_New(str);
}
