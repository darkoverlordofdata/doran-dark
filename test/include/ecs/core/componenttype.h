#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



static int EcsUniqueComponentIndex = 0;


type (EcsComponentType)
{
    Class isa;
    Object* base;
    int Index;
    Class Type;
};


method char* GetName(EcsComponentType* self);
method int GetIndex(EcsComponentType* self);

delegate (EcsComponentType, GetName, char*, (EcsComponentType* self));
delegate (EcsComponentType, GetIndex, int, (EcsComponentType* self));


/**
 * EcsComponentType Vtable
 */
vtable (EcsComponentType) 
{
    const ObjectToString            ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const EcsComponentTypeGetName   GetName;
    const EcsComponentTypeGetIndex  GetIndex;
};

static inline vptr(EcsComponentType);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsComponentType(Class base) 
{
    Class cls = createClass(base, EcsComponentType);
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, EcsComponentType, GetName);
    addMethod(cls, EcsComponentType, GetIndex);

    return cls; 
}



method EcsComponentType* New(EcsComponentType* self, Class type)
{
    self->base = extends(Object);
    self->isa = isa(EcsComponentType);
    self->Type = type;
    self->Index = EcsUniqueComponentIndex++;
    return self;
}

method char* GetName(EcsComponentType* self)
{
    return self->Type->name;
}

method int GetIndex(EcsComponentType* self)
{
    return self->Index;
}
