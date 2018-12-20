/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <SpriteRenderer.h>

/**
 * SpriteRenderer
 * 
 * @param shader to use for rendering
 * 
 */
struct SpriteRenderer * SpriteRenderer_Ctor(
    struct SpriteRenderer *const this, 
    struct Shader *shader)
{
	Object_Ctor(this);
    this->isa = isa(SpriteRenderer);
    this->shader = shader;
    initRenderData(this);
    return this;
}

/**
 * DrawSprite
 * 
 * @param texture the image to render
 * @param position to render at
 * @param size to render
 * @param rotate amount to rotate by
 * @param color to tint
 * 
 */
void overload DrawSprite(
    struct SpriteRenderer *this, 
    struct Texture2D *texture, 
    Vec2 position, 
    Vec2 size, 
    GLfloat rot, 
    Vec3 color)
{
    Use(this->shader);

    Mat model = mat_identity();
    model = glm_translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm_translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    model = glm_rotate(model, rot, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    model = glm_translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back

    model = glm_scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale

    SetMatrix4(this->shader, "model", &model);
    // Render textured quad
    SetArray3(this->shader, "spriteColor", &color);
    
    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void overload Dispose(struct SpriteRenderer *this)
{
    glDeleteVertexArrays(1, this->VAO);
}


static void initRenderData(struct SpriteRenderer *this)
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
char* overload ToString(struct SpriteRenderer *const this)
{
    return "SpriteRenderer";
}

static struct SpriteRenderer* Create(TShader shader) { 
    return SpriteRenderer_Ctor(new(SpriteRenderer), shader);
}

/**
 * SpriteRenderer Class Metadata
 */
register (SpriteRenderer)
{
    if (SpriteRenderer.isa == nullptr) {
        SpriteRenderer = (struct SpriteRendererClass) {
            .isa                = &SpriteRenderer,
            .superclass         = &Object,
            .name               = "SpriteRenderer",
            .ToString           = ToString,
            .Equals             = Object.Equals,
            .GetHashCode        = Object.GetHashCode,
            .Dispose            = Object.Dispose,
            .ReferenceEquals    = Object.ReferenceEquals,
            .InstanceEquals     = Object.InstanceEquals,
            .DrawSprite         = DrawSprite,
            .Dispose            = Dispose,
            .Create             = Create,
        };
        AddMetadata(SpriteRenderer);
    }
    return &SpriteRenderer;
}

