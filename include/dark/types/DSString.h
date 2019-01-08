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

#define IsDSString(x) (x->isa == &$DSString)
#define AsDSString(x) (IsDSString(x) ? (DSString *)x : nullptr)

/**
 * Object class
 */
ivar (DSString) {
    Class isa;
    const char* value;
    int length;
};

/**
 * Object metaclass
 */
vtable (DSString) {
    char*   (*ToString) (const DSString* const);
    bool    (*Equals) (const DSObject* const, const DSObject* const);
    int     (*GetHashCode) (const DSObject* const);
    void    (*Dispose) (DSObject* const);
    int     (*CompareTo) (const DSComparable* const, const DSComparable* const);
    int     (*Length) (const DSString* const);
    bool    (*IsEmpty) (const DSString* const);
    char    (*CharAt) (const DSString* const, int index);
    int     (*CompareToIgnoreCase) (const DSString* const, const DSString* const);
    DSString* (*Concat) (const DSString* const, const DSString* str);
    DSString* (*Concatc) (const DSString* const, const char* str);
    bool    (*Contains) (const DSString* const, const DSString* str);
    DSString* (*CopyOf) (const DSString* const);
    bool    (*EndsWith) (const DSString* const, const DSString* suffix);
    bool    (*StartsWith) (const DSString* const, const DSString* prefix, const int offset);
    char*   (*GetBytes) (const DSString* const);
    int     (*IndexOf) (const DSString* const, const DSString* str, const int fromIndex);
    int     (*LastIndexOf) (const DSString* const, const DSString* str, const int fromIndex);
    DSString* (*ToUpperCase) (const DSString* const);
    DSString* (*ToLowerCase) (const DSString* const);
    DSString* (*Trim) (const DSString* const);

} $$;

class (DSString) {
    DSString* (*Create) (char* value);
};


DSString* $(const char* const value);
DSString* DSString_init(DSString* const this, const char* value);
DSString* DSString_alloc();
void DSString_Dispose(DSString* const this);
int DSString_Compare(const char* x, const char* y);
int DSString_CompareTo(const DSString* const this, const DSString* const other);
int DSString_CompareToIgnoreCase(const DSString* this, const DSString* other);
DSString* DSString_Concat(const DSString* this, const DSString* str);
DSString* DSString_Concatc(const DSString* this, const char* str);
bool DSString_Contains(const DSString* this, const DSString* str);
DSString* DSString_CopyOf(const DSString* this);
bool DSString_EndsWith(const DSString* this, const DSString* suffix);
bool DSString_StartsWith(const DSString* this, const DSString* prefix, const int offset);
char* DSString_GetBytes(const DSString* this);
int DSString_IndexOf(const DSString* this, const DSString* str, const int fromIndex);
int DSString_LastIndexOf(const DSString* this, const DSString* str, const int fromIndex);
DSString* DSString_ToUpperCase(const DSString* this);
DSString* DSString_ToLowerCase(const DSString* this);
DSString* DSString_Trim(const DSString* this);
int overload Length(const DSString* const);
bool DSString_IsEmpty(const DSString* const this);
char DSString_CharAt(const DSString* const this, const int index);
char* DSString_ToString(const DSString* const);

__attribute__((__format__ (__printf__, 1, 2)))
DSString* DSString_Format(const char* format, ...);

#endif _DSSTRING_H_
