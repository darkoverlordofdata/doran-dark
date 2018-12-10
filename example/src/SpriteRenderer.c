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
 * Constructor
 * 
 * @param shader to use for rendering
 * 
 */
TSpriteRenderer SpriteRenderer_New(TShader shader) {
    return SpriteRenderer_Ctor(new(SpriteRenderer), shader);
}

TSpriteRenderer SpriteRenderer_Ctor(TSpriteRenderer const this, TShader shader)
{
	Object_Ctor(this);
    this->isa = isa(SpriteRenderer);
    this->shader = shader;
    initRenderData(this);
    return this;
}

/**
 * SpriteRenderer Class Metadata
 */
register (SpriteRenderer)
{
    if (SpriteRenderer.isa == nullptr) {
        SpriteRenderer = (struct SpriteRendererClass) {
            .isa        = &SpriteRenderer,
            .superclass = &Object,
            .name       = "SpriteRenderer",
            /** VTable */
            .ToString           = ToString,
            .Equals             = Object.Equals,
            .GetHashCode        = Object.GetHashCode,
            .Dispose            = Object.Dispose,
            .ReferenceEquals    = Object.ReferenceEquals,
            .InstanceEquals     = Object.InstanceEquals,
            .DrawSprite         = DrawSprite,
            .Dispose            = Dispose,
            .Create             = SpriteRenderer_New,
        };
        AddMetadata(SpriteRenderer);
    }
    return &SpriteRenderer;
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
void overload DrawSprite(TSpriteRenderer this, TTexture2D texture, Vec2 position, Vec2 size, GLfloat rot, Vec3 color)
{
    Use(this->shader);

    Mat model = mat_identity();
    model = translate(model, (Vec3){ position.x, position.y, 0.0f });  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = translate(model, (Vec3){ 0.5f * size.x, 0.5f * size.y, 0.0f }); // Move origin of rotation to center of quad
    model = rotate(model, rot, (Vec3){ 0.0f, 0.0f, 1.0f }); // Then rotate
    model = translate(model, (Vec3){ -0.5f * size.x, -0.5f * size.y, 0.0f }); // Move origin back

    model = scale(model, (Vec3){ size.x, size.y, 1.0f }); // Last scale

    SetMatrix4(this->shader, "model", &model);
    // Render textured quad
    SetArray3(this->shader, "spriteColor", &color);
    
    glActiveTexture(GL_TEXTURE0);
    Bind(texture);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void overload Dispose(TSpriteRenderer this)
{
    glDeleteVertexArrays(1, this->VAO);
}


static void initRenderData(TSpriteRenderer this)
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
char* overload ToString(TSpriteRenderer const this)
{
    return "SpriteRenderer";
}

