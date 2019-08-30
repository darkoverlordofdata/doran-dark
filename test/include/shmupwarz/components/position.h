#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

type (PositionComponent)
{
    float X;
    float Y;
};

method PositionComponent* New(PositionComponent* self, float x, float y)
{
    self->X = x;
    self->Y = y;
    return self;
}

static inline PositionComponent* AsPositionComponent(void* object)
{
    return (PositionComponent*)object;
}

