#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

type (HealthComponent)
{
    int Current;
    int Maximum;
};

method HealthComponent* New(HealthComponent* self, int current, int maximum)
{
    self->Current = current;
    self->Maximum = maximum;
    return self; 
}

static inline HealthComponent* AsHealthComponent(void* object)
{
    return (HealthComponent*)object;
}

