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
#include <dark/darkfx.h>

#define IsTexture2D(x) (x->isa == &Texture2DClass)
#define AsTexture2D(x) (IsTexture2D(x) ? (Texture2D*)x : nullptr)

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class (Texture2D)
{
    struct Texture2DClass* isa;
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

struct Texture2DClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    char*   (*ToString) (Texture2D* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    Texture2D*  (*Create) (int InternalFormat, int ImageFormat, char* path);

    // Generates texture from image data
    void    (*Generate)     (Texture2D* const, GLuint width, GLuint height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void    (*Bind)         (Texture2D* const);
    
} Texture2DClass;

/**
 * Texture2D API
 */
void overload Generate(Texture2D*, GLuint width, GLuint height, unsigned char* data);
void overload Bind(Texture2D*);
char* overload ToString(Texture2D* const);

