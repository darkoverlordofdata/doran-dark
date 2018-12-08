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
    SpriteRendererClass_t* isa;
    Shader shader; 
    GLuint VAO;
};


typedef struct SpriteRendererClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (SpriteRenderer const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
    // Renders a defined quad textured with given sprite
    void (*DrawSprite)      (SpriteRenderer const, Texture2D *texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);
};

/**
 * SpriteRenderer API
 */
void overload DrawSprite(SpriteRenderer, Texture2D texture, Vec2 position, Vec2 size, GLfloat rot, Vec3 color);
void overload Dispose(SpriteRenderer);
const char* overload ToString(SpriteRenderer const);
SpriteRenderer SpriteRenderer_New(Shader shader);
static void initRenderData(SpriteRenderer this);

#endif SPRITE_RENDERER_H