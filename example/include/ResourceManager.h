/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GL/glew.h>
#include <dark/darkfx.h>

#include "Shader.h"
#include "Texture.h"

// A singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. 

class (ResourceManager)
{
    struct ResourceManagerClass * isa;
    struct Hashmap * Shaders;
    struct Hashmap * Textures;
};

extern TResourceManager Resource;

struct ResourceManagerClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TResourceManager const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
        };
    };

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    TShader      (*LoadShader)           (TResourceManager const, const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
    // Retrieves a stored sader
    TShader      (*GetShader)            (TResourceManager const, char* name);
    // Loads (and generates) a texture from file
    TTexture2D   (*LoadTexture)          (TResourceManager const, const GLchar *file, GLboolean alpha, char* name);
    // Retrieves a stored texture
    TTexture2D   (*GetTexture)           (TResourceManager const, char* name);
    // Properly de-allocates all loaded resources
    void        (*Dtor)                 (TResourceManager const);
    // Loads and generates a shader from file
    TShader      (*loadShaderFromFile)   (TResourceManager const, const GLchar *vShaderFile, const GLchar *fShaderFile);
    // Loads a single texture from file
    TTexture2D   (*loadTextureFromFile)  (TResourceManager const, const GLchar *file, GLboolean alpha);
};

static TShader loadShaderFromFile(TResourceManager, const GLchar *vShaderFile, const GLchar *fShaderFile);
static TTexture2D loadTextureFromFile(TResourceManager, const GLchar *file, bool alpha);
TShader LoadShader(TResourceManager, const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
TShader GetShader(TResourceManager, char* name);
TTexture2D LoadTexture(TResourceManager, const GLchar *file, bool alpha, char* name);
TTexture2D GetTexture(TResourceManager, char* name);
void Dtor(TResourceManager);
TResourceManager ResourceManager_New();
static char* rdbuf(FILE* f);

#endif RESOURCE_MANAGER_H