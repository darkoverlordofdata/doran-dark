/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Texture.h>
$implementation(Texture2D);

$method(ToString,           (Texture2DToString)ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");
$method(Generate,           Generate, "v@:II*");
$method(Bind,               Bind, "v@:@");

$ivar(Id, sizeof(GLuint), "I");
$ivar(path, sizeof(char*), "*");
$ivar(Width, sizeof(GLuint), "I");
$ivar(Height, sizeof(GLuint), "I");
$ivar(InternalFormat, sizeof(GLuint), "I");
$ivar(ImageFormat, sizeof(GLuint), "I");
$ivar(WrapS, sizeof(GLuint), "I");
$ivar(WrapT, sizeof(GLuint), "I");
$ivar(FilterMin, sizeof(GLuint), "I");
$ivar(FilterMag, sizeof(GLuint), "I");

$end;

/**
 * Texture2D
 * 
 * @param InternalFormat for binding the image
 * @param ImageFormat for binding the image
 * 
 */
Texture2D* NewTexture2D(int InternalFormat, int ImageFormat, char* path) { 
    return Texture2D_init(Texture2D_alloc(), InternalFormat, ImageFormat, path);
}

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

Texture2D* Texture2D_alloc() {
    return DSMalloc(getTexture2DSize());
}

/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
void overload Generate(
    Texture2D* this, 
    GLuint width, 
    GLuint height, 
    unsigned char* data)
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

void overload Bind(Texture2D*  this)
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

/**
 * ToString
 */
char* overload ToString(const Texture2D* const this)
{
    return "Texture2D";
}

