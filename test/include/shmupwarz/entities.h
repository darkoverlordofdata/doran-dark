#pragma once
#include <stdlib.h>
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "types.h"
#include "shmupwarz.h"


// #define ENTITY_MAX 141

typedef struct Shmupwarz Shmupwarz;
typedef struct ResourceManager ResourceManager;

delegate (EntityManager, New,           EntityManager*, (EntityManager*, Shmupwarz*, ResourceManager*));
delegate (EntityManager, ToString,      char*, (EntityManager*));
delegate (EntityManager, Dispose,       void, (EntityManager*));

delegate (EntityManager, CreateBackground,  Entity*, (EntityManager*));
delegate (EntityManager, CreatePlayer,      Entity*, (EntityManager*));
delegate (EntityManager, CreateBullet,      Entity*, (EntityManager*));
delegate (EntityManager, CreateEnemy1,      Entity*, (EntityManager*));
delegate (EntityManager, CreateEnemy2,      Entity*, (EntityManager*));
delegate (EntityManager, CreateEnemy3,      Entity*, (EntityManager*));
delegate (EntityManager, CreateExplosion,   Entity*, (EntityManager*));
delegate (EntityManager, CreateBang,        Entity*, (EntityManager*));
delegate (EntityManager, CreateParticle,    Entity*, (EntityManager*));

delegate (EntityManager, ResetBullet,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy1,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy2,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy3,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetExplosion,    Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetBang,         Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetParticle,     Entity*, (EntityManager*, Entity* entity, int x, int y));


static inline vptr(EntityManager);

method EntityManager* New(EntityManager* self, Shmupwarz* game, ResourceManager* resource)
{
    extends(Object);
    self->isa = isa(EntityManager);
    self->game = game;
    self->Resource = resource;
    return self;
}

/**
 * CreateEntity
 * 
 * allocates an entity from the pool
 * 
 */
method Entity* CreateEntity(EntityManager* self, char* name, float scale) {
    self->Count = self->UniqueId+1;
    Entity* entity = &self->Entities[self->UniqueId];
    self->UniqueId += 1;
    entity->Name = strdup(name);
    entity->Transform = new(Transform, GetTexture(self->Resource, name), scale);
    return entity;
}

method Entity* CreateEntity(EntityManager* self, char* name) {
    return CreateEntity(self, name, 1.0);
}

method Entity* CreateBackground(EntityManager* self) {
    Entity* entity = CreateEntity(self, "background", 2.0f);
    entity->Active = true;
    entity->Type = TYPE_BACKGROUND;
    entity->Category = CATEGORY_BACKGROUND;
    return entity;
}

method Entity* CreatePlayer(EntityManager* self) {
    Entity* entity = CreateEntity(self, "spaceshipspr");
    entity->Active = true;
    entity->Type = TYPE_PLAYER;
    entity->Category = CATEGORY_PLAYER;
    return entity;
}

method Entity* CreateBullet(EntityManager* self) {
    Entity* entity = CreateEntity(self, "bullet");
    entity->Type = TYPE_BULLET;
    entity->Category = CATEGORY_BULLET;
    entity->Velocity = new(VelocityComponent, 0, 0);
    entity->Expires = new(ExpireComponent, 1.0);
    entity->Sound = new(SoundComponent, SoundEffectPew);
    entity->Health = new(HealthComponent, 2, 2);
    entity->Tint = new(ColorComponent, 0xd2, 0xfa, 0x00, 0xffa );
    return entity;
}

method Entity* CreateEnemy1(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy1");
    entity->Type = TYPE_ENEMY1;
    entity->Category = CATEGORY_ENEMY;
    entity->Health = new(HealthComponent, 10, 10);
    entity->Velocity = new(VelocityComponent, 0, 0);
    return entity;
}

method Entity* CreateEnemy2(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy2");
    entity->Type = TYPE_ENEMY2;
    entity->Category = CATEGORY_ENEMY;
    entity->Health = new(HealthComponent, 20, 20);
    entity->Velocity = new(VelocityComponent, 0, 0);
    return entity;
}
method Entity* CreateEnemy3(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy3");
    entity->Type = TYPE_ENEMY3;
    entity->Category = CATEGORY_ENEMY;
    entity->Health = new(HealthComponent, 60, 60);
    entity->Velocity = new(VelocityComponent, 0, 0);
    return entity;
}
method Entity* CreateExplosion(EntityManager* self) {
    var scale = 0.6;
    Entity* entity = CreateEntity(self, "explosion", scale);
    entity->Type = TYPE_EXPLOSION;
    entity->Category = CATEGORY_EXPLOSION;
    entity->Sound = new(SoundComponent, SoundEffectAsplode);
    entity->Tween = new(TweenComponent, scale/100.0, scale, -3, false, true);
    entity->Tint = new(ColorComponent, 0xd2, 0xfa, 0xd2, 0xfa);
    entity->Expires = new(ExpireComponent, 0.2);
    return entity;
}
method Entity* CreateBang(EntityManager* self) {
    var scale = 0.4;
    Entity* entity = CreateEntity(self, "explosion", scale);
    entity->Type = TYPE_BANG;
    entity->Category = CATEGORY_EXPLOSION;
    entity->Sound = new(SoundComponent, SoundEffectSmallAsplode);
    entity->Tween = new(TweenComponent, scale/100.0, scale, -3, false, true);
    entity->Tint = new(ColorComponent, 0xd2, 0xfa, 0xd2, 0xfa );
    entity->Expires = new(ExpireComponent, 0.2);
    return entity;
}
method Entity* CreateParticle(EntityManager* self) {
    Entity* entity = CreateEntity(self, "star");
    entity->Type = TYPE_PARTICLE;
    entity->Category = CATEGORY_PARTICLE;
    entity->Velocity = new(VelocityComponent, 0, 0);
    entity->Tint = new(ColorComponent, 0xd2, 0xfa, 0xd2, 0xfa );
    entity->Expires = new(ExpireComponent, 0.75);
    return entity;
}



method Entity* ResetBullet(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Velocity->X = 0;
    entity->Velocity->Y = -800;
    entity->Expires->Value = 1.0;
    entity->Health->Current = 2;
    return entity;
}

method Entity* ResetEnemy1(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Velocity->X = 0;
    entity->Velocity->Y = 40;
    entity->Health->Current = 10;
    return entity;
}

method Entity* ResetEnemy2(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Velocity->X = 0;
    entity->Velocity->Y = 30;
    entity->Health->Current = 20;
    return entity;
}

method Entity* ResetEnemy3(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Velocity->X = 0;
    entity->Velocity->Y = 20;
    entity->Health->Current = 60;
    return entity;
}

method Entity* ResetExplosion(Entity* entity, int x, int y) 
{
    auto scale = 0.6;
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Transform->Scale.x = scale;
    entity->Transform->Scale.y = scale;
    entity->Tween->Active = true;
    entity->Tween = new(TweenComponent, scale/100.0, scale, -3, false, true);
    entity->Expires->Value =  0.2;
    return entity;
}

method Entity* ResetBang(Entity* entity, int x, int y) 
{
    auto scale = 0.4;
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Transform->Scale.x = scale;
    entity->Transform->Scale.y = scale;
    entity->Tween->Active = true;
    entity->Tween = new(TweenComponent, scale/100.0, scale, -3, false, true);    entity->Expires->Value = 0.2;
    return entity;
}

method Entity* ResetParticle(Entity* entity, int x, int y) 
{
    double Tau = 6.28318;
    double r1 = ((double)rand()/(double)1.0);
    double radians = r1 * (double)Tau;
    double magnitude = rand() % 100 + 50;
    double velocityX = magnitude * cos(radians);
    double velocityY = magnitude * sin(radians);
    double scale = (double)(rand() % 10) / 10.0;

    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;
    entity->Transform->Bounds.x = x; 
    entity->Transform->Bounds.y = y; 
    entity->Transform->Scale.x = scale;
    entity->Transform->Scale.y = scale;
    entity->Velocity->X = velocityX;
    entity->Velocity->Y = velocityY;
    entity->Expires->Value = 0.75;
    return entity;
}

