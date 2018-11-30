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
 * String implementation
 */

static Exception(IndexOutOfBounds);


void String_GetChars(String this, char* dst, int dstBegin) {
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
int String_CompareTo(String this, String other) {
    return String_Compare(this->value, other->value);
}

int String_CompareToIgnoreCase(String this, String str) {
    return strcmpi(this->value, str->value);
}

String String_Concatc(String this, char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = calloc(len+length+1, sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    String result = String_New(str);
    free(str);
    return result;

}

String String_Concat(String this, String other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = calloc(len+other->length+1, sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    String result = String_New(str);
    free(str);
    return result;
}

bool String_Contains(String this, String s) {
    return this->IndexOf(this, s, 0) > -1;
}

String String_CopyOf(String this) {
    return String_New(this->value);
}

bool String_EndsWith(String this, String suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

bool String_StartsWith(String this, String prefix, int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

char* String_GetBytes(String this) {
    return strdup(this->value);
}

int String_IndexOf(String this, String str, int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

int String_LastIndexOf(String this, String str, int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

String String_ToUpperCase(String this) {
    return String_New(strupr(this->value));
}

String String_ToLowerCase(String this) {
    return String_New(strlwr(this->value));
}

String String_Trim(String this) {
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

int String_Length(String const this) 
{
    return this->length;
}

bool String_IsEmpty(String const this)
{
    return this->length == 0;
}

char String_CharAt(String const this, int index)
{
    if (index < 0 || index >= this->length)
        return IndexOutOfBoundsException("at index %d", index);
    return this->value[index];
}
 

char* String_ToString(String const this)
{
    return this->value;
}

/**
 * Initialize a new String
 */
String String_Ctor(String const this, char* value)
{
    Comparable_Ctor(this);

    this->ToString      = String_ToString;
    this->CompareTo     = String_CompareTo;
    this->Length        = String_Length;
    this->IsEmpty       = String_IsEmpty;
    this->CharAt        = String_CharAt;
    this->CompareToIgnoreCase = String_CompareToIgnoreCase;
    this->Concat        = String_Concat;
    this->Concatc       = String_Concatc;
    this->Contains      = String_Contains;
    this->CopyOf        = String_CopyOf;
    this->EndsWith      = String_EndsWith;
    this->StartsWith    = String_StartsWith;
    this->GetBytes      = String_GetBytes;
    this->IndexOf       = String_IndexOf;
    this->LastIndexOf   = String_LastIndexOf;
    this->ToLowerCase   = String_ToLowerCase;
    this->ToUpperCase   = String_ToUpperCase;
    this->Trim          = String_Trim;

    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}


/**
 * new String
 * 
 * create a new long
 * 
 * @param value of long
 * 
 */
String String_New(char* value)
{
    return String_Ctor(new(String), value);
}

__attribute__((__format__ (__printf__, 1, 2)))
String String_Format(char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return String_New("");
    char* str = calloc(len+1, sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return String_New(str);
}
