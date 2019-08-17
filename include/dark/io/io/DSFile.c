// /*******************************************************************
// ** This code is part of the Dark Framework.
// **
// MIT License

// Copyright (c) 2018 Dark Overlord of Data

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ******************************************************************/
// #include <dark/io/DSFile.h>
// #include <dark/io/implementation/DSFile.h>
// /* 
//  * File implementation
//  */

// bool overload IsInvalid(DSFile* this) {
//     if (this->status == PS_UNCHECKED) {
//         this->status = (this->path == nullptr || !strcmp(this->path, ""))
//             ? PS_INVALID 
//             : PS_CHECKED;
//     }
//     return this->status == PS_INVALID;

// }

// DSString* overload GetName(DSFile* this) {
//     int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
//     if (index < this->prefixLength) return Substring(this->path, this->prefixLength);
//     return Substring(this->path, index+1);    
// }

// DSString* overload GetParent(DSFile* this) {
//     int index = LastIndexOf(this->path, $($DSFile.Separator), 0);
//     if (index < this->prefixLength) {
//         if ((this->prefixLength > 0) && (this->path->length > this->prefixLength))
//             return Substring(this->path, 0, this->prefixLength);
//         return nullptr;
//     } 
//     return Substring(this->path, 0, index);
// }

// static DSFile* DSFileWithLength(DSString* pathname, int prefixLength) {
//     DSFile* this = alloc(DSFile);
//     this->isa = getDSFileIsa();
//     this->path = CopyOf(pathname);
//     this->prefixLength = prefixLength;
//     return this;
// }

// DSFile* overload GetParentFile(DSFile* this) {
//     auto p = GetParent(this);
//     if (p == nullptr) return nullptr;
//     return DSFileWithLength(p, this->prefixLength);
// }

// bool overload IsAbsolute(DSFile* this) {
//     return fs.IsAbsolute(this);
// }

// DSString* overload GetAbsolutePath(DSFile* this) {
//     return fs.ResolveFile(this);
// }

// DSFile* overload GetAbsoluteFile(DSFile* this) {
//     auto absPath = fs.ResolveFile(this);
//     return DSFileWithLength(absPath, fs.PrefixLength(absPath));
// }

// DSString* overload GetCanonicalPath(DSFile* this) {
//     // if (IsInvalid()) {
//     //     throw new IOException.Exception("Invalid file path");
//     // }
//     return fs.Canonicalize(fs.ResolveFile(this));
// }

// DSFile* overload GetCanonicalFile(DSFile* this) {
//     auto canonPath = GetCanonicalPath(this);
//     return DSFileWithLength(canonPath, fs.PrefixLength(canonPath));
// }

// bool overload CanWrite(DSFile* this) {
//     if (IsInvalid(this)) return false;
//     return fs.CheckAccess(this, ACCESS_WRITE);
// }
 
// bool overload CanRead(DSFile* this) {
//     if (IsInvalid(this)) return false;
//     return fs.CheckAccess(this, ACCESS_READ);
// }

// bool overload Exists(DSFile* this) {
//     if (IsInvalid(this)) return false;
//     return ((fs.GetBooleanAttributes(this) & BA_EXISTS) != 0);
// }

// bool overload IsDirectory(DSFile* this) {
//     if (IsInvalid(this)) return false;
//     return ((fs.GetBooleanAttributes(this) & BA_DIRECTORY) != 0);
// }

// bool overload IsFile(DSFile* this) {
//     if (IsInvalid(this)) return false;
//     return ((fs.GetBooleanAttributes(this) & BA_REGULAR) != 0);
// }

// long overload GetLength(DSFile* this) {
//     if (IsInvalid(this)) return 0L;
// 	return fs.GetLength(this);
// }

// DSString** overload List(DSFile* this) {
//     if (IsInvalid(this)) return nullptr;
// 	return fs.List(this);
// }

//     // const DSFileList                  List;

// // static bool isSlash(char c) {
// //     return (c == slash) || (c == altSlash);
// // }

// static bool isLetter(char c) {
//     return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
// }

// /**
//  * prepend a slash onto a string
//  */
// // static char* slashify(char* p) {
// //     if ((strlen(p) > 0) && (p[0] != slash)) return join(slashString, p);
// //     else return p;
// // }

// int overload GetPrefixLength(DSFile* const this) {
//     return this->prefixLength;
// }

// DSString* overload GetPath(DSFile* const this) {
//     return this->path;
// }

// char* overload ToString(const DSFile* const this) {
//     // return this->name;
//     return "";
// }

// int overload CompareTo(DSFile* const this, DSFile* other) {
//     return fs.Compare(this, other);
// }

// /**
//  * Initialize a new File
//  */
// DSFile* overload DSFile_init(DSFile* const this, const char* path) {
//     DSComparable_init(this);
//     this->isa = getDSFileIsa();
//     this->path = fs.Normalize($(path));
//     this->prefixLength = fs.PrefixLength(this->path);
//     return this;
// }

// DSFile* overload DSFile_init(DSFile* const this, const char* parent, const char* child) {
//     DSComparable_init(this);
//     this->isa = getDSFileIsa();
//     if (!strcmp("", parent)) {
//         this->path = fs.Resolve(fs.GetDefaultParent(), 
//                         fs.Normalize(child));
//     } else {
//         this->path = fs.Resolve(fs.Normalize(parent), 
//                         fs.Normalize(child));
//     }
//     this->prefixLength = fs.PrefixLength(this->path);
//     return this;
// }

// DSFile* overload DSFile_init(DSFile* const this, DSFile* parent, const char* child) {
//     DSComparable_init(this);
//     this->isa = getDSFileIsa();
//     if (parent->path != nullptr) {
//         if (!strcmp("", parent->path)) {
//         this->path = fs.Resolve(fs.GetDefaultParent(), 
//                         fs.Normalize(child));
//         } else {
//         this->path = fs.Resolve(parent->path, 
//                         fs.Normalize(child));
//         }
//     } else {
//         this->path = fs.Normalize(child);
//     }
//     this->prefixLength = fs.PrefixLength(this->path);
//     return this;
// }

// /**
//  * new File
//  * 
//  * 
//  */
// DSFile* overload NewDSFile(const char* path) {
//     return DSFile_init(alloc(DSFile), path);
// }

// DSFile* overload NewDSFile(const char* parent, const char* child) {
//     return DSFile_init(alloc(DSFile), parent, child);
// }
