#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



static int EcsUniqueComponentIndex = 0;


type (EcsComponentType)
{
    Class isa;
    int Index;
    Class Type;
};


method EcsComponentType* New(EcsComponentType* self, Class type)
{
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
