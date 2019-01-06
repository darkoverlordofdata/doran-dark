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
ivar (ParticleGenerator) {
    Class isa;
    struct Particle * particles;
    GLuint amount;
    Shader* shader;
    Texture2D* texture;
    GLuint VAO;
};

typedef char*   (*ParticleGeneratorToString)  (const ParticleGenerator* const);
typedef void    (*ParticleGeneratorDraw) (ParticleGenerator* const);

class (ParticleGenerator) {
    ParticleGenerator*  (*Create) (Shader* shader, Texture2D* texture, int amount);
};

vtable (ParticleGenerator) {
    char*   (*ToString) (const ParticleGenerator* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
        
    // Update all particles
    void    (*Update)               (ParticleGenerator* const, GLfloat dt, GameObject* object, GLuint newParticles, Vec2 offset);
    // Render all particles
    void    (*Draw)                 (ParticleGenerator* const);
    // Initializes buffer and vertex attributes
    
};

/**
 * ParticleGenerator API
 */
void overload Update(ParticleGenerator*, GLfloat dt, GameObject* object, GLuint newParticles, Vec2 offset);
void overload Draw(ParticleGenerator*);
char* overload ToString(const ParticleGenerator* const);
ParticleGenerator* NewParticleGenerator(Shader* shader, Texture2D* texture, int amount);
ParticleGenerator* ParticleGenerator_alloc();
ParticleGenerator* ParticleGenerator_init(ParticleGenerator* const this, Shader* shader, Texture2D* texture, int amount);
static void init(ParticleGenerator* this);
static GLuint firstUnusedParticle(ParticleGenerator* this);
static void respawnParticle(ParticleGenerator* this, struct Particle particle, GameObject* object, Vec2 offset);
