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

DSObject* DSObject_init(DSObject* const);
DSObject* DSObject_Dtor(DSObject*);

method (DSObject, ToString,         char*,  (const DSObject* const) );
method (DSObject, Equals,           bool,   (const DSObject* const, const DSObject* const) );
method (DSObject, GetHashCode,      int,    (const DSObject* const) );
method (DSObject, Dispose,          void,   (DSObject* const) );
method (DSObject, ReferenceEquals,  bool,   (const DSObject* const, const DSObject* const) );
method (DSObject, InstanceEquals,   bool,   (const DSObject* const, const DSObject* const) );
method (DSObject, GetClass,         Class,  (const DSObject* const) );
method (DSObject, GetClassName,     char*,  (const DSObject* const) );

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
class (DSObject) {
    DSObject* Empty;
    DSObjectReferenceEquals ReferenceEquals;
    DSObjectInstanceEquals  InstanceEquals;
};

//=======================================================================//
//              Which came first, the Class or the Object?               //          
//=======================================================================//
typedef char*   (*DSClassToString)  (const DSClass* const);
typedef bool    (*DSClassEquals) (const DSClass* const, const DSClass* const);
typedef int     (*DSClassGetHashCode) (const DSClass* const);
typedef void    (*DSClassDispose) (DSClass* const);

vtable (DSClass) {
    DSClassToString        ToString;
    DSClassEquals          Equals;
    DSClassGetHashCode     GetHashCode;
    DSClassDispose         Dispose;
};

#endif _DSOBJECT_H_ 
