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
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Class.h"

#define OBJECT_TYPE       (TYPE_OBJECT)

/**
 * Object class
 */
struct Object;
struct ObjectClass;
struct Class* IsaObject();
typedef struct Object* TObject;
extern struct ObjectClass Object;
struct Object {
// class (Object) {
	struct ObjectClass* isa;
};

typedef struct Object* id;

/**
 * Object metaclass
 */
struct ObjectClass {
    union {
        struct Class base;
        struct 
        {
            struct Class * isa;
            struct Class * superclass;
            char* name;
        };
    };
    char*   (*ToString) (TObject const);
    bool    (*Equals) (TObject const, TObject const);
    int     (*GetHashCode) (TObject const);
    void    (*Dispose) (TObject const);
    bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
    bool    (*InstanceEquals) (TObject const objA, TObject const objB);
    TObject (*Create) ();

};

static inline char* typename(id obj) { return obj->isa->name; }
static inline int typeid(id obj) { return (int)obj->isa; }


/**
 * Object API
 */
TClass GetClass(TObject const);
char* GetClassName(TObject const);
bool ReferenceEquals(TObject const objA, TObject const objB);
bool InstanceEquals(TObject const objA, TObject const objB);

const char* overload ToString(TObject const);
bool overload Equals(TObject const, TObject const that);
int overload GetHashCode(TObject const);
void overload Dispose(TObject const);

TObject Object_New();
TObject Object_Ctor(TObject const this);
TObject Object_Dtor();

#endif _OBJECT_H_ 
