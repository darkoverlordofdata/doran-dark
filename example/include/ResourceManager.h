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

#include "Shader.h"
#include "Texture.h"

#define IsResourceManager(x) (x->isa == &ResourceManagerClass)
#define AsResourceManager(x) (IsResourceManager(x) ? (ResourceManager*)x : nullptr)

// A singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. 

class (ResourceManager)
{
    struct ResourceManagerClass * isa;
};

extern struct ResourceManagerClass* Resources;

struct ResourceManagerClass
{
    struct  Class * isa;
    struct  Class * superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (ResourceManager* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    ResourceManager*  (*Create) ();

    DSHashmap* Shaders;
    DSHashmap* Textures;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    Shader*      (*LoadShader)           (const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
    // Retrieves a stored sader
    Shader*      (*GetShader)            (char* name);
    // Loads (and generates) a texture from file
    Texture2D*   (*LoadTexture)          (const GLchar *file, GLboolean alpha, char* name);
    // Retrieves a stored texture
    Texture2D*   (*GetTexture)           (char* name);
    // Properly de-allocates all loaded resources
    void        (*Dtor)                 (ResourceManager* const);
    // Loads and generates a shader from file
    Shader*      (*loadShaderFromFile)   (const GLchar *vShaderFile, const GLchar *fShaderFile);
    // Loads a single texture from file
    Texture2D*   (*loadTextureFromFile)  (const GLchar *file, GLboolean alpha);
    
} ResourceManagerClass;

static Shader* loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);
static Texture2D* loadTextureFromFile(const GLchar *file, bool alpha);
Shader* LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, char* name);
Shader* GetShader(char* name);
Texture2D* LoadTexture(const GLchar *file, bool alpha, char* name);
Texture2D* GetTexture(char* name);
void Dtor(ResourceManager*);
static char* rdbuf(FILE* f);

