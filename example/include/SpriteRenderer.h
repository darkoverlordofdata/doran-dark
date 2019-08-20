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

type (SpriteRenderer) {
    Class isa;
    Shader* shader; 
    GLuint VAO;
};
/**
 * SpriteRenderer API
 */
// SpriteRenderer*     NewSpriteRenderer(Shader* shader);
// SpriteRenderer*     SpriteRenderer_init(SpriteRenderer* const this, Shader* shader);
// SpriteRenderer*     SpriteRenderer_alloc();

interface (SpriteRenderer, ToString,    char*, (const SpriteRenderer* const));
interface (SpriteRenderer, Draw,        void, (SpriteRenderer* const, const SpriteRenderer*));
inteface  (SpriteRenderer) Dispose,     void, (SpriteRenderer* const));

static void initRenderData(SpriteRenderer* this);

vtable (SpriteRenderer) {
    SpriteRendererToString  ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    SpriteRendererDispose   Dispose;
    SpriteRendererDraw      Draw;
};

/**
 * Put it all together
 */
function vptr(SpriteRenderer);
/**
 * Class Loader callback
 */
function objc_loadSpriteRenderer(Class super) 
{
    Class cls = createClass(super, SpriteRenderer);
    addMethod(cls, SpriteRenderer, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, SpriteRenderer, Dispose);
    addMethod(cls, SpriteRenderer, Draw);

    return cls;
}
