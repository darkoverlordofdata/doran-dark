/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Texture.h>

/**
 * Constructor
 * 
 * @param InternalFormat for binding the image
 * @param ImageFormat for binding the image
 * 
 */
Texture2D Texture2D_Ctor(Texture2D const this, int InternalFormat, int ImageFormat, char* path)
{
	Object_Ctor(this);
    this->isa = isa(Texture2D);
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
 * Texture2D Class Metadata
 */
register (Texture2D)
{
    if (Texture2DClass.isa == nullptr) {
        Texture2DClass = (Texture2DClass_t) {
            .isa        = &Texture2DClass,
            .superclass = &ObjectClass,
            .name       = "Texture2D",
            /** VTable */
            .ToString       = ToString,
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .Dispose        = ObjectClass.Dispose,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .Generate       = Generate,
            .Bind           = Bind,
        };
    }
}

/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
void overload Generate(Texture2D this, GLuint width, GLuint height, unsigned char* data)
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

void overload Bind(Texture2D this)
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

/**
 * ToString
 */
const char* overload ToString(Texture2D const this)
{
    return "Texture2D";
}

Texture2D Texture2D_New(int InternalFormat, int ImageFormat, char* path)
{
    return Texture2D_Ctor(new(Texture2D), InternalFormat, ImageFormat, path);
}

