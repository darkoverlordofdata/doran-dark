/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Shader.h>
#include "imp/Shader.h"
/**
 * Shader
 */
Shader* NewShader() { 
    return Shader_init(Shader_alloc());
}


Shader* Shader_init(Shader* const this)
{
	DSObject_init(this);
    this->isa = getShaderIsa();
    return this;
}

Shader* Shader_alloc() {
    return DSMalloc(getShaderSize());
}


const char* VERSION = "#version 300 es\n";
const char* HEADER = "#\n"
                    "#ifdef GL_ES\n"
                    "precision mediump float;\n"
                    "#endif\n";

/**
 * Use shader
 */
Shader* overload Use(Shader* this)
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
void overload Compile(
    Shader* this, 
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

Shader* overload SetFloat(
    Shader* this, 
    const GLchar *name, 
    GLfloat value) {
    glUniform1f(glGetUniformLocation(this->Id, name), value);
    return this;
}

Shader* overload SetInteger(
    Shader* this, 
    const GLchar *name, 
    GLint value) {
    glUniform1i(glGetUniformLocation(this->Id, name), value);
    return this;
}

Shader* overload SetArray2f(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y) {
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
    return this;
}

Shader* overload SetArray2(
    Shader* this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform2f(glGetUniformLocation(this->Id, name), value[0], value[1]);
    return this;
}

Shader* overload SetArray3f(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z) {
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
    return this;
}

Shader* overload SetArray3(
    Shader* this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform3f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2]);
    return this;
}

Shader* overload SetArray4f(
    Shader* this, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLfloat w) {
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
    return this;
}

Shader* overload SetArray4(
    Shader* this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform4f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2], value[3]);
    return this;
}

Shader* overload SetMatrix(
    Shader* this, 
    const GLchar *name,  
    GLfloat * matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

Shader* overload SetMatrix4(
    Shader* this, 
    const GLchar *name,  
    GLfloat* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

static void checkCompileErrors(
    Shader* this, 
    GLuint object, 
    char* type) {
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
char* overload ToString(const Shader* const this)
{
    return "Shader";
}

