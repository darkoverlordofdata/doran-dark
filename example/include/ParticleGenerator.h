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
#include <dark/Foundation.h>

#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

#define IsParticleGenerator(object) _Generic((object), ParticleGenerator*: true, default: false)
#define AsParticleGenerator(object) _Generic((object),                          \
                            ParticleGenerator*: (ParticleGenerator *)object,    \
                            default: nullptr)


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
/**
 * ParticleGenerator API
 */
ParticleGenerator* NewParticleGenerator(Shader* shader, Texture2D* texture, int amount);
ParticleGenerator* ParticleGenerator_alloc();
ParticleGenerator* ParticleGenerator_init(ParticleGenerator* const this, Shader* shader, Texture2D* texture, int amount);

char*   overload ToString(const ParticleGenerator* const);
void    overload Update(ParticleGenerator*, GLfloat, GameObject*, GLuint, Vec2);
void    overload Draw(ParticleGenerator*);

typedef char*   (*ParticleGeneratorToString)    (const ParticleGenerator* const);
typedef void    (*ParticleGeneratorUpdate)      (ParticleGenerator*, GLfloat, GameObject*, GLuint, Vec2);
typedef void    (*ParticleGeneratorDraw)        (ParticleGenerator*);

vtable (ParticleGenerator) {
    ParticleGeneratorToString   ToString;
    DSObjectEquals              Equals;
    DSObjectGetHashCode         GetHashCode;
    DSObjectDispose             Dispose;
    ParticleGeneratorUpdate     Update;
    ParticleGeneratorDraw       Draw;
};

/** private */
static  void    init(ParticleGenerator*);
static  GLuint  firstUnusedParticle(ParticleGenerator*);
static  void    respawnParticle(ParticleGenerator*, struct Particle, GameObject*, Vec2);

