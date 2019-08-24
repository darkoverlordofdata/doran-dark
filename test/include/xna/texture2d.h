#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>

type (Texture2D)
{
    Class isa;
    // Holds the ID of the texture object, used for all texture operations to reference to self particlar texture
    GLuint Id;
    // Texture image dimensions
    GLuint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLuint InternalFormat; // Format of texture object
    GLuint ImageFormat; // Format of loaded image
    // Texture configuration
    GLuint wrapS; // Wrapping mode on S axis
    GLuint wrapT; // Wrapping mode on T axis
    GLuint filterMin; // Filtering mode if texture pixels < screen pixels
    GLuint filterMag; // Filtering mode if texture pixels > screen pixels
    char* path;
};

delegate (Texture2D, New,       Texture2D*, (Texture2D*, int, int, char*));
delegate (Texture2D, ToString,  char*, (const Texture2D* const));
delegate (Texture2D, Generate,  void, (Texture2D*, const GLuint, const GLuint, const unsigned char*));
delegate (Texture2D, Bind,      void, (const Texture2D* const));


vtable (Texture2D) {
    Texture2DToString       ToString;
    ObjectEquals            Equals;
    ObjectGetHashCode       GetHashCode;
    ObjectDispose           Dispose;
    Texture2DGenerate       Generate;
    Texture2DBind           Bind;
};

/**
 * Put it all together
 */
static inline vptr(Texture2D);
/**
 * Class Loader callback
 */
static inline Class objc_loadTexture2D(Class base) 
{
    Class cls = createClass(base, Texture2D);
    addMethod(cls, Texture2D, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Texture2D, Generate);
    addMethod(cls, Texture2D, Bind);

    return cls;
}

/**
 * Texture2D
 * 
 * @param InternalFormat for binding the image
 * @param ImageFormat for binding the image
 * 
 */
method Texture2D* New(
    Texture2D* self,
    int InternalFormat,
    int ImageFormat,
    char* path)
{
	extends(Object);
    self->isa = objc_getClass("Texture2D");
    self->path = strdup(path);
    self->Width = 0;
    self->Height = 0;
    self->InternalFormat = GL_RGB;
    self->ImageFormat = GL_RGB;
    self->wrapS = GL_REPEAT;
    self->wrapT = GL_REPEAT;
    self->filterMin = GL_LINEAR;
    self->filterMag = GL_LINEAR;
    self->InternalFormat = InternalFormat;
    self->ImageFormat = ImageFormat;
    glGenTextures(1, &self->Id);
    return self;
}




/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
method void Generate(
    Texture2D* self, 
    GLuint width, 
    GLuint height, 
    unsigned char* data)
{
    self->Width = width;
    self->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, self->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, self->InternalFormat, width, height, 0, self->ImageFormat, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, self->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, self->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, self->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, self->filterMag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Bind
 * 
 * binds the texture to GL
 */
method void Bind(Texture2D* self)
{
    glBindTexture(GL_TEXTURE_2D, self->Id);    
}

/**
 * Dispose
 * 
 * release resources
 */
method void Dispose(Texture2D* self)
{
    if (!_objc_use_gc) {
        free(self);
    }
}
