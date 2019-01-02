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
#ifndef _DSOBJECT_H_
#define _DSOBJECT_H_
#include "DSClass.h"

#define OBJECT_TYPE       (TYPE_OBJECT)

#define IsDSObject(x) (x->isa == &DSObjectClass)
#define AsDSObject(x) (IsDSObject(x) ? (DSObject *)x : nullptr)

/**
 * Object 
 * 
 * the isa field holds the reference to the class that defines this object.
 * All fields afer that make up the IVAR. This means:
 * 
 *  + No multiple inheritance. Mixins should work.
 *  + ivar definition must be the same across an inheritance chain.
 * 
 */
typedef struct DSObject {
	const struct DSObjectClass* isa;
} DSObject;

/**
 * Object Class/MetaClass
 * 
 * This is defined as a singleton.
 * the isa field is a reference to itself.
 * the superclass points to the superclass singleton.
 * 
 * This holds the vtable and class IVAR. Again, these must be
 * kept the same down an entire inheritance chain.
 */
struct DSObjectClass 
{
    Class   isa;
    Class   superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (const DSObject* const);
    bool    (*Equals) (const DSObject* const, const DSObject* const);
    int     (*GetHashCode) (const DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (const DSObject* const, const DSObject* const);
    bool    (*InstanceEquals) (const DSObject* const, const DSObject* const);
    DSObject* (*Create) ();

} DSObjectClass;

/**
 * Object API
 */
Class GetClass(const DSObject* const);
char* GetClassName(const DSObject* const);
bool ReferenceEquals(const DSObject* const, const DSObject* const);
bool InstanceEquals(const DSObject* const, const DSObject* const);
bool DSObject_Equals(DSObject* const, DSObject* const);
void DSObject_Dispose(DSObject* const);
const char *DSObject_ToString(const DSObject* const);
int DSObject_GetHashCode(const DSObject* const);

const char* overload ToString(const DSObject* const);
bool overload Equals(const DSObject* const, const DSObject* const);
int overload GetHashCode(const DSObject* const);
void overload Dispose(DSObject* const);


DSObject* DSObject_init(DSObject* const);
DSObject* DSObject_Dtor(DSObject*);

Class DSDefineDSObject();

#endif _DSOBJECT_H_ 
