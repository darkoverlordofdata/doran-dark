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
#include <dark/DObject.h>

static bool Equals(DObject const , DObject const that);
bool DObject_Equals(DObject const, DObject const that);

/**
 * AddRef
 */
DObject DObject_AddRef(DObject this)
{
    this->RefCount += 1;
    return this;
}

/**
 * Release
 */
DObject DObject_Release(DObject this)
{
    if (--(this->RefCount) == 0) 
    {
        this->Dispose(this);
        free(this);
        return nullptr;
    }
    return this;
}

bool DObject_ReferenceEquals(DObject const objA, DObject const objB)
{
    return objA == objB;
}


bool DObject_InstanceEquals(DObject const objA, DObject const objB)
{
        if (objA == objB) {
            return true;
        }
        if (objA == nullptr || objB == nullptr) {
            return false;
        }
        return DObject_Equals(objA, objB);
    
}

void DObject_Dispose(DObject const this){}
// Returns a String which represents the DObject instance.  The default
// for an DObject is to return the fully qualified name of the class.
// 
const char* DObject_ToString(DObject const this)
{
    return "Dark.DObject";
}


// Returns a boolean indicating if the passed in DObject obj is 
// Equal to this.  Equality is defined as DObject equality for reference
// types and bitwise equality for value types using a loader trick to
// replace Equals with EqualsValue for value types).
//     
bool DObject_Equals(DObject const this, DObject const that)
{
    return this == that;
}

// GetHashCode is intended to serve as a hash function for this DObject.
// Based on the contents of the DObject, the hash function will return a suitable
// value with a relatively random distribution over the various inputs.
//
// The default implementation returns the address for this instance.
// Calling it on the same DObject multiple times will return the same value, so
// it will technically meet the needs of a hash function, but it's less than ideal.
// DObjects (& especially value classes) should override this method.
// 
int DObject_GetHashCode(DObject const this)
{
    return (int)this;
}

/**
 * Magic methods...
 */
DObject DObject_Ctor(DObject const this)
{
    this->RefCount      = 1;
    this->ToString      = &DObject_ToString;
    this->Equals        = &DObject_Equals;
    this->GetHashCode   = &DObject_GetHashCode;
    this->Dispose       = &DObject_Dispose;
    return this;
}

DObject DObject_New()
{
    return DObject_Ctor(new(DObject));
}

