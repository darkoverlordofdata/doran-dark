#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../types.h"

/**
 * Transform
 * 
 * associate a texture with scale, position and bounds
 */
type (Transform)
{
    Class isa;
    Texture2D* Texture;
    SDL_Rect Bounds;
    Vec2 Pos;
    Vec2 Scale;
};

/**
 * New Transform
 * 
 * @param texture
 * @param scale
 * @returns new Transform
 * 
 */
method Transform* New(Transform* self, Texture2D* texture, float scale)
{
    self->isa = isa(Transform);
    self->Texture = texture;
    self->Bounds.x = 0;
    self->Bounds.y = 0;
    self->Bounds.w = texture->Width;
    self->Bounds.h = texture->Height;
    self->Pos.x = 0;
    self->Pos.y = 0;
    self->Scale.x = scale;
    self->Scale.y = scale;
    return self;
}
