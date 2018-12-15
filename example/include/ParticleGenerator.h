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
#include <tglm/tglm.h>
#include <dark/darkfx.h>

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

#define IsParticleGenerator(x) (x->isa == &ParticleGenerator)
#define AsParticleGenerator(x) (IsParticleGenerator(x) ? (struct ParticleGenerator *)x : nullptr)


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
    struct ParticleGeneratorClass * isa;
    struct Particle * particles;
    GLuint amount;
    struct Shader * shader;
    struct Texture2D * texture;
    GLuint VAO;
};

struct ParticleGeneratorClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TParticleGenerator const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TParticleGenerator  (^Create) (TShader shader, TTexture2D texture, int amount);
        };
    };
        
    // Update all particles
    void    (*Update)               (TParticleGenerator const, GLfloat dt, TGameObject object, GLuint newParticles, Vec2 offset);
    // Render all particles
    void    (*Draw)                 (TParticleGenerator const);
    // Initializes buffer and vertex attributes
};

/**
 * ParticleGenerator API
 */
void overload Update(TParticleGenerator, GLfloat dt, TGameObject object, GLuint newParticles, Vec2 offset);
void overload Draw(TParticleGenerator);
char* overload ToString(TParticleGenerator const);

#endif PARTICLE_GENERATOR_H

