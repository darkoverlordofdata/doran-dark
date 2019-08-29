#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "components.h"

// #define ENTITY_MAX 2
// #define ENTITY_MAX 170
#define BULLET_MAX 12
#define ENEMY1_MAX 15
#define ENEMY2_MAX 5
#define ENEMY3_MAX 4
#define EXPLOSION_MAX 20
#define BANG_MAX 12
#define PARTICLE_MAX 100

#define ENTITY_MAX (2+BULLET_MAX+ENEMY1_MAX+ENEMY2_MAX+ENEMY3_MAX + \
                     EXPLOSION_MAX+BANG_MAX+PARTICLE_MAX)

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
    ResourceManager* resource;
    char* title;
    bool *keys;
    double delta;
    double factor;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;
    
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
    long count;
    long _;
    Entity entities[ENTITY_MAX];
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
    long _;
    Vec2 Bullets[BULLET_MAX];
    Vec2 Enemies1[ENEMY1_MAX];
    Vec2 Enemies2[ENEMY2_MAX];
    Vec2 Enemies3[ENEMY3_MAX];
    Vec2 Explosions[EXPLOSION_MAX];
    Vec2 Bangs[BANG_MAX];
    Vec2 Particles[PARTICLE_MAX];
};


