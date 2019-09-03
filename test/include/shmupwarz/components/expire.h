#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (ExpireComponent)
{
    Class isa;
    double Value;
};

method ExpireComponent* New(ExpireComponent* self, double value)
{
    self->isa = isa(ExpireComponent);
    self->Value = value;
    return self; 
}


