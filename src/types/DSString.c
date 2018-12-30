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
/* 
 * Throws IndexOutOfBoundsException:
 */
static DSException(IndexOutOfBounds);

/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
DSString* String_init(DSString* const this, char* value)
{
    DSComparable_init(this);
    this->isa = ISA(DSString);
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

void String_GetChars(DSString* this, char* dst, int dstBegin) {
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
int String_CompareTo(DSString* this, DSString* other) {
    return String_Compare(this->value, other->value);
}

int String_CompareToIgnoreCase(DSString* this, DSString* str) {
    return strcmpi(this->value, str->value);
}

DSString* String_Concatc(DSString* this, char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DSCalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    DSString* result = DSStringClass.Create(str);
    return result;

}

DSString* String_Concat(DSString* this, DSString* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DSCalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    DSString* result = DSStringClass.Create(str);
    return result;
}

bool String_Contains(DSString* this, DSString* s) {
    return this->isa->IndexOf(this, s, 0) > -1;
}

DSString* String_CopyOf(DSString* this) {
    return DSStringClass.Create(this->value);
}

bool String_EndsWith(DSString* this, DSString* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

bool String_StartsWith(DSString* this, DSString* prefix, int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

char* String_GetBytes(DSString* this) {
    return strdup(this->value);
}

int String_IndexOf(DSString* this, DSString* str, int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

int String_LastIndexOf(DSString* this, DSString* str, int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

DSString* String_ToUpperCase(DSString* this) {
    return DSStringClass.Create(strupr(this->value));
}

DSString* String_ToLowerCase(DSString* this) {
    return DSStringClass.Create(strlwr(this->value));
}

DSString* String_Trim(DSString* this) {
    int len = this->length;
    int start = 0;
    while ((start < len) && (this->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (this->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < this->length)) 
        ? DSStringClass.Create(strndup(this->value+start, len-start))
        : this;    
}

int overload Length(DSString* const this) 
{
    return this->length;
}

bool String_IsEmpty(DSString* const this)
{
    return this->length == 0;
}

char String_CharAt(DSString* const this, int index)
{
    printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        return DSIndexOutOfBoundsException("at index %d", index);
    return this->value[index];
}
 

char* String_ToString(DSString* const this)
{
    return this->value;
}

void String_Dispose(DSString* const this)
{
}

/*
 * Shortcut for a new string object
 */
DSString* $(const char* const str) {
    return String_init(class_alloc(DSString), str); 
}

/**
 * String Class Metadata
 */
DSDefine(DSString, DSObject, cls, {
    cls->Create         = $;
    cls->ToString       = String_ToString;
    cls->Dispose        = String_Dispose;
    cls->CompareTo      = String_CompareTo;
    cls->Length         = Length;
    cls->IsEmpty        = String_IsEmpty;
    cls->CharAt         = String_CharAt;
    cls->CompareToIgnoreCase = String_CompareToIgnoreCase;
    cls->Concat         = String_Concat;
    cls->Concatc        = String_Concatc;
    cls->Contains       = String_Contains;
    cls->CopyOf         = String_CopyOf;
    cls->EndsWith       = String_EndsWith;
    cls->StartsWith     = String_StartsWith;
    cls->GetBytes       = String_GetBytes;
    cls->IndexOf        = String_IndexOf;
    cls->LastIndexOf    = String_LastIndexOf;
    cls->ToLowerCase    = String_ToLowerCase;
    cls->ToUpperCase    = String_ToUpperCase;
    cls->Trim           = String_Trim;
});


__attribute__((__format__ (__printf__, 1, 2)))
DSString* String_Format(char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return DSStringClass.Create("");
    char* str = DSCalloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return DSStringClass.Create(str);
}
