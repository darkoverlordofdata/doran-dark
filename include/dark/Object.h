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
	const struct ObjectClass* isa;
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
    char*   (*ToString) (const struct Object *const);
    bool    (*Equals) (const struct Object *const, const struct Object *const);
    int     (*GetHashCode) (const struct Object *const);
    void    (*Dispose) (struct Object *const);
    bool    (*ReferenceEquals) (const struct Object *const, const struct Object *const);
    bool    (*InstanceEquals) (const struct Object *const, const struct Object *const);
    struct Object *(*Create) ();

};

static inline char* typename(id obj) { return obj->isa->name; }
static inline int typeid(id obj) { return (int)obj->isa; }


/**
 * Object API
 */
TClass GetClass(const struct Object *const);
char* GetClassName(const struct Object *const);
bool ReferenceEquals(const struct Object *const, const struct Object *const);
bool InstanceEquals(const struct Object *const, const struct Object *const);

const char* overload ToString(const struct Object *const);
bool overload Equals(const struct Object *const, const struct Object *const that);
int overload GetHashCode(const struct Object *const);
void overload Dispose(struct Object *const);

struct Object *Object_New();
struct Object *Object_Ctor(struct Object *const this);
struct Object *Object_Dtor();

#endif _OBJECT_H_ 
