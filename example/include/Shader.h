/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.h>
#include <dark/darkfx.h>

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class (Shader)
{
    ShaderClass_t* isa;
    GLuint Id; 
};

typedef struct ShaderClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (Shader const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };

    // Sets the current shader as active
    Shader  (*Use)          (Shader const);
    // Compiles the shader from given source code
    void    (*Compile)      (Shader const, const GLchar *vertexSource, const GLchar *fragmentSource); // Note: geometry source code is optional 
    // Utility functions
    Shader  (*SetFloat)     (Shader const, const GLchar *name, GLfloat value);
    Shader  (*SetInteger)   (Shader const, const GLchar *name, GLint value);
    Shader  (*SetArray2f)   (Shader const, const GLchar *name, GLfloat x, GLfloat y);
    Shader  (*SetArray2)    (Shader const, const GLchar *name, GLfloat *value);
    Shader  (*SetArray3f)   (Shader const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    Shader  (*SetArray3)    (Shader const, const GLchar *name, GLfloat *value);
    Shader  (*SetArray4f)   (Shader const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    Shader  (*SetArray4)    (Shader const, const GLchar *name, GLfloat *value);
    Shader  (*SetMatrix4)   (Shader const, const GLchar *name, GLfloat *matrix);
    Shader  (*SetMatrix)    (Shader const, const GLchar *name, GLfloat *matrix);
};

/**
 * Shader API
 */
Shader overload Use(Shader);
void overload Compile(Shader, const GLchar* vertexSource, const GLchar* fragmentSource);
Shader overload SetFloat(Shader, const GLchar *name, GLfloat value);
Shader overload SetInteger(Shader, const GLchar *name, GLint value);
Shader overload SetArray2f(Shader, const GLchar *name, GLfloat x, GLfloat y);
Shader overload SetArray2(Shader, const GLchar *name, const GLfloat* value);
Shader overload SetArray3f(Shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
Shader overload SetArray3(Shader, const GLchar *name, const GLfloat* value);
Shader overload SetArray4f(Shader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
Shader overload SetArray4(Shader, const GLchar *name, const GLfloat* value);
Shader overload SetMatrix(Shader, const GLchar *name,  GLfloat * matrix);
Shader overload SetMatrix4(Shader, const GLchar *name,  GLfloat* matrix);
const char* overload ToString(Shader const);
Shader Shader_New();

#endif SHADER_H