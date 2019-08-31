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

    AddTaxonomyComponent (entity, TypeBackground, SubtypeBackground);
    return entity;
}

method Entity* CreatePlayer(EntityManager* self) {
    Entity* entity = CreateEntity(self, "spaceshipspr");
    entity->Active = true;

    AddTaxonomyComponent (entity, TypePlayer, SubtypePlayer);
    return entity;
}

method Entity* CreateBullet(EntityManager* self) {
    Entity* entity = CreateEntity(self, "bullet");

    AddTaxonomyComponent (entity, TypeBullet, SubtypeBullet);
    AddVelocityComponent (entity, 0, -800);
    AddExpireComponent (entity, 1.0);
    AddSoundComponent (entity, SoundEffectPew);
    AddHealthComponent (entity, 2, 2);
    AddColorComponent (entity, 0xd2, 0xfa, 0x00, 0xffa);
    return entity;
}

method Entity* CreateEnemy1(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy1");

    AddTaxonomyComponent (entity, TypeEnemy, SubtypeEnemy1);
    AddHealthComponent (entity, 10, 10);
    AddVelocityComponent (entity, 0, 40);
    return entity;
}

method Entity* CreateEnemy2(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy2");

    AddTaxonomyComponent (entity, TypeEnemy, SubtypeEnemy2);
    AddHealthComponent (entity, 20, 20);
    AddVelocityComponent (entity, 0, 30);
    return entity;
}
method Entity* CreateEnemy3(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy3");

    AddTaxonomyComponent (entity, TypeEnemy, SubtypeEnemy3);
    AddHealthComponent (entity, 60, 60);
    AddVelocityComponent (entity, 0, 20);
    return entity;
}

method Entity* CreateExplosion(EntityManager* self) {   
    var scale = 0.6;
    Entity* entity = CreateEntity(self, "explosion", scale);

    AddTaxonomyComponent (entity, TypeExplosion, SubtypeExplosion1);
    AddSoundComponent (entity, SoundEffectAsplode);
    AddTweenComponent (entity, scale/100.0, scale, -3, false, true);
    AddColorComponent (entity, 0xd2, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity,0.2);
    return entity;
}

method Entity* CreateBang(EntityManager* self) {
    var scale = 0.4;
    Entity* entity = CreateEntity(self, "explosion", scale);

    AddTaxonomyComponent (entity, TypeExplosion, SubtypeExplosion2);
    AddSoundComponent (entity, SoundEffectSmallAsplode);
    AddTweenComponent (entity, scale/100.0, scale, -3, false, true);
    AddColorComponent (entity, 0xd2, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity,0.2);
    return entity;
}

method Entity* CreateParticle(EntityManager* self) {
    Entity* entity = CreateEntity(self, "star");

    AddTaxonomyComponent (entity, TypeParticle, SubtypeParticle);
    AddVelocityComponent (entity, 0, 0);
    AddColorComponent (entity, 0xfa, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity,0.75);
    return entity;
}



method Entity* ResetBullet(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;

    GetVelocityComponent (entity)->Y = -800;
    GetExpireComponent (entity)->Value = 1.0;
    GetHealthComponent (entity)->Current = 2;
    return entity;
}

method Entity* ResetEnemy1(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;

    GetVelocityComponent (entity)->Y = 40;
    GetHealthComponent (entity)->Current = 10;
    return entity;
}

method Entity* ResetEnemy2(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;

    GetVelocityComponent (entity)->Y = 30;
    GetHealthComponent (entity)->Current = 20;
    return entity;
}

method Entity* ResetEnemy3(Entity* entity, int x, int y) 
{
    entity->Active = true;
    entity->Transform->Pos.x = x;
    entity->Transform->Pos.y = y;

    GetVelocityComponent (entity)->Y = 20;
    GetHealthComponent (entity)->Current = 60;
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

    GetTweenComponent (entity)->Active = true;
    GetExpireComponent (entity)->Value = 0.2;
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

    GetTweenComponent (entity)->Active = true;
    GetExpireComponent (entity)->Value = 0.2;
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

    GetVelocityComponent (entity)->X = velocityX;
    GetVelocityComponent (entity)->Y = velocityY;
    GetExpireComponent (entity)->Value = 0.75;
    return entity;
}

