/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software:ou can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (atour
** option) any later version.
******************************************************************/
#pragma once
#include <GL/glew.h>
#include <tglm/tglm.h>
#include <dark/Foundation.h>

#define IsShader(x) (x->isa == &ShaderClass)
#define AsShader(x) (IsShader(x) ? (Shader*)x : nullptr)
#define IsShader(object) _Generic((object), Shader*: true, default: false)
#define AsShader(object) _Generic((object),                     \
                            Shader*: (Shader *)object,          \
                            default: nullptr)

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
ivar (Shader) {
    Class isa;
    GLuint Id; 
};

Shader* Shader_init(Shader* const this);
Shader* Shader_alloc();
Shader* NewShader();

char*   overload ToString(const Shader* const);
Shader* overload Use(Shader*);
void    overload Compile(Shader* const, const GLchar*, const GLchar*);
Shader* overload SetFloat(Shader*, const GLchar*, const GLfloat);
Shader* overload SetInteger(Shader*, const GLchar*, const GLint);
Shader* overload SetArray2f(Shader*, const GLchar*, const GLfloat, const GLfloat);
Shader* overload SetArray2(Shader*, const GLchar*, const GLfloat*);
Shader* overload SetArray3f(Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat);
Shader* overload SetArray3(Shader*, const GLchar*, const GLfloat*);
Shader* overload SetArray4f(Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat, const GLfloat);
Shader* overload SetArray4(Shader*, const GLchar*, const GLfloat*);
Shader* overload SetMatrix(Shader*, const GLchar*, const GLfloat*);
Shader* overload SetMatrix4(Shader*, const GLchar*, const GLfloat*);

static void checkCompileErrors(Shader* const, const GLuint, const char*);

typedef char*   (*ShaderToString)   (const Shader* const);
typedef Shader* (*ShaderUse)        (Shader*);
typedef Shader* (*ShaderCompile)    (Shader* const, const GLchar*, const GLchar*);
typedef Shader* (*ShaderSetFloat)   (Shader*, const GLchar*, const GLfloat);
typedef Shader* (*ShaderSetInteger) (Shader*, const GLchar*, const GLint);
typedef Shader* (*ShaderSetArray2f) (Shader*, const GLchar*, const GLfloat, const GLfloat);
typedef Shader* (*ShaderSetArray2)  (Shader*, const GLchar*, const GLfloat*);
typedef Shader* (*ShaderSetArray3f) (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat);
typedef Shader* (*ShaderSetArray3)  (Shader*, const GLchar*, const GLfloat*);
typedef Shader* (*ShaderSetArray4f) (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat, const GLfloat);
typedef Shader* (*ShaderSetArray4)  (Shader*, const GLchar*, const GLfloat*);
typedef Shader* (*ShaderSetMatrix)  (Shader*, const GLchar*, const GLfloat*);
typedef Shader* (*ShaderSetMatrix4) (Shader*, const GLchar*, const GLfloat*);


vtable (Shader) {
    ShaderToString          ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    ShaderUse               Use;
    ShaderCompile           Compile;
    ShaderSetFloat          SetFloat;
    ShaderSetInteger        SetInteger;
    ShaderSetArray2f        SetArray2f;
    ShaderSetArray2         SetArray2;
    ShaderSetArray3f        SetArray3f;
    ShaderSetArray3         SetArray3;
    ShaderSetArray4f        SetArray4f;
    ShaderSetArray4         SetArray4;
    ShaderSetMatrix4        SetMatrix4;
    ShaderSetMatrix         SetMatrix;
};

class (Shader) {
    Shader* (*Create) (void);
};


