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
#include <dark/io/FileSystem.h>
/* 
 * FileSystem implementation
 */
static Exception(InternalIOError);


static bool isSlash(char c) {
    return (c == '\\') || (c == '/');
}

static bool isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

/**
 * prepend a shash onto a string
 */
String FileSystem_Slashify(FileSystem const this, String p) {
    if ((p->Length(p)>0) && p->CharAt(p, 0) != this->slash) 
        return p->Concatc(p, this->slashString);    
    else return p;
}

String FileSystem_GetUserPath(FileSystem const this) {
    String user = String_New(".");
    String result = this->Normalize(this, user);
    return result;
}

String FileSystem_GetDrive(FileSystem const this, String path) {
    int p1 = this->PrefixLength(this, path);
    return (p1 == 3) ? String_New(strndup(path->value, 2)) : nullptr;
}

int FileSystem_DriveIndex(FileSystem const this, char d) {
    if ((d >= 'a') && (d <= 'z')) return d - 'a';
    if ((d >= 'A') && (d <= 'Z')) return d - 'A';
    return -1;
}

String FileSystem_GetDriveDirectory(FileSystem const this, char drive) {
    int i = this->DriveIndex(this, drive);
    if (i < 0) return nullptr;
    return nullptr;
    // string s = driveDirCache[i];
    // if (s != null) return s;
    // // s = getDriveDirectory(i + 1);
    // // driveDirCache[i] = s;
    // return s;
}

char* FileSystem_ToString(FileSystem const this){
    return "dark.io.FileSystem";
}


char FileSystem_GetSeparator(FileSystem const this) {
    return this->slash;
}

char FileSystem_GetPathSeparator(FileSystem const this) {
    return this->semicolon;
}

static int NormalizePrefix(FileSystem const this, String path, int len, StringBuilder sb) {
    int src = 0;
    while ((src < len) && isSlash(path->value[src])) src++;
    char c = 0;
    if ((len - src >= 2)
        && isLetter(c = path->value[src])
        && path->value[src+1] == ':') {
            sb->Appendc(sb, c);
            sb->Appendc(sb, ':');
            src += 2;
    } else {
        src = 0;
        if ((len >= 2)
            && isSlash(path->value[0])
            && isSlash(path->value[1])) {
            src = 1;
            sb->Appendc(sb, c);
        }
    }
    return src;
}


/**
 * Normalize a chunk of the pathname
 */
static String Normalize2(FileSystem const this, String path, int len, int off) {
    if (len == 0) return path;
    if (off < 3) off = 0;
    int src;
    // char slash = this->slash;
    String tmp;
    StringBuilder sb = StringBuilder_New();

    if (off == 0) {
        src = NormalizePrefix(this, path, len, sb);
    } else {
        src = off;
        sb->Append(sb, strndup(path->value, off));

    }
    while (src < len) {
        char c = path->value[src++];
        if (isSlash(c)) {
            while ((src < len) && isSlash(path->value[src])) src++;
            if (src == len) {
                tmp = sb->Concat(sb);
                int sn = sb->length;
                if ((sn == 2) && (tmp->value[1] == ':')) {
                    sb->Appendc(sb, this->slash);
                    break;
                }
                if (sn == 0) {
                    sb->Appendc(sb, this->slash);
                    break;
                }
                if ((sn == 1) && (isSlash(tmp->value[0]))) {
                    sb->Appendc(sb, this->slash);
                    break;
                }
                break;
            } else {
                sb->Appendc(sb, this->slash);
            }
        } else {
            sb->Appendc(sb, c);
        }
    }
    String result = sb->Concat(sb);
    return result;
}

/**
 * Normalize path
 */
String FileSystem_Normalize(FileSystem const this, String path) {
    int n = path->length;
    char slash = this->slash;
    char altSlash = this->altSlash;
    char prev = 0;

    for (int i = 0; i < n; i++) {
        char c = path->CharAt(path, i);
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

int FileSystem_PrefixLength(FileSystem const this, String path) {
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

String FileSystem_Resolve(FileSystem const this, String parent, String child) {
    int pn = parent->length;
    if (pn == 0) return child;
    int cn = child->length;
    if (cn == 0) return parent;

    char slash = this->slash;

    String c = child;
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
                return String_New(strndup(parent->value, pn-1));
            return parent;
        }
    }

    if (parent->value[pn - 1] == slash)
        parentEnd--;

    int len = parentEnd - cn - childStart;
    char* theChars = nullptr;
    if (child->value[childStart] == slash) {
        theChars = darko_malloc (len * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        memcpy(theChars+parentEnd, child->value+childStart, cn);
    } else {
        theChars = darko_malloc ((len+1) * sizeof(char));
        memcpy(theChars, parent->value, parentEnd);
        theChars[parentEnd] = slash;
        memcpy(theChars+parentEnd+1, child->value+childStart, cn);
    }
    return String_New(theChars);
}

String FileSystem_GetDefaultParent(FileSystem const this) {
    return String_New(this->slashString);
}

String FileSystem_FromURIPath(FileSystem const this, String path) {
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
    String result = String_New(p);
    return result;
}

bool FileSystem_IsAbsolute(FileSystem const this, File f) {
    int p1 = f->GetPrefixLength(f);
    return  (((p1 == 2) && (f->GetPath(f)->value[0] == this->slash))
            || p1 == 3);
}

String FileSystem_ResolveFile(FileSystem const this, File f) {
    String path = f->GetPath(f);
    int p1 = f->GetPrefixLength(f);
    if ((p1 == 2) && path->value[0] == this->slash)
        return path;
    if (p1 == 3)
        return path;
    if (p1 == 0) {
        String temp = this->GetUserPath(this);
        String dir = this->Slashify(this, path);
        String result = temp->Concat(this, dir);
        #ifdef __ARC__
        DObject_Release(path);
        DObject_Release(temp);
        DObject_Release(dir);
        #endif
        return result;
    }
    if (p1 == 1) {
        String up = this->GetUserPath(this);
        String ud = this->GetDrive(this, up);
        if (ud != nullptr) {
            String result = ud->Concat(ud, path);
            #ifdef __ARC__
            DObject_Release(path);
            DObject_Release(up);
            DObject_Release(ud);
            #endif
            return result;
        }
    }
    if (p1 == 2) {
        String up = this->GetUserPath(this);
        String ud = this->GetDrive(this, up);
        if ((ud != nullptr) && path->StartsWith(path, ud, 0)) {
            String temp = String_New(strndup(path->value, 2));
            String dir = this->Slashify(this, temp);
            String result = up->Concat(up, dir);
            #ifdef __ARC__
            DObject_Release(path);
            DObject_Release(temp);
            DObject_Release(dir);
            DObject_Release(up);
            DObject_Release(ud);
            #endif
            return result;
        }
        char drive = path->value[0];
        String dir = this->GetDriveDirectory(this, drive);
        String temp = String_New(strndup(path->value, 2));
        StringBuilder sb = StringBuilder_New();
        sb->Appendc(sb, drive);
        sb->Appendc(sb, ':');
        sb->Append(sb, dir);
        sb->Append(sb, temp);
        String result = sb->Concat(sb);
        #ifdef __ARC__
        DObject_Release(path);
        DObject_Release(temp);
        DObject_Release(dir);
        DObject_Release(up);
        DObject_Release(ud);
        DObject_Release(sb);
        #endif
        return result;
    }
    return InternalIOErrorException("Unresolvable path: %s", path->value);
}

String FileSystem_Canonicalize(FileSystem const this, String path) {

}
int FileSystem_GetBooleanAttributes(FileSystem const this, File f) {

}
bool FileSystem_CheckAccess(FileSystem const this, File f, int access) {

}
bool FileSystem_SetPermission(FileSystem const this, File f, int access, bool enable, bool owneronly) {

}
long FileSystem_GetLastModifiedTime(FileSystem const this, File f) {

}
long FileSystem_GetLength(FileSystem const this, File f) {

}
bool FileSystem_CreateFileExclusively(FileSystem const this, String path) {

}
bool FileSystem_Delete(FileSystem const this, File f) {

}
String* FileSystem_List(FileSystem const this, File f) {

}
bool FileSystem_CreateDirectory(FileSystem const this, File f) {

}
bool FileSystem_Rename(FileSystem const this, File f1, File f2) {

}
bool FileSystem_SetLastModifiedTime(FileSystem const this, File f, long time) {

}
String* FileSystem_SetReadOnly(FileSystem const this, File f) {

}
File* FileSystem_ListRoots(FileSystem const this) {

}
int FileSystem_Compare(FileSystem const this, File f1, File f2) {

}
int FileSystem_HashCode(FileSystem const this, File f) {

}

/**
 * Initialize a new FileSystem
 */
FileSystem FileSystem_init(FileSystem const this)
{
    DObject_init(this);

    this->ToString = FileSystem_ToString;

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
 * new FileSystem
 * 
 * 
 */
FileSystem FileSystem_New()
{
    return FileSystem_init(class_alloc(FileSystem));
}

