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
#ifndef _FILE_H_
#define _FILE_H_
#include <stdio.h>
#include "../Comparable.h"
#include "../types/String.h"
#include "FileSystem.h"

cyclic_reference(FileSystem);

typedef enum { PS_UNCHECKED, PS_INVALID, PS_CHECKED } PathStatus;

class (File)
{
    union {
        Comparable_t _;
        struct 
        {
            Class isa;
            retained
            char*       (*ToString)(Object const);
            bool        (*Equals)(Object const, Object const);
            int         (*GetHashCode)(Object const);
            void        (*Dispose) (Object const);
            int         (*CompareTo) (Comparable const, Comparable other);
        };
    };
    FileSystem          fs;
    String              path;   
    PathStatus          status;
    int                 prefixLength;
    bool                (*IsInvalid) (File const);
    int                 (*GetPrefixLength) (File const);
    String              (*GetName) (File const);
    String              (*GetParent) (File const);
    File                (*GetParentFile) (File const);
    String              (*GetPath) (File const);
    bool                (*IsAbsolute) (File const);
    String              (*GetAbsolutePath) (File const);
    File                (*GetAbsoluteFile) (File const);
    String              (*GetCanonicalPath) (File const);
    File                (*GetCanonicalFile) (File const);
    bool                (*CanRead) (File const);
    bool                (*CanWrite) (File const);
    bool                (*Exists) (File const);
    bool                (*IsDirectory) (File const);
    bool                (*IsFile) (File const);
    long                (*GetLength) (File const);
    String*             (*List) (File const);
};


#endif _FILE_H_ 
