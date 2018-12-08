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
    ResourceManagerClass_t* isa;
    Hashmap Shaders;
    Hashmap Textures;
};

extern ResourceManager Resource;

typedef struct ResourceManagerClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (ResourceManager const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };

    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    Shader      (*LoadShader)           (ResourceManager const, const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
    // Retrieves a stored sader
    Shader      (*GetShader)            (ResourceManager const, char* name);
    // Loads (and generates) a texture from file
    Texture2D   (*LoadTexture)          (ResourceManager const, const GLchar *file, GLboolean alpha, char* name);
    // Retrieves a stored texture
    Texture2D   (*GetTexture)           (ResourceManager const, char* name);
    // Properly de-allocates all loaded resources
    void        (*Dtor)                 (ResourceManager const);
    // Loads and generates a shader from file
    Shader      (*loadShaderFromFile)   (ResourceManager const, const GLchar *vShaderFile, const GLchar *fShaderFile);
    // Loads a single texture from file
    Texture2D   (*loadTextureFromFile)  (ResourceManager const, const GLchar *file, GLboolean alpha);
};

static Shader loadShaderFromFile(ResourceManager, const GLchar *vShaderFile, const GLchar *fShaderFile);
static Texture2D loadTextureFromFile(ResourceManager, const GLchar *file, bool alpha);
Shader LoadShader(ResourceManager, const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
Shader GetShader(ResourceManager, char* name);
Texture2D LoadTexture(ResourceManager, const GLchar *file, bool alpha, char* name);
Texture2D GetTexture(ResourceManager, char* name);
void Dtor(ResourceManager);
ResourceManager ResourceManager_New();
static char* rdbuf(FILE* f);

#endif RESOURCE_MANAGER_H