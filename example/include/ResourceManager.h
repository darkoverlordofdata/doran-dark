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

#include "Shader.h"
#include "Texture.h"

#define IsDResourceManager(object) _Generic((object), DResourceManager*: true, default: false)
#define AsDResourceManager(object) _Generic((object),                           \
                            DResourceManager*: (DResourceManager *)object,      \
                            default: nullptr)

// A singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. 

type (ResourceManager) {
    Class isa;
};
/**
 * ResourceManager API
 */
// ResourceManager* NewResourceManager();
// ResourceManager* ResourceManager_init(ResourceManager* this);
// ResourceManager* ResourceManager_alloc();

interface (ResourceManager, ToString,     char*, (const ResourceManager* const));

Shader*     LoadShader(const GLchar*, const GLchar*, char*);
Shader*     GetShader(char*);
Texture2D*  LoadTexture(const GLchar*, bool, char*);
Texture2D*  GetTexture(char*);
void        Dtor(ResourceManager*);

static  char*       rdbuf(FILE* f);
static  Shader*     loadShaderFromFile(const GLchar*, const GLchar*);
static  Texture2D*  loadTextureFromFile(const GLchar*, bool);


vtable (ResourceManager) {
    ResourceManagerToString ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
};

class (ResourceManager) {
    Map* Shaders;
    Map* Textures;
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
};

/**
 * Put it all together
 */
function vptr(ResourceManager);
/**
 * Class Loader callback
 */
function objc_loadResourceManager(Class super) 
{
    Class cls = createClass(super, ResourceManager);

    $ResourceManager.Shaders = new(Map, ofShader);
    $ResourceManager.Textures = new(Map, ofTexture2D);
    $ResourceManager.LoadShader = LoadShader);
    $ResourceManager.GetShader = GetShader);
    $ResourceManager.LoadTexture = LoadTexture);
    $ResourceManager.GetTexture = GetTexture);
    $ResourceManager.Dtor = Dtor);
    $ResourceManager.loadShaderFromFile = loadShaderFromFile);
    $ResourceManager.loadTextureFromFile = loadTextureFromFile);
    return cls;
}