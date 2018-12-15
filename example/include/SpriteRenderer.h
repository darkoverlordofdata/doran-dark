/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <tglm/tglm.h>
#include <dark/darkfx.h>

#include "Texture.h"
#include "Shader.h"

#define IsSpriteRenderer(x) (x->isa == &SpriteRenderer)
#define AsSpriteRenderer(x) (IsSpriteRenderer(x) ? (struct SpriteRenderer *)x : nullptr)

class (SpriteRenderer)
{
    struct SpriteRendererClass * isa;
    struct Shader * shader; 
    GLuint VAO;
};

struct SpriteRendererClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TSpriteRenderer const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TSpriteRenderer  (^Create) (TShader shader);
        };
    };
    // Renders a defined quad textured with given sprite
    void (*DrawSprite)      (TSpriteRenderer const, TTexture2D *texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);
};

/**
 * SpriteRenderer API
 */
void overload DrawSprite(TSpriteRenderer, TTexture2D texture, Vec2 position, Vec2 size, GLfloat rot, Vec3 color);
void overload Dispose(TSpriteRenderer);
char* overload ToString(TSpriteRenderer const);
static void initRenderData(TSpriteRenderer this);

#endif SPRITE_RENDERER_H