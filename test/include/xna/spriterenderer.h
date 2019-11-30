#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include "texture2d.h"
#include "shader.h"

type (SpriteRenderer)
{
    Class isa;
    Shader* shader; 
    GLuint quadVAO;
};

method void InitRenderData(SpriteRenderer* self);


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
    self->isa = isa(SpriteRenderer);
    self->shader = shader;
    InitRenderData(self);
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
    SpriteRenderer* self, 
    Texture2D* texture, 
    SDL_Rect* bounds,
    GLfloat 
    rotate, 
    Vec3 color)
{
    // printf("%s (%d,%d)\n", texture.Path, texture.Width, texture.Height);
    // Prepare transformations
    Use(self->shader);
    Mat model= {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    static Vec3 zero = { 0, 0, 0 };
    static Vec3 tr = { 0, 0, 0 };
    static Vec3 sc = { 0, 0, 1 };
    tr.x = bounds->x;
    tr.y = bounds->y;
    model = glm_translate(model, tr);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    tr.x = 0.5f * bounds->w;
    tr.y = 0.5f * bounds->h;
    model = glm_translate(model, tr); // Move origin of rotation to center of quad
    model = glm_rotate(model, rotate, zero); // Then rotate
    tr.x = -0.5f * bounds->w;
    tr.y = -0.5f * bounds->h;
    model = glm_translate(model, tr); // Move origin back
    sc.x = bounds->w;
    sc.y = bounds->h;
    model = glm_scale(model, sc); // Last scale

    // model = glm_translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    // model = glm_translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    // model = glm_rotate(model, rotate, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    // model = glm_translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back
    // model = glm_scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale


    SetMatrix(self->shader, "model", &model);

    // Render textured quad
    SetVector3(self->shader, "spriteColor", &color);

    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(self->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
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
    SpriteRenderer* self, 
    Texture2D* texture, 
    Vec2 position, 
    Vec2 size, 
    GLfloat 
    rotate, 
    Vec3 color)
{
    // printf("%s (%d,%d)\n", texture.Path, texture.Width, texture.Height);
    // Prepare transformations
    Use(self->shader);
    Mat model= {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    static Vec3 zero = { 0, 0, 0 };
    static Vec3 tr = { 0, 0, 0 };
    static Vec3 sc = { 0, 0, 1 };
    tr.x = position.x;
    tr.y = position.y;
    model = glm_translate(model, tr);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    tr.x = 0.5f * size.x;
    tr.y = 0.5f * size.y;
    model = glm_translate(model, tr); // Move origin of rotation to center of quad
    model = glm_rotate(model, rotate, zero); // Then rotate
    tr.x = -0.5f * size.x;
    tr.y = -0.5f * size.y;
    model = glm_translate(model, tr); // Move origin back
    sc.x = size.x;
    sc.y = size.y;
    model = glm_scale(model, sc); // Last scale

    // model = glm_translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    // model = glm_translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    // model = glm_rotate(model, rotate, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    // model = glm_translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back
    // model = glm_scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale

    SetMatrix(self->shader, "model", &model);

    // Render textured quad
    SetVector3(self->shader, "spriteColor", &color);

    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(self->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


method void InitRenderData(SpriteRenderer* self)
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

    glGenVertexArrays(1, &self->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(self->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}          

method void Dispose(SpriteRenderer* self)
{
    glDeleteVertexArrays(1, &self->quadVAO);
    if (!_use_gc) {
        free(self);
    }
}

