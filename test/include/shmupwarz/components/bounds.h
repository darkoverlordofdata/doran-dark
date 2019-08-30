#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

type (BoundsComponent)
{
    int X;
    int Y;
    int W;
    int H;
};

method BoundsComponent* New(BoundsComponent* self, int x, int y, int w, int h)
{
    self->X = x;
    self->Y = y;
    self->W = w;
    self->H = h;
    return self;
}

static inline BoundsComponent* AsBoundsComponent(void* object)
{
    return (BoundsComponent*)object;
}