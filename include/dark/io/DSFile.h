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
#include <dark/types.h>
#include <dark/DSObject.h>
#include <dark/DSComparable.h>
#include "DSFileSystem.h"

typedef struct DSFileSystem DSFileSystem;
typedef enum { PS_UNCHECKED, PS_INVALID, PS_CHECKED } PathStatus;


IVAR (DSFile) {
    Class isa;
    DSString*           path;   
    PathStatus          status;
    int                 prefixLength;

};


static inline overload DSFile* NewDSFile(const char*);
static inline overload DSFile* NewDSFile(const char*, const char*);
static inline overload DSFile* DSFile_init(DSFile* this, const char*);
static inline overload DSFile* DSFile_init(DSFile* this, const char*, const char*);
static inline overload DSFile* DSFile_init(DSFile* this, DSFile*, const char*);

METHOD (DSFile, ToString,           char*,      (const DSFile* const) );
METHOD (DSFile, CompareTo,          int,        (DSFile* const, DSFile* other) );
METHOD (DSFile, IsInvalid,          bool,       (DSFile* const) );
METHOD (DSFile, GetPrefixLength,    int,        (DSFile* const) );
METHOD (DSFile, GetName,            DSString*,  (DSFile* const) );
METHOD (DSFile, GetParent,          DSString*,  (DSFile* const) );
METHOD (DSFile, GetParentFile,      DSFile*,    (DSFile* const) );
METHOD (DSFile, GetPath,            DSString*,  (DSFile* const) );
METHOD (DSFile, IsAbsolute,         bool,       (DSFile* const) );
METHOD (DSFile, GetAbsolutePath,    DSString*,  (DSFile* const) );
METHOD (DSFile, GetAbsoluteFile,    DSFile*,    (DSFile* const) );
METHOD (DSFile, GetCanonicalPath,   DSString*,  (DSFile* const) );
METHOD (DSFile, GetCanonicalFile,   DSFile*,    (DSFile* const) );
METHOD (DSFile, CanRead,            bool,       (DSFile* const) );
METHOD (DSFile, CanWrite,           bool,       (DSFile* const) );
METHOD (DSFile, Exists,             bool,       (DSFile* const) );
METHOD (DSFile, IsDireCTORy,        bool,       (DSFile* const) );
METHOD (DSFile, IsFile,             bool,       (DSFile* const) );
METHOD (DSFile, GetLength,          long,       (DSFile* const) );
METHOD (DSFile, List,               DSString**, (DSFile* const) );

VTABLE (DSFile) {
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
    const DSFileIsDireCTORy           IsDireCTORy;
    const DSFileIsFile                IsFile;
    const DSFileGetLength             GetLength;
    const DSFileList                  List;
};

class (DSFile) {
    DSFile*(*Create) (const char*);
    // DSFileSystem* fs;
    char SeparatorChar;
    char Separator[2];
    char PathSeparatorChar;
    char PathSeparator[2];
};

DEF_VPTR(DSFile);

static inline overload bool IsInvalid(DSFile* this) {
    if (this->status == PS_UNCHECKED) {
        this->status = (this->path == nullptr || !strcmp(this->path, ""))
            ? PS_INVALID 
            : PS_CHECKED;
    }
    return this->status == PS_INVALID;

}

static inline overload DSString* GetName(DSFile* this) {
    int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
    if (index < this->prefixLength) return Substring(this->path, this->prefixLength);
    return Substring(this->path, index+1);    
}

static inline overload DSString* GetParent(DSFile* this) {
    int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
    if (index < this->prefixLength) {
        if ((this->prefixLength > 0) && (this->path->length > this->prefixLength))
            return Substring(this->path, 0, this->prefixLength);
        return nullptr;
    } 
    return Substring(this->path, 0, index);
}

static inline DSFile* DSFileWithLength(DSString* pathname, int prefixLength) {
    DSFile* this = alloc(DSFile);
    this->isa = objc_getClass("DSFile");
    this->path = CopyOf(pathname);
    this->prefixLength = prefixLength;
    return this;
}

static inline overload DSFile* GetParentFile(DSFile* this) {
    auto p = GetParent(this);
    if (p == nullptr) return nullptr;
    return DSFileWithLength(p, this->prefixLength);
}

static inline overload bool IsAbsolute(DSFile* this) {
    return fs.IsAbsolute(this);
}

static inline overload DSString* GetAbsolutePath(DSFile* this) {
    return fs.ResolveFile(this);
}

static inline overload DSFile* GetAbsoluteFile(DSFile* this) {
    auto absPath = fs.ResolveFile(this);
    return DSFileWithLength(absPath, fs.PrefixLength(absPath));
}

static inline overload DSString* GetCanonicalPath(DSFile* this) {
    // if (IsInvalid()) {
    //     throw new IOException.Exception("Invalid file path");
    // }
    return fs.Canonicalize(fs.ResolveFile(this));
}

static inline overload DSFile* GetCanonicalFile(DSFile* this) {
    auto canonPath = GetCanonicalPath(this);
    return DSFileWithLength(canonPath, fs.PrefixLength(canonPath));
}

static inline overload bool CanWrite(DSFile* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_WRITE);
}
 
static inline overload bool CanRead(DSFile* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_READ);
}

static inline overload bool Exists(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_EXISTS) != 0);
}

static inline overload bool IsDireCTORy(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_DIRECTORY) != 0);
}

static inline overload bool IsFile(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_REGULAR) != 0);
}

static inline overload long GetLength(DSFile* this) {
    if (IsInvalid(this)) return 0L;
	return fs.GetLength(this);
}

static inline overload DSString** List(DSFile* this) {
    if (IsInvalid(this)) return nullptr;
	return fs.List(this);
}

    // const DSFileList                  List;

// static bool isSlash(char c) {
//     return (c == slash) || (c == altSlash);
// }

static inline bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a slash onto a string
 */
// static char* slashify(char* p) {
//     if ((strlen(p) > 0) && (p[0] != slash)) return join(slashString, p);
//     else return p;
// }

static inline overload int GetPrefixLength(DSFile* const this) {
    return this->prefixLength;
}

static inline overload DSString* GetPath(DSFile* const this) {
    return this->path;
}

static inline overload char* ToString(const DSFile* const this) {
    // return this->name;
    return "";
}

static inline overload int CompareTo(DSFile* const this, DSFile* other) {
    return fs.Compare(this, other);
}

/**
 * Initialize a new File
 */
static inline overload DSFile* DSFile_init(DSFile* const this, const char* path) {
    DSComparable_init(this);
    this->isa = objc_getClass("DSFile");
    this->path = fs.Normalize($(path));
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

static inline overload DSFile* DSFile_init(DSFile* const this, const char* parent, const char* child) {
    DSComparable_init(this);
    this->isa = objc_getClass("DSFile");
    if (!strcmp("", parent)) {
        this->path = fs.Resolve(fs.GetDefaultParent(), 
                        fs.Normalize(child));
    } else {
        this->path = fs.Resolve(fs.Normalize(parent), 
                        fs.Normalize(child));
    }
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

static inline overload DSFile* DSFile_init(DSFile* const this, DSFile* parent, const char* child) {
    DSComparable_init(this);
    this->isa = objc_getClass("DSFile");
    if (parent->path != nullptr) {
        if (!strcmp("", parent->path)) {
        this->path = fs.Resolve(fs.GetDefaultParent(), 
                        fs.Normalize(child));
        } else {
        this->path = fs.Resolve(parent->path, 
                        fs.Normalize(child));
        }
    } else {
        this->path = fs.Normalize(child);
    }
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

/**
 * new File
 * 
 * 
 */
static inline overload DSFile* NewDSFile(const char* path) {
    return DSFile_init(alloc(DSFile), path);
}

static inline overload DSFile* NewDSFile(const char* parent, const char* child) {
    return DSFile_init(alloc(DSFile), parent, child);
}

VTABLE_BIND( DSFile );
VTABLE_OVERRIDE( ToString,        (DSFileToString)ToString, "$@:v" );
VTABLE_METHOD( Equals,            (DSObjectEquals)Equals, "B@:@@" );
VTABLE_METHOD( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
VTABLE_METHOD( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
VTABLE_OVERRIDE( CompareTo,       (DSFileCompareTo)CompareTo, "i@:@" );
VTABLE_METHOD( IsInvalid,         (DSFileIsInvalid)IsInvalid, "B@:v");
VTABLE_METHOD( GetName,           (DSFileGetName)GetName, "$@:v" );
VTABLE_METHOD( GetParent,         (DSFileGetParent)GetParent, "$@:v" );
VTABLE_METHOD( GetParentFile,     (DSFileGetParentFile)GetParentFile, "$@:v" );
VTABLE_METHOD( IsAbsolute,        (DSFileIsAbsolute)IsAbsolute, "B@:v" );
VTABLE_METHOD( GetAbsolutePath,   (DSFileGetAbsolutePath)GetAbsolutePath, "$@:v" );
VTABLE_METHOD( GetAbsoluteFile,   (DSFileGetAbsoluteFile)GetAbsolutePath, "@@:v" );
VTABLE_METHOD( GetCanonicalPath,  (DSFileGetCanonicalPath)GetCanonicalPath, "$@:v");
VTABLE_METHOD( GetCanonicalFile,  (DSFileGetCanonicalFile)GetCanonicalFile, "@@:v");
VTABLE_METHOD( CanRead,           (DSFileCanRead)CanRead, "B@:v");
VTABLE_METHOD( CanWrite,          (DSFileCanWrite)CanWrite, "B@:v");
VTABLE_METHOD( Exists,            (DSFileExists)Exists, "B@:v");
VTABLE_METHOD( IsDireCTORy,       (DSFileIsDireCTORy)IsDireCTORy, "B@:v");
VTABLE_METHOD( IsFile,            (DSFileIsFile)IsFile, "B@:v");
VTABLE_METHOD( GetLength,         (DSFileGetLength)GetLength, "l@:v");

$DSFile.SeparatorChar = fs.GetSeparator();
$DSFile.Separator[0] = $DSFile.SeparatorChar;
$DSFile.Separator[1] = '\0';
$DSFile.PathSeparatorChar = fs.GetPathSeparator();
$DSFile.PathSeparator[0] = $DSFile.PathSeparatorChar;
$DSFile.PathSeparator[1] =  '\0';

VTABLE_METHODIZE;

#endif _FILE_H_ 
