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
#include <tglm/tglm.h>
#include <dark/darkfx.h>

#define IsShader(x) (x->isa == &Shader)
#define AsShader(x) (IsShader(x) ? (struct Shader *)x : nullptr)

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class (Shader)
{
    struct ShaderClass * isa;
    GLuint Id; 
};

struct ShaderClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TShader const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TShader (*Create) (void);
        };
    };

    // Sets the current shader as active
    TShader  (*Use)          (TShader const);
    // Compiles the shader from given source code
    void    (*Compile)      (TShader const, const GLchar *vertexSource, const GLchar *fragmentSource); // Note: geometry source code is optional 
    // Utility functions
    TShader  (*SetFloat)     (TShader const, const GLchar *name, GLfloat value);
    TShader  (*SetInteger)   (TShader const, const GLchar *name, GLint value);
    TShader  (*SetArray2f)   (TShader const, const GLchar *name, GLfloat x, GLfloat y);
    TShader  (*SetArray2)    (TShader const, const GLchar *name, GLfloat *value);
    TShader  (*SetArray3f)   (TShader const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    TShader  (*SetArray3)    (TShader const, const GLchar *name, GLfloat *value);
    TShader  (*SetArray4f)   (TShader const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    TShader  (*SetArray4)    (TShader const, const GLchar *name, GLfloat *value);
    TShader  (*SetMatrix4)   (TShader const, const GLchar *name, GLfloat *matrix);
    TShader  (*SetMatrix)    (TShader const, const GLchar *name, GLfloat *matrix);
};

/**
 * Shader API
 */
TShader overload Use(TShader);
void overload Compile(TShader, const GLchar* vertexSource, const GLchar* fragmentSource);
TShader overload SetFloat(TShader, const GLchar *name, GLfloat value);
TShader overload SetInteger(TShader, const GLchar *name, GLint value);
TShader overload SetArray2f(TShader, const GLchar *name, GLfloat x, GLfloat y);
TShader overload SetArray2(TShader, const GLchar *name, const GLfloat* value);
TShader overload SetArray3f(TShader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
TShader overload SetArray3(TShader, const GLchar *name, const GLfloat* value);
TShader overload SetArray4f(TShader, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
TShader overload SetArray4(TShader, const GLchar *name, const GLfloat* value);
TShader overload SetMatrix(TShader, const GLchar *name,  GLfloat * matrix);
TShader overload SetMatrix4(TShader, const GLchar *name,  GLfloat* matrix);
char* overload ToString(TShader const);

