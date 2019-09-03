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
    SoundComponent* sound = GetSoundComponent(entity);

    if (entity->Active && sound) 
    {
        switch(sound->Effect) 
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

        VelocityComponent* velocity = GetVelocityComponent(entity);

        // Move entity?
        if (velocity)
        {
            entity->Transform->Pos.x += velocity->X * self->game->delta;
            entity->Transform->Pos.y += velocity->Y * self->game->delta;
        }
        // Set new bounding box
        if (GetTaxonomyComponent(entity)->Type == TypeBackground) 
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

    ExpireComponent* expire = GetExpireComponent(entity);

    if (entity->Active && expire) 
    {
        auto exp = expire->Value - self->game->delta;

        expire->Value = exp;
        if (expire->Value < 0) {
            entity->Active = false;
        }
    }
}

method void TweenSystem(GameSystems* self, Entity* entity) 
{
    TweenComponent* tween = GetTweenComponent(entity);

    if (entity->Active && tween) 
    {
        auto x = entity->Transform->Scale.x + (tween->Speed * self->game->delta);
        auto y = entity->Transform->Scale.y + (tween->Speed * self->game->delta);
        auto Active = tween->Active;


        if (x > tween->Max) {
            x = tween->Max;
            y = tween->Max;
            Active = false;
        } else if (x < tween->Min) {
            x = tween->Min;
            y = tween->Min;
            Active = false;
        }
        entity->Transform->Scale.x = x; 
        entity->Transform->Scale.y = y; 
        tween->Active = Active;
    }
}

method void RemoveSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active) 
    {

        switch (GetTaxonomyComponent(entity)->Type) 
        {
            case TypeEnemy:
                if (entity->Transform->Pos.y > self->game->height) {
                    entity->Active = false;
                }
                break;
            case TypeBullet:
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
        switch(GetTaxonomyComponent(entity)->Subtype) {

            case SubtypeBullet: 
                if (self->bulletCount < 0) break;
                ResetBullet(entity, self->Bullets[self->bulletCount].x, self->Bullets[self->bulletCount].y);
                self->bulletCount--;
                break;

            case SubtypeEnemy1:
                if (self->enemy1Count < 0) break;
                ResetEnemy1(entity, self->Enemies1[self->enemy1Count].x, self->Enemies1[self->enemy1Count].y);
                self->enemy1Count--;
                break;

            case SubtypeEnemy2:
                if (self->enemy2Count < 0) break;
                ResetEnemy2(entity, self->Enemies2[self->enemy2Count].x, self->Enemies2[self->enemy2Count].y);
                self->enemy2Count--;
                break;

            case SubtypeEnemy3:
                if (self->enemy3Count < 0) break;
                ResetEnemy3(entity, self->Enemies3[self->enemy3Count].x, self->Enemies3[self->enemy3Count].y);
                self->enemy3Count--;
                break;

            case SubtypeExplosion1:  
                if (self->explosionCount < 0) break;
                ResetExplosion(entity, self->Explosions[self->explosionCount].x, self->Explosions[self->explosionCount].y);
                self->explosionCount--;
                break;

            case SubtypeExplosion2:
                if (self->bangCount < 0) break;
                ResetBang(entity, self->Bangs[self->bangCount].x, self->Bangs[self->bangCount].y);
                self->bangCount--;
                break;

            case SubtypeParticle:
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


    HealthComponent* health = GetHealthComponent(a);
    if (health) 
    {
        auto h = health->Current - 2;
        if (h < 0) {
            assert(self->explosionCount < EXPLOSION_MAX);
            self->Explosions[++self->explosionCount] = (Vec2) { a->Transform->Pos.x, a->Transform->Pos.y };
            a->Active = false;
        } else {
            health->Current = h;
        }   
    }
}


method void CollisionSystem(GameSystems* self, Entity* entity) 
{
    if (entity->Active && GetTaxonomyComponent(entity)->Type == TypeEnemy) {
        for (int i=0; i<self->game->em->Count; i++) {
            auto bullet = self->game->em->Entities[i];
            if (bullet->Active && GetTaxonomyComponent(bullet)->Type == TypeBullet) {
                if (Collides(entity, bullet)) {
                    if (entity->Active && bullet->Active) HandleCollision(self, entity, bullet);
                    return;
                }
            }
        }
    }
}
