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

#define IsSpriteRenderer(x) (x->isa == &SpriteRendererClass)
#define AsSpriteRenderer(x) (IsSpriteRenderer(x) ? (SpriteRenderer*)x : nullptr)

ivar (SpriteRenderer) {
    Class isa;
    Shader* shader; 
    GLuint VAO;
};

typedef char*   (*SpriteRendererToString)  (const SpriteRenderer* const);

class (SpriteRenderer) {
    SpriteRenderer*  (*Create) (Shader* shader);
};

vtable (SpriteRenderer) {
    char*   (*ToString) (const SpriteRenderer* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);

    // Renders a defined quad textured with given sprite
    void (*DrawSprite)      (SpriteRenderer* const, const Texture2D* const texture, const Vec2 position, const Vec2 size, const GLfloat rotate, const Vec3 color);
    
};

/**
 * SpriteRenderer API
 */
void overload DrawSprite(SpriteRenderer* const, const Texture2D* const texture, const Vec2 position, const Vec2 size, const GLfloat rot, const Vec3 color);
void overload Dispose(SpriteRenderer*);
char* overload ToString(const SpriteRenderer* const);
static void initRenderData(SpriteRenderer* this);
SpriteRenderer*  SpriteRenderer_init(SpriteRenderer* const this, Shader* shader);
SpriteRenderer* SpriteRenderer_alloc();
SpriteRenderer* NewSpriteRenderer(Shader* shader);