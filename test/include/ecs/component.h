#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
/** complete - phase I */

type (EcsComponent)
{
    Class isa;
}

method EcsComponent* New(EcsComponent* self)
{
    extends(Object);
    self->isa = isa(EcsComponent);
    return self;
}