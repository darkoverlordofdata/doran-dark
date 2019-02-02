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
#include <dark/DSClass.h>
#include <dark/DSLog.h>
#include <dark/implementation/DSObject.h>
/**class_getAlignedInstanceSize
 * DSObject constructor
 */
DSObject* DSObject_init(DSObject* this) {
    this->isa = getDSObjectIsa();
    return this;
}

bool overload ReferenceEquals(const DSObject* const objA, const DSObject* const objB)
{
    return objA == objB;
}


bool overload InstanceEquals(const DSObject* const objA, const DSObject* const objB)
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

void overload Dispose(DSObject* const this){
    return _vptr(this)->Dispose(this);
}
/**
 * virtual Dispose method
 */
void DSObject_Dispose(DSObject* const this){}

/**
 * Returns the string value of this Object. The default for 
 * a Object is to return the fully qualified name of the class.
 */
char* overload ToString(const DSObject* const this)
{
    return _vptr(this)->ToString(this);
}
/**
 * virtual ToString method
 */
const char *DSObject_ToString(const DSObject* const this)
{
    return "DSObject";
}
/**
 * virtual ToString method
 */
const char *DSClass_ToString(const DSClass* const this)
{
    return "DSClass";
}

/**
 * Compare to another object
 */
bool overload Equals(const DSObject* const this, const DSObject* const that)
{
    // return this == that;
    return _vptr(this)->Equals(this, that);
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
    return _vptr(this)->GetHashCode(this);
}
/**
 * virtual GetHashCode method
 */
// int DSObject_GetHashCode(const DSObject* const this)
// {
//     return (int)this;
// }

Class overload GetClass(const DSObject* const this)
{
    return &this->isa;
}
char* overload GetClassName(const DSObject* const this)
{
    return this->isa->name;
}

