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
Ivar (DSString) {
    Class isa;
    const char* value;
    int length;
};

/**
 * Object metaclass
 */
VTable (DSString) {
    char*   (*ToString) (DSString* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const objA, DSObject* const objB);
    bool    (*InstanceEquals) (DSObject* const objA, DSObject* const objB);
    int     (*CompareTo) (DSComparable* const, DSComparable* const);
    int     (*Length) (DSString* const);
    bool    (*IsEmpty) (DSString* const);
    char    (*CharAt) (DSString* const, int index);
    int     (*CompareToIgnoreCase) (DSString* const, DSString* const);
    DSString* (*Concat) (DSString* const, DSString* str);
    DSString* (*Concatc) (DSString* const, char* str);
    bool    (*Contains) (DSString* const, DSString* str);
    DSString* (*CopyOf) (DSString* const);
    bool    (*EndsWith) (DSString* const, DSString* suffix);
    bool    (*StartsWith) (DSString* const, DSString* prefix, int offset);
    char*   (*GetBytes) (DSString* const);
    int     (*IndexOf) (DSString* const, DSString* str, int fromIndex);
    int     (*LastIndexOf) (DSString* const, DSString* str, int fromIndex);
    DSString* (*ToUpperCase) (DSString* const);
    DSString* (*ToLowerCase) (DSString* const);
    DSString* (*Trim) (DSString* const);

} $$;

Singleton ($DSString) {
    DSString* (*Create) (char* value);
};


DSString* $(const char* const value);
void DSString_Dispose(DSString* const this);
int DSString_Compare(char* x, char* y);
int DSString_CompareTo(DSString* this, DSString* other);
int DSString_CompareToIgnoreCase(DSString* this, DSString* other);
DSString* DSString_Concat(DSString* this, DSString* str);
DSString* DSString_Concatc(DSString* this, char* str);
bool DSString_Contains(DSString* this, DSString* str);
DSString* DSString_CopyOf(DSString* this);
bool DSString_EndsWith(DSString* this, DSString* suffix);
bool DSString_StartsWith(DSString* this, DSString* prefix, int offset);
char* DSString_GetBytes(DSString* this);
int DSString_IndexOf(DSString* this, DSString* str, int fromIndex);
int DSString_LastIndexOf(DSString* this, DSString* str, int fromIndex);
DSString* DSString_ToUpperCase(DSString* this);
DSString* DSString_ToLowerCase(DSString* this);
DSString* DSString_Trim(DSString* this);
int overload Length(DSString* const);
bool DSString_IsEmpty(DSString* const this);
char DSString_CharAt(DSString* const this, int index);
char* DSString_ToString(const DSString* const this);
DSString* DSString_init(DSString* const this, char* value);
DSString* DSString_alloc();

__attribute__((__format__ (__printf__, 1, 2)))
DSString* DSString_Format(char* format, ...);

#endif _DSSTRING_H_
