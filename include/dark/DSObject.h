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
#include "DSLog.h"

#define OBJECT_TYPE       (TYPE_OBJECT)


#define IsDSClass(object) _Generic((object), DSClass*: true, default: false)
#define AsDSClass(object) _Generic((object),                            \
                            DSClass*: (DSClass *)object,                \
                            default: nullptr)

/**
 * DSObject ivar
 */
IVAR (DSObject) {
    Class isa;
};

METHOD (DSObject, ToString,         char*,  (const DSObject* const) );
METHOD (DSObject, Equals,           bool,   (const DSObject* const, const DSObject* const) );
METHOD (DSObject, GetHashCode,      int,    (const DSObject* const) );
METHOD (DSObject, Dispose,          void,   (DSObject* const) );
METHOD (DSObject, ReferenceEquals,  bool,   (const DSObject* const, const DSObject* const) );
METHOD (DSObject, InstanceEquals,   bool,   (const DSObject* const, const DSObject* const) );
METHOD (DSObject, GetClass,         Class,  (const DSObject* const) );
METHOD (DSObject, GetClassName,     char*,  (const DSObject* const) );

VTABLE (DSObject) 
{
    const DSObjectToString        ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
};

/**
 * DSObject Class Methods & Variables
 * 
 */
CLASS (DSObject) 
{
    DSObject* Empty;
    DSObjectReferenceEquals ReferenceEquals;
    DSObjectInstanceEquals  InstanceEquals;
};

IVAR (DSClass) {
    Class isa;
};

//=======================================================================//
//              Which came first, the Class or the Object?               //          
//=======================================================================//
TYPEDEF (DSClass, ToString,         char*,  (const DSClass* const) );
TYPEDEF (DSClass, Equals,           bool,   (const DSClass* const, const DSClass* const) );
TYPEDEF (DSClass, GetHashCode,      int,    (const DSClass* const) );
TYPEDEF (DSClass, Dispose,          void,   (DSClass* const) );


VTABLE (DSClass) 
{
    const DSClassToString        ToString;
    const DSClassEquals          Equals;
    const DSClassGetHashCode     GetHashCode;
    const DSClassDispose         Dispose;
};

DEF_VPTR(DSObject);

//=======================================================================//
//              I M P L E M E N T A T I O N                              //          
//=======================================================================//
// bool InstanceOf(Class class, DSObject* obj);

static inline bool InstanceOf(Class class, DSObject* obj) {
    Class isa = obj->isa; 
    
    while (isa != class) {
        isa = isa->super_class;
        if (isa == nullptr) return false;
    }
    return true;
}

/**
 * DSObject constructor
 */
static inline DSObject* DSObject_init(DSObject* this) {
    this->isa = objc_getClass("DSObject");
    return this;
}

static inline overload bool ReferenceEquals(const DSObject* const objA, const DSObject* const objB)
{
    return objA == objB;
}


static inline overload bool InstanceEquals(const DSObject* const objA, const DSObject* const objB)
{
    if (objA == objB) {
        return true;
    }
    if (objA == nullptr || objB == nullptr) {
        return false;
    }
    // return DSObject_Equals(objA, objB);    
    return Equals(objA, objB);    
}

static inline overload void Dispose(DSObject* const this)
{
    return getVptr(DSObject)->Dispose(this);
}
/**
 * virtual Dispose method
 */
static inline void DSObject_Dispose(DSObject* const this){}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
static inline overload char* ToString(const DSObject* const this)
{
    return getVptr(DSObject)->ToString(this);
}
/**
 * virtual ToString method
 */
static inline const char *DSObject_ToString(const DSObject* const this)
{
    return "DSObject";
}

/**
 * Compare to another object
 */
static inline overload bool Equals(const DSObject* const this, const DSObject* const that)
{
    // return this == that;
    return getVptr(DSObject)->Equals(this, that);
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
static inline overload int GetHashCode(const DSObject* const this)
{
    return getVptr(DSObject)->GetHashCode(this);
}

static inline overload Class GetClass(const DSObject* const this)
{
    return &this->isa;
}

static inline overload char* GetClassName(const DSObject* const this)
{
    return this->isa->name;
}

VTABLE_BIND(DSClass);
VTABLE_METHOD(ToString,           (DSObjectToString)ToString, "$@:v");
VTABLE_METHOD(Equals,             (DSObjectEquals)Equals, "B@:@@");
VTABLE_METHOD(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
VTABLE_METHOD(Dispose,            (DSObjectDispose)Dispose, "v@:v");
VTABLE_METHOD(ReferenceEquals,    ReferenceEquals, "@:v");
VTABLE_METHOD(InstanceEquals,     InstanceEquals, "$@:v");
VTABLE_METHODIZE;


/**
 * Build the vtable
 */
VTABLE_BIND(DSObject);
VTABLE_METHOD(ToString,           ToString, "$@:v");
VTABLE_METHOD(Equals,             Equals, "B@:@@");
VTABLE_METHOD(GetHashCode,        GetHashCode, "l@:v");
VTABLE_METHOD(Dispose,            Dispose, "v@:v");
VTABLE_METHOD(ReferenceEquals,    ReferenceEquals, "@:v");
VTABLE_METHOD(InstanceEquals,     InstanceEquals, "$@:v");
$DSObject.Empty = nullptr;
VTABLE_METHODIZE;
// static inline Class objc_loadDSObject(Class super)
// {
//     int k = 0;
//     IMP* vt = &DSObject_vtable;
//     char* class_name = "DSObject";
//     Class isa = objc_allocateClassPair(super,"DSObject", 0);
//     isa->vtable = &vt[0];            

//     class_addMethod(isa, "ToString", ToString, "");
//     vt[k++] = ToString;
//     class_addMethod(isa, "Equals", Equals, "");
//     vt[k++] = Equals; 
//     class_addMethod(isa, "GetHashCode", GetHashCode, "");
//     vt[k++] = GetHashCode; 
//     class_addMethod(isa, "Dispose", Dispose, "");
//     vt[k++] = Dispose; 
//     class_addMethod(isa, "ReferenceEquals", ReferenceEquals, "");
//     vt[k++] = ReferenceEquals; 
//     class_addMethod(isa, "InstanceEquals", InstanceEquals, "");
//     vt[k++] = InstanceEquals; 
//     $DSObject.Empty = nullptr;
//     return methodizeClass(isa);
// }


#endif _DSOBJECT_H_ 
