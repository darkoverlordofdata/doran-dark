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
#include <dark/Foundation.h>

#define IsShader(x) (x->isa == &ShaderClass)
#define AsShader(x) (IsShader(x) ? (Shader*)x : nullptr)

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
ivar (Shader) {
    Class isa;
    GLuint Id; 
};

typedef char*   (*ShaderToString)  (const Shader* const);

class (Shader) {
    Shader* (*Create) (void);
};

vtable (Shader) {
    char*   (*ToString) (const Shader* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);

    // Sets the current shader as active
    Shader*  (*Use)          (Shader* const);
    // Compiles the shader from given source code
    void    (*Compile)      (Shader* const, const GLchar *vertexSource, const GLchar *fragmentSource); 
    // Utility functions
    Shader*  (*SetFloat)     (Shader* const, const GLchar *name, const GLfloat value);
    Shader*  (*SetInteger)   (Shader* const, const GLchar *name, const GLint value);
    Shader*  (*SetArray2f)   (Shader* const, const GLchar *name, const GLfloat x, const GLfloat y);
    Shader*  (*SetArray2)    (Shader* const, const GLchar *name, const GLfloat *value);
    Shader*  (*SetArray3f)   (Shader* const, const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z);
    Shader*  (*SetArray3)    (Shader* const, const GLchar *name, const GLfloat *value);
    Shader*  (*SetArray4f)   (Shader* const, const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);
    Shader*  (*SetArray4)    (Shader* const, const GLchar *name, const GLfloat *value);
    Shader*  (*SetMatrix4)   (Shader* const, const GLchar *name, const GLfloat *matrix);
    Shader*  (*SetMatrix)    (Shader* const, const GLchar *name, const GLfloat *matrix);
    
};

/**
 * Shader API
 */
Shader* overload Use(Shader*);
void overload Compile(Shader* const, const GLchar* vertexSource, const GLchar* fragmentSource);
Shader* overload SetFloat(Shader*, const GLchar *name, const GLfloat value);
Shader* overload SetInteger(Shader*, const GLchar *name, const GLint value);
Shader* overload SetArray2f(Shader*, const GLchar *name, const GLfloat x, const GLfloat y);
Shader* overload SetArray2(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetArray3f(Shader*, const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z);
Shader* overload SetArray3(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetArray4f(Shader*, const GLchar *name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);
Shader* overload SetArray4(Shader*, const GLchar *name, const GLfloat* value);
Shader* overload SetMatrix(Shader*, const GLchar *name,  const GLfloat * matrix);
Shader* overload SetMatrix4(Shader*, const GLchar *name,  const GLfloat* matrix);
char* overload ToString(const Shader* const);
Shader* Shader_init(Shader* const this);
Shader* Shader_alloc();
Shader* NewShader();
static void checkCompileErrors(Shader* const, const GLuint, const char*);
