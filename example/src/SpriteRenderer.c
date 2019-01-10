/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <SpriteRenderer.h>
#include "private/SpriteRenderer.h"
/**
 * SpriteRenderer
 * 
 * @param shader to use for rendering
 * 
 */
SpriteRenderer* NewSpriteRenderer(Shader* shader) { 
    return SpriteRenderer_init(SpriteRenderer_alloc(), shader);
}

SpriteRenderer*  SpriteRenderer_init(
    SpriteRenderer* const this, 
    Shader* shader)
{
	DSObject_init(this);
    this->isa = getSpriteRendererIsa();
    this->shader = shader;
    initRenderData(this);
    return this;
}

SpriteRenderer* SpriteRenderer_alloc() {
    return DSMalloc(getSpriteRendererSize());
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
void overload Draw(
    SpriteRenderer* this, 
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

    Use(this->shader);
    SetMatrix4(this->shader, "model", &model);
    SetArray3(this->shader, "spriteColor", &color);
    
    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void overload Dispose(SpriteRenderer* const this)
{
    glDeleteVertexArrays(1, this->VAO);
}

static void initRenderData(SpriteRenderer* this)
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

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


/**
 * ToString
 */
char* overload ToString(const SpriteRenderer* const this)
{
    return "SpriteRenderer";
}


