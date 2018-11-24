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
#include <dark/Object.h>

static bool Equals(Object const , Object const that);
bool Object_Equals(Object const, Object const that);

/**
 * AddRef
 */
Object Object_AddRef(Object this)
{
    this->RefCount += 1;
    return this;
}

/**
 * Release
 */
Object Object_Release(Object this)
{
    if (--(this->RefCount) == 0) 
    {
        this->Dispose(this);
        free(this);
        return nullptr;
    }
    return this;
}

bool Object_ReferenceEquals(Object const objA, Object const objB)
{
    return objA == objB;
}


bool Object_InstanceEquals(Object const objA, Object const objB)
{
        if (objA == objB) {
            return true;
        }
        if (objA == nullptr || objB == nullptr) {
            return false;
        }
        return Object_Equals(objA, objB);
    
}

void Object_Dispose(Object const this){}
// Returns a String which represents the object instance.  The default
// for an object is to return the fully qualified name of the class.
// 
const char* Object_ToString(Object const this)
{
    return "Dark.Object";
}


// Returns a boolean indicating if the passed in object obj is 
// Equal to this.  Equality is defined as object equality for reference
// types and bitwise equality for value types using a loader trick to
// replace Equals with EqualsValue for value types).
//     
bool Object_Equals(Object const this, Object const that)
{
    return this == that;
}

// GetHashCode is intended to serve as a hash function for this object.
// Based on the contents of the object, the hash function will return a suitable
// value with a relatively random distribution over the various inputs.
//
// The default implementation returns the address for this instance.
// Calling it on the same object multiple times will return the same value, so
// it will technically meet the needs of a hash function, but it's less than ideal.
// Objects (& especially value classes) should override this method.
// 
int Object_GetHashCode(Object const this)
{
    return (int)this;
}

/**
 * Magic methods...
 */
Object Object_Ctor(Object const this)
{
    this->RefCount      = 1;
    this->ToString      = &Object_ToString;
    this->Equals        = &Object_Equals;
    this->GetHashCode   = &Object_GetHashCode;
    this->Dispose       = &Object_Dispose;
    return this;
}

Object Object_New()
{
    return Object_Ctor(new(Object));
}

