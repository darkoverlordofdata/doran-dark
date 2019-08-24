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

type (ResourceManager) 
{
    Class isa;
};
delegate (ResourceManager, New,      ResourceManager*, (ResourceManager*));
delegate (ResourceManager, ToString, char*, (const ResourceManager* const));

static  char*       rdbuf(FILE* f);
static  Shader*     loadShaderFromFile(const GLchar*, const GLchar*);
static  Texture2D*  loadTextureFromFile(const GLchar*, bool);

vtable (ResourceManager) 
{
    ResourceManagerToString ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
};

class (ResourceManager) 
{
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
static inline vptr(ResourceManager);
/**
 * Class Loader callback0
 */

/**
 * ResourceManager
 */
static inline ResourceManager* ResourceManager_ctor(ResourceManager* self) {
    New((Object*)self); 
    self->isa = objc_getClass("ResourceManager");
    return self;
}

/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */
static inline Shader* loadShaderFromFile(
    const GLchar *vShaderFile, 
    const GLchar *fShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    // char* vertexCode;
    // char* fragmentCode;
    // Open files
    char* vFile = join("assets/", vShaderFile);
    char* fFile = join("assets/", fShaderFile);

    FILE* vertexShaderFile = fopen(vFile, "r");
    FILE* fragmentShaderFile = fopen(fFile, "r");

    if (!vertexShaderFile) Log("Unable to open %s", vShaderFile);
    if (!fragmentShaderFile) Log("Unable to open %s", fShaderFile);

    // Read file's buffer contents into streams
    const GLchar *vShaderCode = rdbuf(vertexShaderFile);
    const GLchar *fShaderCode = rdbuf(fragmentShaderFile);

    // close file handlers
    fclose(vertexShaderFile);
    fclose(fragmentShaderFile);

    // 2. Now create shader object from source code
    Shader* shader = new(Shader);
    Compile(shader, vShaderCode, fShaderCode);
    return shader;
}

/**
 * loadTextureFromFile
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @returns Texture
 * 
 */
static inline Texture2D* loadTextureFromFile(const GLchar *file, bool alpha)
{
    // Create Texture object
    int format = alpha ? GL_RGBA : GL_RGB;
    char* path = join("assets/", file);
    int width, height, channels;
    
    Texture2D* texture = new(Texture2D, format, format, path);
    // Load image
    unsigned char* image = stbi_load(path, &width, &height, &channels, texture->ImageFormat == GL_RGBA ? 4 : 3); //texture->ImageFormat == GL_RGBA ? 4 : 3);
    // generate texture
    Generate(texture, width, height, image);
    // And then free image data
    stbi_image_free(image);
    return texture;
}

/**
 * LoadShader
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @param name to cache as
 * @returns loaded, compiled and linked shader program
 */
static inline Shader* LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, char* name)
{
    Put($ResourceManager.Shaders, name, (Object*)loadShaderFromFile(vShaderFile, fShaderFile));
    return (Shader*)Get($ResourceManager.Shaders, name);
    // return s;
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
static inline Shader* GetShader(char* name)
{
    return (Shader*)Get($ResourceManager.Shaders, name);
}

/**
 * loadTextureFromFile
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @param name to cache as
 * @returns Texture
 * 
 */
static inline Texture2D* LoadTexture(const GLchar *file, bool alpha, char* name)
{
    Texture2D* tex = loadTextureFromFile(file, alpha);
    Put($ResourceManager.Textures, name, (Object*)tex);
    return tex;
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
static inline Texture2D* GetTexture(char* name)
{
    Texture2D* tex = (Texture2D*)Get($ResourceManager.Textures, name);
    return tex;
}

// Clear1(Any item, Any data)
// {
//     Shader* s = data;
//     glDeleteProgram(s->Id);
// }

// Clear2(Any item, Any data)
// {
//     Texture2D* t = data;
//     glDeleteTextures(1, &t->Id);
// }

method void Dtor(struct ResourceManager * self)
{
    // (Properly) delete all shaders	
    // Iterate($ResourceManager.Shaders, Clear1, nullptr);
    // (Properly) delete all textures
    // Iterate($ResourceManager.Textures, Clear2, nullptr);
}

/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
static inline char* rdbuf(FILE* f)
{
    fseek(f, 0L, SEEK_END);
    long s = ftell(f);
    rewind(f);
    char* buf = (char*)DScalloc(1, s+1);
    buf[s] = '\0';

    if (buf != nullptr)
    {
        fread(buf, s, 1, f);
        return buf;
    }
    return buf;
}

/**
 * ToString
 */
method char* ToString(const ResourceManager* const self)
{
    return "ResourceManager";
}

/**
 * Class Loader callback0
 */
static inline Class objc_loadResourceManager(Class base) 
{
    Class cls = createClass(base, ResourceManager);
    addMethod(cls, ResourceManager,  ToString);

    $ResourceManager.Shaders = new(Map, of(Shader));
    $ResourceManager.Textures = new(Map, of(Texture2D));
    $ResourceManager.LoadShader = LoadShader;
    $ResourceManager.GetShader = GetShader;
    $ResourceManager.LoadTexture = LoadTexture;
    $ResourceManager.GetTexture = GetTexture;
    $ResourceManager.Dtor = Dtor;
    $ResourceManager.loadShaderFromFile = loadShaderFromFile;
    $ResourceManager.loadTextureFromFile = loadTextureFromFile;
    return cls;
}

