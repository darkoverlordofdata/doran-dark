#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

type (TweenComponent)
{
    Class isa;
    double Min;
    double Max;
    double Speed;
    bool Repeat;
    bool Active;
};

method TweenComponent* New(TweenComponent* self, double min, double max, double speed, bool repeat, bool active)
{
    self->isa = isa(TweenComponent);
    self->Min = min;
    self->Max = max;
    self->Speed = speed;
    self->Repeat = repeat;
    self->Active = active;
    return self;
}

