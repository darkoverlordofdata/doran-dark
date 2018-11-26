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
#include <string.h>
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
    return strcmpi(this->value, other->value);
}

String String_Concat(String this, String other) {

}

bool String_Contains(char* s) {

}

String String_CopyOf(String this, String other) {

}

bool String_EndsWith(String this, String suffix) {

}

bool String_StartsWith(String this, String prefix) {

}
// sprintf...
String String_Format(String this, String format, ...) {

}

char* String_GetBytes(String this) {

}

int String_IndexOf(String this, int fromIndex) {

}

int String_LastIndexOf(String this, int fromIndex) {

}

String String_ToUpperCase(String this) {

}

String String_ToLowerCase(String this) {

}

String String_Trim(String this) {

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
