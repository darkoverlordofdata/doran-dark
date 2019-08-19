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
#include <dark/core/class.h>

#define OBJECT_TYPE       (TYPE_OBJECT)

/**
 * Object ivar
 */
type (Object) 
{
    Class isa;
};

interface (Object, ToString,         char*,  (const Object* const) );
interface (Object, Equals,           bool,   (const Object* const, const Object* const) );
interface (Object, GetHashCode,      int,    (const Object* const) );
interface (Object, Dispose,          void,   (Object* const) );
interface (Object, ReferenceEquals,  bool,   (const Object* const, const Object* const) );
interface (Object, InstanceEquals,   bool,   (const Object* const, const Object* const) );
interface (Object, GetClass,         Class,  (const Object* const) );
interface (Object, GetClassName,     char*,  (const Object* const) );

vtable (Object) 
{
    const ObjectToString        ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
};

/**
 * Object Class Methods & Variables
 * 
 */
class (Object) 
{
    Object* Empty;
    ObjectReferenceEquals ReferenceEquals;
    ObjectInstanceEquals  InstanceEquals;
};


function vptr(Object);
/**
 * 
 * Class Loader callback
 */
function objc_loadObject(Class super) 
{
    Class cls = createClass(super, Object);
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Object, ReferenceEquals);
    addMethod(cls, Object, InstanceEquals);
    $Object.Empty = nullptr;
    return cls;
}

//=======================================================================//
//              I M P L E M E N T A T I O N                              //          
//=======================================================================//
// bool InstanceOf(Class class, Object* obj);

function bool InstanceOf(Class class, Object* obj) {
    Class isa = obj->isa; 
    
    while (isa != class) {
        isa = isa->super_class;
        if (isa == nullptr) return false;
    }
    return true;
}

/**
 * Object constructor
 */
function Object* Object_init(Object* this) {
    this->isa = objc_getClass("Object");
    return this;
}

method bool ReferenceEquals(const Object* const objA, const Object* const objB)
{
    return objA == objB;
}


method bool InstanceEquals(const Object* const objA, const Object* const objB)
{
    if (objA == objB) {
        return true;
    }
    if (objA == nullptr || objB == nullptr) {
        return false;
    }
    // return Object_Equals(objA, objB);    
    return Equals(objA, objB);    
}

method void Dispose(Object* const this)
{
    return get_vptr(Object)->Dispose(this);
}
/**
 * virtual Dispose method
 */
function void Object_Dispose(Object* const this){}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
method char* ToString(const Object* const this)
{
    return get_vptr(Object)->ToString(this);
}
/**
 * virtual ToString method
 */
function const char *Object_ToString(const Object* const this)
{
    return "Object";
}

/**
 * Compare to another object
 */
method bool Equals(const Object* const this, const Object* const that)
{
    // return this == that;
    return get_vptr(Object)->Equals(this, that);
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
method int GetHashCode(const Object* const this)
{
    return get_vptr(Object)->GetHashCode(this);
}

method Class GetClass(const Object* const this)
{
    return &this->isa;
}

method char* GetClassName(const Object* const this)
{
    return this->isa->name;
}

