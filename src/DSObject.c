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
#include <dark/DSObject.h>
/**
 * DSObjectClass constructor
 */
DSObject* DSObject_init(DSObject* this)
{
    this->isa = &DSObjectClass;
    return this;
}

DSObject* DSObject_alloc()
{
    return DSMalloc(DSObjectClass.instance_size);
}

/**
 * Destructor
 */
DSObject* DSObject_Dtor(DSObject* this)
{
    this->isa->Dispose(this);
    return nullptr;
}

bool ReferenceEquals(const DSObject* const objA, const DSObject* const objB)
{
    return objA == objB;
}


bool InstanceEquals(const DSObject* const objA, const DSObject* const objB)
{
    if (objA == objB) {
        return true;
    }
    if (objA == nullptr || objB == nullptr) {
        return false;
    }
    return DSObject_Equals(objA, objB);    
}

void overload Dispose(DSObject* const this){
    this->isa->Dispose(this);
}
/**
 * virtual Dispose method
 */
void DSObject_Dispose(DSObject* const this){}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
const char* overload ToString(const DSObject* const this)
{
    return this->isa->ToString(this);
}
/**
 * virtual ToString method
 */
const char *DSObject_ToString(const DSObject* const this)
{
    return "dark.Object";
}

/**
 * Compare to another object
 */
bool overload Equals(const DSObject* const this, const DSObject* const that)
{
    return this->isa->Equals(this, that);
}
/**
 * virtual Equals method
 */
bool DSObject_Equals(DSObject* const this, DSObject* const that)
{
    return this == that;
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
int overload GetHashCode(const DSObject* const this)
{
    return this->isa->GetHashCode(this);
}
/**
 * virtual GetHashCode method
 */
int DSObject_GetHashCode(const DSObject* const this)
{
    return (int)this;
}

Class GetClass(const DSObject* const this)
{
    return &this->isa;
}
char* GetClassName(const DSObject* const this)
{
    return this->isa->name;
}

DSObject* $DSObject() 
{ 
    return DSObject_init(DSObject_alloc()); 
}

Class implement_DSObject() 
{
    Class obj = objc_allocateClassPair(nullptr, "DSObject", 0);
    class_addMethod(obj, $toString, (IMP)DSObject_ToString, "$@:v");
    class_addMethod(obj, $equals, (IMP)DSObject_Equals, "B@:@@");
    class_addMethod(obj, $getHashCode, (IMP)DSObject_GetHashCode, "l@:v");
    class_addMethod(obj, $dispose, (IMP)DSObject_Dispose, "v@:v");
    class_addMethod(obj, $referenceEquals, (IMP)ReferenceEquals, "$@:v");
    class_addMethod(obj, $instanceEquals, (IMP)InstanceEquals, "$@:v");
    return obj;
}

/**
 * Object Class Metadata
 */
Class class_loadDSObject() {
    DSObjectClass = (struct DSObjectClass) {
        .isa            = IZA(DSObject),
        .superclass     = IZA(DS),
        .name           = "DSObject",
        .instance_size  = sizeof(DSObject), 
        .Create         = $DSObject,
        .ToString       = DSObject_ToString,
        .Equals         = DSObject_Equals,
        .GetHashCode    = DSObject_GetHashCode,
        .Dispose        = DSObject_Dispose,
        .ReferenceEquals= ReferenceEquals,
        .InstanceEquals = InstanceEquals
    };
    DSClassList.classes[DSClassList.count++] = IZA(DSObject); 

    return IZA(DSObject);
}
