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
#include <dark/types.h>
#include <dark/core/object.h>
#include <dark/core/comparable.h>
#include <dark/io/filesystem.h>

typedef struct FileSystem FileSystem;
typedef enum { PS_UNCHECKED, PS_INVALID, PS_CHECKED } PathStatus;


type (File) {
    Class isa;
    String*           path;   
    PathStatus          status;
    int                 prefixLength;

};


method File* NewFile(const char*);
method File* NewFile(const char*, const char*);
method File* File_init(File* this, const char*);
method File* File_init(File* this, const char*, const char*);
method File* File_init(File* this, File*, const char*);

interface (File, ToString,           char*,      (const File* const) );
interface (File, CompareTo,          int,        (File* const, File* other) );
interface (File, IsInvalid,          bool,       (File* const) );
interface (File, GetPrefixLength,    int,        (File* const) );
interface (File, GetName,            String*,  (File* const) );
interface (File, GetParent,          String*,  (File* const) );
interface (File, GetParentFile,      File*,    (File* const) );
interface (File, GetPath,            String*,  (File* const) );
interface (File, IsAbsolute,         bool,       (File* const) );
interface (File, GetAbsolutePath,    String*,  (File* const) );
interface (File, GetAbsoluteFile,    File*,    (File* const) );
interface (File, GetCanonicalPath,   String*,  (File* const) );
interface (File, GetCanonicalFile,   File*,    (File* const) );
interface (File, CanRead,            bool,       (File* const) );
interface (File, CanWrite,           bool,       (File* const) );
interface (File, Exists,             bool,       (File* const) );
interface (File, IsDireCTORy,        bool,       (File* const) );
interface (File, IsFile,             bool,       (File* const) );
interface (File, GetLength,          long,       (File* const) );
// interface (File, List,               String**, (File* const) );

vtable (File) {
    const FileToString              ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const FileCompareTo             CompareTo;
    const FileIsInvalid             IsInvalid;
    const FileGetPrefixLength       GetPrefixLength;
    const FileGetName               GetName;
    const FileGetParent             GetParent;
    const FileGetParentFile         GetParentFile;
    const FileGetPath               GetPath;
    const FileIsAbsolute            IsAbsolute;
    const FileGetAbsolutePath       GetAbsolutePath;
    const FileGetAbsoluteFile       GetAbsoluteFile;
    const FileGetCanonicalPath      GetCanonicalPath;
    const FileGetCanonicalFile      GetCanonicalFile;
    const FileCanRead               CanRead;
    const FileCanWrite              CanWrite;
    const FileExists                Exists;
    const FileIsDireCTORy           IsDireCTORy;
    const FileIsFile                IsFile;
    const FileGetLength             GetLength;
    // const FileList                  List;
};

class (File) {
    File*(*Create) (const char*);
    // FileSystem* fs;
    char SeparatorChar;
    char Separator[2];
    char PathSeparatorChar;
    char PathSeparator[2];
};

function vptr(File);
/**
 * 
 * Class Loader callback
 */
function objc_loadFile(Class super) 
{
    Class cls = createClass(super, File);
    addMethod(cls, FileToString, ToString);
    addMethod(cls, ObjectEquals, Equals);
    addMethod(cls, ObjectGetHashCode, GetHashCode);
    addMethod(cls, ObjectDispose, Dispose);
    addMethod(cls, FileCompareTo, CompareTo);
    addMethod(cls, FileIsInvalid, IsInvalid);
    addMethod(cls, FileGetName, GetName);
    addMethod(cls, FileGetParent, GetParent);
    addMethod(cls, FileGetParentFile, GetParentFile);
    addMethod(cls, FileIsAbsolute, IsAbsolute);
    addMethod(cls, FileGetAbsolutePath, GetAbsolutePath);
    addMethod(cls, FileGetAbsoluteFile, GetAbsolutePath);
    addMethod(cls, FileGetCanonicalPath, GetCanonicalPath);
    addMethod(cls, FileGetCanonicalFile, GetCanonicalFile);
    addMethod(cls, FileCanRead, CanRead);
    addMethod(cls, FileCanWrite, CanWrite);
    addMethod(cls, FileExists, Exists);
    addMethod(cls, FileIsDireCTORy, IsDireCTORy);
    addMethod(cls, FileIsFile, IsFile);
    addMethod(cls, FileGetLength, GetLength);

    $File.SeparatorChar = fs.GetSeparator();
    $File.Separator[0] = $File.SeparatorChar;
    $File.Separator[1] = '\0';
    $File.PathSeparatorChar = fs.GetPathSeparator();
    $File.PathSeparator[0] = $File.PathSeparatorChar;
    $File.PathSeparator[1] =  '\0';

    return cls;
}


method bool IsInvalid(File* this) {
    if (this->status == PS_UNCHECKED) {
        this->status = (this->path == nullptr || !strcmp(this->path, ""))
            ? PS_INVALID 
            : PS_CHECKED;
    }
    return this->status == PS_INVALID;

}

method String* GetName(File* this) {
    int index = LastIndexOf(this->path, $($File.Separator), 0);
    if (index < this->prefixLength) return Substring(this->path, this->prefixLength);
    return Substring(this->path, index+1);    
}

method String* GetParent(File* this) {
    int index = LastIndexOf(this->path, $($File.Separator), 0);
    if (index < this->prefixLength) {
        if ((this->prefixLength > 0) && (this->path->length > this->prefixLength))
            return Substring(this->path, 0, this->prefixLength);
        return nullptr;
    } 
    return Substring(this->path, 0, index);
}

function File* FileWithLength(String* pathname, int prefixLength) {
    File* this = alloc(File);
    this->isa = objc_getClass("File");
    this->path = CopyOf(pathname);
    this->prefixLength = prefixLength;
    return this;
}

method File* GetParentFile(File* this) {
    auto p = GetParent(this);
    if (p == nullptr) return nullptr;
    return FileWithLength(p, this->prefixLength);
}

method bool IsAbsolute(File* this) {
    return fs.IsAbsolute(this);
}

method String* GetAbsolutePath(File* this) {
    return fs.ResolveFile(this);
}

method File* GetAbsoluteFile(File* this) {
    auto absPath = fs.ResolveFile(this);
    return FileWithLength(absPath, fs.PrefixLength(absPath));
}

method String* GetCanonicalPath(File* this) {
    // if (IsInvalid()) {
    //     throw new IOException.Exception("Invalid file path");
    // }
    return fs.Canonicalize(fs.ResolveFile(this));
}

method File* GetCanonicalFile(File* this) {
    auto canonPath = GetCanonicalPath(this);
    return FileWithLength(canonPath, fs.PrefixLength(canonPath));
}

method bool CanWrite(File* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_WRITE);
}
 
method bool CanRead(File* this) {
    if (IsInvalid(this)) return false;
    return fs.CheckAccess(this, ACCESS_READ);
}

method bool Exists(File* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_EXISTS) != 0);
}

method bool IsDireCTORy(File* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_DIRECTORY) != 0);
}

method bool IsFile(File* this) {
    if (IsInvalid(this)) return false;
    return ((fs.GetBooleanAttributes(this) & BA_REGULAR) != 0);
}

method long GetLength(File* this) {
    if (IsInvalid(this)) return 0L;
	return fs.GetLength(this);
}

// method String** List(File* this) {
//     if (IsInvalid(this)) return nullptr;
// 	return fs.List(this);
// }

    // const FileList                  List;

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

method int GetPrefixLength(File* const this) {
    return this->prefixLength;
}

method String* GetPath(File* const this) {
    return this->path;
}

method char* ToString(const File* const this) {
    // return this->name;
    return "";
}

method int CompareTo(File* const this, File* other) {
    return fs.Compare(this, other);
}

/**
 * Initialize a new File
 */
method File* File_init(File* const this, const char* path) {
    Comparable_init(this);
    this->isa = objc_getClass("File");
    this->path = fs.Normalize($(path));
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

method File* File_init(File* const this, const char* parent, const char* child) {
    Comparable_init(this);
    this->isa = objc_getClass("File");
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

method File* File_init(File* const this, File* parent, const char* child) {
    Comparable_init(this);
    this->isa = objc_getClass("File");
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
method File* NewFile(const char* path) {
    return File_init(alloc(File), path);
}

method File* NewFile(const char* parent, const char* child) {
    return File_init(alloc(File), parent, child);
}
