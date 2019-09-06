#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



/*
 * Used only internally to generate distinct ids for entities and reuse them.
 */
type (EcsIdentifierPool)
{
    Array* Ids;
    int NextAvailableId;

};
method EcsIdentifierPool* New(EcsIdentifierPool* self)
{
    self->Ids = new(Array);
    self->NextAvailableId = 0;
    return self;
}

method void CheckIn(EcsIdentifierPool* self, int id)
{
    Add(self->Ids, new(Integer, id));
}

method int CheckOut(EcsIdentifierPool* self)
{
    auto length = Length(self->Ids);
    if (length > 0) {
        int retval = IntValue((Number*)Get(self->Ids, length));
        Remove(self->Ids, length);
        return retval;
    }
    return self->NextAvailableId++;
}


type (EcsEntityManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Array* Entities;
    BitSet* Disabled;
    int Active;
    int Added;
    int Created;
    int Deleted;
    EcsIdentifierPool* IdentifierPool;
};

delegate (EcsEntityManager, New,          EcsEntityManager*, (EcsEntityManager*));
delegate (EcsEntityManager, ToString,     char*,    (const EcsEntityManager* const));
delegate (EcsEntityManager, GetWorld,     EcsWorld*, (EcsEntityManager*));
delegate (EcsEntityManager, SetWorld,     void, (EcsEntityManager*, EcsWorld*));
delegate (EcsEntityManager, Added,        void, (EcsEntityManager*, EcsEntity*));
delegate (EcsEntityManager, Changed,      void, (EcsEntityManager*, EcsEntity*));
delegate (EcsEntityManager, Deleted,      void, (EcsEntityManager*, EcsEntity*));
delegate (EcsEntityManager, Disabled,     void, (EcsEntityManager*, EcsEntity*));
delegate (EcsEntityManager, Enabled,      void, (EcsEntityManager*, EcsEntity*));


/**
 * EcsEntityManager Vtable
 */
vtable (EcsEntityManager) 
{
    const EcsEntityManagerToString  ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const EcsEntityManagerGetWorld  GetWorld;
    const EcsEntityManagerSetWorld  SetWorld;
    const EcsEntityManagerAdded     Added;
    const EcsEntityManagerChanged   Changed;
    const EcsEntityManagerDeleted   Deleted;
    const EcsEntityManagerDisabled  Disabled;
    const EcsEntityManagerEnabled   Enabled;
};

static inline vptr(EcsEntityManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsEntityManager(Class base) 
{
    Class cls = createClass(base, EcsEntityManager);
    addMethod(cls, Object,              ToString);
    addMethod(cls, Object,              Equals);
    addMethod(cls, Object,              GetHashCode);
    addMethod(cls, Object,              Dispose);
    addMethod(cls, EcsEntityManager,    GetWorld);
    addMethod(cls, EcsEntityManager,    SetWorld);
    addMethod(cls, EcsEntityManager,    Added);
    addMethod(cls, EcsEntityManager,    Changed);
    addMethod(cls, EcsEntityManager,    Deleted);
    addMethod(cls, EcsEntityManager,    Disabled);
    addMethod(cls, EcsEntityManager,    Enabled);
    return cls;
}



method EcsEntityManager* New(EcsEntityManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsEntityManager);
    self->Entities = new(Array, of(EcsEntity));
    self->Disabled = new(BitSet);
    self->IdentifierPool = new(EcsIdentifierPool);
    self->Active = 0;
    self->Added = 0;
    self->Created = 0;
    self->Deleted = 0;
    return self;
}
method void SetWorld(EcsEntityManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsEntityManager* self)
{
    return GetWorld(self->base);
}

method EcsEntity* CreateEntityInstance(EcsEntityManager* self, char* name)
{
    auto e = new(EcsEntity, self->World, CheckOut(self->IdentifierPool), name);
    self->Created += 1;
    return e;
}


method void Added(EcsEntityManager* self, EcsEntity* entity)
{
    self->Active += 1;
    self->Added += 1;
    Put(self->Entities, entity->Id, entity);
}

method void Changed(EcsEntityManager* self, EcsEntity* entity) {  }

method void Enabled(EcsEntityManager* self, EcsEntity* entity)
{
    Clear(self->Disabled, entity->Id);
}

method void Disabled(EcsEntityManager* self, EcsEntity* entity)
{
    Set(self->Disabled, entity->Id, true);
}

method void Deleted(EcsEntityManager* self, EcsEntity* entity)
{
    Put(self->Entities, entity->Id, nullptr);
    Clear(self->Disabled, entity->Id);
    CheckIn(self->IdentifierPool, entity->Id);
    self->Active -=1;
    self->Deleted += 1;
}

/**
 * Check if this entity is active.
 * Active means the entity is being actively processed.
 * 
 * @param entityId
 * @return true if active, false if not.
 */
method bool IsActive(EcsEntityManager* self, int entityId)
{
    return Get(self->Entities, entityId) != nullptr;
}

/**
 * Check if the specified entityId is enabled.
 * 
 * @param entityId
 * @return true if the entity is enabled, false if it is disabled.
 */
method bool IsEnabled(EcsEntityManager* self, int entityId)
{   
    return !Get(self->Disabled, entityId);
}

/**
 * Get a entity with this id.
 * 
 * @param entityId
 * @return the entity
 */
method EcsEntity* GetEntity(EcsEntityManager* self, int entityId)
{
    return Get(self->Entities, entityId);
}

/**
 * Get how many entities are active in this world.
 * @return how many entities are currently active.
 */
method int GetActiveEntityCount(EcsEntityManager* self) 
{
    return self->Active;
}


/**
 * Get how many entities have been created in the world since start.
 * Note: A created entity may not have been added to the world, thus
 * created count is always equal or larger than added count.
 * @return how many entities have been created since start.
 */
method int GetTotalCreated(EcsEntityManager* self)
{
    return self->Created;
}

/**
 * Get how many entities have been added to the world since start.
 * @return how many entities have been added.
 */
method int GetTotalAdded(EcsEntityManager* self) 
{
    return self->Added;
}

/**
 * Get how many entities have been deleted from the world since start.
 * @return how many entities have been deleted since start.
 */
method int GetTotalDeleted(EcsEntityManager* self)
{
    return self->Deleted;
}


