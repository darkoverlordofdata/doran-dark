#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsTagManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Map* EntitiesByTag;
    Map* TagsByEntity;
};

method void Register(EcsTagManager* self, char* tag, EcsEntity* e);
method void Unregister(EcsTagManager* self, char* tag);
method bool IsRegistered(EcsTagManager* self, char* tag);
method EcsEntity* GetEntity(EcsTagManager* self, char* tag);
method Array* GetRegisteredTags(EcsTagManager* self);

delegate (EcsTagManager, New,          EcsTagManager*, (EcsTagManager*));
delegate (EcsTagManager, ToString,     char*,    (const EcsTagManager* const));
delegate (EcsTagManager, Initialize,   void, (EcsTagManager*));
delegate (EcsTagManager, GetWorld,     EcsWorld*, (EcsTagManager*));
delegate (EcsTagManager, SetWorld,     void, (EcsTagManager*, EcsWorld*));
delegate (EcsTagManager, Added,        void, (EcsTagManager*, EcsEntity*));
delegate (EcsTagManager, Changed,      void, (EcsTagManager*, EcsEntity*));
delegate (EcsTagManager, Deleted,      void, (EcsTagManager*, EcsEntity*));
delegate (EcsTagManager, Disabled,     void, (EcsTagManager*, EcsEntity*));
delegate (EcsTagManager, Enabled,      void, (EcsTagManager*, EcsEntity*));


/**
 * EcsTagManager Vtable
 */
vtable (EcsTagManager) 
{
    const EcsTagManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsTagManagerToString    Initialize;
    const EcsTagManagerGetWorld    GetWorld;
    const EcsTagManagerSetWorld    SetWorld;
    const EcsTagManagerAdded       Added;
    const EcsTagManagerChanged     Changed;
    const EcsTagManagerDeleted     Deleted;
    const EcsTagManagerDisabled    Disabled;
    const EcsTagManagerEnabled     Enabled;
};

static inline vptr(EcsTagManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsTagManager(Class base) 
{
    Class cls = createClass(base, EcsTagManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsTagManager,  Initialize);
    addMethod(cls, EcsTagManager,  GetWorld);
    addMethod(cls, EcsTagManager,  SetWorld);
    addMethod(cls, EcsTagManager,  Added);
    addMethod(cls, EcsTagManager,  Changed);
    addMethod(cls, EcsTagManager,  Deleted);
    addMethod(cls, EcsTagManager,  Disabled);
    addMethod(cls, EcsTagManager,  Enabled);
    return cls; 
}

method EcsTagManager* New(EcsTagManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsTagManager);
    self->EntitiesByTag = new(Map, of(Entity));
    self->TagsByEntity = new(Map, of(String));
    return self;
}

method void Initialize(EcsTagManager* self) { virtual(EcsTagManager)->Initialize(self); }

method void SetWorld(EcsTagManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsTagManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsTagManager* self, EcsEntity* entity) { virtual(EcsTagManager)->Added(self, entity); }

method void Changed(EcsTagManager* self, EcsEntity* entity) { virtual(EcsTagManager)->Changed(self, entity); }

method void Deleted(EcsTagManager* self, EcsEntity* entity) 
{ 
    Remove(self->EntitiesByTag, (char*)Get(self->TagsByEntity, entity->key));
}

method void Disabled(EcsTagManager* self, EcsEntity* entity) { virtual(EcsTagManager)->Disabled(self, entity); }

method void Enabled(EcsTagManager* self, EcsEntity* entity) { virtual(EcsTagManager)->Enabled(self, entity); }

method void Register(EcsTagManager* self, char* tag, EcsEntity* e) {
    Put(self->EntitiesByTag, tag, e);
    Put(self->TagsByEntity, e->key, tag);
}

method void Unregister(EcsTagManager* self, char* tag) {
    Remove(self->TagsByEntity, ((EcsEntity*)(Get(self->EntitiesByTag, tag)))->key);
    Remove(self->EntitiesByTag, tag);
}

method bool IsRegistered(EcsTagManager* self, char* tag) {
    return Get(self->EntitiesByTag, tag) != nullptr;
}

method EcsEntity* GetEntity(EcsTagManager* self, char* tag) {
    return Get(self->EntitiesByTag, tag);
}

method Array* GetRegisteredTags(EcsTagManager* self) {

    Array* res = new(Array);
    ForEach(self->TagsByEntity, ^(Object* s) {
        Add(res, s);
    });
    return res;
}
