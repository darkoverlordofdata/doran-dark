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
ResourceManager ResourceManager_Ctor(ResourceManager this)
{
    Object_Ctor(this); 
    this->isa = isa(ResourceManager);
    this->Shaders = Hashmap_New();
    this->Textures = Hashmap_New();
    return this;
}

/**
 * ResourceManager Class Metadata
 */
register (ResourceManager)
{
    if (ResourceManagerClass.isa == nullptr) {
        ResourceManagerClass = (ResourceManagerClass_t) {
            .isa        = &ResourceManagerClass,
            .superclass = &ObjectClass,
            .name       = "ResourceManager",
            /** VTable */
            .ToString           = ObjectClass.ToString,
            .Equals             = ObjectClass.Equals,
            .GetHashCode        = ObjectClass.GetHashCode,
            .Dispose            = ObjectClass.Dispose,
            .ReferenceEquals    = ObjectClass.ReferenceEquals,
            .InstanceEquals     = ObjectClass.InstanceEquals,
            .LoadShader         = LoadShader,
            .GetShader          = GetShader,
            .LoadTexture        = LoadTexture,
            .GetTexture         = GetTexture,
            .Dtor               = Dtor,
            .loadShaderFromFile = loadShaderFromFile,
            .loadTextureFromFile= loadTextureFromFile,
        };
        AddMetadata(ResourceManager);
    }
    return &ResourceManagerClass;
}

/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */
static Shader loadShaderFromFile(ResourceManager this, const GLchar *vShaderFile, const GLchar *fShaderFile)
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
    Shader shader = Shader_New();
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
static Texture2D loadTextureFromFile(ResourceManager this, const GLchar *file, bool alpha)
{
    // Create Texture object
    int format = alpha ? GL_RGBA : GL_RGB;
    char* path = join("assets/", file);
    int width, height, channels;
    Texture2D texture = Texture2D_New(format, format, path);
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
Shader LoadShader(ResourceManager this, const GLchar *vShaderFile, const GLchar *fShaderFile, char* name)
{
    Put(this->Shaders, name, loadShaderFromFile(this, vShaderFile, fShaderFile));
    return Get(this->Shaders, name);
    // return s;
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
Shader GetShader(ResourceManager this, char* name)
{
    return Get(this->Shaders, name);
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
Texture2D LoadTexture(ResourceManager this, const GLchar *file, bool alpha, char* name)
{
    Texture2D tex = loadTextureFromFile(this, file, alpha);
    Put(this->Textures, name, tex);
    return tex;
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
Texture2D GetTexture(ResourceManager this, char* name)
{
    Texture2D tex = Get(this->Textures, name);
    return tex;
}

Clear1(Any item, Any data)
{
    Shader s = data;
    glDeleteProgram(s->Id);
}

Clear2(Any item, Any data)
{
    Texture2D t = data;
    glDeleteTextures(1, &t->Id);
}

void Dtor(ResourceManager this)
{
    // (Properly) delete all shaders	
    Iterate(this->Shaders, Clear1, nullptr);
    // (Properly) delete all textures
    Iterate(this->Textures, Clear2, nullptr);
}

ResourceManager ResourceManager_New()
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

