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
type (Shader) {
    Class isa;
    GLuint Id; 
};
/**
 * Shader API
 */
// Shader* Shader_init(Shader* const this);
// Shader* Shader_alloc();
// Shader* NewShader();

interface (Shader, ToString,    char*, (const Game* const));
interface (Shader, Use,         Shader*, (Shader*));
interface (Shader, Compile,     Shader*, (Shader* const, const GLchar*, const GLchar*));
interface (Shader, SetFloat,    Shader*, (Shader*, const GLchar*, const GLfloat));
interface (Shader, SetInteger,  Shader*, (Shader*, const GLchar*, const GLint));
interface (Shader, SetArray2f,  Shader*, (Shader*, const GLchar*, const GLfloat, const GLfloat));
interface (Shader, SetArray2,   Shader*, (Shader*, const GLchar*, const GLfloat*));
interface (Shader, SetArray3f,  Shader*, (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat));
interface (Shader, SetArray3,   Shader*, (Shader*, const GLchar*, const GLfloat*));
interface (Shader, SetArray4f,  Shader*, (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat, const GLfloat));
interface (Shader, SetArray4,   Shader*, (Shader*, const GLchar*, const GLfloat*));
interface (Shader, SetMatrix,   Shader*, (Shader*, const GLchar*, const GLfloat*));
interface (Shader, SetMatrix4,  Shader*, (Shader*, const GLchar*, const GLfloat*));

function void checkCompileErrors(Shader* const, const GLuint, const char*);


vtable (Shader) {
    ShaderToString          ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
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

/**
 * Put it all together
 */
function vptr(Shader);
/**
 * Class Loader callback
 */
function objc_loadShader(Class super) 
{
    Class cls = createClass(super, Shader);
    addMethod(cls, Shader,  ToString);
    addMethod(cls, Object,  Equals);
    addMethod(cls, Object,  GetHashCode);
    addMethod(cls, Object,  Dispose);
    addMethod(cls, Shader,  Use);
    addMethod(cls, Shader,  Compile);
    addMethod(cls, Shader,  SetFloat));
    addMethod(cls, Shader,  SetInteger));
    addMethod(cls, Shader,  SetArray2f));
    addMethod(cls, Shader,  SetArray2));
    addMethod(cls, Shader,  SetArray3f));
    addMethod(cls, Shader,  SetArray3));
    addMethod(cls, Shader,  SetArray4f));
    addMethod(cls, Shader,  SetArray4));
    addMethod(cls, Shader,  SetMatrix4));
    addMethod(cls, Shader,  SetMatrix));

    return cls;
}

/**
 * Shader
 */
Shader* Shader_init(Shader* const this)
{
	DSObject_init(this);
    this->isa = getShaderIsa();
    return this;
}

const char* VERSION = "#version 300 es\n";
const char* HEADER = "#\n"
                    "#ifdef GL_ES\n"
                    "precision mediump float;\n"
                    "#endif\n";

/**
 * Use shader
 */
method Shader* Use(Shader* const this)
{
    glUseProgram(this->Id);
    return this;
}

/**
 * Compile
 * 
 * @param vertexSource vertex shader source code
 * @param fragmentSource fragment shader source code
 * 
 */
method void Compile(
    Shader* const this, 
    const GLchar* vertexSource, 
    const GLchar* fragmentSource)
{
    GLuint sVertex, sFragment;
    // Vertex Shader
    char* vSource[] = { VERSION, HEADER, vertexSource };
    int vLength[] = { strlen(VERSION), strlen(HEADER), strlen(vertexSource) };
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 3, vSource, vLength);
    glCompileShader(sVertex);
    checkCompileErrors(this, sVertex, "VERTEX");
    // Fragment Shader
    char* fSource[] = { VERSION, HEADER, fragmentSource };
    int fLength[] = { strlen(VERSION), strlen(HEADER), strlen(fragmentSource) };
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 3, fSource, fLength);
    glCompileShader(sFragment);
    checkCompileErrors(this, sFragment, "FRAGMENT");
    // Shader Program
    this->Id = glCreateProgram();
    glAttachShader(this->Id, sVertex);
    glAttachShader(this->Id, sFragment);
    glLinkProgram(this->Id);
    checkCompileErrors(this, this->Id, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

method Shader* SetFloat(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat value) {
    glUniform1f(glGetUniformLocation(this->Id, name), value);
    return this;
}

method Shader* SetInteger(
    Shader* const this, 
    const GLchar *name, 
    const GLint value) {
    glUniform1i(glGetUniformLocation(this->Id, name), value);
    return this;
}

method Shader* SetArray2f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y) {
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
    return this;
}

method Shader* SetArray2(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform2f(glGetUniformLocation(this->Id, name), value[0], value[1]);
    return this;
}

method Shader* SetArray3f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y, 
    const GLfloat z) {
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
    return this;
}

method Shader* SetArray3(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform3f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2]);
    return this;
}

method Shader* SetArray4f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y, 
    const GLfloat z, 
    const GLfloat w) {
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
    return this;
}

method Shader* SetArray4(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform4f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2], value[3]);
    return this;
}

method Shader* SetMatrix(
    Shader* const this, 
    const GLchar *name,  
    const GLfloat * matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

method Shader* SetMatrix4(
    Shader* const this, 
    const GLchar *name,  
    const GLfloat* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

function void checkCompileErrors(
    Shader* const this, 
    const GLuint object, 
    const char* type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            DSLog("| ERROR::SHADER: Compile-time error: Type: %s", type);
            DSLog("%s", infoLog);
            DSLog("-- --------------------------------------------------- -- ");
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            DSLog("| ERROR::SHADER: Link-time error: Type: %s", type);
            DSLog("%s", infoLog);
            DSLog("-- --------------------------------------------------- -- ");
        }
    }
}

/**
 * ToString
 */
method char* ToString(const Shader* const this)
{
    return "Shader";
}

