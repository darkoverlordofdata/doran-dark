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
#include <stdio.h>
#include <dark/io/DSFileSystem.h>

static char fsSlash;
static char fsSemicolon;
static char fsAltSlash;
static char fsSlashString[2];
static char fsSemicolonString[2];
static char fsAltSlashString[2];

static bool fsIsSlash(char c) {
    return (c == '\\') || (c == '/');
}

static bool fsIsLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a shash onto a string
 */
static DSString* fsSlashify(DSString* p) {
    if ((Length(p)>0) && CharAt(p, 0) != fsSlash) 
        return Concatc(p, fsSlashString);    
    else return p;
}

static DSString* fsGetUserPath() {
    DSString* user = $(".");
    DSString* result = fsNormalize(user);
    return result;
}

static DSString* fsGetDrive(DSString* path) {
    int p1 = fsPrefixLength(path);
    return (p1 == 3) ? $(strndup(path->value, 2)) : nullptr;
}

static int fsDriveIndex(char d) {
    if ((d >= 'a') && (d <= 'z')) return d - 'a';
    if ((d >= 'A') && (d <= 'Z')) return d - 'A';
    return -1;
}

static DSString* fsGetDriveDirectory(char drive) {
    int i = fsDriveIndex(drive);
    if (i < 0) return nullptr;
    return nullptr;
    // string s = driveDirCache[i];
    // if (s != null) return s;
    // // s = getDriveDirectory(i + 1);
    // // driveDirCache[i] = s;
    // return s;
}


static char fsGetSeparator() {
    return fsSlash;
}

static char fsGetPathSeparator() {
    return fsSemicolon;
}

static int fsNormalizePrefix(DSString* path, int len, DSStringBuilder* sb) {
    int src = 0;
    while ((src < len) && fsIsSlash(path->value[src])) src++;
    char c = 0;
    if ((len - src >= 2)
        && fsIsLetter(c = path->value[src])
        && path->value[src+1] == ':') {
            Appendc(sb, c);
            Appendc(sb, ':');
            src += 2;
    } else {
        src = 0;
        if ((len >= 2)
            && fsIsSlash(path->value[0])
            && fsIsSlash(path->value[1])) {
            src = 1;
            Appendc(sb, c);
        }
    }
    return src;
}


/**
 * Normalize a chunk of the pathname
 */
static DSString* fsNormalize2(DSString* path, int len, int off) {
    if (len == 0) return path;
    if (off < 3) off = 0;
    int src;
    DSString* tmp;
    auto sb = new(DSStringBuilder);

    if (off == 0) {
        src = fsNormalizePrefix(path, len, sb);
    } else {
        src = off;
        Append(sb, strndup(path->value, off));

    }
    while (src < len) {
        char c = path->value[src++];
        if (fsIsSlash(c)) {
            while ((src < len) && fsIsSlash(path->value[src])) src++;
            if (src == len) {
                tmp = Concat(sb);
                int sn = Length(tmp);
                if ((sn == 2) && (tmp->value[1] == ':')) {
                    Appendc(sb, fsSlash);
                    break;
                }
                if (sn == 0) {
                    Appendc(sb, fsSlash);
                    break;
                }
                if ((sn == 1) && (fsIsSlash(tmp->value[0]))) {
                    Appendc(sb, fsSlash);
                    break;
                }
                break;
            } else {
                Appendc(sb, fsSlash);
            }
        } else {
            Appendc(sb, c);
        }
    }
    DSString* result = Concat(sb);
    return result;
}

/**
 * Normalize path
 */
static DSString* fsNormalize(DSString* path) {

    if (path->isa != getDSStringIsa()) return nullptr;


    int n = path->length;
    char fsSlash = fsSlash;
    char fsAltSlash = fsAltSlash;
    char prev = 0;

    for (int i = 0; i < n; i++) {
        char c = CharAt(path, i);
        if (c == fsAltSlash) 
            return fsNormalize2(path, n, (prev == fsSlash) ? i - 1 : i);
        if ((c == fsSlash) && (prev == fsSlash) && i > 1)
            return fsNormalize2(path, n, i - 1);
        if ((c == ':') && (i > 1))
            return fsNormalize2(path, n, 0);
        prev = c;
    }
    if (prev == fsSlash) return fsNormalize2(path, n, n - 1);
    return path;
}

static int fsPrefixLength(DSString* path) {
    char fsSlash = fsSlash;
    int n = path->length;
    if (n == 0) return 0;
    char c0 = path->value[0];
    char c1 = (n > 1) ? path->value[1] : 0;
    if (c0 == fsSlash) {
        if (c1 == fsSlash) return 2;
        return 1;
    }
    if (fsIsLetter(c0) && (c1 == ':')) {
        if ((n > 2) && (path->value[2] == fsSlash))
            return 3;
        return 2;
    }
    return 0;
}

static DSString* fsResolve(DSString* parent, DSString* child) {
    int pn = parent->length;
    if (pn == 0) return child;
    int cn = child->length;
    if (cn == 0) return parent;

    char fsSlash = fsSlash;

    DSString* c = child;
    int childStart = 0;
    int parentEnd = pn;

    if ((cn > 1) && (c->value[0] == fsSlash)) {
        if (c->value[1] == fsSlash) {
            childStart = 2;
        } else {
            childStart = 1;
        }
        if (cn == childStart) {
            if (parent->value[pn - 1] == fsSlash)
                return $(strndup(parent->value, pn-1));
            return parent;
        }
    }
    if (parent->value[pn - 1] == fsSlash)
        parentEnd--;

    int len = parentEnd + cn - childStart;
    char* theChars = nullptr;
    if (child->value[childStart] == fsSlash) {
        theChars = DSMalloc (len * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    } else {
        theChars = DSMalloc ((len+1) * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        theChars[parentEnd] = fsSlash;
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    }

    return $(theChars);
}

static DSString* fsGetDefaultParent() {
    return $(fsSlashString);
}

static DSString* fsFromURIPath(DSString* path) {
    int length = path->length;
    char* p, buf = strndup(path->value, length);
    if ((length > 2) && (p[2] == ':')) {
        p++;
        length--;
        if ((length > 3) && (p[length - 1] == '/'))
            length--;
    } else if ((length > 1) &&  (p[length - 1] == '/')) {
        length--;
    }
    p[length-1] = 0;
    DSString* result = $(p);
    return result;
}

static bool fsIsAbsolute(DSFile* f) {
    int p1 = GetPrefixLength(f);
    return  (((p1 == 2) && (GetPath(f)->value[0] == fsSlash))
            || p1 == 3);
}

static DSString* fsResolveFile(DSFile* f) {
    DSString* path = GetPath(f);
    int p1 = GetPrefixLength(f);
    if ((p1 == 2) && path->value[0] == fsSlash)
        return path;
    if (p1 == 3)
        return path;
    if (p1 == 0) {
        DSString* temp = fsGetUserPath();
        DSString* dir = fsSlashify(path);
        DSString* result = Concat(temp, dir);
        return result;
    }
    if (p1 == 1) {
        DSString* up = fsGetUserPath();
        DSString* ud = fsGetDrive(up);
        if (ud != nullptr) {
            DSString* result = Concat(ud, path);
            return result;
        }
    }
    if (p1 == 2) {
        DSString* up = fsGetUserPath();
        DSString* ud = fsGetDrive(up);
        if ((ud != nullptr) && StartsWith(path, ud, 0)) {
            DSString* temp = $(strndup(path->value, 2));
            DSString* dir = fsSlashify(temp);
            DSString* result = Concat(up, dir);
            return result;
        }
        char drive = path->value[0];
        DSString* dir = fsGetDriveDirectory(drive);
        DSString* temp = $(strndup(path->value, 2));
        DSStringBuilder* sb = new(DSStringBuilder);
        Appendc(sb, drive);
        Appendc(sb, ':');
        Append(sb, dir);
        Append(sb, temp);
        DSString* result = Concat(sb);
        return result;
    }
    return nullptr; //InternalIOErrorException("Unresolvable path: %s", path->value);
}

static DSString* fsCanonicalize(DSString* path) {

}
static int fsGetBooleanAttributes(DSFile* f) {

}
static bool fsCheckAccess(DSFile* f, int access) {

}
static bool fsSetPermission(DSFile* f, int access, bool enable, bool owneronly) {

}
static long fsGetLastModifiedTime(DSFile* f) {

}
static long fsGetLength(DSFile* f) {

}
static bool fsCreateFileExclusively(DSString* path) {

}
static bool fsDelete(DSFile* f) {

}
static DSString* fsList(DSFile* f) {

}
static bool fsCreateDirectory(DSFile* f) {

}
static bool fsRename(DSFile* f1, DSFile* f2) {

}
static bool fsSetLastModifiedTime(DSFile* f, long time) {

}
static DSString* fsSetReadOnly(DSFile* f) {

}
static DSFile* fsListRoots() {

}
static int fsCompare(DSFile* f1, DSFile* f2) {

}
static int fsHashCode(DSFile* f) {

}

void __attribute__((constructor())) FileSystemInit()
{
    fsSlash = '/';
    fsSemicolon = ';';
    fsAltSlash = (fsSlash == '\\') ? '/' : '\\';

    fsSlashString[0] = fsSlash;
    fsSlashString[1] = 0;

    fsSemicolonString[0] = fsSemicolon;
    fsSemicolonString[1] = 0;
    
    fsAltSlashString[0] = fsAltSlash;
    fsAltSlashString[1] = 0;

    DSFileSystem local = (struct DSFileSystem) 
    {
        .slash = fsSlash,
        .semicolon = fsSemicolon,
        .altSlash = fsAltSlash,
        .slashString = fsSlashString,
        .semicolonString = fsSemicolonString,
        .altSlashString = fsAltSlashString,
        .isSlash = fsIsSlash,
        .isLetter = fsIsLetter,
        .Slashify = fsSlashify,
        .GetUserPath = fsGetUserPath,
        .GetDrive = fsGetDrive,
        .DriveIndex = fsDriveIndex,
        .GetDriveDirectory = fsGetDriveDirectory,
        .GetSeparator = fsGetSeparator,
        .GetPathSeparator = fsGetPathSeparator,
        .NormalizePrefix = fsNormalizePrefix,
        .Normalize2 = fsNormalize2,
        .Normalize = fsNormalize,
        .PrefixLength = fsPrefixLength,
        .Resolve = fsResolve,
        .GetDefaultParent = fsGetDefaultParent,
        .FromURIPath = fsFromURIPath,
        .IsAbsolute = fsIsAbsolute,
        .ResolveFile = fsResolveFile,
        .Canonicalize = fsCanonicalize,
        .GetBooleanAttributes = fsGetBooleanAttributes,
        .CheckAccess = fsCheckAccess,
        .SetPermission = fsSetPermission,
        .GetLastModifiedTime = fsGetLastModifiedTime,
        .GetLength = fsGetLength,
        .CreateFileExclusively = fsCreateFileExclusively,
        .Delete = fsDelete,
        .List = fsList,
        .CreateDirectory = fsCreateDirectory,
        .Rename = fsRename,
        .SetLastModifiedTime = fsSetLastModifiedTime,
        .SetReadOnly = fsSetReadOnly,
        .ListRoots = fsListRoots,
        .Compare = fsCompare,
        .HashCode = fsHashCode
    };
    memcpy(&fs, &local, sizeof(DSFileSystem));
}

