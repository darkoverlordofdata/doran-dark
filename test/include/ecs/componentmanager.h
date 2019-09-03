#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>

type (EcsComponentManager)
{
    Class isa;
    EcsWorld* World;
    Array* ComponentsByType;
    Array* Deleted;
    EcsComponentTypeFactory* TypeFactory;
};

method EcsComponentManager* New(EcsComponentManager* self)
{
    extends(EcsManager);
    self->isa = isa(EcsComponentManager);
}

