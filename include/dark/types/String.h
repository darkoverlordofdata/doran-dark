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
#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#include "../Comparable.h"

#define STRING_TYPE       (TYPE_STRING)

/**
 * Object class
 */
class (String) 
{
    struct StringClass * isa;
    const char* value;
    int length;
};

/**
 * Object metaclass
 */
struct StringClass
{
    union {
        struct ComparableClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TString const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            int     (*CompareTo) (TComparable const, TComparable other);
            int     (*Length) (TString const);
            bool    (*IsEmpty) (TString const);
            char    (*CharAt) (TString const, int index);
            int     (*CompareToIgnoreCase) (TString const, TString other);
            TString (*Concat) (TString const, TString str);
            TString (*Concatc) (TString const, char* str);
            bool    (*Contains) (TString const, TString str);
            TString (*CopyOf) (TString const);
            bool    (*EndsWith) (TString const, TString suffix);
            bool    (*StartsWith) (TString const, TString prefix, int offset);
            char*   (*GetBytes) (TString const);
            int     (*IndexOf) (TString const, TString str, int fromIndex);
            int     (*LastIndexOf) (TString const, TString str, int fromIndex);
            TString (*ToUpperCase) (TString const);
            TString (*ToLowerCase) (TString const);
            TString (*Trim) (TString const);
        };
    };
};


int String_Compare(char* x, char* y);
int String_CompareTo(TString this, TString other);
int String_CompareToIgnoreCase(TString this, TString other);
TString String_Concat(TString this, TString str);
TString String_Concatc(TString this, char* str);
bool String_Contains(TString this, TString str);
TString String_CopyOf(TString this);
bool String_EndsWith(TString this, TString suffix);
bool String_StartsWith(TString this, TString prefix, int offset);
char* String_GetBytes(TString this);
int String_IndexOf(TString this, TString str, int fromIndex);
int String_LastIndexOf(TString this, TString str, int fromIndex);
TString String_ToUpperCase(TString this);
TString String_ToLowerCase(TString this);
TString String_Trim(TString this);
int overload Length(TString const);
bool String_IsEmpty(TString const this);
char String_CharAt(TString const this, int index);
char* String_ToString(TString const this);
TString String_New(char* value);
TString String_Ctor(TString const this, char* value);

__attribute__((__format__ (__printf__, 1, 2)))
TString String_Format(char* format, ...);

#endif _STRING_H_
