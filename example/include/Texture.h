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

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class (Texture2D)
{
    Texture2DClass_t* isa;
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

typedef struct Texture2DClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (Texture2D const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };

    // Generates texture from image data
    void    (*Generate)     (Texture2D const, GLuint width, GLuint height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void    (*Bind)         (Texture2D const);
};

/**
 * Texture2D API
 */
void overload Generate(Texture2D, GLuint width, GLuint height, unsigned char* data);
void overload Bind(Texture2D);
const char* overload ToString(Texture2D const);
Texture2D Texture2D_New(int InternalFormat, int ImageFormat, char* path);
Texture2D Texture2D_Ctor(Texture2D const this, int InternalFormat, int ImageFormat, char* path);

#endif TEXTURE_H