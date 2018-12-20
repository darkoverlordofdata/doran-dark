/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <ParticleGenerator.h>

static void init(struct ParticleGenerator *this);
static GLuint firstUnusedParticle(struct ParticleGenerator *this);
static void respawnParticle(struct ParticleGenerator *this, struct Particle particle, TGameObject object, Vec2 offset);

/**
 * ParticleGenerator
 * 
 * @param shader to use
 * @param texture to source from
 * @param amount number of particles to generate
 * 
 */
struct ParticleGenerator *ParticleGenerator_Ctor(
    struct ParticleGenerator *const this, 
    struct Shader *shader, 
    struct Texture2D *texture, 
    int amount)
{
	Object_Ctor(this);
    this->isa = isa(ParticleGenerator);
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
void overload Update(
    struct ParticleGenerator *this, 
    GLfloat dt, 
    struct GameObject *object, 
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
void overload Draw(struct ParticleGenerator *this)
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
static void init(struct ParticleGenerator *this)
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

    this->particles =  dark_calloc(this->amount, sizeof(Particle));
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
static GLuint firstUnusedParticle(struct ParticleGenerator *this)
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

static void respawnParticle(
    struct ParticleGenerator *this, 
    struct Particle particle, 
    struct GameObject *object, 
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
char* overload ToString(struct ParticleGenerator *const this)
{
    return "ParticleGenerator";
}

static struct ParticleGenerator* Create(
    struct Shader *shader, 
    struct Texture2D *texture, 
    int amount) { 
    return ParticleGenerator_Ctor(new(ParticleGenerator), shader, texture, amount);
}

/**
 * ParticleGenerator Class Metadata
 */
register (ParticleGenerator)
{
    if (ParticleGenerator.isa == nullptr) {
        ParticleGenerator = (struct ParticleGeneratorClass) {
            .isa            = &ParticleGenerator,
            .superclass     = &Object,
            .name           = "ParticleGenerator",
            .ToString       = ToString,
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .Update         = Update,
            .Draw           = Draw,
            .Create         = Create,
        };
        AddMetadata(ParticleGenerator);
    }
    return &ParticleGenerator;
}

