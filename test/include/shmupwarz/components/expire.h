#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (ExpireComponent)
{
    double Value;
};

method ExpireComponent* New(ExpireComponent* self, double value)
{
    self->Value = value;
    return self; 
}


