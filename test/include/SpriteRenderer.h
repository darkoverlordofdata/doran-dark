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

// #include "Texture.h"
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
delegate (SpriteRenderer, New,          SpriteRenderer*, (SpriteRenderer*, Shader*));
delegate (SpriteRenderer, ToString,    char*, (const SpriteRenderer* const));
delegate (SpriteRenderer, Draw,        void, (const SpriteRenderer*, const Texture2D* const, const Vec2, const Vec2, const GLfloat, const Vec3));
delegate (SpriteRenderer, Dispose,     void, (SpriteRenderer* const));

static void initRenderData(SpriteRenderer* self);

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
static inline vptr(SpriteRenderer);
/**
 * Class Loader callback
 */
static inline Class objc_loadSpriteRenderer(Class base) 
{
    Class cls = createClass(base, SpriteRenderer);
    addMethod(cls, SpriteRenderer, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, SpriteRenderer, Dispose);
    addMethod(cls, SpriteRenderer, Draw);

    return cls;
}

/**
 * SpriteRenderer
 * 
 * @param shader to use for rendering
 * 
 */
method SpriteRenderer*  New(
    SpriteRenderer* self, 
    Shader* shader)
{
	extends(Object);
    self->isa = objc_getClass("SpriteRenderer");
    self->shader = shader;
    initRenderData(self);
    return self;
}
/**
 * Draw
 * 
 * @param texture the image to render
 * @param position to render at
 * @param size to render
 * @param rotate amount to rotate by
 * @param color to tint
 * 
 */
method void Draw(
    const SpriteRenderer* self, 
    const Texture2D* const texture, 
    const Vec2 position, 
    const Vec2 size, 
    const GLfloat rot, 
    const Vec3 color)
{
    Mat model = mat_identity();
    model = glm_translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    model = glm_translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    model = glm_rotate(model, rot, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    model = glm_translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back
    model = glm_scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale

    Use(self->shader);
    SetMatrix4(self->shader, "model", &model);
    SetArray3(self->shader, "spriteColor", &color);
    
    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(self->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

method void Dispose(SpriteRenderer* const self)
{
    glDeleteVertexArrays(1, self->VAO);
}

static void initRenderData(SpriteRenderer* self)
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = { 
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &self->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(self->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


/**
 * ToString
 */
method char* ToString(const SpriteRenderer* const self)
{
    return "SpriteRenderer";
}


