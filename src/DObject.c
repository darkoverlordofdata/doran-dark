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
#include <dark/DObject.h>

#ifdef GOBJECT_COMPILATION
#include <glib.h>
#include <glib-object.h>
#endif

#ifdef __ARC__
/**
 * AddRef
 */
DObject DObject_AddRef(DObject this)
{
    #ifdef GOBJECT_COMPILATION
    g_atomic_int_inc(&this->RefCount);
    #else
    this->RefCount += 1;
    #endif
    return this;
}
/**
 * Release
 */
DObject DObject_Release(DObject this)
{
    #ifdef GOBJECT_COMPILATION
    if (g_atomic_int_dec_and_test(&this->RefCount))
    #else
    if (--(this->RefCount) == 0) 
    #endif
    {
        return DObject_Dtor(this);
    }
    return this;
}
#endif

static bool Equals(DObject const, DObject const that);
bool DObject_Equals(DObject const, DObject const that);

/**
 * Destructor
 */
DObject DObject_Dtor(DObject this)
{
    this->Dispose(this);
    delete(this);
    return nullptr;
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

void DObject_Dispose(DObject const this){
    this->Dispose(this);
}
/**
 * virtual Dispose method
 */
static void Dispose(DObject const this){
}

/**
 * Returns the string value of this DObject. The default for 
 * a DObject is to return the fully qualified name of the class.
 */
const char* DObject_ToString(DObject const this)
{
    return this->ToString(this);
}
/**
 * virtual ToString method
 */
static const char *ToString(DObject const this)
{
    return "dark.DObject";
}

/**
 * Compare to another object
 */
bool DObject_Equals(DObject const this, DObject const that)
{
    return this->Equals(this, that);
}
/**
 * virtual Equals method
 */
static bool Equals(DObject const this, DObject const that)
{
    return this == that;
}

/**
 * Get's the hashcode for this object. Default is the object's address in memory,
 */
int DObject_GetHashCode(DObject const this)
{
    return this->GetHashCode(this);
}
/**
 * virtual GetHashCode method
 */
static int GetHashCode(DObject const this)
{
    return (int)this;
}

/**
 */
DObject DObject_Ctor(DObject const this)
{
    this->RefCount      = 1;
    this->ToString      = &ToString;
    this->Equals        = &Equals;
    this->GetHashCode   = &GetHashCode;
    this->Dispose       = &Dispose;
    return this;
}

DObject DObject_New()
{
    return DObject_Ctor(new(DObject));
}

