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


// method File* NewFile(const char*);
// method File* NewFile(const char*, const char*);
// method File* File_ctor(File* self, const char*);
// method File* File_ctor(File* self, const char*, const char*);
// method File* File_ctor(File* self, File*, const char*);

delegate (File, New,                File*,      (File*, const char*) );
delegate (File, ToString,           char*,      (const File* const) );
delegate (File, CompareTo,          int,        (File* const, File* other) );
delegate (File, IsInvalid,          bool,       (File* const) );
delegate (File, GetPrefixLength,    int,        (File* const) );
delegate (File, GetName,            String*,  (File* const) );
delegate (File, GetParent,          String*,  (File* const) );
delegate (File, GetParentFile,      File*,    (File* const) );
delegate (File, GetPath,            String*,  (File* const) );
delegate (File, IsAbsolute,         bool,       (File* const) );
delegate (File, GetAbsolutePath,    String*,  (File* const) );
delegate (File, GetAbsoluteFile,    File*,    (File* const) );
delegate (File, GetCanonicalPath,   String*,  (File* const) );
delegate (File, GetCanonicalFile,   File*,    (File* const) );
delegate (File, CanRead,            bool,       (File* const) );
delegate (File, CanWrite,           bool,       (File* const) );
delegate (File, Exists,             bool,       (File* const) );
delegate (File, IsDireCTORy,        bool,       (File* const) );
delegate (File, IsFile,             bool,       (File* const) );
delegate (File, GetLength,          long,       (File* const) );

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
};

class (File) {
    File*(*Create) (const char*);
    char SeparatorChar;
    char Separator[2];
    char PathSeparatorChar;
    char PathSeparator[2];
};

static inline vptr(File);
/**
 * 
 * Class Loader callback
 */
static inline Class ClassLoadFile(Class base) 
{
    Class cls = createClass(base, File);
    addMethod(cls, File, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, File, CompareTo);
    addMethod(cls, File, IsInvalid);
    addMethod(cls, File, GetName);
    addMethod(cls, File, GetParent);
    addMethod(cls, File, GetParentFile);
    addMethod(cls, File, IsAbsolute);
    addMethod(cls, File, GetAbsolutePath);
    addMethod(cls, File, GetAbsolutePath);
    addMethod(cls, File, GetCanonicalPath);
    addMethod(cls, File, GetCanonicalFile);
    addMethod(cls, File, CanRead);
    addMethod(cls, File, CanWrite);
    addMethod(cls, File, Exists);
    addMethod(cls, File, IsDireCTORy);
    addMethod(cls, File, IsFile);
    addMethod(cls, File, GetLength);

    $File.SeparatorChar = fs.GetSeparator();
    $File.Separator[0] = $File.SeparatorChar;
    $File.Separator[1] = '\0';
    $File.PathSeparatorChar = fs.GetPathSeparator();
    $File.PathSeparator[0] = $File.PathSeparatorChar;
    $File.PathSeparator[1] =  '\0';

    return cls;
}


method bool IsInvalid(File* self) {
    if (self->status == PS_UNCHECKED) {
        self->status = (self->path == nullptr || !strcmp(self->path->value, ""))
            ? PS_INVALID 
            : PS_CHECKED;
    }
    return self->status == PS_INVALID;

}

method String* GetName(File* self) {
    int index = LastIndexOf(self->path, new(String, $File.Separator), 0);
    if (index < self->prefixLength) return Substring(self->path, self->prefixLength);
    return Substring(self->path, index+1);    
}

method String* GetParent(File* self) {
    int index = LastIndexOf(self->path, new(String, $File.Separator), 0);
    if (index < self->prefixLength) {
        if ((self->prefixLength > 0) && (self->path->length > self->prefixLength))
            return Substring(self->path, 0, self->prefixLength);
        return nullptr;
    } 
    return Substring(self->path, 0, index);
}

static inline File* FileWithLength(String* pathname, int prefixLength) {
    File* self = alloc(File);
    set_isa(File);
    self->path = CopyOf(pathname);
    self->prefixLength = prefixLength;
    return self;
}

method File* GetParentFile(File* self) {
    auto p = GetParent(self);
    if (p == nullptr) return nullptr;
    return FileWithLength(p, self->prefixLength);
}

method bool IsAbsolute(File* self) {
    return fs.IsAbsolute(self);
}

method String* GetAbsolutePath(File* self) {
    return fs.ResolveFile(self);
}

method File* GetAbsoluteFile(File* self) {
    auto absPath = fs.ResolveFile(self);
    return FileWithLength(absPath, fs.PrefixLength(absPath));
}

method String* GetCanonicalPath(File* self) {
    // if (IsInvalid()) {
    //     throw new IOException.Exception("Invalid file path");
    // }
    return fs.Canonicalize(fs.ResolveFile(self));
}

method File* GetCanonicalFile(File* self) {
    auto canonPath = GetCanonicalPath(self);
    return FileWithLength(canonPath, fs.PrefixLength(canonPath));
}

method bool CanWrite(File* self) {
    if (IsInvalid(self)) return false;
    return fs.CheckAccess(self, ACCESS_WRITE);
}
 
method bool CanRead(File* self) {
    if (IsInvalid(self)) return false;
    return fs.CheckAccess(self, ACCESS_READ);
}

method bool Exists(File* self) {
    if (IsInvalid(self)) return false;
    return ((fs.GetBooleanAttributes(self) & BA_EXISTS) != 0);
}

method bool IsDireCTORy(File* self) {
    if (IsInvalid(self)) return false;
    return ((fs.GetBooleanAttributes(self) & BA_DIRECTORY) != 0);
}

method bool IsFile(File* self) {
    if (IsInvalid(self)) return false;
    return ((fs.GetBooleanAttributes(self) & BA_REGULAR) != 0);
}

method long GetLength(File* self) {
    if (IsInvalid(self)) return 0L;
	return fs.GetLength(self);
}

// method String** List(File* self) {
//     if (IsInvalid(self)) return nullptr;
// 	return fs.List(self);
// }

    // const FileList                  List;

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

method int GetPrefixLength(File* const self) {
    return self->prefixLength;
}

method String* GetPath(File* const self) {
    return self->path;
}

method char* ToString(const File* const self) {
    // return self->name;
    return "";
}

method int CompareTo(File* const self, File* other) {
    return fs.Compare(self, other);
}

/**
 * Initialize a new File
 */
method File* New(File* self, const char* path) {
    extends(Comparable);
    set_isa(File);
    self->path = fs.Normalize(new(String, path));
    self->prefixLength = fs.PrefixLength(self->path);
    return self;
}

method File* New(File* self, const char* parent, const char* child) {
    extends(Comparable);
    set_isa(File);
    if (!strcmp("", parent)) {
        self->path = fs.Resolve(fs.GetDefaultParent(), 
                        fs.Normalize(child));
    } else {
        self->path = fs.Resolve(fs.Normalize(parent), 
                        fs.Normalize(child));
    }
    self->prefixLength = fs.PrefixLength(self->path);
    return self;
}

method File* New(File* self, File* parent, const char* child) {
    extends(Comparable);
    set_isa(File);
    if (parent->path != nullptr) {
        if (!strcmp("", parent->path)) {
        self->path = fs.Resolve(fs.GetDefaultParent(), 
                        fs.Normalize(child));
        } else {
        self->path = fs.Resolve(parent->path, 
                        fs.Normalize(child));
        }
    } else {
        self->path = fs.Normalize(child);
    }
    self->prefixLength = fs.PrefixLength(self->path);
    return self;
}
/**
 * new File
 * 
 * 
 */
// method File* NewFile(const char* path) {
//     return File_ctor(alloc(File), path);
// }

// method File* NewFile(const char* parent, const char* child) {
//     return File_ctor(alloc(File), parent, child);
// }
