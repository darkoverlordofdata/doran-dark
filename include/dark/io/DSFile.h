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


type (DSFile) {
    Class isa;
    DSString*           path;   
    PathStatus          status;
    int                 prefixLength;

};


method DSFile* NewDSFile(const char*);
method DSFile* NewDSFile(const char*, const char*);
method DSFile* DSFile_init(DSFile* this, const char*);
method DSFile* DSFile_init(DSFile* this, const char*, const char*);
method DSFile* DSFile_init(DSFile* this, DSFile*, const char*);

method_proto (DSFile, ToString,           char*,      (const DSFile* const) );
method_proto (DSFile, CompareTo,          int,        (DSFile* const, DSFile* other) );
method_proto (DSFile, IsInvalid,          bool,       (DSFile* const) );
method_proto (DSFile, GetPrefixLength,    int,        (DSFile* const) );
method_proto (DSFile, GetName,            DSString*,  (DSFile* const) );
method_proto (DSFile, GetParent,          DSString*,  (DSFile* const) );
method_proto (DSFile, GetParentFile,      DSFile*,    (DSFile* const) );
method_proto (DSFile, GetPath,            DSString*,  (DSFile* const) );
method_proto (DSFile, IsAbsolute,         bool,       (DSFile* const) );
method_proto (DSFile, GetAbsolutePath,    DSString*,  (DSFile* const) );
method_proto (DSFile, GetAbsoluteFile,    DSFile*,    (DSFile* const) );
method_proto (DSFile, GetCanonicalPath,   DSString*,  (DSFile* const) );
method_proto (DSFile, GetCanonicalFile,   DSFile*,    (DSFile* const) );
method_proto (DSFile, CanRead,            bool,       (DSFile* const) );
method_proto (DSFile, CanWrite,           bool,       (DSFile* const) );
method_proto (DSFile, Exists,             bool,       (DSFile* const) );
method_proto (DSFile, IsDireCTORy,        bool,       (DSFile* const) );
method_proto (DSFile, IsFile,             bool,       (DSFile* const) );
method_proto (DSFile, GetLength,          long,       (DSFile* const) );
method_proto (DSFile, List,               DSString**, (DSFile* const) );

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

class_load( DSFile );
class_override( ToString,        (DSFileToString)ToString, "$@:v" );
class_method( Equals,            (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,       (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,           (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,       (DSFileCompareTo)CompareTo, "i@:@" );
class_method( IsInvalid,         (DSFileIsInvalid)IsInvalid, "B@:v");
class_method( GetName,           (DSFileGetName)GetName, "$@:v" );
class_method( GetParent,         (DSFileGetParent)GetParent, "$@:v" );
class_method( GetParentFile,     (DSFileGetParentFile)GetParentFile, "$@:v" );
class_method( IsAbsolute,        (DSFileIsAbsolute)IsAbsolute, "B@:v" );
class_method( GetAbsolutePath,   (DSFileGetAbsolutePath)GetAbsolutePath, "$@:v" );
class_method( GetAbsoluteFile,   (DSFileGetAbsoluteFile)GetAbsolutePath, "@@:v" );
class_method( GetCanonicalPath,  (DSFileGetCanonicalPath)GetCanonicalPath, "$@:v");
class_method( GetCanonicalFile,  (DSFileGetCanonicalFile)GetCanonicalFile, "@@:v");
class_method( CanRead,           (DSFileCanRead)CanRead, "B@:v");
class_method( CanWrite,          (DSFileCanWrite)CanWrite, "B@:v");
class_method( Exists,            (DSFileExists)Exists, "B@:v");
class_method( IsDireCTORy,       (DSFileIsDireCTORy)IsDireCTORy, "B@:v");
class_method( IsFile,            (DSFileIsFile)IsFile, "B@:v");
class_method( GetLength,         (DSFileGetLength)GetLength, "l@:v");

$DSFile.SeparatorChar = fs.GetSeparator();
$DSFile.Separator[0] = $DSFile.SeparatorChar;
$DSFile.Separator[1] = '\0';
$DSFile.PathSeparatorChar = fs.GetPathSeparator();
$DSFile.PathSeparator[0] = $DSFile.PathSeparatorChar;
$DSFile.PathSeparator[1] =  '\0';

class_fini;

method bool IsInvalid(DSFile* this) {
    if (this->status == PS_UNCHECKED) {
        this->status = (this->path == nullptr || !strcmp(this->path, ""))
            ? PS_INVALID 
            : PS_CHECKED;
    }
    return this->status == PS_INVALID;

}

method DSString* GetName(DSFile* this) {
    int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
    if (index < this->prefixLength) return Substring(this->path, this->prefixLength);
    return Substring(this->path, index+1);    
}

method DSString* GetParent(DSFile* this) {
    int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
    if (index < this->prefixLength) {
        if ((this->prefixLength > 0) && (this->path->length > this->prefixLength))
            return Substring(this->path, 0, this->prefixLength);
        return nullptr;
    } 
    return Substring(this->path, 0, index);
}

function DSFile* DSFileWithLength(DSString* pathname, int prefixLength) {
    DSFile* this = alloc(DSFile);
    this->isa = objc_getClass("DSFile");
    this->path = CopyOf(pathname);
    this->prefixLength = prefixLength;
    return this;
}

method DSFile* GetParentFile(DSFile* this) {
    auto p = GetParent(this);
    if (p == nullptr) return nullptr;
    return DSFileWithLength(p, this->prefixLength);
}

method bool IsAbsolute(DSFile* this) {
    return fs.IsAbsolute(this);
}

method DSString* GetAbsolutePath(DSFile* this) {
    return fs.ResolveFile(this);
}

method DSFile* GetAbsoluteFile(DSFile* this) {
    auto absPath = fs.ResolveFile(this);
    return DSFileWithLength(absPath, fs.PrefixLength(absPath));
}

method DSString* GetCanonicalPath(DSFile* this) {
    // if (IsInvalid()) {
    //     throw new IOException.Exception("Invalid file path");
    // }
    return fs.Canonicalize(fs.ResolveFile(this));
}

method DSFile* GetCanonicalFile(DSFile* this) {
    auto canonPath = GetCanonicalPath(this);
    return DSFileWithLength(canonPath, fs.PrefixLength(canonPath));
}

method bool CanWrite(DSFile* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_WRITE);
}
 
method bool CanRead(DSFile* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_READ);
}

method bool Exists(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_EXISTS) != 0);
}

method bool IsDireCTORy(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_DIRECTORY) != 0);
}

method bool IsFile(DSFile* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_REGULAR) != 0);
}

method long GetLength(DSFile* this) {
    if (IsInvalid(this)) return 0L;
	return fs.GetLength(this);
}

method DSString** List(DSFile* this) {
    if (IsInvalid(this)) return nullptr;
	return fs.List(this);
}

    // const DSFileList                  List;

// static bool isSlash(char c) {
//     return (c == slash) || (c == altSlash);
// }

function bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a slash onto a string
 */
// static char* slashify(char* p) {
//     if ((strlen(p) > 0) && (p[0] != slash)) return join(slashString, p);
//     else return p;
// }

method int GetPrefixLength(DSFile* const this) {
    return this->prefixLength;
}

method DSString* GetPath(DSFile* const this) {
    return this->path;
}

method char* ToString(const DSFile* const this) {
    // return this->name;
    return "";
}

method int CompareTo(DSFile* const this, DSFile* other) {
    return fs.Compare(this, other);
}

/**
 * Initialize a new File
 */
method DSFile* DSFile_init(DSFile* const this, const char* path) {
    DSComparable_init(this);
    this->isa = objc_getClass("DSFile");
    this->path = fs.Normalize($(path));
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

method DSFile* DSFile_init(DSFile* const this, const char* parent, const char* child) {
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

method DSFile* DSFile_init(DSFile* const this, DSFile* parent, const char* child) {
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
method DSFile* NewDSFile(const char* path) {
    return DSFile_init(alloc(DSFile), path);
}

method DSFile* NewDSFile(const char* parent, const char* child) {
    return DSFile_init(alloc(DSFile), parent, child);
}


#endif _FILE_H_ 
