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
delegate (ParticleGenerator, New,           ParticleGenerator*, (ParticleGenerator*, Shader*, Texture2D*, int));
delegate (ParticleGenerator, ToString,     char*, (const ParticleGenerator* const));
delegate (ParticleGenerator, Update,       void, (ParticleGenerator*, GLfloat, GameObject*, GLuint, Vec2));
delegate (ParticleGenerator, Draw,         void, (ParticleGenerator*));
delegate (ParticleGenerator, init,         void, (ParticleGenerator*));
delegate (ParticleGenerator, firstUnused,  GLuint, (ParticleGenerator*));
delegate (ParticleGenerator, respawn,      void, (ParticleGenerator*, struct Particle, GameObject*, Vec2));

vtable (ParticleGenerator) {
    ParticleGeneratorToString   ToString;
    ObjectEquals                Equals;
    ObjectGetHashCode           GetHashCode;
    ObjectDispose               Dispose;
    ParticleGeneratorUpdate     Update;
    ParticleGeneratorDraw       Draw;
};

/**
 * Put it all together
 */
static inline vptr(ParticleGenerator);
/**
 * Class Loader callback
 */
static inline Class objc_loadParticleGenerator(Class super) 
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
method ParticleGenerator* New(
    ParticleGenerator* self, 
    Shader* shader, 
    Texture2D* texture, 
    int amount)
{
	extends(Object);
    self->isa = objc_getClass("ParticleGenerator");
    self->shader = shader;
    self->texture = texture;
    self->amount = amount;
    init(self);
    return self;
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
    ParticleGenerator* self, 
    GLfloat dt, 
    GameObject* object, 
    GLuint newParticles, 
    Vec2 offset)
{
    // Add new particles 
    for (GLuint i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnused(self);
        respawn(self, self->particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < self->amount; ++i)
    {
        self->particles[i].Life -= dt; // reduce life
        if (self->particles[i].Life > 0.0f)
        {	// particle is alive, thus update
                    
            self->particles[i].Position -= self->particles[i].Velocity * dt; 
            self->particles[i].Color[3] -= dt * 2.5;
        }
    }
}

/**
 * Render all particles
 * 
 */
method void Draw(ParticleGenerator* self)
{
    // Use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Use(self->shader);
    for (int i=0; i<self->amount; i++)
    {
        struct Particle particle = self->particles[i];
        if (particle.Life > 0.0f)
        {
            SetArray2(self->shader, "offset", &particle.Position);
            SetArray4(self->shader, "color", &particle.Color);
            Bind(self->texture);
            glBindVertexArray(self->VAO);
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
method void init(ParticleGenerator* self)
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
    glGenVertexArrays(1, &self->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(self->VAO);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    self->particles = (struct Particle*)DSmalloc(sizeof(Particle) * self->amount);
}

// Stores the index of the last particle used (for quick access to next dead particle)
static GLuint lastUsedParticle = 0;
method GLuint firstUnused(ParticleGenerator* self)
{
    // First search from last used particle, self will usually return almost instantly
    for (GLuint i = lastUsedParticle; i < self->amount; ++i){
        if (self->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle; ++i){
        if (self->particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits self case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

method void respawn(
    ParticleGenerator* self, 
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
method char* ToString(const ParticleGenerator* const self)
{
    return "ParticleGenerator";
}


