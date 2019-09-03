#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (VelocityComponent)
{
    Class isa;
    float X;
    float Y;
};

method VelocityComponent* New(VelocityComponent* self, float x, float y)
{
    self->isa = isa(VelocityComponent);
    self->X = x;
    self->Y = y;
    return self;
}


