#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

#include "types.h"
#include "components.h"
#include "entities.h"
#include "systems.h"

// 100,149,237,255
// #define bgd_r 0.392156f
// #define bgd_g 0.584313f
// #define bgd_b 0.929411f

typedef struct EntityManager EntityManager;
typedef struct GameSystems GameSystems;


delegate (Shmupwarz, New,           Shmupwarz*, (Shmupwarz*, int, int));
delegate (Shmupwarz, ToString,      char*, (const Shmupwarz* const));
delegate (Shmupwarz, Dispose,       void, (const Shmupwarz* const));
delegate (Shmupwarz, Start,         void, (const Shmupwarz* const));
delegate (Shmupwarz, Run,           void, (const Shmupwarz* const));
delegate (Shmupwarz, Tick,          void, (const Shmupwarz* const));
delegate (Shmupwarz, HandleEvents,  void, (const Shmupwarz* const));
delegate (Shmupwarz, RunLoop,       void, (const Shmupwarz* const));
delegate (Shmupwarz, Draw,          void, (const Shmupwarz* const));
delegate (Shmupwarz, Update,        void, (const Shmupwarz* const));
delegate (Shmupwarz, Initialize,    void, (Shmupwarz* const));
delegate (Shmupwarz, LoadContent,   void, (Shmupwarz* const));

/**
 * Shmupwarz vtable
 */
vtable (Shmupwarz) 
{
    const ShmupwarzToString     ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ShmupwarzDispose      Dispose;
    const ShmupwarzStart        Start;
    const ShmupwarzRun          Run;
    const ShmupwarzTick         Tick;
    const ShmupwarzHandleEvents HandleEvents;
    const ShmupwarzRunLoop      RunLoop;
    const ShmupwarzDraw         Draw;
    const ShmupwarzUpdate       Update;
    const ShmupwarzInitialize   Initialize;
    const ShmupwarzLoadContent  LoadContent;
};

/**
 * Put it all together
 */
static inline vptr(Shmupwarz);
/**
 * Class Loader callback
 */
static inline Class ClassLoadShmupwarz(Class base) 
{
    Class cls = createClass(base, Shmupwarz);
    addMethod(cls, Shmupwarz,   ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Shmupwarz,   Dispose);
    addMethod(cls, Shmupwarz,   Start);
    addMethod(cls, Shmupwarz,   Run);
    addMethod(cls, Shmupwarz,   Tick);
    addMethod(cls, Shmupwarz,   HandleEvents);
    addMethod(cls, Shmupwarz,   RunLoop);
    addMethod(cls, Shmupwarz,   Draw);
    addMethod(cls, Shmupwarz,   Update);
    addMethod(cls, Shmupwarz,   Initialize);
    addMethod(cls, Shmupwarz,   LoadContent);
    return cls;
}

/**
 * New Shmupwarz game
 * 
 * @param self
 * @param width
 * @param height
 */
method Shmupwarz* New(Shmupwarz* self, int width, int height)
{
	extends(Game, "Shmupwarz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    self->isa = isa(Shmupwarz);
    Log("%d", ENTITY_MAX);
    return self;
}

/**
 * Shmupwarz::ToString
 */
method char* ToString(const Shmupwarz* const self)
{
    static char* toStringCache;

    if (!toStringCache)
        toStringCache = DSsprintf("{ title: %s, width: %d. height: %d }", 
                                    self->title, self->width, self->height);

    return toStringCache;
}

/**
 * Shmupwarz::Dispose
 * 
 */
method void Dispose(const Shmupwarz* const self)
{
    Log("Shmuwarz dispose");
    Dispose((Game*)self);
}

/**
 * Shmupwarz::Start
 * 
 */
method void Start(const Shmupwarz* const self)
{
}

/**
 * Shmupwarz::Draw
 * 
 *  Draw an entity
 */
method void Draw(const Shmupwarz* const self, Entity* entity)
{
    if (!entity->Active) return;
    Vec3 color = (Vec3) { 1, 1, 1 };
    if (entity->Tint) {
        color[0] = (float)entity->Tint->R/255.0;
        color[1] = (float)entity->Tint->G/255.0;
        color[2] = (float)entity->Tint->B/255.0;
    }

    Draw(self->spriteBatch, entity->Transform->Texture, &entity->Transform->Bounds, 0.0f, color);

}

/**
 * Shmupwarz::Draw
 * 
 *  Draw all entities
 */
method void Draw(const Shmupwarz* const self)
{
    for (int i=0; i<self->em->Count; i++) 
        Draw(self, &self->em->Entities[i]);
}

/**
 * Shmupwarz::Update
 * 
 */
method void Update(const Shmupwarz* const self)
{
    SpawnSystem(self->sys, self->player);
    for (int i=0; i<self->em->Count; i++) CollisionSystem(self->sys, &self->em->Entities[i]);
    for (int i=0; i<self->em->Count; i++) EntitySystem(self->sys, &self->em->Entities[i]);
    InputSystem(self->sys, self->player);
    for (int i=0; i<self->em->Count; i++) PhysicsSystem(self->sys, &self->em->Entities[i]);
    for (int i=0; i<self->em->Count; i++) ExpireSystem(self->sys, &self->em->Entities[i]);
    for (int i=0; i<self->em->Count; i++) TweenSystem(self->sys, &self->em->Entities[i]);
    for (int i=0; i<self->em->Count; i++) RemoveSystem(self->sys, &self->em->Entities[i]);
}

/**
 * Shmupwarz::Update
 * 
 */
method void Initialize(Shmupwarz* const self)
{
    Log("Initialize");
}
/**
 * Shmupwarz::Update
 * 
 */
method void LoadContent(Shmupwarz* const self)
{
    self->sys = new(GameSystems, self);
    self->em = new(EntityManager, self, self->resource);

    // Load shaders
    LoadShader(self->resource, "assets/shaders/sprite.vs", "assets/shaders/sprite.frag", "sprite");
    LoadShader(self->resource, "assets/shaders/particle.vs", "assets/shaders/particle.frag", "particle");

    // Configure shaders
    Mat projection = glm_ortho(0.0f, self->width, self->height, 0.0f, -1.0f, 1.0f);

    SetInteger(GetShader(self->resource, "sprite"), "sprite", 0, true);
    SetMatrix(GetShader(self->resource, "sprite"), "projection", &projection, true);

    SetInteger(GetShader(self->resource, "particle"), "sprite", 0, true);
    SetMatrix(GetShader(self->resource, "particle"), "projection", &projection, true);

    // Load textures
    LoadTexture(self->resource, "assets/images/background.png", GL_TRUE, "background");
    LoadTexture(self->resource, "assets/images/bang.png", GL_TRUE, "bang");
    LoadTexture(self->resource, "assets/images/bullet.png", GL_TRUE, "bullet");
    LoadTexture(self->resource, "assets/images/enemy1.png", GL_TRUE, "enemy1");
    LoadTexture(self->resource, "assets/images/enemy2.png", GL_TRUE, "enemy2");
    LoadTexture(self->resource, "assets/images/enemy3.png", GL_TRUE, "enemy3");
    LoadTexture(self->resource, "assets/images/explosion.png", GL_TRUE, "explosion");
    LoadTexture(self->resource, "assets/images/particle.png", GL_TRUE, "particle");
    LoadTexture(self->resource, "assets/images/spaceshipspr.png", GL_TRUE, "spaceshipspr");
    LoadTexture(self->resource, "assets/images/star.png", GL_TRUE, "star");

    CreateBackground(self->em);
    self->player = CreatePlayer(self->em);
    for (int i=0; i<BULLET_MAX; i++)    CreateBullet(self->em);
    for (int i=0; i<ENEMY1_MAX; i++)    CreateEnemy1(self->em);
    for (int i=0; i<ENEMY2_MAX; i++)    CreateEnemy2(self->em);
    for (int i=0; i<ENEMY3_MAX; i++)    CreateEnemy3(self->em);
    for (int i=0; i<EXPLOSION_MAX; i++) CreateExplosion(self->em);
    for (int i=0; i<BANG_MAX; i++)      CreateBang(self->em);
    for (int i=0; i<PARTICLE_MAX; i++)  CreateParticle(self->em);
    
    self->spriteBatch = new(SpriteRenderer, GetShader(self->resource, "sprite"));

}
/**
 * Shmupwarz::Run
 * 
 */
method void Run(const Shmupwarz* const self)
{
    Run((Game*)self);
}

/**
 * Shmupwarz::Tick
 * 
 */
method void Tick(const Shmupwarz* const self)
{
    Tick((Game*)self);
}

/**
 * Shmupwarz::HandleEvents
 * 
 */
method void HandleEvents(const Shmupwarz* const self)
{
    HandleEvents((Game*)self);
}

/**
 * Shmupwarz::RunLoop
 * 
 */
method void RunLoop(const Shmupwarz* const self)
{
    RunLoop((Game*)self);
}


