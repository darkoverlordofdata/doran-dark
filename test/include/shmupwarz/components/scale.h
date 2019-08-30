#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

type (ScaleComponent)
{
    float X;
    float Y;
};

method ScaleComponent* New(ScaleComponent* self, float x, float y)
{
    self->X = x;
    self->Y = y;
    return self;
}

static inline ScaleComponent* AsScaleComponent(void* object)
{
    return (ScaleComponent*)object;
}

