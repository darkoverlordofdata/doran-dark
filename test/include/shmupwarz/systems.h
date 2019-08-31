#pragma once
#include <stdlib.h>
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "types.h"
#include "shmupwarz.h"
#include "components.h"
#include "entities.h"

typedef struct Shmupwarz Shmupwarz;
typedef struct EntityManager EntityManager;

#define Keys_z  122

delegate (GameSystems, New,             GameSystems*, (GameSystems*, Shmupwarz*));
delegate (GameSystems, ToString,        char*, (GameSystems*));
delegate (GameSystems, Dispose,         void, (GameSystems*));
delegate (GameSystems, InputSystem,     void, (GameSystems*, Entity* entity));
delegate (GameSystems, SoundSystem,     void, (GameSystems*, Entity* entity));
delegate (GameSystems, InputSystem,     void, (GameSystems*, Entity* entity));
delegate (GameSystems, PhysicsSystem,   void, (GameSystems*, Entity* entity));
delegate (GameSystems, ExpireSystem,    void, (GameSystems*, Entity* entity));
delegate (GameSystems, TweenSystem,     void, (GameSystems*, Entity* entity));
delegate (GameSystems, RemoveSystem,    void, (GameSystems*, Entity* entity));
delegate (GameSystems, SpawnSystem,     void, (GameSystems*, Entity* entity));
delegate (GameSystems, EntitySystem,    void, (GameSystems*, Entity* entity));
delegate (GameSystems, CollisionSystem, void, (GameSystems*, Entity* entity));


static inline vptr(GameSystems);

method GameSystems* New(GameSystems* self, Shmupwarz* game)
{
    extends(Object);
    self->isa = isa(GameSystems);
    self->game = game;
    self->FireRate = 0.1;
    self->TimeToFire = 0.0;
    self->EnemyT1 = 1.0;
    self->EnemyT2 = 4.0;
    self->EnemyT3 = 6.0;
    self->bulletCount = -1;
    self->enemy1Count = -1;
    self->enemy2Count = -1;
    self->enemy3Count = -1;
    self->explosionCount = -1;
    self->bangCount = -1;
    self->particleCount = -1;


    return self;
}


method void InputSystem(GameSystems* self, Entity* entity) 
{

    entity->Transform->Pos.x = self->game->mouseX;
    entity->Transform->Pos.y = self->game->mouseY;

    // entity->Transform->Bounds.x = entity->Transform->Pos.x - entity->Transform->Bounds.w / 2;
    // entity->Transform->Bounds.y = entity->Transform->Pos.y - entity->Transform->Bounds.h / 2;

    if (self->game->keys[Keys_z] || self->game->mouseDown)
    {
        self->TimeToFire -= self->game->delta;
        if (self->TimeToFire < 0.0) {
            assert(self->bulletCount < BULLET_MAX);
            self->Bullets[++self->bulletCount] = (Vec2) { entity->Transform->Pos.x - 27, entity->Transform->Pos.y + 2 };
            self->Bullets[++self->bulletCount] = (Vec2) { entity->Transform->Pos.x + 27, entity->Transform->Pos.y + 2 };
            self->TimeToFire = self->FireRate;
        }
    }
}

method void SoundSystem(GameSystems* self, Entity* entity)  
{
    if (entity->Active && (entity->Sound)) 
    {
        switch(entity->Sound->Effect) 
        {
            case SoundEffectPew: 
                Mix_PlayChannelTimed(-1, self->Pew, 0, 0);
                break;

            case SoundEffectAsplode: 
                Mix_PlayChannelTimed(-1, self->Asplode, 0, 0);
                break;

            case SoundEffectSmallAsplode: 
                Mix_PlayChannelTimed(-1, self->Smallasplode, 0, 0);
                break;
        }
    }
}

method void PhysicsSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active)
    {
        // Move entity?
        if (entity->Velocity)
        {
            entity->Transform->Pos.x += entity->Velocity->X * self->game->delta;
            entity->Transform->Pos.y += entity->Velocity->Y * self->game->delta;
        }
        // Set new bounding box
        if (entity->Category == CATEGORY_BACKGROUND) 
        {
            entity->Transform->Bounds.w = self->game->width;
            entity->Transform->Bounds.h = self->game->height;
            entity->Transform->Bounds.x = 0; 
            entity->Transform->Bounds.y = 0; 
        } else {
            entity->Transform->Bounds.w = entity->Transform->Texture->Width * entity->Transform->Scale.x;
            entity->Transform->Bounds.h = entity->Transform->Texture->Height * entity->Transform->Scale.y;
            entity->Transform->Bounds.x = entity->Transform->Pos.x - entity->Transform->Bounds.w / 2;
            entity->Transform->Bounds.y = entity->Transform->Pos.y - entity->Transform->Bounds.h / 2;


        }
    }
}

method void ExpireSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active && entity->Expires) 
    {
        auto exp = entity->Expires->Value - self->game->delta;

        entity->Expires->Value = exp;
        if (entity->Expires->Value < 0) {
            entity->Active = false;
        }
    }
}

method void TweenSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active && entity->Tween) 
    {
        auto x = entity->Transform->Scale.x + (entity->Tween->Speed * self->game->delta);
        auto y = entity->Transform->Scale.y + (entity->Tween->Speed * self->game->delta);
        auto Active = entity->Tween->Active;


        if (x > entity->Tween->Max) {
            x = entity->Tween->Max;
            y = entity->Tween->Max;
            Active = false;
        } else if (x < entity->Tween->Min) {
            x = entity->Tween->Min;
            y = entity->Tween->Min;
            Active = false;
        }
        entity->Transform->Scale.x = x; 
        entity->Transform->Scale.y = y; 
        entity->Tween->Active = Active;
    }
}

method void RemoveSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active) 
    {
        switch(entity->Category) 
        {
            case CATEGORY_ENEMY:
                if (entity->Transform->Pos.y > self->game->height) {
                    entity->Active = false;
                }
                break;
            case CATEGORY_BULLET:
                if (entity->Transform->Pos.y < 0) {
                    entity->Active = false;
                }
                break;
            default:
                break;
        }
    }
}

method double SpawnEnemy(GameSystems* self, double delta, double t, int enemy) 
{
    auto d1 = t-delta;
    if (d1 < 0.0) 
    {
        switch(enemy) 
        {
            case 1:
                assert(self->enemy1Count < ENEMY1_MAX);
                self->Enemies1[++self->enemy1Count] = (Vec2){ (rand() % (self->game->width-70))+35, 35 };
                return 1.0;
            case 2:
                assert(self->enemy2Count < ENEMY2_MAX);
                self->Enemies2[++self->enemy2Count] = (Vec2){ (rand() % (self->game->width-170))+85, 85 };
                return 4.0;
            case 3:
                assert(self->enemy3Count < ENEMY3_MAX);
                self->Enemies3[++self->enemy3Count] = (Vec2){ (rand() % (self->game->width-320))+160, 160 };
                return 6.0;
            default:
                return 0;
        }
    } else return d1;    
}


method void SpawnSystem(GameSystems* self, Entity* entity) 
{
    self->EnemyT1 = SpawnEnemy(self, self->game->delta, self->EnemyT1, 1);
    self->EnemyT2 = SpawnEnemy(self, self->game->delta, self->EnemyT2, 2);
    self->EnemyT3 = SpawnEnemy(self, self->game->delta, self->EnemyT3, 3);

}

method void EntitySystem(GameSystems* self, Entity* entity) 
{
    if (!entity->Active) {
        switch(entity->Type) {

            case TYPE_BULLET: 
                if (self->bulletCount < 0) break;
                ResetBullet(entity, self->Bullets[self->bulletCount].x, self->Bullets[self->bulletCount].y);
                self->bulletCount--;
                break;

            case TYPE_ENEMY1:
                if (self->enemy1Count < 0) break;
                ResetEnemy1(entity, self->Enemies1[self->enemy1Count].x, self->Enemies1[self->enemy1Count].y);
                self->enemy1Count--;
                break;

            case TYPE_ENEMY2:
                if (self->enemy2Count < 0) break;
                ResetEnemy2(entity, self->Enemies2[self->enemy2Count].x, self->Enemies2[self->enemy2Count].y);
                self->enemy2Count--;
                break;

            case TYPE_ENEMY3:
                if (self->enemy3Count < 0) break;
                ResetEnemy3(entity, self->Enemies3[self->enemy3Count].x, self->Enemies3[self->enemy3Count].y);
                self->enemy3Count--;
                break;

            case TYPE_EXPLOSION:  
                if (self->explosionCount < 0) break;
                ResetExplosion(entity, self->Explosions[self->explosionCount].x, self->Explosions[self->explosionCount].y);
                self->explosionCount--;
                break;

            case TYPE_BANG:
                if (self->bangCount < 0) break;
                ResetBang(entity, self->Bangs[self->bangCount].x, self->Bangs[self->bangCount].y);
                self->bangCount--;
                break;

            case TYPE_PARTICLE:
                if (self->particleCount < 0) break;
                ResetParticle(entity, self->Particles[self->particleCount].x, self->Particles[self->particleCount].y);
                self->particleCount--;
                break;

            default:
                break;
        }
    }

}

method void HandleCollision(GameSystems* self, Entity* a, Entity* b) 
{
    assert(self->bangCount < BANG_MAX);
    self->Bangs[++self->bangCount] = (Vec2) { b->Transform->Bounds.x, b->Transform->Bounds.y };
    b->Active = false;
    for (int i=0; i<3; i++) {
        assert(self->particleCount < PARTICLE_MAX);
        self->Particles[++self->particleCount] = (Vec2) { b->Transform->Bounds.x, b->Transform->Bounds.y };
    }
    if (a->Health) 
    {
        auto h = a->Health->Current - 2;
        if (h < 0) {
            assert(self->explosionCount < EXPLOSION_MAX);
            self->Explosions[++self->explosionCount] = (Vec2) { a->Transform->Pos.x, a->Transform->Pos.y };
            a->Active = false;
        } else {
            a->Health->Current = h;
        }   
    }
}

method void CollisionSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active && entity->Category == CATEGORY_ENEMY) {
        for (int i=0; i<self->game->em->Count; i++) {
            auto bullet = &self->game->em->Entities[i];
            if (bullet->Active && bullet->Category == CATEGORY_BULLET) {
                if (Collides(entity, bullet)) {
                    if (entity->Active && bullet->Active) HandleCollision(self, entity, bullet);
                    return;
                }
            }
        }
    }
}
