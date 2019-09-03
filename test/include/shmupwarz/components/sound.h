#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

typedef enum SoundEffect {

    SoundEffectPew,
    SoundEffectSmallAsplode,
    SoundEffectAsplode

} SoundEffect;

type (SoundComponent)
{
    Class isa;
    SoundEffect Effect;
};

method SoundComponent* New(SoundComponent* self, SoundEffect effect)
{
    self->isa = isa(SoundComponent);
    self->Effect = effect;
    return self;
}

