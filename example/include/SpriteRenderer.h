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
#include <glm/glm.h>
#include <dark/darkfx.h>

#include "Texture.h"
#include "Shader.h"


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
TSpriteRenderer SpriteRenderer_New(TShader shader);
TSpriteRenderer SpriteRenderer_Ctor(TSpriteRenderer const this, TShader shader);
static void initRenderData(TSpriteRenderer this);

#endif SPRITE_RENDERER_H