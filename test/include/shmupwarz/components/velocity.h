#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (VelocityComponent)
{
    float X;
    float Y;
};

method VelocityComponent* New(VelocityComponent* self, float x, float y)
{
    self->X = x;
    self->Y = y;
    return self;
}


