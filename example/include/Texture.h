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
// Texture2D* NewTexture2D(int InternalFormat, int ImageFormat, char* path);
// Texture2D* Texture2D_init(Texture2D* const this, int InternalFormat, int ImageFormat, char* path);
// Texture2D* Texture2D_alloc();

interface (Texture2D, ToString,    char*, (const Texture2D* const));
interface (Texture2D, Generate,    char*, (Texture2D*, const GLuint, const GLuint, const unsigned char*));
interface (Texture2D, Bind,        char*, (Texture2D*));


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
function vptr(Texture2D);
/**
 * Class Loader callback
 */
function objc_loadTexture2D(Class super) 
{
    Class cls = createClass(super, Texture2D);
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
Texture2D* Texture2D_init(
    Texture2D* const this,
    int InternalFormat,
    int ImageFormat,
    char* path)
{
	DSObject_init(this);
    this->isa = getTexture2DIsa();
    this->path = strdup(path);
    this->Width = 0;
    this->Height = 0;
    this->InternalFormat = GL_RGB;
    this->ImageFormat = GL_RGB;
    this->WrapS = GL_REPEAT;
    this->WrapT = GL_REPEAT;
    this->FilterMin = GL_LINEAR;
    this->FilterMag = GL_LINEAR;
    this->InternalFormat = InternalFormat;
    this->ImageFormat = ImageFormat;
    glGenTextures(1, &this->Id);
    return this;
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
    Texture2D* const this, 
    const GLuint width, 
    const GLuint height, 
    const unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

method void Bind(Texture2D*  this)
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

/**
 * ToString
 */
method char* ToString(const Texture2D* const this)
{
    return "Texture2D";
}

