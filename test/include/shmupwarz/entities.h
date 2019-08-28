#pragma once
#include <stdlib.h>
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "types.h"
#include "shmupwarz.h"

#define BACKGROUND_MASK 0;
#define PLAYER_MASK 0;
#define BULLET_MASK OPTION_SOUND | OPTION_HEALTH | OPTION_TINT | OPTION_VELOCITY;
#define ENEMY_MASK OPTION_HEALTH | OPTION_VELOCITY;
#define EXPLOSION_MASK OPTION_SOUND | OPTION_TWEEN | OPTION_TINT;
#define BANG_MASK OPTION_SOUND | OPTION_TWEEN | OPTION_TINT;
#define PARTICLE_MASK OPTION_SOUND | OPTION_TINT;

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

delegate (EntityManager, InitBackground,    Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitPlayer,        Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitBullet,        Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitEnemy1,        Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitEnemy2,        Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitEnemy3,        Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitExplosion,     Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitBang,          Entity*, (EntityManager*, Entity* entity));
delegate (EntityManager, InitParticle,      Entity*, (EntityManager*, Entity* entity));

// delegate (EntityManager, ResetBackground, Entity*, (EntityManager*, Entity* entity, int x, int y));
// delegate (EntityManager, ResetPlayer,     Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetBullet,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy1,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy2,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetEnemy3,       Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetExplosion,    Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetBang,         Entity*, (EntityManager*, Entity* entity, int x, int y));
delegate (EntityManager, ResetParticle,     Entity*, (EntityManager*, Entity* entity, int x, int y));


static int UniqueId = 0;

static inline vptr(EntityManager);

method EntityManager* New(EntityManager* self, Shmupwarz* game, ResourceManager* resource)
{
    extends(Object);
    self->isa = isa(EntityManager);
    self->game = game;
    self->resource = resource;
    return self;
}


static inline SDL_Surface* GetResource(char* name) {
    const char* path = join("assets/images/", name);
    return IMG_Load(path);
}

method Entity* CreateEntity(EntityManager* self) {
    self->count = UniqueId+1;
    return  &self->entities[UniqueId++];
}

method Entity* CreateBackground(EntityManager* self) {
    return InitBackground(self, CreateEntity(self));
}

method Entity* CreatePlayer(EntityManager* self) {
    return InitPlayer(self, CreateEntity(self));
}

method Entity* CreateBullet(EntityManager* self) {
    return InitBullet(self, CreateEntity(self));
}

method Entity* CreateEnemy1(EntityManager* self) {
    return InitEnemy1(self, CreateEntity(self));
}

method Entity* CreateEnemy2(EntityManager* self) {
    return InitEnemy2(self, CreateEntity(self));
}
method Entity* CreateEnemy3(EntityManager* self) {
    return InitEnemy3(self, CreateEntity(self));
}
method Entity* CreateExplosion(EntityManager* self) {
    return InitExplosion(self, CreateEntity(self));
}
method Entity* CreateBang(EntityManager* self) {
    return InitBang(self, CreateEntity(self));
}
method Entity* CreateParticle(EntityManager* self) {
    return InitParticle(self, CreateEntity(self));
}

method Entity* InitBackground(EntityManager* self, Entity* entity) 
{
    const auto scale = 2.0;
    entity->Active = true;
    entity->Type = TYPE_BACKGROUND;
    entity->Category = CATEGORY_BACKGROUND;
    entity->Sprite.Texture = GetTexture(self->resource, "background");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Optional = BACKGROUND_MASK;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitPlayer(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_PLAYER;
    entity->Category = CATEGORY_PLAYER;
    entity->Sprite.Texture = GetTexture(self->resource, "spaceshipspr");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitBullet(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_BULLET;
    entity->Category = CATEGORY_BULLET;
    entity->Sprite.Texture = GetTexture(self->resource, "bullet");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitEnemy1(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_ENEMY1;
    entity->Category = CATEGORY_ENEMY;
    entity->Sprite.Texture = GetTexture(self->resource, "enemy1");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}
method Entity* InitEnemy2(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_ENEMY2;
    entity->Category = CATEGORY_ENEMY;
    entity->Sprite.Texture = GetTexture(self->resource, "enemy2");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitEnemy3(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_ENEMY3;
    entity->Category = CATEGORY_ENEMY;
    entity->Sprite.Texture = GetTexture(self->resource, "enemy3");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitExplosion(EntityManager* self, Entity* entity) 
{
    auto scale = 0.6;
    entity->Type = TYPE_EXPLOSION;
    entity->Category = CATEGORY_EXPLOSION;
    entity->Sprite.Texture = GetTexture(self->resource, "explosion");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitBang(EntityManager* self, Entity* entity) 
{
    auto scale = 0.4;
    entity->Type = TYPE_BANG;
    entity->Category = CATEGORY_EXPLOSION;
    entity->Sprite.Texture = GetTexture(self->resource, "explosion");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}

method Entity* InitParticle(EntityManager* self, Entity* entity) 
{
    auto scale = 1.0;
    entity->Type = TYPE_PARTICLE;
    entity->Category = CATEGORY_PARTICLE;
    entity->Sprite.Texture = GetTexture(self->resource, "star");
    entity->Sprite.Width = entity->Sprite.Texture->Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture->Height*scale;
    entity->Bounds.w = entity->Sprite.Texture->Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture->Height*scale; 
    entity->Scale.x = scale;
    entity->Scale.y = scale;
}


method Entity* ResetBullet(Entity* entity, int x, int y) 
{
    entity->Position = (Vec2) { x, y };
    entity->Expires = 1.0;
    entity->Sound = EFFECT_PEW;
    entity->Health = (Health) { 2, 2 };
    entity->Tint = (Color) { 0xd2, 0xfa, 0x00, 0xffa };
    entity->Velocity = (Vec2) { 0, -800 };
    entity->Active = true;
}

method Entity* ResetEnemy1(Entity* entity, int x, int y) 
{
    entity->Position = (Vec2) { x, y };
    entity->Health = (Health) { 10, 10 };
    entity->Velocity = (Vec2) { 0, 40 };
    entity->Active = true;
}

method Entity* ResetEnemy2(Entity* entity, int x, int y) 
{
    entity->Position = (Vec2) { x, y };
    entity->Health = (Health) { 20, 20 };
    entity->Velocity = (Vec2) { 0, 30 };
    entity->Active = true;
}

method Entity* ResetEnemy3(Entity* entity, int x, int y) 
{
    entity->Position = (Vec2) { x, y };
    entity->Health = (Health) { 60, 60 };
    entity->Velocity = (Vec2) { 0, 20 };
    entity->Active = true;
}

method Entity* ResetExplosion(Entity* entity, int x, int y) 
{
    auto scale = 0.6;
    entity->Position = (Vec2) { x, y };
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale - (Vec2) { scale, scale };
    entity->Sound = EFFECT_ASPLODE;
    entity->Tween = (Tween) { scale/100.0, scale, -3, false, true };
    entity->Tint = (Color)  { 0xd2, 0xfa, 0xd2, 0xfa };
    entity->Expires = 0.2;
    entity->Active = true;
}

method Entity* ResetBang(Entity* entity, int x, int y) 
{
    auto scale = 0.4;
    entity->Position = (Vec2) { x, y };
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale - (Vec2) { scale, scale };
    entity->Sound = EFFECT_SMALLASPLODE;
    entity->Tween = (Tween) { scale/100.0, scale, -3, false, true };
    entity->Tint = (Color) { 0xd2, 0xfa, 0xd2, 0xfa };
    entity->Expires = 0.2;
    entity->Active = true;
}

method Entity* ResetParticle(Entity* entity, int x, int y) 
{
    auto Tau = 6.28318;
    auto radians = ((double)rand()/(double)1.0) * (double)Tau;
    auto magnitude = rand() % 100 + 50;
    auto velocityX = magnitude * cos(radians);
    auto velocityY = magnitude * sin(radians);
    auto scale = (double)(rand() % 10) / 10.0;
    entity->Position = (Vec2) { x, y };
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale - (Vec2) { scale, scale };
    entity->Velocity = (Vec2) { velocityX, velocityY };
    entity->Tint = (Color) { 0xfa, 0xfa, 0xd2, 0xff };
    entity->Expires = 0.75;
    entity->Active = true;
}

