#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

type (ExpireComponent)
{
    double Value;
};

method ExpireComponent* New(ExpireComponent* self, double value)
{
    self->Value = value;
    return self; 
}

static inline ExpireComponent* AsExpireComponent(void* object)
{
    return (ExpireComponent*)object;
}

