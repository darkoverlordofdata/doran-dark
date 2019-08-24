#pragma once

#include <stdio.h>
#include <sys/stat.h>
#include <dark/types.h>
#include <dark/io/file.h>

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

type (IOBuff) {
    char* buff;
    int len;
};

typedef struct File File;

method int GetPrefixLength(File* const self);
method String* GetPath(File* const self);

static inline bool fsIsSlash(char c);
static inline bool fsIsLetter(char c);
static inline String* fsSlashify(String* p);
static inline String* fsGetUserPath();
static inline String* fsGetDrive(String* path);
static inline int fsDriveIndex(char d);
static inline String* fsGetDriveDireCTORy(char drive);
static inline char fsGetSeparator();
static inline char fsGetPathSeparator();
static inline int fsNormalizePrefix(String* path, int len, StringBuilder* sb);
static inline String* fsNormalize2(String* path, int len, int off);
static inline String* fsNormalize(String* path);
static inline int fsPrefixLength(String* path);
static inline String* fsResolve(String* parent, String* child);
static inline String* fsGetDefaultParent();
static inline String* fsFromURIPath(String* path);
static inline bool fsIsAbsolute(File* f);
static inline String* fsResolveFile(File* f);
static inline String* fsCanonicalize(String* path);
static inline int GetBooleanAttributes(File* f);
static inline bool fsCheckAccess(File* f, int access);
static inline bool fsSetPermission(File* f, int access, bool enable, bool owneronly);
static inline long fsGetLastModifiedTime(File* f);
static inline long fsGetLength(File* f);
static inline bool fsCreateFileExclusively(String* path);
static inline bool fsDelete(File* f);
static inline String** fsList(File* f);
static inline bool fsCreateDireCTORy(File* f);
static inline bool fsRename(File* f1, File* f2);
static inline bool fsSetLastModifiedTime(File* f, long time);
static inline String* fsSetReadOnly(File* f);
static inline File** fsListRoots();
static inline int fsCompare(File* f1, File* f2);
static inline int fsHashCode(File* f);

typedef struct FileSystem FileSystem;
const FileSystem fs;

struct FileSystem {
    const char slash;
    const char semicolon;
    const char altSlash;
    const char* slashString;
    const char* semicolonString;
    const char* altSlashString;
    const bool UseCanonCaches;
    const bool UseCanonPrefixCache;
    const bool (*isSlash)(char c);
    const bool (*isLetter)(char c);
    const String* (*Slashify)(String* p);
    const String* (*GetUserPath)();
    const String* (*GetDrive)(String* path);
    const int (*DriveIndex)(char d);
    const String* (*GetDriveDireCTORy)(char drive);
    const char (*GetSeparator)();
    const char (*GetPathSeparator)();
    const int (*NormalizePrefix)(String* path, int len, StringBuilder* sb);
    const String* (*Normalize2)(String* path, int len, int off);
    const String* (*Normalize)(String* path);
    const int (*PrefixLength)(String* path);
    const String* (*Resolve)(String* parent, String* child);
    const String* (*GetDefaultParent)();
    const String* (*FromURIPath)(String* path);
    const bool (*IsAbsolute)(File* f);
    const String* (*ResolveFile)(File* f);
    const String* (*Canonicalize)(String* path);
    const int (*GetBooleanAttributes)(File* f);
    const bool (*CheckAccess)(File* f, int access);
    const bool (*SetPermission)(File* f, int access, bool enable, bool owneronly);
    const long (*GetLastModifiedTime)(File* f);
    const long (*GetLength)(File* f);
    const bool (*CreateFileExclusively)(String* path);
    const bool (*Delete)(File* f);
    const String** (*List)(File* f);
    const bool (*CreateDireCTORy)(File* f);
    const bool (*Rename)(File* f1, File* f2);
    const bool (*SetLastModifiedTime)(File* f, long time);
    const String* (*SetReadOnly)(File* f);
    const File** (*ListRoots)();
    const int (*Compare)(File* f1, File* f2);
    const int (*HashCode)(File* f);
};

static char fsSlash;
static char fsSemicolon;
static char fsAltSlash;
static char fsSlashString[2];
static char fsSemicolonString[2];
static char fsAltSlashString[2];

static inline bool fsIsSlash(char c) {
    return (c == '\\') || (c == '/');
}

static inline bool fsIsLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a shash onto a string
 */
static inline String* fsSlashify(String* p) {
    if ((Length(p)>0) && CharAt(p, 0) != fsSlash) 
        return Concatc(p, fsSlashString);    
    else return p;
}

static inline String* fsGetUserPath() {
    String* user = new(String, ".");
    String* result = fsNormalize(user);
    return result;
}

static inline String* fsGetDrive(String* path) {
    int p1 = fsPrefixLength(path);
    return (p1 == 3) ? new(String, strndup(path->value, 2)) : nullptr;
}

static inline int fsDriveIndex(char d) {
    if ((d >= 'a') && (d <= 'z')) return d - 'a';
    if ((d >= 'A') && (d <= 'Z')) return d - 'A';
    return -1;
}

static inline String* fsGetDriveDireCTORy(char drive) {
    int i = fsDriveIndex(drive);
    if (i < 0) return nullptr;
    return nullptr;
    // string s = driveDirCache[i];
    // if (s != null) return s;
    // // s = getDriveDireCTORy(i + 1);
    // // driveDirCache[i] = s;
    // return s;
}


static inline char fsGetSeparator() {
    return fsSlash;
}

static inline char fsGetPathSeparator() {
    return fsSemicolon;
}

static inline int fsNormalizePrefix(String* path, int len, StringBuilder* sb) {
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
static inline String* fsNormalize2(String* path, int len, int off) {
    if (len == 0) return path;
    if (off < 3) off = 0;
    int src;
    String* tmp;
    auto sb = new(StringBuilder);

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
    String* result = Concat(sb);
    return result;
}

/**
 * Normalize path
 */
static inline String* fsNormalize(String* path) {

    // if (path->isa != getStringIsa()) return nullptr;

    int n = path->length;
    char prev = 0;

    for (int i = 0; i < n; i++) {
        char c = CharAt(path, i);
        if (c == fsAltSlash) {
            return fsNormalize2(path, n, (prev == fsSlash) ? i - 1 : i);
        }
        if ((c == fsSlash) && (prev == fsSlash) && i > 1) {
            return fsNormalize2(path, n, i - 1);
        }
        if ((c == ':') && (i > 1)) {
            return fsNormalize2(path, n, 0);
        }
        prev = c;
    }
    if (prev == fsSlash) return fsNormalize2(path, n, n - 1);
    return path;
}

static inline int fsPrefixLength(String* path) {
    int n = path->length;
    if (n == 0) return 0;
    int c0 = CharAt(path, 0);
    int c1 = (n > 1) ? CharAt(path, 1) : 0;
    if (c0 == fsAltSlash) { // MSys2 : /c/Program Files/
        if ((n > 2) && CharAt(path, 2) == fsAltSlash) {
            return 3;
        }
        return 1;
    }
    if (c0 == fsSlash) {
        if (c1 == fsSlash) return 2;
        return 1;
    }
    if (fsIsLetter(c0) && (c1 == ':')) {
        if ((n > 2) && (CharAt(path, 2) == fsSlash))
            return 3;
        return 2;
    }
    return 0;
}

static inline String* fsResolve(String* parent, String* child) {
    int pn = parent->length;
    if (pn == 0) return child;
    int cn = child->length;
    if (cn == 0) return parent;

    String* c = child;
    int childStart = 0;
    int parentEnd = pn;

    if ((cn > 1) && (CharAt(c, 0) == fsSlash)) {
        if (CharAt(c, 1) == fsSlash) {
            childStart = 2;
        } else {
            childStart = 1;
        }
        if (cn == childStart) {
            if (CharAt(parent, pn - 1) == fsSlash)
                return new(String, strndup(parent->value, pn-1));
            return parent;
        }
    }
    if (CharAt(parent, pn - 1) == fsSlash)
        parentEnd--;

    int len = parentEnd + cn - childStart;
    char* theChars = nullptr;
    if (CharAt(child, childStart) == fsSlash) {
        theChars = DSmalloc (len * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    } else {
        theChars = DSmalloc ((len+1) * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        theChars[parentEnd] = fsSlash;
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    }

    return new(String, theChars);
}

static inline String* fsGetDefaultParent() {
    return new(String, fsSlashString);
}

static inline String* fsFromURIPath(String* path) {
    int length = path->length;
    char* p = strndup(path->value, length);
    if ((length > 2) && (p[2] == ':')) {
        p++;
        length--;
        if ((length > 3) && (p[length - 1] == '/'))
            length--;
    } else if ((length > 1) && (p[length - 1] == '/')) {
        length--;
    }
    p[length-1] = 0;
    String* result = new(String, p);
    return result;
}

static inline bool fsIsAbsolute(File* f) {
    int p1 = GetPrefixLength(f);
    return  (((p1 == 2) && (GetPath(f)->value[0] == fsSlash))
            || p1 == 3);
}

static inline String* fsResolveFile(File* f) {
    String* path = GetPath(f);
    int p1 = GetPrefixLength(f);
    if ((p1 == 2) && path->value[0] == fsSlash)
        return path;
    if (p1 == 3)
        return path;
    if (p1 == 0) {
        String* temp = fsGetUserPath();
        String* dir = fsSlashify(path);
        String* result = Concat(temp, dir);
        return result;
    }
    if (p1 == 1) {
        String* up = fsGetUserPath();
        String* ud = fsGetDrive(up);
        if (ud != nullptr) {
            String* result = Concat(ud, path);
            return result;
        }
    }
    if (p1 == 2) {
        String* up = fsGetUserPath();
        String* ud = fsGetDrive(up);
        if ((ud != nullptr) && StartsWith(path, ud, 0)) {
            String* temp = new(String, strndup(path->value, 2));
            String* dir = fsSlashify(temp);
            String* result = Concat(up, dir);
            return result;
        }
        char drive = path->value[0];
        String* dir = fsGetDriveDireCTORy(drive);
        String* temp = new(String, strndup(path->value, 2));
        StringBuilder* sb = new(StringBuilder);
        Appendc(sb, drive);
        Appendc(sb, ':');
        Append(sb, dir);
        Append(sb, temp);
        String* result = Concat(sb);
        return result;
    }
    return nullptr; //InternalIOErrorException("Unresolvable path: %s", path->value);
}

static inline String* fsCanonicalize(String* path) {
    int len = Length(path);
    if (len == 2) {
        if (fsIsLetter(CharAt(path, 0)) &&
        (CharAt(path, 1) == ':')) {

            char c = CharAt(path, 0);
            if ((c >= 'A') && (c <= 'Z'))
                return path;
            char p[2] = { CharAt(path, 0)-32, 0 };
            return new(String, join(p, &path->value[1]));

        } else if ((len == 3) &&
        (fsIsLetter(CharAt(path, 0))) &&
        (CharAt(path, 1) == ':') &&
        (CharAt(path, 2) == '\\')) {

            char c = ChatAt(path, 0);
            if ((c >= 'A') && (c <= 'Z'))
                return path;
            char p[2] = { CharAt(path, 0)-32, 0 };
            return new(String, join(p, &path->value[1]));
        }
    }
    if (!fs.UseCanonCaches) {
        return path;
    } else {
        return path;
    }

}

static inline int fsGetBooleanAttributes(File* f) {
    struct stat sbuf;
    if (stat(ToString(GetPath(f)), &sbuf) < 0) return 0;
    return sbuf.st_mode;
}

static inline bool fsCheckAccess(File* f, int access) {
    struct stat sbuf;
    if (stat(ToString(GetPath(f)), &sbuf) < 0) return 0;
    return ((sbuf.st_size & access) != 0);
}

static inline bool fsSetPermission(File* f, int access, bool enable, bool owneronly) {

}

static inline long fsGetLastModifiedTime(File* f) {

}

static inline long fsGetLength(File* f) {
    struct stat sbuf;
    if (stat(ToString(GetPath(f)), &sbuf) < 0) return 0;
    return sbuf.st_size;
}

static inline bool fsCreateFileExclusively(String* path) {

}

static inline bool fsDelete(File* f) {

}

static inline String** fsList(File* f) {

}

static inline bool fsCreateDireCTORy(File* f) {

}

static inline bool fsRename(File* f1, File* f2) {

}

static inline bool fsSetLastModifiedTime(File* f, long time) {

}

static inline String* fsSetReadOnly(File* f) {

}

static inline File** fsListRoots() {

}

static inline int fsCompare(File* f1, File* f2) {
    return CompareTo(GetPath(f1), GetPath(f2));
    return 0;
}

static inline int fsHashCode(File* f) {

}

// void __attribute__((construCTOR())) 

static inline void FileSystemInit()
{
    fsSlash = '\\';
    fsSemicolon = ';';
    fsAltSlash = (fsSlash == '\\') ? '/' : '\\';

    fsSlashString[0] = fsSlash;
    fsSlashString[1] = 0;

    fsSemicolonString[0] = fsSemicolon;
    fsSemicolonString[1] = 0;
    
    fsAltSlashString[0] = fsAltSlash;
    fsAltSlashString[1] = 0;


    FileSystem local = (struct FileSystem) 
    {
        .slash = fsSlash,
        .semicolon = fsSemicolon,
        .altSlash = fsAltSlash,
        .slashString = fsSlashString,
        .semicolonString = fsSemicolonString,
        .altSlashString = fsAltSlashString,
        .isSlash = fsIsSlash,
        .isLetter = fsIsLetter,
        .UseCanonCaches = false,
        .UseCanonPrefixCache = false,
        .Slashify = fsSlashify,
        .GetUserPath = fsGetUserPath,
        .GetDrive = fsGetDrive,
        .DriveIndex = fsDriveIndex,
        .GetDriveDireCTORy = fsGetDriveDireCTORy,
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
        .CreateDireCTORy = fsCreateDireCTORy,
        .Rename = fsRename,
        .SetLastModifiedTime = fsSetLastModifiedTime,
        .SetReadOnly = fsSetReadOnly,
        .ListRoots = fsListRoots,
        .Compare = fsCompare,
        .HashCode = fsHashCode
    };
    memcpy(&fs, &local, sizeof(FileSystem));
}

