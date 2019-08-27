#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <tglm/tglm.h>

type (Shader) 
{
    Class isa;
    GLuint Id; 
};

delegate (Shader, New,                  Shader*, (Shader* self));
delegate (Shader, ToString,             char*, (const Shader* const));
delegate (Shader, Dispose,              void, (const Shader* const));
delegate (Shader, Use,                  void, (const Shader* const));
delegate (Shader, Compile,              void, (Shader* const, const GLchar*, const GLchar*));
delegate (Shader, CheckCompileErrors,   void, (const Shader* const, GLuint object, char* type));
delegate (Shader, SetFloat,             void, (Shader*, const GLchar*, const GLfloat));
delegate (Shader, SetInteger,           void, (Shader*, const GLchar*, const GLint));
delegate (Shader, SetArray2f,           void, (Shader*, const GLchar*, const GLfloat, const GLfloat));
delegate (Shader, SetArray2,            void, (Shader*, const GLchar*, const GLfloat*));
delegate (Shader, SetArray3f,           void, (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat));
delegate (Shader, SetArray3,            void, (Shader*, const GLchar*, const GLfloat*));
delegate (Shader, SetArray4f,           void, (Shader*, const GLchar*, const GLfloat, const GLfloat, const GLfloat, const GLfloat));
delegate (Shader, SetArray4,            void, (Shader*, const GLchar*, const GLfloat*));
delegate (Shader, SetMatrix,            void, (Shader*, const GLchar*, const GLfloat*));
delegate (Shader, SetMatrix4,           void, (Shader*, const GLchar*, const GLfloat*));



vtable (Shader) 
{
    const ShaderToString            ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ShaderDispose             Dispose;
    const ShaderUse                 Use;
    const ShaderCompile             Compile;
    const ShaderCheckCompileErrors  CheckCompileErrors;
    const ShaderSetFloat            SetFloat;
    const ShaderSetInteger          SetInteger;
    const ShaderSetArray2f          SetArray2f;
    const ShaderSetArray2           SetArray2;
    const ShaderSetArray3f          SetArray3f;
    const ShaderSetArray3           SetArray3;
    const ShaderSetArray4f          SetArray4f;
    const ShaderSetArray4           SetArray4;
    const ShaderSetMatrix4          SetMatrix4;
    const ShaderSetMatrix           SetMatrix;
};

/**
 * Put it all together
 */
static inline vptr(Shader);
/**
 * Class Loader callback
 */
static inline Class ClassLoadShader(Class base) 
{
    Class cls = createClass(base, Shader);
    addMethod(cls, Shader,  ToString);
    addMethod(cls, Object,  Equals);
    addMethod(cls, Object,  GetHashCode);
    addMethod(cls, Shader,  Dispose);
    addMethod(cls, Shader,  Use);
    addMethod(cls, Shader,  Compile);
    addMethod(cls, Shader,  CheckCompileErrors);
    addMethod(cls, Shader,  SetFloat);
    addMethod(cls, Shader,  SetInteger);
    addMethod(cls, Shader,  SetArray2f);
    addMethod(cls, Shader,  SetArray2);
    addMethod(cls, Shader,  SetArray3f);
    addMethod(cls, Shader,  SetArray3);
    addMethod(cls, Shader,  SetArray4f);
    addMethod(cls, Shader,  SetArray4);
    addMethod(cls, Shader,  SetMatrix4);
    addMethod(cls, Shader,  SetMatrix);
    return cls;
}

static const char* VERSION = "#version 300 es\n";
static const char* HEADER = "#\n"
                    "#ifdef GL_ES\n"
                    "precision mediump float;\n"
                    "#endif\n";


method Shader* New(Shader* self)
{
	extends(Object);
    self->isa = isa(Shader);
    return self;
}

/**
 * Use shader
 */
method Shader* Use(Shader* self)
{
    glUseProgram(self->Id);
    return self;
}

/**
 * CheckCompileErrors
 * 
 * Checks if compilation or linking failed and if so, print the error logs
 */
method void CheckCompileErrors(
    Shader* self, 
    GLuint object, 
    char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (strncmp(type, "PROGRAM", 7) != 0)
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            printf("| ERROR::SHADER: Compile-time error: type: %s\n%s\n", type, infoLog);
            printf(" -- --------------------------------------------------- --\n");
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            printf("| ERROR::SHADER: Link-time error: type: %s\n%s\n", type, infoLog);
            printf(" -- --------------------------------------------------- --\n");
        }
    }
}        

/**
 * Compile
 * 
 * @param vertexSource vertex shader source code
 * @param fragmentSource fragment shader source code
 * 
 */
method void Compile(
    Shader* self, 
    const GLchar* vertexSource, 
    const GLchar* fragmentSource, 
    const GLchar* geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileErrors(self, sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileErrors(self, sFragment, "FRAGMENT");

    self->Id = glCreateProgram();
    glAttachShader(self->Id, sVertex);
    glAttachShader(self->Id, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(self->Id, gShader);
    glLinkProgram(self->Id);
    CheckCompileErrors(self, self->Id, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);

} 

method void SetFloat(
    Shader* self, 
    const GLchar *name, 
    const GLfloat value, 
    const GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform1f(glGetUniformLocation(self->Id, name), value);
}

method void SetFloat(
    Shader* self, 
    const GLchar *name, 
    const GLfloat value)
{
    SetFloat(self, name, value, true);
}

method void SetInteger(
    Shader* self, 
    const GLchar *name, 
    GLint value, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform1i(glGetUniformLocation(self->Id, name), value);
}

method void SetInteger(
    Shader* self, 
    const GLchar *name, 
    GLint value)
{
    SetInteger(self, name, value, true);
}

method void SetVector2(
    Shader* self, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform2f(glGetUniformLocation(self->Id, name), x, y);
}

method void SetVector2(
    Shader* self, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y)
{
    SetVector2(self, name, x, y, true);
}

method void SetVector2(
    Shader* self, 
    const GLchar *name, 
    const Vec2 value, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform2f(glGetUniformLocation(self->Id, name), value.x, value.y);
}

method void SetVector2(
    Shader* self, 
    const GLchar *name, 
    const Vec2 value)
{
    SetVector2(self, name, value, true);
}

method void SetVector3(
    Shader* self, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform3f(glGetUniformLocation(self->Id, name), x, y, z);
}

method void SetVector3(
    Shader* self, 
    const GLchar *name, 
    GLfloat x, 
    GLfloat y, 
    GLfloat z)
{
    SetVector3(self, name, x, y, z, true);
}

method void SetVector3(
    Shader* self, 
    const GLchar *name, 
    const Vec3* value, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform3f(glGetUniformLocation(self->Id, name), value->x, value->y, value->z);
}

method void SetVector3(
    Shader* self, 
    const GLchar *name, 
    const Vec3* value)
{
    SetVector3(self, name, value, true);
}

method void SetVector4(
    Shader* self, 
    const GLchar *name,
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLfloat w, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform4f(glGetUniformLocation(self->Id, name), x, y, z, w);
}

method void SetVector4(
    Shader* self, 
    const GLchar *name,
    GLfloat x, 
    GLfloat y, 
    GLfloat z, 
    GLfloat w)
{
    SetVector4(self, name, x, y, z, w, true);

}
method void SetVector4(
    Shader* self, 
    const GLchar *name, 
    const Vec4 value, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniform4f(glGetUniformLocation(self->Id, name), value.x, value.y, value.z, value.w);
}

method void SetVector4(
    Shader* self, 
    const GLchar *name, 
    const Vec4 value)
{
    SetVector4(self, name, value, true);
}

method void SetMatrix(
    Shader* self, 
    const GLchar *name, 
    const Mat* matrix, 
    GLboolean useShader)
{
    if (useShader)
        Use(self);
    glUniformMatrix4fv(glGetUniformLocation(self->Id, name), 1, GL_FALSE, (GLfloat*)matrix);
}

method void SetMatrix(
    Shader* self, 
    const GLchar *name, 
    const Mat* matrix)
{
    SetMatrix(self, name, matrix, true);
}

/**
 * Dispose
 * 
 * release resources
 */
method void Dispose(Shader* self)
{
    if (!_use_gc) {
        free(self);
    }
}
