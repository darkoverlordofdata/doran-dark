#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"


typedef enum SoundEffect {

    SoundEffectPew,
    SoundEffectSmallAsplode,
    SoundEffectAsplode

} SoundEffect;

type (SoundComponent)
{
    SoundEffect Effect;
};

method SoundComponent* New(SoundComponent* self, SoundEffect effect)
{
    self->Effect = effect;
    return self;
}

static inline SoundComponent* AsSoundComponent(void* object)
{
    return (SoundComponent*)object;
}