/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <GL/glew.h>
#include <glm/glm.h>
#include <dark/darkfx.h>

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"


// Represents a single particle and its state
typedef struct Particle
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
    ParticleGeneratorClass_t* isa;
    Particle* particles;
    GLuint amount;
    Shader shader;
    Texture2D texture;
    GLuint VAO;
};

typedef struct ParticleGeneratorClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (ParticleGenerator const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
        
    // Update all particles
    void    (*Update)               (ParticleGenerator const, GLfloat dt, GameObject object, GLuint newParticles, Vec2 offset);
    // Render all particles
    void    (*Draw)                 (ParticleGenerator const);
    // Initializes buffer and vertex attributes
};

/**
 * ParticleGenerator API
 */
void overload Update(ParticleGenerator, GLfloat dt, GameObject object, GLuint newParticles, Vec2 offset);
void overload Draw(ParticleGenerator);
const char* overload ToString(ParticleGenerator const);
ParticleGenerator ParticleGenerator_Ctor(ParticleGenerator const, Shader shader, Texture2D texture, int amount);

#endif PARTICLE_GENERATOR_H