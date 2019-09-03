#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (HealthComponent)
{
    Class isa;
    int Current;
    int Maximum;
};

method HealthComponent* New(HealthComponent* self, int current, int maximum)
{
    self->isa = isa(HealthComponent);
    self->Current = current;
    self->Maximum = maximum;
    return self; 
}

