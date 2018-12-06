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

typedef struct StringClass_t StringClass_t;
extern StringClass_t StringClass;

/**
 * Object class
 */
class (String) 
{
    StringClass_t* isa;
    const char*     value;
    int             length;
};

/**
 * Object metaclass
 */
typedef struct StringClass_t
{
    union {
        ComparableClass_t base;
        struct 
        {
            Class isa;
            Class superclass;
            char* name;
            char*   (*ToString) (Object const);
            bool    (*Equals) (Object const, Object const);
            int     (*GetHashCode) (Object const);
            void    (*Dispose) (Object const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
            int     (*CompareTo) (Comparable const, Comparable other);
            int     (*Length) (String const);
            bool    (*IsEmpty) (String const);
            char    (*CharAt) (String const, int index);
            int     (*CompareToIgnoreCase) (String const, String other);
            String  (*Concat) (String const, String str);
            String  (*Concatc) (String const, char* str);
            bool    (*Contains) (String const, String str);
            String  (*CopyOf) (String const);
            bool    (*EndsWith) (String const, String suffix);
            bool    (*StartsWith) (String const, String prefix, int offset);
            char*   (*GetBytes) (String const);
            int     (*IndexOf) (String const, String str, int fromIndex);
            int     (*LastIndexOf) (String const, String str, int fromIndex);
            String  (*ToUpperCase) (String const);
            String  (*ToLowerCase) (String const);
            String  (*Trim) (String const);
        };
    };
};


int String_Compare(char* x, char* y);
int String_CompareTo(String this, String other);
int String_CompareToIgnoreCase(String this, String other);
String String_Concat(String this, String str);
String String_Concatc(String this, char* str);
bool String_Contains(String this, String str);
String String_CopyOf(String this);
bool String_EndsWith(String this, String suffix);
bool String_StartsWith(String this, String prefix, int offset);
char* String_GetBytes(String this);
int String_IndexOf(String this, String str, int fromIndex);
int String_LastIndexOf(String this, String str, int fromIndex);
String String_ToUpperCase(String this);
String String_ToLowerCase(String this);
String String_Trim(String this);
int overload Length(String const);
bool String_IsEmpty(String const this);
char String_CharAt(String const this, int index);
char* String_ToString(String const this);
String String_New(char* value);

__attribute__((__format__ (__printf__, 1, 2)))
String String_Format(char* format, ...);

#endif _STRING_H_
