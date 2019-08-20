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
type (ParticleGenerator) {
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
// ParticleGenerator* NewParticleGenerator(Shader* shader, Texture2D* texture, int amount);
// ParticleGenerator* ParticleGenerator_alloc();
// ParticleGenerator* ParticleGenerator_init(ParticleGenerator* const this, Shader* shader, Texture2D* texture, int amount);

interface (ParticleGenerator, ToString,     char*, (const ParticleGenerator* const));
interface (ParticleGenerator, Update,       void, (ParticleGenerator*, GLfloat, GameObject*, GLuint, Vec2));
interface (ParticleGenerator, Draw,         void, (ParticleGenerator*));

vtable (ParticleGenerator) {
    ParticleGeneratorToString   ToString;
    ObjectEquals              Equals;
    ObjectGetHashCode         GetHashCode;
    ObjectDispose             Dispose;
    ParticleGeneratorUpdate     Update;
    ParticleGeneratorDraw       Draw;
};

/** private */
// static  void    init(ParticleGenerator*);
// static  GLuint  firstUnusedParticle(ParticleGenerator*);
// static  void    respawnParticle(ParticleGenerator*, struct Particle, GameObject*, Vec2);

/**
 * Put it all together
 */
function vptr(ParticleGenerator);
/**
 * Class Loader callback
 */
function objc_loadParticleGenerator(Class super) 
{
    Class cls = createClass(super, ParticleGenerator);
    addMethod(cls, ParticleGenerator, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, ParticleGenerator, Update);
    addMethod(cls, ParticleGenerator, Draw);
    return cls;
}

/**
 * ParticleGenerator
 * 
 * @param shader to use
 * @param texture to source from
 * @param amount number of particles to generate
 * 
 */
function ParticleGenerator* ParticleGenerator_init(
    ParticleGenerator* const this, 
    Shader* shader, 
    Texture2D* texture, 
    int amount)
{
	Object_init(this);
    this->isa = getParticleGeneratorIsa();
    this->shader = shader;
    this->texture = texture;
    this->amount = amount;
    init(this);
    return this;
}

/**
 * Update
 * 
 * @param dt delta time
 * @param object GameObject
 * @param newParticles count
 * @param offset to display from
 * 
 */
method void Update(
    ParticleGenerator* this, 
    GLfloat dt, 
    GameObject* object, 
    GLuint newParticles, 
    Vec2 offset)
{
    // Add new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle(this);
        respawnParticle(this, this->particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i)
    {
        this->particles[i].Life -= dt; // reduce life
        if (this->particles[i].Life > 0.0f)
        {	// particle is alive, thus update
                    
            this->particles[i].Position -= this->particles[i].Velocity * dt; 
            this->particles[i].Color[3] -= dt * 2.5;
        }
    }
}

/**
 * Render all particles
 * 
 */
method void Draw(ParticleGenerator* this)
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Use(this->shader);
    for (int i=0; i<this->amount; i++)
    {
        struct Particle particle = this->particles[i];
        if (particle.Life > 0.0f)
        {
            SetArray2(this->shader, "offset", &particle.Position);
            SetArray4(this->shader, "color", &particle.Color);
            Bind(this->texture);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // Don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * initialize generator
 */
function void init(ParticleGenerator* this)
{
    // Set up mesh and attribute properties
    GLuint VBO;
    GLfloat particle_quad[24] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    this->particles = DSmalloc(sizeof(Particle) * this->amount);
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
function GLuint firstUnusedParticle(ParticleGenerator* this)
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

function void respawnParticle(
    ParticleGenerator* this, 
    struct Particle particle, 
    GameObject* object, 
    Vec2 offset)
{
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle.Position = object->Position + random + offset;
    particle.Color = (Vec4){ rColor, rColor, rColor, 1.0f };
    particle.Life = 1.0f;
    particle.Velocity = object->Velocity * 0.1f;
}

/**
 * ToString
 */
method char* ToString(const ParticleGenerator* const this)
{
    return "ParticleGenerator";
}


