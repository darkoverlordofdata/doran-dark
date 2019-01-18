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
#include <dark/io/DSFileSystem.h>
#include "private/DSFileSystem.h"
/* 
 * DSFileSystem implementation
 */

static bool isSlash(char c) {
    return (c == '\\') || (c == '/');
}

static bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a shash onto a string
 */
DSString* overload Slashify(DSFileSystem* const this, DSString* p) {
    if ((Length(p)>0) && CharAt(p, 0) != this->slash) 
        return Concatc(p, this->slashString);    
    else return p;
}

DSString* overload GetUserPath(DSFileSystem* const this) {
    DSString* user = $(".");
    DSString* result = Normalize(this, user);
    return result;
}

DSString* overload GetDrive(DSFileSystem* const this, DSString* path) {
    int p1 = PrefixLength(this, path);
    return (p1 == 3) ? $(strndup(path->value, 2)) : nullptr;
}

int overload DriveIndex(DSFileSystem* const this, char d) {
    if ((d >= 'a') && (d <= 'z')) return d - 'a';
    if ((d >= 'A') && (d <= 'Z')) return d - 'A';
    return -1;
}

DSString* overload GetDriveDirectory(DSFileSystem* const this, char drive) {
    int i = DriveIndex(this, drive);
    if (i < 0) return nullptr;
    return nullptr;
    // string s = driveDirCache[i];
    // if (s != null) return s;
    // // s = getDriveDirectory(i + 1);
    // // driveDirCache[i] = s;
    // return s;
}

char* overload ToString(DSFileSystem* const this){
    return "dark.io.DSFileSystem";
}


char overload GetSeparator(DSFileSystem* const this) {
    return this->slash;
}

char overload GetPathSeparator(DSFileSystem* const this) {
    return this->semicolon;
}

static int NormalizePrefix(DSFileSystem* const this, DSString* path, int len, DSStringBuilder* sb) {
    int src = 0;
    while ((src < len) && isSlash(path->value[src])) src++;
    char c = 0;
    if ((len - src >= 2)
        && isLetter(c = path->value[src])
        && path->value[src+1] == ':') {
            Appendc(sb, c);
            Appendc(sb, ':');
            src += 2;
    } else {
        src = 0;
        if ((len >= 2)
            && isSlash(path->value[0])
            && isSlash(path->value[1])) {
            src = 1;
            Appendc(sb, c);
        }
    }
    return src;
}


/**
 * Normalize a chunk of the pathname
 */
static DSString* Normalize2(DSFileSystem* const this, DSString* path, int len, int off) {
    if (len == 0) return path;
    if (off < 3) off = 0;
    int src;
    // char slash = this->slash;
    DSString* tmp;
    auto sb = new(DSStringBuilder);

    if (off == 0) {
        src = NormalizePrefix(this, path, len, sb);
    } else {
        src = off;
        Append(sb, strndup(path->value, off));

    }
    while (src < len) {
        char c = path->value[src++];
        if (isSlash(c)) {
            while ((src < len) && isSlash(path->value[src])) src++;
            if (src == len) {
                tmp = Concat(sb);
                int sn = Length(tmp);
                if ((sn == 2) && (tmp->value[1] == ':')) {
                    Appendc(sb, this->slash);
                    break;
                }
                if (sn == 0) {
                    Appendc(sb, this->slash);
                    break;
                }
                if ((sn == 1) && (isSlash(tmp->value[0]))) {
                    Appendc(sb, this->slash);
                    break;
                }
                break;
            } else {
                Appendc(sb, this->slash);
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
DSString* overload Normalize(DSFileSystem* const this, DSString* path) {
    int n = path->length;
    char slash = this->slash;
    char altSlash = this->altSlash;
    char prev = 0;

    for (int i = 0; i < n; i++) {
        char c = CharAt(path, i);
        if (c == altSlash) 
            return Normalize2(this, path, n, (prev == slash) ? i - 1 : i);
        if ((c == slash) && (prev == slash) && i > 1)
            return Normalize2(this, path, n, i - 1);
        if ((c == ':') && (i > 1))
            return Normalize2(this, path, n, 0);
        prev = c;
    }
    if (prev == slash) return Normalize2(this, path, n, n - 1);
    return path;
}

int overload PrefixLength(DSFileSystem* const this, DSString* path) {
    char slash = this->slash;
    int n = path->length;
    if (n == 0) return 0;
    char c0 = path->value[0];
    char c1 = (n > 1) ? path->value[1] : 0;
    if (c0 == slash) {
        if (c1 == slash) return 2;
        return 1;
    }
    if (isLetter(c0) && (c1 == ':')) {
        if ((n > 2) && (path->value[2] == slash))
            return 3;
        return 2;
    }
    return 0;
}

DSString* overload Resolve(DSFileSystem* const this, DSString* parent, DSString* child) {
    int pn = parent->length;
    if (pn == 0) return child;
    int cn = child->length;
    if (cn == 0) return parent;

    char slash = this->slash;

    DSString* c = child;
    int childStart = 0;
    int parentEnd = pn;

    if ((cn > 1) && (c->value[0] == slash)) {
        if (c->value[1] == slash) {
            childStart = 2;
        } else {
            childStart = 1;
        }
        if (cn == childStart) {
            if (parent->value[pn - 1] == slash)
                return $(strndup(parent->value, pn-1));
            return parent;
        }
    }

    if (parent->value[pn - 1] == slash)
        parentEnd--;

    int len = parentEnd - cn - childStart;
    char* theChars = nullptr;
    if (child->value[childStart] == slash) {
        theChars = DSMalloc (len * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    } else {
        theChars = DSMalloc ((len+1) * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        theChars[parentEnd] = slash;
        memcpy(theChars+parentEnd+1, child->value+childStart, cn);
    }
    return $(theChars);
}

DSString* overload GetDefaultParent(DSFileSystem* const this) {
    return $(this->slashString);
}

DSString* overload FromURIPath(DSFileSystem* const this, DSString* path) {
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

bool overload IsAbsolute(DSFileSystem* const this, DSFile* f) {
    int p1 = GetPrefixLength(f);
    return  (((p1 == 2) && (GetPath(f)->value[0] == this->slash))
            || p1 == 3);
}

DSString* overload ResolveFile(DSFileSystem* const this, DSFile* f) {
    DSString* path = GetPath(f);
    int p1 = GetPrefixLength(f);
    if ((p1 == 2) && path->value[0] == this->slash)
        return path;
    if (p1 == 3)
        return path;
    if (p1 == 0) {
        DSString* temp = GetUserPath(this);
        DSString* dir = Slashify(this, path);
        DSString* result = Concat(temp, dir);
        return result;
    }
    if (p1 == 1) {
        DSString* up = GetUserPath(this);
        DSString* ud = GetDrive(this, up);
        if (ud != nullptr) {
            DSString* result = Concat(ud, path);
            return result;
        }
    }
    if (p1 == 2) {
        DSString* up = GetUserPath(this);
        DSString* ud = GetDrive(this, up);
        if ((ud != nullptr) && StartsWith(path, ud, 0)) {
            DSString* temp = $(strndup(path->value, 2));
            DSString* dir = Slashify(this, temp);
            DSString* result = Concat(up, dir);
            return result;
        }
        char drive = path->value[0];
        DSString* dir = GetDriveDirectory(this, drive);
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

DSString* overload Canonicalize(DSFileSystem* const this, DSString* path) {

}
int overload GetBooleanAttributes(DSFileSystem* const this, DSFile* f) {

}
bool overload CheckAccess(DSFileSystem* const this, DSFile* f, int access) {

}
bool overload SetPermission(DSFileSystem* const this, DSFile* f, int access, bool enable, bool owneronly) {

}
long overload GetLastModifiedTime(DSFileSystem* const this, DSFile* f) {

}
long overload GetLength(DSFileSystem* const this, DSFile* f) {

}
bool overload CreateFileExclusively(DSFileSystem* const this, DSString* path) {

}
bool overload Delete(DSFileSystem* const this, DSFile* f) {

}
DSString* overload List(DSFileSystem* const this, DSFile* f) {

}
bool overload CreateDirectory(DSFileSystem* const this, DSFile* f) {

}
bool overload Rename(DSFileSystem* const this, DSFile* f1, DSFile* f2) {

}
bool overload SetLastModifiedTime(DSFileSystem* const this, DSFile* f, long time) {

}
DSString* overload SetReadOnly(DSFileSystem* const this, DSFile* f) {

}
DSFile* overload ListRoots(DSFileSystem* const this) {

}
int overload Compare(DSFileSystem* const this, DSFile* f1, DSFile* f2) {

}
int overload HashCode(DSFileSystem* const this, DSFile* f) {

}

/**
 * Initialize a new DSFileSystem
 */
DSFileSystem* DSFileSystem_init(DSFileSystem* this)
{
    DSObject_init(this);

    this->slash = '/';
    this->semicolon = ';';
    this->altSlash = (this->slash == '\\') ? '/' : '\\';

    char slash_string[2] = { this->slash, 0 };
    char semi_colon_string[2] = { this->semicolon, 0 };
    char alt_slash_string[2] = { this->altSlash, 0 };
    
    this->slashString = strdup(slash_string);
    this->semicolonString = strdup(semi_colon_string);
    this->altSlashString = strdup(alt_slash_string);

    return this;
}

/**
 * new DSFileSystem
 * 
 * 
 */
DSFileSystem* NewDSFileSystem()
{
    return DSFileSystem_init(alloc(DSFileSystem));
}

