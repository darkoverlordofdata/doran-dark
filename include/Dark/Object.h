/*============================================================
**
** Class:  Object
**
**
** Object is the root class for all objects.  This class
** defines only the basics.
**
** 
===========================================================*/
#ifndef _VALA_OBJECT_H_
#define _VALA_OBJECT_H_

#include <assert.h>
#include <stdlib.h>
#include <types.h>

/**
 * Object Instance Data
 */
typedef struct 
{
    struct Dark_Object_VTable const *_vptr;
    int RefCount;
    
} Dark_Object;

/**
 * Define Object Interface
 */
typedef Dark_Object*    (TDark_Object_New)              ();
typedef Dark_Object*    (TDark_Object_Ctor)             (Dark_Object *);
typedef Dark_Object*    (TDark_Object_AddRef)           (Dark_Object *);
typedef void            (TDark_Object_Release)          (Dark_Object *);
typedef char*           (TDark_Object_ToString)         (Dark_Object const * const);
typedef bool            (TDark_Object_Equals)           (Dark_Object const * const, Dark_Object const * const);
typedef int             (TDark_Object_GetHashCode)      (Dark_Object const * const);
typedef bool            (TDark_Object_ReferenceEquals)  (Dark_Object *, Dark_Object *);
typedef bool            (TDark_Object_InstanceEquals)   (Dark_Object *, Dark_Object *);

/**
 * Declare Object Interface
 */
TDark_Object_New                Dark_Object_New;
TDark_Object_Ctor               Dark_Object_Ctor;
TDark_Object_AddRef             Dark_Object_AddRef;
TDark_Object_Release            Dark_Object_Release;
static TDark_Object_ToString    Dark_Object_ToString;
static TDark_Object_Equals      Dark_Object_Equals;
static TDark_Object_GetHashCode Dark_Object_GetHashCode;
TDark_Object_ReferenceEquals    Dark_Object_ReferenceEquals;
TDark_Object_InstanceEquals     Dark_Object_InstanceEquals;

/**
 * Object VTable
 */
typedef struct Dark_Object_VTable
{
    TDark_Object_ToString*      ToString;
    TDark_Object_Equals*        Equals;
    TDark_Object_GetHashCode*   GetHashCode;
};

/**
 * Dispatch
 */
static inline char* Dark_Object_ToString(Dark_Object const * const this)
{
    return (*this->_vptr->ToString)(this);
}

static inline bool Dark_Object_Equals(Dark_Object const * const this, Dark_Object const * const that)
{
    return (*this->_vptr->Equals)(this, that);
}

static inline int Dark_Object_GetHashCode(Dark_Object const * const this)
{
    return (*this->_vptr->GetHashCode)(this);
}

#endif /* _VALA_OBJECT_H_ */
