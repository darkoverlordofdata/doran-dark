/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Shader.h>

static void checkCompileErrors(TShader this, GLuint object, char* type);

const char* VERSION = "#version 300 es\n";
const char* HEADER = "#\n"
                    "#ifdef GL_ES\n"
                    "precision mediump float;\n"
                    "#endif\n";

/**
 * Shader
 */
struct Shader * Shader_Ctor(TShader const this)
{
	Object_Ctor(this);
    this->isa = isa(Shader);
    return this;
}

/**
 * Use shader
 */
TShader overload Use(TShader this)
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
void overload Compile(TShader this, const GLchar* vertexSource, const GLchar* fragmentSource)
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

TShader overload SetFloat(TShader this, const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(this->Id, name), value);
    return this;
}

TShader overload SetInteger(TShader this, const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(this->Id, name), value);
    return this;
}

TShader overload SetArray2f(TShader this, const GLchar *name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(this->Id, name), x, y);
    return this;
}

TShader overload SetArray2(TShader this, const GLchar *name, const GLfloat* value)
{
    glUniform2f(glGetUniformLocation(this->Id, name), value[0], value[1]);
    return this;
}

TShader overload SetArray3f(TShader this, const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(this->Id, name), x, y, z);
    return this;
}

TShader overload SetArray3(TShader this, const GLchar *name, const GLfloat* value)
{
    glUniform3f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2]);
    return this;
}

TShader overload SetArray4f(TShader this, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(this->Id, name), x, y, z, w);
    return this;
}

TShader overload SetArray4(TShader this, const GLchar *name, const GLfloat* value)
{
    glUniform4f(glGetUniformLocation(this->Id, name), value[0], value[1], value[2], value[3]);
    return this;
}

TShader overload SetMatrix(TShader this, const GLchar *name,  GLfloat * matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

TShader overload SetMatrix4(TShader this, const GLchar *name,  GLfloat* matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, GL_FALSE, matrix);
    return this;
}

static void checkCompileErrors(TShader this, GLuint object, char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            printf("| ERROR::SHADER: Compile-time error: Type: %s\n", type);
            printf("%s\n", infoLog);
            printf("-- --------------------------------------------------- -- \n");
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            printf("| ERROR::SHADER: Link-time error: Type: %s\n", type);
            printf("%s\n", infoLog);
            printf("-- --------------------------------------------------- -- \n");
        }
    }
}

/**
 * ToString
 */
char* overload ToString(TShader const this)
{
    return "Shader";
}

/**
 * Shader Class Metadata
 */
register (Shader)
{
    if (Shader.isa == nullptr) {
        Shader = (struct ShaderClass) {
            .isa        = &Shader,
            .superclass = &Object,
            .name       = "Shader",
            /** VTable */
            .ToString       = ToString,
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .ToString       = ToString,
            .Use            = Use,
            .Compile        = Compile,
            .SetFloat       = SetFloat,
            .SetInteger     = SetInteger,
            .SetArray2f     = SetArray2f,
            .SetArray2      = SetArray2,
            .SetArray3f     = SetArray3f,
            .SetArray3      = SetArray3,
            .SetArray4f     = SetArray4f,
            .SetArray4      = SetArray4,
            .SetMatrix4     = SetMatrix4,
            .Create         = ^() { return Shader_Ctor(new(Shader));},
        };
        AddMetadata(Shader);
    }
    return &Shader;
}

