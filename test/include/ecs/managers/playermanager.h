#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsPlayerManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Map* PlayerByEntity;
    Map* EntitiesByPlayer;
};

method void SetPlayer(EcsPlayerManager* self, EcsEntity* e, char* player);
method Array* GetEntitiesOfPlayer(EcsPlayerManager* self, char* player);
method void RemoveFromPlayer(EcsPlayerManager* self, EcsEntity* e);
method char* GetPlayer(EcsPlayerManager* self, EcsEntity* e);

delegate (EcsPlayerManager, New,          EcsPlayerManager*, (EcsPlayerManager*));
delegate (EcsPlayerManager, ToString,     char*,    (const EcsPlayerManager* const));
delegate (EcsPlayerManager, Initialize,   void, (EcsPlayerManager*));
delegate (EcsPlayerManager, GetWorld,     EcsWorld*, (EcsPlayerManager*));
delegate (EcsPlayerManager, SetWorld,     void, (EcsPlayerManager*, EcsWorld*));
delegate (EcsPlayerManager, Added,        void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Changed,      void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Deleted,      void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Disabled,     void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Enabled,      void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, SetPlayer, void, (EcsPlayerManager* self, EcsEntity* e, char* player));
delegate (EcsPlayerManager, GetEntitiesOfPlayer, Array*, (EcsPlayerManager* self, char* player));
delegate (EcsPlayerManager, RemoveFromPlayer, void, (EcsPlayerManager* self, EcsEntity* e));
delegate (EcsPlayerManager, GetPlayer, char*, (EcsPlayerManager* self, EcsEntity* e));


/**
 * EcsPlayerManager Vtable
 */
vtable (EcsPlayerManager) 
{
    const EcsPlayerManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsPlayerManagerToString    Initialize;
    const EcsPlayerManagerGetWorld    GetWorld;
    const EcsPlayerManagerSetWorld    SetWorld;
    const EcsPlayerManagerAdded       Added;
    const EcsPlayerManagerChanged     Changed;
    const EcsPlayerManagerDeleted     Deleted;
    const EcsPlayerManagerDisabled    Disabled;
    const EcsPlayerManagerEnabled     Enabled;
    const EcsPlayerManagerSetPlayer       SetPlayer;
    const EcsPlayerManagerGetEntitiesOfPlayer       GetEntitiesOfPlayer;
    const EcsPlayerManagerRemoveFromPlayer       RemoveFromPlayer;
    const EcsPlayerManagerGetPlayer       GetPlayer;
};

static inline vptr(EcsPlayerManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsPlayerManager(Class base) 
{
    Class cls = createClass(base, EcsPlayerManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsPlayerManager,  Initialize);
    addMethod(cls, EcsPlayerManager,  GetWorld);
    addMethod(cls, EcsPlayerManager,  SetWorld);
    addMethod(cls, EcsPlayerManager,  Added);
    addMethod(cls, EcsPlayerManager,  Changed);
    addMethod(cls, EcsPlayerManager,  Deleted);
    addMethod(cls, EcsPlayerManager,  Disabled);
    addMethod(cls, EcsPlayerManager,  Enabled);
    addMethod(cls, EcsPlayerManager, SetPlayer);
    addMethod(cls, EcsPlayerManager, GetEntitiesOfPlayer);
    addMethod(cls, EcsPlayerManager, RemoveFromPlayer);
    addMethod(cls, EcsPlayerManager, GetPlayer);
    return cls; 
}

method EcsPlayerManager* New(EcsPlayerManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsPlayerManager);
    self->PlayerByEntity = new(Map, of(String));
    self->EntitiesByPlayer = new(Map, of(Array));
    return self;
}

method void Initialize(EcsPlayerManager* self) { virtual(EcsPlayerManager)->Initialize(self); }

method void SetWorld(EcsPlayerManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsPlayerManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Added(self, entity); }

method void Changed(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Changed(self, entity); }

method void Deleted(EcsPlayerManager* self, EcsEntity* entity) 
{ 
    RemoveFromPlayer(self, entity);
}

method void Disabled(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Disabled(self, entity); }

method void Enabled(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Enabled(self, entity); }


method void SetPlayer(EcsPlayerManager* self, EcsEntity* e, char* player) {
    Put(self->PlayerByEntity, e->key, player);
    Array* entities = Get(self->EntitiesByPlayer, player);
    if (entities == nullptr) {
        entities = new(Array, of(Entity));
        Put(self->EntitiesByPlayer, player, entities);
    }
    Add(entities, e);
}

method Array* GetEntitiesOfPlayer(EcsPlayerManager* self, char* player)  {
    Array* entities = Get(self->EntitiesByPlayer, player);
    if (entities == nullptr) {
        entities = new(Array, of(Entity));
    }
    return entities;
}

method void RemoveFromPlayer(EcsPlayerManager* self, EcsEntity* e) {
    char* player = Get(self->PlayerByEntity, e->key);
    if (player != nullptr) {
        Array* entities = Get(self->EntitiesByPlayer, player);
        if(entities != nullptr) {
            Remove(entities, e);
        }
    }
}

method char* GetPlayer(EcsPlayerManager* self, EcsEntity* e) {
    return Get(self->PlayerByEntity, e->key);
}



