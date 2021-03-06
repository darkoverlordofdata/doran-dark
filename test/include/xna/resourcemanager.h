#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include "texture2d.h"
#include "shader.h"

type (ResourceManager)
{
    Class isa;
    Map* Shaders;
    Map* Textures;
};

method Shader* LoadShaderFromFile(ResourceManager* self, const GLchar *vShaderFile, const GLchar *fShaderFile);
method Texture2D* LoadTextureFromFile(ResourceManager* self, const GLchar *file, GLboolean alpha);


/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
static inline char* ReadTextFile(FILE* f)
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


method void Init(ResourceManager* self)
{
    self->Shaders = new(Map, of(Shader));
    self->Textures = new(Map, of(Texture2D));
}

method ResourceManager* New(ResourceManager* self)
{
	extends(Object);
    self->isa = isa(ResourceManager);
    Init(self);
    return self;
}

method void Dispose(ResourceManager* self)
{
    Dispose(self->Shaders);
    Dispose(self->Textures);
    if (_use_gc) return;
    free(self);
}

/**
 * LoadShader
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @param name to cache as
 * @returns loaded, compiled and linked shader program
 */
method Shader* LoadShader(
    ResourceManager* self, 
    const GLchar *vShaderFile, 
    const GLchar *fShaderFile, 
    const char* name)
{
    Put(self->Shaders, name, LoadShaderFromFile(self, vShaderFile, fShaderFile));
    return Get(self->Shaders, name);
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
method Shader* GetShader(
    ResourceManager* self, 
    const char* name)
{
    return Get(self->Shaders, name);    
}

/**
 * loadTexture
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @param name to cache as
 * @returns Texture
 * 
 */
method Texture2D* LoadTexture(
    ResourceManager* self, 
    const GLchar *file, 
    GLboolean alpha,
    const char* name)
{
    Put(self->Textures, name, LoadTextureFromFile(self, file, alpha));
    return Get(self->Textures, name);
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
method Texture2D* GetTexture(
    ResourceManager* self, 
    const char* name)
{
    return Get(self->Textures, name);    
}

method void Clear(ResourceManager* self)
{
    Dispose(self->Shaders);
    Dispose(self->Textures);
    self->Shaders = new(Map);
    self->Textures = new(Map);

}

// static inline char* join(const char* s1, const char* s2) { return nullptr;}
/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */
method Shader* LoadShaderFromFile(
    ResourceManager* self, 
    const GLchar *vShaderFile, 
    const GLchar *fShaderFile)
{
    FILE* vertexShaderFile = fopen(vShaderFile, "r");
    FILE* fragmentShaderFile = fopen(fShaderFile, "r");

    if (!vertexShaderFile) Log("Unable to open %s", vShaderFile);
    if (!fragmentShaderFile) Log("Unable to open %s", fShaderFile);

    // Read file's buffer contents into streams
    const GLchar *vShaderCode = ReadTextFile(vertexShaderFile);
    const GLchar *fShaderCode = ReadTextFile(fragmentShaderFile);
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
method Texture2D* LoadTextureFromFile(
    ResourceManager* self, 
    const GLchar *file, 
    GLboolean alpha)
{
    int format = alpha ? GL_RGBA : GL_RGB;
    char* path = join("assets/", file);
    
    Texture2D* texture = new(Texture2D, format, format, path);
    
    SDL_Surface * surface = IMG_Load(file);
    if (SDL_MUSTLOCK(surface)) 
        SDL_LockSurface(surface);
    // Now generate texture
    printf("%s: (%d,%d)\n", file, surface->w, surface->h);
    Generate(texture, surface->w, surface->h, (unsigned char*)surface->pixels);
    if (SDL_MUSTLOCK(surface)) 
        SDL_UnlockSurface(surface);
    // And finally free image data
    SDL_FreeSurface(surface);
    return texture;

}
