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
ivar (DSString) {
    Class isa;
    const char* value;
    int length;
};

DSString* NewDSString(const char* const value);
DSString* DSString_init(DSString* const this, const char* value);
DSString* DSString_alloc();

char*       overload ToString(const DSString* const);
bool        overload Equals(const DSString* const, const DSString* const);
int         overload CompareTo(const DSString* const this, const DSString* const other);
int         overload Compare(const char* x, const char* y);
int         overload CompareToIgnoreCase(const DSString* this, const DSString* other);
DSString*   overload Concat(const DSString* this, const DSString* str);
DSString*   overload Concatc(const DSString* this, const char* str);
bool        overload Contains(const DSString* this, const DSString* str);
DSString*   overload CopyOf(const DSString* this);
bool        overload EndsWith(const DSString* this, const DSString* suffix);
bool        overload StartsWith(const DSString* this, const DSString* prefix, const int offset);
char*       overload GetBytes(const DSString* this);
int         overload IndexOf(const DSString* this, const DSString* str, const int fromIndex);
int         overload LastIndexOf(const DSString* this, const DSString* str, const int fromIndex);
DSString*   overload ToUpperCase(const DSString* this);
DSString*   overload ToLowerCase(const DSString* this);
DSString*   overload Trim(const DSString* this);
int         overload Length(const DSString* const);
bool        overload IsEmpty(const DSString* const this);
char        overload CharAt(const DSString* const this, const int index);
DSString*   overload Substring(const DSString* const this, const int index);
DSString*   overload Substring(const DSString* const this, const int index, const int length);
__attribute__((__format__ (__printf__, 1, 2)))
DSString*   overload Format(const char* format, ...);

typedef char*       (*DSStringToString) (const DSString* const);
typedef bool        (*DSStringEquals)   (const DSString* const, const DSString* const);
typedef int         (*DSStringCompareTo)(const DSString* const this, const DSString* const other);
typedef int         (*DSStringCompare)  (const char* x, const char* y);
typedef int         (*DSStringCompareToIgnoreCase)(const DSString* this, const DSString* other);
typedef DSString*   (*DSStringConcat)   (const DSString* this, const DSString* str);
typedef DSString*   (*DSStringConcatc)  (const DSString* this, const char* str);
typedef bool        (*DSStringContains) (const DSString* this, const DSString* str);
typedef DSString*   (*DSStringCopyOf)   (const DSString* this);
typedef bool        (*DSStringEndsWith) (const DSString* this, const DSString* suffix);
typedef bool        (*DSStringStartsWith)(const DSString* this, const DSString* prefix, const int offset);
typedef char*       (*DSStringGetBytes) (const DSString* this);
typedef int         (*DSStringIndexOf)  (const DSString* this, const DSString* str, const int fromIndex);
typedef int         (*DSStringLastIndexOf)(const DSString* this, const DSString* str, const int fromIndex);
typedef DSString*   (*DSStringToUpperCase)(const DSString* this);
typedef DSString*   (*DSStringToLowerCase)(const DSString* this);
typedef DSString*   (*DSStringTrim)     (const DSString* this);
typedef int         (*DSStringLength)   (const DSString* const);
typedef bool        (*DSStringIsEmpty)  (const DSString* const this);
typedef char        (*DSStringCharAt)   (const DSString* const this, const int index);
typedef DSString*   (*DSStringSubstring) (const DSString* const this, const int index, const int length);
__attribute__((__format__ (__printf__, 1, 2)))
typedef DSString*   (*DSStringFormat)   (const char* format, ...);

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
    DSString* (*Create) (char* value);
    DSString* (*Join) (int count, ...);
};



#endif _DSSTRING_H_
