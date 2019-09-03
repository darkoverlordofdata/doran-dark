#pragma once
#include <stdlib.h>
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <string.h>
#include <tglm/tglm.h>
#include "types.h"
#include "shmupwarz.h"

typedef struct Shmupwarz Shmupwarz;
typedef struct ResourceManager ResourceManager;

method EntityManager* New(EntityManager* self, ResourceManager* resource)
{
    var base = extends(Object);
    self->isa = isa(EntityManager);
    self->Resource = resource;

    self->EntityPool = new(MemoryPool, sizeof(Entity), ENTITY_MAX);
    self->Entities = malloc(sizeof(Entity*)*ENTITY_MAX);
    self->ColorPool = new(MemoryPool, sizeof(ColorComponent), ENTITY_MAX);
    self->ExpirePool = new(MemoryPool, sizeof(ExpireComponent), ENTITY_MAX);
    self->HealthPool = new(MemoryPool, sizeof(HealthComponent), ENTITY_MAX);
    self->SoundPool = new(MemoryPool, sizeof(SoundComponent), ENTITY_MAX);
    self->TaxonomyPool = new(MemoryPool, sizeof(TaxonomyComponent), ENTITY_MAX);
    self->TweenPool = new(MemoryPool, sizeof(TweenComponent), ENTITY_MAX);
    self->VelocityPool = new(MemoryPool, sizeof(VelocityComponent), ENTITY_MAX);

    self->Count = 0;
    return self;
}

method void Dispose(EntityManager* self)
{
    Dispose(self->Resource);
    Dispose(self->EntityPool);
    if (_use_gc) return;
    free(self);
    free(self->Entities);
}
/**
 * CreateEntity
 * 
 * allocates an entity from the pool
 * 
 */
method Entity* CreateEntity(EntityManager* self, char* name, float scale) {
    Entity* entity = Alloc(self->EntityPool);
    self->Entities[self->Count] = entity;
    entity->Name = strdup(name);
    entity->Id = self->Count;
    entity->Transform = new(Transform, GetTexture(self->Resource, name), scale);
    self->Count +=1;
    return entity;
}

method Entity* CreateEntity(EntityManager* self, char* name) {
    return CreateEntity(self, name, 1.0);
}

method Entity* CreateBackground(EntityManager* self) {
    Entity* entity = CreateEntity(self, "background", 2.0f);
    entity->Active = true;
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeBackground, SubtypeBackground);
    return entity;
}

method Entity* CreatePlayer(EntityManager* self) {
    Entity* entity = CreateEntity(self, "spaceshipspr");
    entity->Active = true;
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypePlayer, SubtypePlayer);
    return entity;
}

method Entity* CreateBullet(EntityManager* self) {
    Entity* entity = CreateEntity(self, "bullet");
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeBullet, SubtypeBullet);
    AddVelocityComponent (entity, self->VelocityPool, 0, -800);
    AddExpireComponent (entity, self->ExpirePool, 1.0);
    AddSoundComponent (entity, self->SoundPool, SoundEffectPew);
    AddHealthComponent (entity, self->HealthPool, 2, 2);
    AddColorComponent (entity, self->ColorPool, 0xd2, 0xfa, 0x00, 0xffa);
    return entity;
}

method Entity* CreateEnemy1(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy1");
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeEnemy, SubtypeEnemy1);
    AddHealthComponent (entity, self->HealthPool, 10, 10);
    AddVelocityComponent (entity, self->VelocityPool, 0, 40);
    return entity;
}

method Entity* CreateEnemy2(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy2");
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeEnemy, SubtypeEnemy2);
    AddHealthComponent (entity, self->HealthPool, 20, 20);
    AddVelocityComponent (entity, self->VelocityPool, 0, 30);
    return entity;
}
method Entity* CreateEnemy3(EntityManager* self) {
    Entity* entity = CreateEntity(self, "enemy3");
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeEnemy, SubtypeEnemy3);
    AddHealthComponent (entity, self->HealthPool, 60, 60);
    AddVelocityComponent (entity, self->VelocityPool, 0, 20);
    return entity;
}

method Entity* CreateExplosion(EntityManager* self) {   
    var scale = 0.6;
    Entity* entity = CreateEntity(self, "explosion", scale);
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeExplosion, SubtypeExplosion1);
    AddSoundComponent (entity, self->SoundPool, SoundEffectAsplode);
    AddTweenComponent (entity, self->TweenPool, scale/100.0, scale, -3, false, true);
    AddColorComponent (entity, self->ColorPool, 0xd2, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity, self->ExpirePool, 0.2);
    return entity;
}

method Entity* CreateBang(EntityManager* self) {
    var scale = 0.4;
    Entity* entity = CreateEntity(self, "explosion", scale);
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeExplosion, SubtypeExplosion2);
    AddSoundComponent (entity, self->SoundPool, SoundEffectSmallAsplode);
    AddTweenComponent (entity, self->TweenPool, scale/100.0, scale, -3, false, true);
    AddColorComponent (entity, self->ColorPool, 0xd2, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity, self->ExpirePool, 0.2);
    return entity;
}

method Entity* CreateParticle(EntityManager* self) {
    Entity* entity = CreateEntity(self, "star");
    AddTaxonomyComponent (entity, self->TaxonomyPool, TypeParticle, SubtypeParticle);
    AddVelocityComponent (entity, self->VelocityPool, 0, 0);
    AddColorComponent (entity, self->ColorPool, 0xfa, 0xfa, 0xd2, 0xfa);
    AddExpireComponent (entity, self->ExpirePool, 0.75);
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

