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
#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_
#include <stdio.h>
#include "../DObject.h"
#include "../types/StringBuilder.h"
#include "File.h"

cyclic_reference(File);

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


class (FileSystem)
{
    union {
        DObject_t _;
        struct 
        {
            int         RefCount;
            char*       (*ToString)(DObject const);
            bool        (*Equals)(DObject const, DObject const);
            int         (*GetHashCode)(DObject const);
            void        (*Dispose) (DObject const);
        };
    };

    char                slash;
    char                semicolon;
    char                altSlash;
    char*               slashString;
    char*               semicolonString;
    char*               altSlashString;
    String              (*Slashify) (FileSystem const, String path);
    String              (*GetUserPath) (FileSystem const);
    String              (*GetDrive) (FileSystem const, String path);
    int                 (*DriveIndex) (FileSystem const, char drive);
    String              (*GetDriveDirectory) (FileSystem const, char drive);
    char                (*GetSeparator) (FileSystem const);
    char                (*GetPathSeparator) (FileSystem const);
    String              (*Normalize) (FileSystem const, String path);
    int                 (*PrefixLength) (FileSystem const, String path);
    String              (*Resolve) (FileSystem const, String parent, String child);
    String              (*GetDefaultParent) (FileSystem const);
    String              (*FromURIPath) (FileSystem const, String path);
    bool                (*IsAbsolute) (FileSystem const, File f);
    String              (*ResolveFile) (FileSystem const, File f);
    String              (*Canonicalize) (FileSystem const, String path);
    int                 (*GetBooleanAttributes) (FileSystem const, File f);
    bool                (*CheckAccess) (FileSystem const, File f, int access);
    bool                (*SetPermission) (FileSystem const, File f, int access, bool enable, bool owneronly);
    long                (*GetLastModifiedTime) (FileSystem const, File f);
    long                (*GetLength) (FileSystem const, File f);
    bool                (*CreateFileExclusively) (FileSystem const, String path);
    bool                (*Delete) (FileSystem const, File f);
    String*             (*List) (FileSystem const, File f);
    bool                (*CreateDirectory) (FileSystem const, File f);
    bool                (*Rename) (FileSystem const, File f1, File f2);
    bool                (*SetLastModifiedTime) (FileSystem const, File f, long time);
    String*             (*SetReadOnly) (FileSystem const, File const);
    File*               (*ListRoots) (FileSystem const);
    int                 (*Compare) (FileSystem const, File f1, File f2);
    int                 (*HashCode) (FileSystem const, File f);


};


#endif _FILE_SYSTEM_H_ 
