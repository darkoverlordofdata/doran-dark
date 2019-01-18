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
#include <dark/io/DSFile.h>
#include "private/DSFile.h"
/* 
 * File implementation
 */


// static bool isSlash(char c) {
//     return (c == slash) || (c == altSlash);
// }

static bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a slash onto a string
 */
// static char* slashify(char* p) {
//     if ((strlen(p) > 0) && (p[0] != slash)) return join(slashString, p);
//     else return p;
// }

int overload GetPrefixLength(DSFile* const this) {
    return this->prefixLength;
}

DSString* overload GetPath(DSFile* const this) {
    return this->path;
}
char* overload ToString(const DSFile* const this) {
    // return this->name;
    return "";
}

int overload CompareTo(DSFile* const this, DSFile* other) {
    return 0;
}

/**
 * Initialize a new File
 */
DSFile* overload DSFile_init(DSFile* const this, const char* path) {
    DSComparable_init(this);
    this->isa = getDSFileIsa();
    this->path = fs.Normalize(path);
    this->prefixLength = fs.PrefixLength(this->path);
    return this;
}

DSFile* overload DSFile_init(DSFile* const this, const char* parent, const char* child) {
    DSComparable_init(this);
    this->isa = getDSFileIsa();
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

DSFile* overload DSFile_init(DSFile* const this, DSFile* parent, const char* child) {
    DSComparable_init(this);
    this->isa = getDSFileIsa();
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
DSFile* overload DSFile_New(const char* path) {
    return DSFile_init(alloc(DSFile), path);
}

DSFile* overload DSFile_New(const char* parent, const char* child) {
    return DSFile_init(alloc(DSFile), parent, child);
}
