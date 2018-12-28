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

#define IsDSObject(x) (x->isa == &DSObjectClass)
#define AsDSObject(x) (IsDSObject(x) ? (DSObject *)x : nullptr)


/**
 * Object class
 */
class (DSObject) {
	const struct DSObjectClass* isa;
};


typedef DSObject id;


/**
 * Object metaclass
 */
struct DSObjectClass {
    union {
        struct Class base; 
        struct 
        {
            Class*  isa;
            Class*  superclass;
            char*   name;
        };
    };
    char*   (*ToString) (const DSObject* const);
    bool    (*Equals) (const DSObject* const, const DSObject* const);
    int     (*GetHashCode) (const DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (const DSObject* const, const DSObject* const);
    bool    (*InstanceEquals) (const DSObject* const, const DSObject* const);
    DSObject* (*Create) ();

} DSObjectClass;

static inline char* typename(id* obj) { return obj->isa->name; }
static inline int typeid(id* obj) { return (int)obj->isa; }


/**
 * Object API
 */
Class* GetClass(const DSObject* const);
char* GetClassName(const DSObject* const);
bool ReferenceEquals(const DSObject* const, const DSObject* const);
bool InstanceEquals(const DSObject* const, const DSObject* const);
static bool Virtual_Equals(DSObject* const, DSObject* const);

const char* overload ToString(const DSObject* const);
bool overload Equals(const DSObject* const, const DSObject* const);
int overload GetHashCode(const DSObject* const);
void overload Dispose(DSObject* const);


DSObject* DSObject_Ctor(DSObject* const);
DSObject* DSObject_Dtor(DSObject*);


#endif _OBJECT_H_ 
