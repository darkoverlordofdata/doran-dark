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
#include <dark/darkfx.h>

#include "Texture.h"
#include "Shader.h"

#define IsSpriteRenderer(x) (x->isa == &SpriteRendererClass)
#define AsSpriteRenderer(x) (IsSpriteRenderer(x) ? (SpriteRenderer*)x : nullptr)

class (SpriteRenderer)
{
    struct SpriteRendererClass* isa;
    Shader* shader; 
    GLuint VAO;
};

struct SpriteRendererClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (SpriteRenderer* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    SpriteRenderer*  (*Create) (Shader* shader);

    // Renders a defined quad textured with given sprite
    void (*DrawSprite)      (SpriteRenderer* const, Texture2D* *texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);
    
} SpriteRendererClass;

/**
 * SpriteRenderer API
 */
void overload DrawSprite(SpriteRenderer*, Texture2D* texture, Vec2 position, Vec2 size, GLfloat rot, Vec3 color);
void overload Dispose(SpriteRenderer*);
char* overload ToString(SpriteRenderer* const);
static void initRenderData(SpriteRenderer* this);

