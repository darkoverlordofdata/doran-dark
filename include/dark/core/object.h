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
#include "class.h"
#include <string.h>
#define OBJECT_TYPE       (TYPE_OBJECT)
#define IsObject(object) _Generic((object), Object*: true, default: false)
#define AsObject(object) _Generic((object),                   \
                            Object*: (Object *)object,  \
                            default: nullptr)

static const long ObjectTypeID = -1;
/**
 * Object ivar
 */
type (Object) 
{
    Class isa;
};

delegate (Object, New,              Object*,  (Object*) );
delegate (Object, ToString,         char*,  (const Object* const) );
delegate (Object, Equals,           bool,   (const Object* const, const Object* const) );
delegate (Object, GetHashCode,      int,    (const Object* const) );
delegate (Object, Dispose,          void,   (Object* const) );
delegate (Object, ReferenceEquals,  bool,   (const Object* const, const Object* const) );
delegate (Object, InstanceEquals,   bool,   (const Object* const, const Object* const) );
delegate (Object, GetClass,         Class,  (const Object* const) );
delegate (Object, GetClassName,     char*,  (const Object* const) );

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


static inline vptr(Object);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadObject(Class super) 
{
    Class cls = createClass(super, Object);
    cls->id = ObjectTypeID;

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

static inline bool InstanceOf(Class klass, Object* obj) {
    Class isa = obj->isa; 
    
    while (isa != klass) {
        isa = isa->super_class;
        if (isa == nullptr) return false;
    }
    return true;
}

/**
 * Object constructor
 */
method Object* New(Object* self) {
    self->isa = objc_getClass("Object");
    return self;
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

method void Dispose(Object* const self)
{
    if (virtual(Object)->Dispose == Dispose) {
        // if (!_objc_use_gc) free(self);
    } else {
        // return virtual(Object)->Dispose(self);
    }
}
/**
 * virtual Dispose method
 */
// static inline void Object_Dispose(Object* const self){
//     if (!_objc_use_gc) free(self);
// }

/**
 * Returns the string value of self Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
method char* ToString(const Object* const self)
{
    return virtual(Object)->ToString(self);
}
/**
 * virtual ToString method
 */
static inline const char *Object_ToString(const Object* const self)
{
    return "Object";
}

/**
 * Compare to another object
 */
method bool Equals(const Object* const self, const Object* const that)
{
    // return self == that;
    return virtual(Object)->Equals(self, that);
}

/**
 * Get's the hashcode for self object. Default is the object's address in memory,
 */
method int GetHashCode(const Object* const self)
{
    return virtual(Object)->GetHashCode(self);
}

method Class GetClass(const Object* const self)
{
    return &self->isa;
}

method char* GetClassName(const Object* const self)
{
    return self->isa->name;
}

