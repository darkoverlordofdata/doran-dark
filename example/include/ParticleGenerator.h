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

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

#define IsParticleGenerator(x) (x->isa == &ParticleGeneratorClass)
#define AsParticleGenerator(x) (IsParticleGenerator(x) ? (ParticleGenerator*)x : nullptr)


// Represents a single particle and its state
struct Particle
{
    Vec2 Position;
    Vec2 Velocity;
    Vec4 Color;
    GLfloat Life;

    // Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
} Particle;


// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class (ParticleGenerator)
{
    struct ParticleGeneratorClass* isa;
    struct Particle * particles;
    GLuint amount;
    Shader* shader;
    Texture2D* texture;
    GLuint VAO;
};

struct ParticleGeneratorClass
{
    union {
        struct DSObjectClass base;
        struct 
        {
            Class*  isa;
            Class*  superclass;
            char*   name;
            char*   (*ToString) (ParticleGenerator* const);
            bool    (*Equals) (DSObject* const, DSObject* const);
            int     (*GetHashCode) (DSObject* const);
            void    (*Dispose) (DSObject* const);
            bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
            bool    (*InstanceEquals) (DSObject* const, DSObject* const);
            ParticleGenerator*  (*Create) (Shader* shader, Texture2D* texture, int amount);
        };
    };
        
    // Update all particles
    void    (*Update)               (ParticleGenerator* const, GLfloat dt, GameObject* object, GLuint newParticles, Vec2 offset);
    // Render all particles
    void    (*Draw)                 (ParticleGenerator* const);
    // Initializes buffer and vertex attributes
} ParticleGeneratorClass;

/**
 * ParticleGenerator API
 */
void overload Update(ParticleGenerator*, GLfloat dt, GameObject* object, GLuint newParticles, Vec2 offset);
void overload Draw(ParticleGenerator*);
char* overload ToString(ParticleGenerator* const);


