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
#include <dark/Foundation.h>

#define IsTexture2D(object) _Generic((object), Texture2D*: true, default: false)
#define AsTexture2D(object) _Generic((object),                          \
                            Texture2D*: (Texture2D *)object,            \
                            default: nullptr)

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
type (Texture2D)
{
    Class isa;
    // Holds the Id of the texture object, used for all texture operations to reference to particlar texture
    GLuint Id;
    char* path;
                            // Texture image dimensions
    GLuint Width;
    GLuint Height;          // Width and height of loaded image in pixels
                            // Texture Format
    GLuint InternalFormat;  // Format of texture object
    GLuint ImageFormat;     // Format of loaded image
                            // Texture configuration
    GLuint WrapS;           // Wrapping mode on S axis
    GLuint WrapT;           // Wrapping mode on T axis
    GLuint FilterMin;       // Filtering mode if texture pixels < screen pixels
    GLuint FilterMag;       // Filtering mode if texture pixels > screen pixels
};
/**
 * Texture2D API
 */
delegate (Texture2D, New,       Texture2D*, (Texture2D*, int, int, char*));
delegate (Texture2D, ToString,  char*, (const Texture2D* const));
delegate (Texture2D, Generate,  void, (Texture2D*, const GLuint, const GLuint, const unsigned char*));
delegate (Texture2D, Bind,      void, (const Texture2D* const));


vtable (Texture2D) {
    Texture2DToString       ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
    Texture2DGenerate       Generate;
    Texture2DBind           Bind;
};

/**
 * Put it all together
 */
static inline vptr(Texture2D);
/**
 * Class Loader callback
 */
static inline Class ClassLoadTexture2D(Class base) 
{
    Class cls = createClass(base, Texture2D);
    addMethod(cls, Texture2D, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Texture2D, Generate);
    addMethod(cls, Texture2D, Bind);

    return cls;
}

/**
 * Texture2D
 * 
 * @param InternalFormat for binding the image
 * @param ImageFormat for binding the image
 * 
 */
method Texture2D* New(
    Texture2D* self,
    int InternalFormat,
    int ImageFormat,
    char* path)
{
	extends(Object);
    self->isa = isa(Texture2D);
    self->path = strdup(path);
    self->Width = 0;
    self->Height = 0;
    self->InternalFormat = GL_RGB;
    self->ImageFormat = GL_RGB;
    self->WrapS = GL_REPEAT;
    self->WrapT = GL_REPEAT;
    self->FilterMin = GL_LINEAR;
    self->FilterMag = GL_LINEAR;
    self->InternalFormat = InternalFormat;
    self->ImageFormat = ImageFormat;
    glGenTextures(1, &self->Id);
    return self;
}

/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
method void Generate(
    Texture2D* const self, 
    const GLuint width, 
    const GLuint height, 
    const unsigned char* data)
{
    self->Width = width;
    self->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, self->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, self->InternalFormat, width, height, 0, self->ImageFormat, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, self->WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, self->WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, self->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, self->FilterMag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

method void Bind(const Texture2D* const self)
{
    glBindTexture(GL_TEXTURE_2D, self->Id);
}

/**
 * ToString
 */
method char* ToString(const Texture2D* const self)
{
    return "Texture2D";
}

