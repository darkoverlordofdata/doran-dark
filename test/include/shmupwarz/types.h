#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "components.h"

#define ENTITY_MAX 141
#define BULLET_MAX 12
#define ENEMY1_MAX 15
#define ENEMY2_MAX 5
#define ENEMY3_MAX 4
#define EXPLOSION_MAX 20
#define BANG_MAX 12
#define PARTICLE_MAX 100


typedef struct Shmupwarz Shmupwarz;
typedef struct ResourceManager ResourceManager;
typedef struct EntityManager EntityManager;
typedef struct GameSystems GameSystems;

/**
 * We need to forward declare all types up front 
 */
type (Shmupwarz)
{
    Class isa;
    SDL_Window *window;
    SDL_GLContext context;
    char* title;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    double delta;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;
    double factor;
    bool *keys;
    ResourceManager* resource;
    SpriteRenderer* spriteBatch;
    EntityManager* em;
    GameSystems* sys;
    Entity* player;
};

type (EntityManager)
{
    Class isa;
    Shmupwarz* game;
    ResourceManager* resource;
    Entity entities[ENTITY_MAX];
    long count;
};

type (GameSystems)
{
    Class isa;
    Shmupwarz* game;
    double FireRate;
    double TimeToFire;
    double EnemyT1;
    double EnemyT2;
    double EnemyT3;
    Mix_Chunk* Pew;
    Mix_Chunk* Asplode;
    Mix_Chunk* Smallasplode;
    /** event stacks */
    long bulletCount;
    long enemy1Count;
    long enemy2Count;
    long enemy3Count;
    long explosionCount;
    long bangCount;
    long particleCount;
    Vec2 Bullets[BULLET_MAX];
    Vec2 Enemies1[ENEMY1_MAX];
    Vec2 Enemies2[ENEMY2_MAX];
    Vec2 Enemies3[ENEMY3_MAX];
    Vec2 Explosions[EXPLOSION_MAX];
    Vec2 Bangs[BANG_MAX];
    Vec2 Particles[PARTICLE_MAX];
};


