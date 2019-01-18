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
#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_
#include <stdio.h>
#include "../types.h"
#include "DSFile.h"


#define BA_EXISTS    0xffff
#define BA_FIFO      0x1000
#define BA_CHAR      0x2000
#define BA_BLOCK     0x3000
#define BA_DIRECTORY 0x4000
#define BA_REGULAR   0x8000

#define ACCESS_READ    0400
#define ACCESS_WRITE   0200
#define ACCESS_EXECUTE 0100

#define SPACE_TOTAL  0
#define SPACE_FREE   1
#define SPACE_USABLE 2

typedef struct DSFile DSFile;

ivar (DSFileSystem){
    Class isa;
    char slash;
    char semicolon;
    char altSlash;
    char* slashString;
    char* semicolonString;
    char* altSlashString;
};

DSFileSystem* NewDSFileSystem();
DSFileSystem* DSFileSystem_init(DSFileSystem*);

method (DSFileSystem, ToString,          char*,     (const DSFile* const) );
method (DSFileSystem, Slashify,          DSString*, (DSFileSystem* const, DSString*) );
method (DSFileSystem, GetUserPath,       DSString*, (DSFileSystem* const) );
method (DSFileSystem, GetDrive,          DSString*, (DSFileSystem* const, DSString*) );
method (DSFileSystem, DriveIndex,        int,       (DSFileSystem* const, char) );
method (DSFileSystem, GetDriveDirectory, DSString*, (DSFileSystem* const, char) );
method (DSFileSystem, GetSeparator,      char,      (DSFileSystem* const) );
method (DSFileSystem, GetPathSeparator,  char,      (DSFileSystem* const) );
method (DSFileSystem, Normalize,         DSString*, (DSFileSystem* const, DSString*) );
method (DSFileSystem, PrefixLength,      int,       (DSFileSystem* const, DSString*) );
method (DSFileSystem, Resolve,           DSString*, (DSFileSystem* const, DSString*, DSString*) );
method (DSFileSystem, GetDefaultParent,  DSString*, (DSFileSystem* const) );
method (DSFileSystem, FromURIPath,       DSString*, (DSFileSystem* const, DSString*) );
method (DSFileSystem, IsAbsolute,        bool,      (DSFileSystem* const, DSFile*) );
method (DSFileSystem, ResolveFile,       DSString*, (DSFileSystem* const, DSFile*) );
method (DSFileSystem, Canonicalize,      DSString*, (DSFileSystem* const, DSString*) );
method (DSFileSystem, GetBooleanAttributes, int,    (DSFileSystem* const, DSFile*) );
method (DSFileSystem, CheckAccess,       bool,      (DSFileSystem* const, DSFile*, int) );
method (DSFileSystem, SetPermission,     bool,      (DSFileSystem* const, DSFile*, int, bool, bool) );
method (DSFileSystem, GetLastModifiedTime, long,    (DSFileSystem* const, DSFile*) );
method (DSFileSystem, GetLength,         long,      (DSFileSystem* const, DSFile*) );
method (DSFileSystem, CreateFileExclusively, bool,  (DSFileSystem* const, DSString*) );
method (DSFileSystem, Delete,            bool,      (DSFileSystem* const, DSFile*) );
method (DSFileSystem, List,              DSString*, (DSFileSystem* const, DSFile*) );
method (DSFileSystem, CreateDirectory,   bool,      (DSFileSystem* const, DSFile*) );
method (DSFileSystem, Rename,            bool,      (DSFileSystem* const, DSFile*, DSFile*) );
method (DSFileSystem, SetLastModifiedTime, bool,    (DSFileSystem* const, DSFile*, long) );
method (DSFileSystem, SetReadOnly,       DSString*, (DSFileSystem* const, DSFile* const) );
method (DSFileSystem, ListRoots,         DSFile*,   (DSFileSystem* const) );
method (DSFileSystem, Compare,           int,       (DSFileSystem* const, DSFile*, DSFile*) );
method (DSFileSystem, HashCode,          int,       (DSFileSystem* const, DSFile*) );


vtable (DSFileSystem) {
    DSFileSystemToString            ToString;
    DSObjectEquals                  Equals;
    DSObjectGetHashCode             GetHashCode;
    DSObjectDispose                 Dispose;
    DSFileSystemSlashify            Slashify;    
    DSFileSystemGetUserPath         GetUserPath;
    DSFileSystemGetDrive            GetDrive;
    DSFileSystemDriveIndex          DriveIndex;
    DSFileSystemGetDriveDirectory   GetDriveDirectory;
    DSFileSystemGetSeparator        GetSeparator;
    DSFileSystemGetPathSeparator    GetPathSeparator;
    DSFileSystemNormalize           Normalize;
    DSFileSystemPrefixLength        PrefixLength;
    DSFileSystemResolve             Resolve;
    DSFileSystemGetDefaultParent    GetDefaultParent;
    DSFileSystemFromURIPath         FromURIPath;
    DSFileSystemIsAbsolute          IsAbsolute;
    DSFileSystemResolveFile         ResolveFile;
    DSFileSystemCanonicalize        Canonicalize;
    DSFileSystemGetBooleanAttributes    GetBooleanAttributes;
    DSFileSystemCheckAccess         CheckAccess;
    DSFileSystemSetPermission       SetPermission;
    DSFileSystemGetLastModifiedTime GetLastModifiedTime;
    DSFileSystemGetLength           GetLength;
    DSFileSystemCreateFileExclusively   CreateFileExclusively;
    DSFileSystemDelete              Delete;
    DSFileSystemList                List;
    DSFileSystemCreateDirectory     CreateDirectory;
    DSFileSystemRename              Rename;
    DSFileSystemSetLastModifiedTime SetLastModifiedTime;
    DSFileSystemSetReadOnly         SetReadOnly;
    DSFileSystemListRoots           ListRoots;
    DSFileSystemCompare             Compare;
    DSFileSystemHashCode            HashCode;
};

class (DSFileSystem) {
    DSFileSystem*(*Create) ();
};


#endif _FILE_SYSTEM_H_ 
