#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"


type (SpriteComponent)
{
    Texture2D* Texture;
    SDL_Rect Bounds;
    Vec2 Position;
    Vec2 Scale;
    int Width;
    int Height;

};


method SpriteComponent* New (SpriteComponent* self, Texture2D* texture)
{
    self->Texture = texture;
    self->Width = texture->Width;
    self->Height = texture->Height;
    return self;
}

static inline SpriteComponent* AsSpriteComponent(void* object)
{
    return (SpriteComponent*)object;
}
