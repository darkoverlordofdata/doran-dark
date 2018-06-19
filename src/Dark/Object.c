#include "Dark/Object.h"

/* Overrides */
static TDark_Object_ToString    Virtual_Dark_Object_ToString;
static TDark_Object_Equals      Virtual_Dark_Object_Equals;
static TDark_Object_GetHashCode Virtual_Dark_Object_GetHashCode;

static struct Dark_Object_VTable const vTable = 
{ 
    .ToString =     &Virtual_Dark_Object_ToString,
    .Equals =       &Virtual_Dark_Object_Equals,
    .GetHashCode =  &Virtual_Dark_Object_GetHashCode
};
/**
 * Constructor
 * Initialize the vTable
 * Start Reference Count at 1
 */
Dark_Object* Dark_Object_Ctor(Dark_Object *this)
{
    this->_vptr = &vTable;
    this->RefCount = 1;
    return this;
}

/**
 * AddRef
 */
Dark_Object* Dark_Object_AddRef(Dark_Object *this)
{
    assert(this != NULL);
    this->RefCount += 1;
    return this;
}

/**
 * Release
 */
void Dark_Object_Release(Dark_Object *this)
{
    assert(this != NULL);
    if (--(this->RefCount) == 0) 
    {
        free(this);
    }

}

bool Dark_Object_ReferenceEquals(Dark_Object *objA, Dark_Object *objB)
{
    return objA == objB;
}

bool Dark_Object_InstanceEquals(Dark_Object *objA, Dark_Object *objB)
{
        if (objA == objB) {
            return true;
        }
        if (objA == NULL || objB == NULL) {
            return false;
        }
        return Virtual_Dark_Object_Equals(objA, objB);
    
}

/**
 * Allocate a new Object
 */
Dark_Object* Dark_Object_New()
{
    Dark_Object* this;
    this = (Dark_Object*)calloc (1, sizeof(Dark_Object));
    return Dark_Object_Ctor(this);
}


// Returns a String which represents the object instance.  The default
// for an object is to return the fully qualified name of the class.
// 
static char* Virtual_Dark_Object_ToString(Dark_Object const * const this)
{
    assert(this != NULL);
    return (char*)"System.Object";
}

// Returns a boolean indicating if the passed in object obj is 
// Equal to this.  Equality is defined as object equality for reference
// types and bitwise equality for value types using a loader trick to
// replace Equals with EqualsValue for value types).
//     
static bool Virtual_Dark_Object_Equals(Dark_Object const * const this, Dark_Object const * const that)
{
    assert(this != NULL);
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
static int Virtual_Dark_Object_GetHashCode(Dark_Object const * const this)
{
    assert(this != NULL);
    return (int)this;
}

