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

#define IsShader(x) (x->isa == &ShaderClass)
#define AsShader(x) (IsShader(x) ? (Shader*)x : nullptr)

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class (Shader)
{
    struct ShaderClass* isa;
    GLuint Id; 
};

struct ShaderClass
{
    Class  isa;
    Class  superclass;
    char*   name;
    long    version, info, instance_size;
    char*   (*ToString) (Shader* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    Shader* (*Create) (void);

    // Sets the current shader as active
    Shader*  (*Use)          (Shader* const);
    // Compiles the shader from given source code
    void    (*Compile)      (Shader* const, const GLchar *vertexSource, const GLchar *fragmentSource); // Note: geometry source code is optional 
    // Utility functions
    Shader*  (*SetFloat)     (Shader* const, const GLchar *name, GLfloat value);
    Shader*  (*SetInteger)   (Shader* const, const GLchar *name, GLint value);
    Shader*  (*SetArray2f)   (Shader* const, const GLchar *name, GLfloat x, GLfloat y);
    Shader*  (*SetArray2)    (Shader* const, const GLchar *name, GLfloat *value);
    Shader*  (*SetArray3f)   (Shader* const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
    Shader*  (*SetArray3)    (Shader* const, const GLchar *name, GLfloat *value);
    Shader*  (*SetArray4f)   (Shader* const, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    Shader*  (*SetArray4)    (Shader* const, const GLchar *name, GLfloat *value);
    Shader*  (*SetMatrix4)   (Shader* const, const GLchar *name, GLfloat *matrix);
    Shader*  (*SetMatrix)    (Shader* const, const GLchar *name, GLfloat *matrix);
    
} ShaderClass;

/**
 * Shader API
 */
Shader* overload Use(Shader*);
void overload Compile(Shader*, const GLchar* vertexSource, const GLchar* fragmentSource);
Shader* overload SetFloat(Shader*, const GLchar *name, GLfloat value);
Shader* overload SetInteger(Shader*, const GLchar *name, GLint value);
Shader* overload SetArray2f(Shader*, const GLchar *name, GLfloat x, GLfloat y);
Shader* overload SetArray2(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetArray3f(Shader*, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
Shader* overload SetArray3(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetArray4f(Shader*, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
Shader* overload SetArray4(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetMatrix(Shader*, const GLchar *name,  GLfloat * matrix);
Shader* overload SetMatrix4(Shader*, const GLchar *name,  GLfloat* matrix);
char* overload ToString(Shader* const);

