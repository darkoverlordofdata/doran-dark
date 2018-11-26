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
#include "../Comparable.h"

#define STRING_TYPE       (TYPE_STRING)

class (String)
{
    union {
        Comparable_t _;
        struct 
        {
            int         RefCount;
            char*       (*ToString) (DObject const);
            bool        (*Equals) (DObject const, DObject const);
            int         (*GetHashCode) (DObject const);
            void        (*Dispose) (DObject const);
            int         (*CompareTo) (String const, String other);
        };
    };
    const char*         value;
    int                 length;
    int                 (*Length) (String const);
    bool                (*IsEmpty) (String const);
    char                (*CharAt) (String const, int index);

};

int String_Compare(char* x, char* y);
int String_CompareTo(String this, String other);
int String_CompareToIgnoreCase(String this, String other);
String String_Concat(String this, String str);
bool String_Contains(char* s);
String String_CopyOf(String this, String other);
bool String_EndsWith(String this, String suffix);
bool String_StartsWith(String this, String prefix);
String String_Format(String this, String format, ...);
char* String_GetBytes(String this);
int String_IndexOf(String this, int fromIndex);
int String_LastIndexOf(String this, int fromIndex);
String String_ToUpperCase(String this);
String String_ToLowerCase(String this);
String String_Trim(String this);
int String_Length(String const this);
bool String_IsEmpty(String const this);
char String_CharAt(String const this, int index);
char* String_ToString(String const this);
String String_New(char* value);

#endif _STRING_H_
