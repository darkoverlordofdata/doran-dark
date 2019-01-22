#pragma once

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

static bool fsIsSlash(char c);
static bool fsIsLetter(char c);
static DSString* fsSlashify(DSString* p);
static DSString* fsGetUserPath();
static DSString* fsGetDrive(DSString* path);
static int fsDriveIndex(char d);
static DSString* fsGetDriveDirectory(char drive);
static char fsGetSeparator();
static char fsGetPathSeparator();
static int fsNormalizePrefix(DSString* path, int len, DSStringBuilder* sb);
static DSString* fsNormalize2(DSString* path, int len, int off);
static DSString* fsNormalize(DSString* path);
static int fsPrefixLength(DSString* path);
static DSString* fsResolve(DSString* parent, DSString* child);
static DSString* fsGetDefaultParent();
static DSString* fsFromURIPath(DSString* path);
static bool fsIsAbsolute(DSFile* f);
static DSString* fsResolveFile(DSFile* f);
static DSString* fsCanonicalize(DSString* path);
static int GetBooleanAttributes(DSFile* f);
static bool fsCheckAccess(DSFile* f, int access);
static bool fsSetPermission(DSFile* f, int access, bool enable, bool owneronly);
static long fsGetLastModifiedTime(DSFile* f);
static long fsGetLength(DSFile* f);
static bool fsCreateFileExclusively(DSString* path);
static bool fsDelete(DSFile* f);
static DSString** fsList(DSFile* f);
static bool fsCreateDirectory(DSFile* f);
static bool fsRename(DSFile* f1, DSFile* f2);
static bool fsSetLastModifiedTime(DSFile* f, long time);
static DSString* fsSetReadOnly(DSFile* f);
static DSFile** fsListRoots();
static int fsCompare(DSFile* f1, DSFile* f2);
static int fsHashCode(DSFile* f);

typedef struct DSFileSystem DSFileSystem;
const DSFileSystem fs;

struct DSFileSystem {
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
    const DSString* (*Slashify)(DSString* p);
    const DSString* (*GetUserPath)();
    const DSString* (*GetDrive)(DSString* path);
    const int (*DriveIndex)(char d);
    const DSString* (*GetDriveDirectory)(char drive);
    const char (*GetSeparator)();
    const char (*GetPathSeparator)();
    const int (*NormalizePrefix)(DSString* path, int len, DSStringBuilder* sb);
    const DSString* (*Normalize2)(DSString* path, int len, int off);
    const DSString* (*Normalize)(DSString* path);
    const int (*PrefixLength)(DSString* path);
    const DSString* (*Resolve)(DSString* parent, DSString* child);
    const DSString* (*GetDefaultParent)();
    const DSString* (*FromURIPath)(DSString* path);
    const bool (*IsAbsolute)(DSFile* f);
    const DSString* (*ResolveFile)(DSFile* f);
    const DSString* (*Canonicalize)(DSString* path);
    const int (*GetBooleanAttributes)(DSFile* f);
    const bool (*CheckAccess)(DSFile* f, int access);
    const bool (*SetPermission)(DSFile* f, int access, bool enable, bool owneronly);
    const long (*GetLastModifiedTime)(DSFile* f);
    const long (*GetLength)(DSFile* f);
    const bool (*CreateFileExclusively)(DSString* path);
    const bool (*Delete)(DSFile* f);
    const DSString** (*List)(DSFile* f);
    const bool (*CreateDirectory)(DSFile* f);
    const bool (*Rename)(DSFile* f1, DSFile* f2);
    const bool (*SetLastModifiedTime)(DSFile* f, long time);
    const DSString* (*SetReadOnly)(DSFile* f);
    const DSFile** (*ListRoots)();
    const int (*Compare)(DSFile* f1, DSFile* f2);
    const int (*HashCode)(DSFile* f);
};

