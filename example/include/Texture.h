/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <dark/darkfx.h>

#define IsTexture2D(x) (x->isa == &Texture2D)
#define AsTexture2D(x) (IsTexture2D(x) ? (struct Texture2D *)x : nullptr)

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class (Texture2D)
{
    struct Texture2DClass * isa;
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
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TTexture2D const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TTexture2D  (*Create) (int InternalFormat, int ImageFormat, char* path);
        };
    };

    // Generates texture from image data
    void    (*Generate)     (TTexture2D const, GLuint width, GLuint height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void    (*Bind)         (TTexture2D const);
};

/**
 * Texture2D API
 */
void overload Generate(TTexture2D, GLuint width, GLuint height, unsigned char* data);
void overload Bind(TTexture2D);
char* overload ToString(TTexture2D const);
TTexture2D Texture2D_New(int InternalFormat, int ImageFormat, char* path);
TTexture2D Texture2D_Ctor(TTexture2D const this, int InternalFormat, int ImageFormat, char* path);

#endif TEXTURE_H