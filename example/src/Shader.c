/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Shader.h>
#include <implementation/Shader.h>
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
overload Shader* Use(Shader* const this)
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

overload Shader* SetFloat(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat value) {
    glUniform1f(glGetUniformLocation(this->Id, name), value);
    return this;
}

overload Shader* SetInteger(
    Shader* const this, 
    const GLchar *name, 
    const GLint value) {
    glUniform1i(glGetUniformLocation(this->Id, name), value);
    return this;
}

overload Shader* SetArray2f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y) {
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
    return this;
}

overload Shader* SetArray2(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform2f(glGetUniformLocation(this->Id, name), value[0], value[1]);
    return this;
}

overload Shader* SetArray3f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y, 
    const GLfloat z) {
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
    return this;
}

overload Shader* SetArray3(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform3f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2]);
    return this;
}

overload Shader* SetArray4f(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat x, 
    const GLfloat y, 
    const GLfloat z, 
    const GLfloat w) {
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
    return this;
}

overload Shader* SetArray4(
    Shader* const this, 
    const GLchar *name, 
    const GLfloat* value) {
    glUniform4f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2], value[3]);
    return this;
}

overload Shader* SetMatrix(
    Shader* const this, 
    const GLchar *name,  
    const GLfloat * matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

overload Shader* SetMatrix4(
    Shader* const this, 
    const GLchar *name,  
    const GLfloat* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

static void checkCompileErrors(
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
overload char* ToString(const Shader* const this)
{
    return "Shader";
}

