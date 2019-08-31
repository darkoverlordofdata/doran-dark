#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../components.h"

type (ColorComponent)
{
    int R;
    int G;
    int B;
    int A;
};


method ColorComponent* New(ColorComponent* self, int r, int g, int b, int a)
{
    self->R = r;
    self->G = g;
    self->B = b;
    self->A = a;
    return self;
}

