/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <GL/glew.h>
#include <tglm/tglm.h>
#include <dark/Foundation.h>

#include "Texture.h"
#include "Shader.h"

#define IsSpriteRenderer(object) _Generic((object), SpriteRenderer*: true, default: false)
#define AsSpriteRenderer(object) _Generic((object),                             \
                            SpriteRenderer*: (SpriteRenderer *)object,          \
                            default: nullptr)

ivar (SpriteRenderer) {
    Class isa;
    Shader* shader; 
    GLuint VAO;
};

SpriteRenderer*     NewSpriteRenderer(Shader* shader);
SpriteRenderer*     SpriteRenderer_init(SpriteRenderer* const this, Shader* shader);
SpriteRenderer*     SpriteRenderer_alloc();

char*   overload ToString(const SpriteRenderer* const);
void    overload Draw(SpriteRenderer* , const Texture2D* const, const Vec2, const Vec2, const GLfloat, const Vec3);
void    overload Dispose(SpriteRenderer* const);

static void initRenderData(SpriteRenderer* this);

typedef char*   (*SpriteRendererToString)   (const SpriteRenderer* const);
typedef void    (*SpriteRendererDispose)    (SpriteRenderer* const);
typedef char*   (*SpriteRendererDraw)       (SpriteRenderer*, const Texture2D* const, const Vec2, const Vec2, const GLfloat, const Vec3);

vtable (SpriteRenderer) {
    SpriteRendererToString  ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    SpriteRendererDispose   Dispose;
    SpriteRendererDraw      Draw;
};

class (SpriteRenderer) {
    SpriteRenderer*  (*Create) (Shader* shader);
};

