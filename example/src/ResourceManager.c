/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <ResourceManager.h>

/**
 * Constructor
 */
TResourceManager ResourceManager_Ctor(TResourceManager this)
{
    Object_Ctor(this); 
    this->isa = isa(ResourceManager);
    return this;
}

/**
 * ResourceManager Class Metadata
 */
register (ResourceManager)
{
    if (ResourceManager.isa == nullptr) {
        ResourceManager = (struct ResourceManagerClass) {
            .isa        = &ResourceManager,
            .superclass = &Object,
            .name       = "ResourceManager",
            /** VTable */
            .ToString           = Object.ToString,
            .Equals             = Object.Equals,
            .GetHashCode        = Object.GetHashCode,
            .Dispose            = Object.Dispose,
            .ReferenceEquals    = Object.ReferenceEquals,
            .InstanceEquals     = Object.InstanceEquals,
            .Create             = ResourceManager_New,
            .LoadShader         = LoadShader,
            .GetShader          = GetShader,
            .LoadTexture        = LoadTexture,
            .GetTexture         = GetTexture,
            .Dtor               = Dtor,
            .loadShaderFromFile = loadShaderFromFile,
            .loadTextureFromFile= loadTextureFromFile,
            .Shaders            = Hashmap.Create(),
            .Textures           = Hashmap.Create(),

        };
        AddMetadata(ResourceManager);
    }
    return &ResourceManager;
}

/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */
static TShader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    // char* vertexCode;
    // char* fragmentCode;
    // Open files
    char* vFile = join("assets/", vShaderFile);
    char* fFile = join("assets/", fShaderFile);

    FILE* vertexShaderFile = fopen(vFile, "r");
    FILE* fragmentShaderFile = fopen(fFile, "r");

    if (!vertexShaderFile) printf("Unable to open %s\n", vShaderFile);
    if (!fragmentShaderFile) printf("Unable to open %s\n", fShaderFile);

    // Read file's buffer contents into streams
    const GLchar *vShaderCode = rdbuf(vertexShaderFile);
    const GLchar *fShaderCode = rdbuf(fragmentShaderFile);
    // close file handlers
    fclose(vertexShaderFile);
    fclose(fragmentShaderFile);

    // 2. Now create shader object from source code
    TShader shader = Shader.Create();
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
static TTexture2D loadTextureFromFile(const GLchar *file, bool alpha)
{
    // Create Texture object
    int format = alpha ? GL_RGBA : GL_RGB;
    char* path = join("assets/", file);
    int width, height, channels;
    TTexture2D texture = Texture2D.Create(format, format, path);
    // Load image
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0); //texture->ImageFormat == GL_RGBA ? 4 : 3);
    // Now generate texture
    Generate(texture, width, height, image);
    
    // And finally free image data
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
TShader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, char* name)
{
    Put(ResourceManager.Shaders, name, loadShaderFromFile(vShaderFile, fShaderFile));
    return Get(ResourceManager.Shaders, name);
    // return s;
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
TShader GetShader(char* name)
{
    return Get(ResourceManager.Shaders, name);
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
TTexture2D LoadTexture(const GLchar *file, bool alpha, char* name)
{
    TTexture2D tex = loadTextureFromFile(file, alpha);
    Put(ResourceManager.Textures, name, tex);
    return tex;
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
TTexture2D GetTexture(char* name)
{
    TTexture2D tex = Get(ResourceManager.Textures, name);
    return tex;
}

Clear1(Any item, Any data)
{
    TShader s = data;
    glDeleteProgram(s->Id);
}

Clear2(Any item, Any data)
{
    TTexture2D t = data;
    glDeleteTextures(1, &t->Id);
}

void Dtor(TResourceManager this)
{
    // (Properly) delete all shaders	
    // Iterate(ResourceManager.Shaders, Clear1, nullptr);
    // (Properly) delete all textures
    // Iterate(ResourceManager.Textures, Clear2, nullptr);
}

TResourceManager ResourceManager_New()
{
    return ResourceManager_Ctor(new(ResourceManager));
}

/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
static char* rdbuf(FILE* f)
{
    fseek(f, 0L, SEEK_END);
    long s = ftell(f);
    rewind(f);
    char* buf = dark_calloc(1, s+1);
    buf[s] = '\0';

    if (buf != nullptr)
    {
        fread(buf, s, 1, f);
        return buf;
    }
    return buf;
}

