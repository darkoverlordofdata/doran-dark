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


#define IsDSClass(object) _Generic((object), DSClass*: true, default: false)
#define AsDSClass(object) _Generic((object),                            \
                            DSClass*: (DSClass *)object,                \
                            default: nullptr)

/**
 * DSObject ivar
 */
ivar (DSObject) {
    Class isa;
};
ivar (DSClass) {
    Class isa;
};

DSObject* NewDSObject();
DSObject* DSObject_init(DSObject* const);
DSObject* DSObject_Dtor(DSObject*);

const char* overload ToString(const DSObject* const);
bool overload Equals(const DSObject* const, const DSObject* const);
int overload GetHashCode(const DSObject* const);
void overload Dispose(DSObject* const);
bool ReferenceEquals(const DSObject* const, const DSObject* const);
bool InstanceEquals(const DSObject* const, const DSObject* const);

bool DSObject_Equals(DSObject* const, DSObject* const);
void DSObject_Dispose(DSObject* const);
const char *DSObject_ToString(const DSObject* const);
int DSObject_GetHashCode(const DSObject* const);

/**
 * API Function Templates
 */
Class GetClass(const DSObject* const);
char* GetClassName(const DSObject* const);

/** 
 * DSObject Interface
 */
typedef DSObject* (*DSObjectCreate) ();
typedef char*   (*DSObjectToString)     (const DSObject* const);
typedef bool    (*DSObjectEquals)       (const DSObject* const, const DSObject* const);
typedef int     (*DSObjectGetHashCode)  (const DSObject* const);
typedef void    (*DSObjectDispose)      (DSObject* const);
typedef bool    (*DSObjectReferenceEquals)  (const DSObject* const, const DSObject* const);
typedef bool    (*DSObjectInstanceEquals)   (const DSObject* const, const DSObject* const);
/**
 * DSObject Vtable
 * 
 */
vtable (DSObject) {
    const DSObjectToString        ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
};


/**
 * DSObject Class Methods & Variables
 * 
 */
// struct $DSObject $DSObject;
// struct $DSObject {
class (DSObject) {
    DSObject* Empty;
    DSObjectCreate          Create;
    DSObjectReferenceEquals ReferenceEquals;
    DSObjectInstanceEquals  InstanceEquals;
};

//=======================================================================//
//              Which came first, the Class or the Object?               //          
//=======================================================================//

/**
 * Class ivar
 * 
 */
// ivar (DSClass) {
//     Class isa;
// };
/** 
 * DSClass Interface
 */
typedef DSClass* (*DSClassCreate) ();
typedef char*   (*DSClassToString)  (const DSClass* const);
typedef bool    (*DSClassEquals) (const DSClass* const, const DSClass* const);
typedef int     (*DSClassGetHashCode) (const DSClass* const);
typedef void    (*DSClassDispose) (DSClass* const);
typedef bool    (*DSClassReferenceEquals) (const DSClass* const, const DSClass* const);
typedef bool    (*DSClassInstanceEquals) (const DSClass* const, const DSClass* const);
/**
 * DSClass vtable
 */
vtable (DSClass) {
    DSClassToString        ToString;
    DSClassEquals          Equals;
    DSClassGetHashCode     GetHashCode;
    DSClassDispose         Dispose;
};




#endif _DSOBJECT_H_ 
