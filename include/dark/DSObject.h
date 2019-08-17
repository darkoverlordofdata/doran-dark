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
type (DSObject) {
    Class isa;
};

def_method (DSObject, ToString,         char*,  (const DSObject* const) );
def_method (DSObject, Equals,           bool,   (const DSObject* const, const DSObject* const) );
def_method (DSObject, GetHashCode,      int,    (const DSObject* const) );
def_method (DSObject, Dispose,          void,   (DSObject* const) );
def_method (DSObject, ReferenceEquals,  bool,   (const DSObject* const, const DSObject* const) );
def_method (DSObject, InstanceEquals,   bool,   (const DSObject* const, const DSObject* const) );
def_method (DSObject, GetClass,         Class,  (const DSObject* const) );
def_method (DSObject, GetClassName,     char*,  (const DSObject* const) );

vtable (DSObject) 
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
class (DSObject) 
{
    DSObject* Empty;
    DSObjectReferenceEquals ReferenceEquals;
    DSObjectInstanceEquals  InstanceEquals;
};

type (DSClass) {
    Class isa;
};

#define TYPEDEF(T, name, type, signature)                                \
    typedef type (*T##name)signature;

//=======================================================================//
//              Which came first, the Class or the Object?               //          
//=======================================================================//
typedef char* (*DSClassToString)(const DSClass* const);
typedef _Bool (*DSClassEquals)(const DSClass* const, const DSClass* const);
typedef int (*DSClassGetHashCode)(const DSClass* const);
typedef void (*DSClassDispose)(DSClass* const);


vtable (DSClass) 
{
    const DSClassToString        ToString;
    const DSClassEquals          Equals;
    const DSClassGetHashCode     GetHashCode;
    const DSClassDispose         Dispose;
};

vtable_ptr(DSObject);

//=======================================================================//
//              I M P L E M E N T A T I O N                              //          
//=======================================================================//
// bool InstanceOf(Class class, DSObject* obj);

proc bool InstanceOf(Class class, DSObject* obj) {
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
proc DSObject* DSObject_init(DSObject* this) {
    this->isa = objc_getClass("DSObject");
    return this;
}

method bool ReferenceEquals(const DSObject* const objA, const DSObject* const objB)
{
    return objA == objB;
}


method bool InstanceEquals(const DSObject* const objA, const DSObject* const objB)
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

method void Dispose(DSObject* const this)
{
    return get_vptr(DSObject)->Dispose(this);
}
/**
 * virtual Dispose method
 */
proc void DSObject_Dispose(DSObject* const this){}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
method char* ToString(const DSObject* const this)
{
    return get_vptr(DSObject)->ToString(this);
}
/**
 * virtual ToString method
 */
proc const char *DSObject_ToString(const DSObject* const this)
{
    return "DSObject";
}

/**
 * Compare to another object
 */
method bool Equals(const DSObject* const this, const DSObject* const that)
{
    // return this == that;
    return get_vptr(DSObject)->Equals(this, that);
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
method int GetHashCode(const DSObject* const this)
{
    return get_vptr(DSObject)->GetHashCode(this);
}

method Class GetClass(const DSObject* const this)
{
    return &this->isa;
}

method char* GetClassName(const DSObject* const this)
{
    return this->isa->name;
}

class_bind(DSClass);
class_method(ToString,           (DSObjectToString)ToString, "$@:v");
class_method(Equals,             (DSObjectEquals)Equals, "B@:@@");
class_method(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
class_method(Dispose,            (DSObjectDispose)Dispose, "v@:v");
class_method(ReferenceEquals,    ReferenceEquals, "@:v");
class_method(InstanceEquals,     InstanceEquals, "$@:v");
class_methodize;


/**
 * Build the vtable
 */
class_bind(DSObject);
class_method(ToString,           ToString, "$@:v");
class_method(Equals,             Equals, "B@:@@");
class_method(GetHashCode,        GetHashCode, "l@:v");
class_method(Dispose,            Dispose, "v@:v");
class_method(ReferenceEquals,    ReferenceEquals, "@:v");
class_method(InstanceEquals,     InstanceEquals, "$@:v");
$DSObject.Empty = nullptr;
class_methodize;
// proc Class objc_loadDSObject(Class super)
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
