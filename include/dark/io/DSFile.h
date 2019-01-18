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
#ifndef _FILE_H_
#define _FILE_H_
#include "../types.h"
#include "DSFileSystem.h"

typedef struct DSFileSystem DSFileSystem;
typedef enum { PS_UNCHECKED, PS_INVALID, PS_CHECKED } PathStatus;


ivar (DSFile) {
    Class isa;
    DSString*           path;   
    PathStatus          status;
    int                 prefixLength;

};


DSFile* overload NewDSFile(const char*);
DSFile* overload NewDSFile(const char*, const char*);
DSFile* overload DSFile_init(DSFile* this, const char*);
DSFile* overload DSFile_init(DSFile* this, const char*, const char*);
DSFile* overload DSFile_init(DSFile* this, DSFile*, const char*);

method (DSFile, ToString,           char*,      (const DSFile* const) );
method (DSFile, CompareTo,          int,        (DSFile* const, DSFile* other) );
method (DSFile, IsInvalid,          bool,       (DSFile* const) );
method (DSFile, GetPrefixLength,    int,        (DSFile* const) );
method (DSFile, GetName,            DSString*,  (DSFile* const) );
method (DSFile, GetParent,          DSString*,  (DSFile* const) );
method (DSFile, GetParentFile,      DSFile*,    (DSFile* const) );
method (DSFile, GetPath,            DSString*,  (DSFile* const) );
method (DSFile, IsAbsolute,         bool,       (DSFile* const) );
method (DSFile, GetAbsolutePath,    DSString*,  (DSFile* const) );
method (DSFile, GetAbsoluteFile,    DSFile*,    (DSFile* const) );
method (DSFile, GetCanonicalPath,   DSString*,  (DSFile* const) );
method (DSFile, GetCanonicalFile,   DSFile*,    (DSFile* const) );
method (DSFile, CanRead,            bool,       (DSFile* const) );
method (DSFile, CanWrite,           bool,       (DSFile* const) );
method (DSFile, Exists,             bool,       (DSFile* const) );
method (DSFile, IsDirectory,        bool,       (DSFile* const) );
method (DSFile, IsFile,             bool,       (DSFile* const) );
method (DSFile, GetLength,          long,       (DSFile* const) );
method (DSFile, List,               DSString*,  (DSFile* const) );

vtable (DSFile) {
    const DSFileToString              ToString;
    const DSObjectEquals              Equals;
    const DSObjectGetHashCode         GetHashCode;
    const DSObjectDispose             Dispose;
    const DSFileCompareTo             CompareTo;
    const DSFileIsInvalid             IsInvalid;
    const DSFileGetPrefixLength       GetPrefixLength;
    const DSFileGetName               GetName;
    const DSFileGetParent             GetParent;
    const DSFileGetParentFile         GetParentFile;
    const DSFileGetPath               GetPath;
    const DSFileIsAbsolute            IsAbsolute;
    const DSFileGetAbsolutePath       GetAbsolutePath;
    const DSFileGetAbsoluteFile       GetAbsoluteFile;
    const DSFileGetCanonicalPath      GetCanonicalPath;
    const DSFileGetCanonicalFile      GetCanonicalFile;
    const DSFileCanRead               CanRead;
    const DSFileCanWrite              CanWrite;
    const DSFileExists                Exists;
    const DSFileIsDirectory           IsDirectory;
    const DSFileIsFile                IsFile;
    const DSFileGetLength             GetLength;
    const DSFileList                  List;
};

class (DSFile) {
    DSFile*(*Create) (const char*);
    // DSFileSystem* fs;
    char SeparatorChar;
    char* Separator;
    char PathSeparatorChar;
    char* PathSeparator;
};

#endif _FILE_H_ 
