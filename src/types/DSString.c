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
$implementation(DSString)

$method(ToString,           DSString_ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");
$method(CompareTo,          DSString_CompareTo, "i@:@");
$method(Dispose,            DSString_Dispose, "v@:v");
$method(Length,             Length, "i@:v");
$method(IsEmpty,            DSString_IsEmpty, "B@:v");    
$method(CharAt,             DSString_CharAt, "c@:i");
$method(CompareToIgnoreCase, DSString_CompareToIgnoreCase, "@:");    
$method(Concat,             DSString_Concat, "v@:$");
$method(Concatc,            DSString_Concatc, "v@:c");
$method(Contains,           DSString_Contains, "B@:$");
$method(CopyOf,             DSString_CopyOf, "$@:v");
$method(EndsWith,           DSString_EndsWith, "B@:$");
$method(StartsWith,         DSString_StartsWith, "B@:$");
$method(GetBytes,           DSString_GetBytes, "b@:*");
$method(IndexOf,            DSString_IndexOf, "i@:$");
$method(LastIndexOf,        DSString_LastIndexOf, "i@:$");
$method(ToLowerCase,        DSString_ToLowerCase, "$@:v");
$method(ToUpperCase,        DSString_ToUpperCase, "$@:v");
$method(Trim,               DSString_Trim, "$@:v");

$ivar(value, sizeof(char*), "*");
$ivar(length, sizeof(int), "i");

$end;

/**
 * Constructor
 * create a new long
 * 
 * @param value of long
 * 
 */
DSString* $(const char* const str) {
    return DSString_init(DSString_alloc(), str); 
}

DSString* DSString_init(DSString* const this, char* value)
{
    DSComparable_init(this);
    this->isa = getDSStringIsa();
    this->value = strdup(value);
    this->length = strlen(value);
    return this;
}

DSString* DSString_alloc() {
    return DSMalloc(getDSStringSize());
}

void DSString_GetChars(DSString* this, char* dst, int dstBegin) {
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
int DSString_Compare(char* x, char* y) {
    return strcmp(x, y);
}

/**
 * Compares two String objects.
 *
 * @param   other  String to be compared
 * @return same as String_Compare
 */
int DSString_CompareTo(DSString* this, DSString* other) {
    return DSString_Compare(this->value, other->value);
}

int DSString_CompareToIgnoreCase(DSString* this, DSString* str) {
    return strcmpi(this->value, str->value);
}

DSString* DSString_Concatc(DSString* this, char* other) {
    int length = strlen(other);
    if (length == 0) return this;
    int len = this->length;
    char* str = DSCalloc((len+length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other, length);
    DSString* result = $DSString.Create(str);
    return result;

}

DSString* DSString_Concat(DSString* this, DSString* other) {
    if (other->length == 0)
        return this;

    int len = this->length;
    char* str = DSCalloc((len+other->length+1), sizeof(char));
    strncpy(str, this->value, len);
    strncpy(str+len, other->value, other->length);
    DSString* result = $DSString.Create(str);
    return result;
}

bool DSString_Contains(DSString* this, DSString* s) {
    return _vptr(this)->IndexOf(this, s, 0) > -1;
}

DSString* DSString_CopyOf(DSString* this) {
    return $DSString.Create(this->value);
}

bool DSString_EndsWith(DSString* this, DSString* suffix) {
    char* offset = this->value + this->length - suffix->length;
    return !strcmp(offset, suffix);
}

bool DSString_StartsWith(DSString* this, DSString* prefix, int offset) {
    char* c = strstr(this->value+offset, prefix->value);
    return c == (this->value+offset) ? true : false;
}

char* DSString_GetBytes(DSString* this) {
    return strdup(this->value);
}

int DSString_IndexOf(DSString* this, DSString* str, int offset) {
    char* c = strstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

int DSString_LastIndexOf(DSString* this, DSString* str, int offset) {
    char* c = strrstr(this->value+offset, str->value);
    return c == nullptr ? 0 : c - this->value;
}

DSString* DSString_ToUpperCase(DSString* this) {
    return $DSString.Create(strupr(this->value));
}

DSString* DSString_ToLowerCase(DSString* this) {
    return $DSString.Create(strlwr(this->value));
}

DSString* DSString_Trim(DSString* this) {
    int len = this->length;
    int start = 0;
    while ((start < len) && (this->value[start] <= ' ')) {
        start++;
    }
    while ((start < len) && (this->value[len - 1] <= ' ')) {
        len--;
    }
    return ((start > 0) || (len < this->length)) 
        ? $DSString.Create(strndup(this->value+start, len-start))
        : this;    
}

int overload Length(DSString* const this) 
{
    return this->length;
}

bool DSString_IsEmpty(DSString* const this)
{
    return this->length == 0;
}

char DSString_CharAt(DSString* const this, int index)
{
    printf("string %d,%d %s\n", index, this->length, this->value);
    if (index < 0 || index >= this->length)
        return DSIndexOutOfBoundsException("at index %d", index);
    return this->value[index];
}
 

char* DSString_ToString(const DSString* const this)
{
    return this->value;
}

void DSString_Dispose(DSString* const this)
{
}



__attribute__((__format__ (__printf__, 1, 2)))
DSString* DSString_Format(char* format, ...) {
    va_list args1;
    va_list args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  

    int len = vsnprintf(nullptr, 0, format, args1);
    va_end(args1);
    if (len == 0) return $DSString.Create("");
    char* str = DSCalloc((len+1), sizeof(char));
    len = vsnprintf(str, len+1, format, args2);
    va_end(args2);
    return $DSString.Create(str);
}
