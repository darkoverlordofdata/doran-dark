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
AUTHORS OR COPYRIGHT HOLDERS BE LI  ABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include <dark/Object.h>

bool __attribute__((overloadable)) Equals(Object const, Object const that);
static bool Virtual_Equals(Object const, Object const that);

ObjectClass_t ObjectClass;
/**
 * Destructor
 */
Object Object_Dtor(Object this)
{
    this->isa->Dispose(this);
    tgc_free(&gc, this);
    return nullptr;
}

bool ReferenceEquals(Object const objA, Object const objB)
{
    return objA == objB;
}


bool InstanceEquals(Object const objA, Object const objB)
{
    if (objA == objB) {
        return true;
    }
    if (objA == nullptr || objB == nullptr) {
        return false;
    }
    return Virtual_Equals(objA, objB);    
}

void __attribute__((overloadable)) Dispose(Object const this){
    this->isa->Dispose(this);
}
/**
 * virtual Dispose method
 */
static void Virtual_Dispose(Object const this){
}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
const char* __attribute__((overloadable)) ToString(Object const this)
{
    return this->isa->ToString(this);
}
/**
 * virtual ToString method
 */
static const char *Virtual_ToString(Object const this)
{
    return "dark.Object";
}

/**
 * Compare to another object
 */
bool __attribute__((overloadable)) Equals(Object const this, Object const that)
{
    return this->isa->Equals(this, that);
}
/**
 * virtual Equals method
 */
static bool Virtual_Equals(Object const this, Object const that)
{
    return this == that;
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
int __attribute__((overloadable)) GetHashCode(Object const this)
{
    return this->isa->GetHashCode(this);
}
/**
 * virtual GetHashCode method
 */
static int Virtual_GetHashCode(Object const this)
{
    return (int)this;
}

Class GetClass(Object const this)
{
    return &this->isa;
}
char* GetClassName(Object const this)
{
    return this->isa->base.name;
}

/**
 * Object Class Metadata
 */
void Object_Init()
{
    if (ObjectClass.isa == nullptr) {
        ObjectClass = (ObjectClass_t) {
            .isa         = &ObjectClass,
            .superclass  = nullptr,
            .name        = "Object",

            .ToString    = Virtual_ToString,
            .Equals      = Virtual_Equals,
            .GetHashCode = Virtual_GetHashCode,
            .Dispose     = Virtual_Dispose,
            .ReferenceEquals = ReferenceEquals,
            .InstanceEquals = InstanceEquals,
        };
    }
}

/**
 */
Object Object_Ctor(Object const this)
{
    this->isa = &ObjectClass;
    return this;
}

Object Object_New()
{
    return Object_Ctor(new(Object));
}

