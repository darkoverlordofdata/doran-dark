#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsGroupManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Map* EntitiesByGroup;
    Map* GroupsByEntity;
};
method void Add(EcsGroupManager* self, EcsEntity* e, char* group);
method void Remove(EcsGroupManager* self, EcsEntity* e, char* group);
method void RemoveFromAllGroups(EcsGroupManager* self, EcsEntity* e);
method Array* GetEntities(EcsGroupManager* self, char* group);
method Array* GetGroups(EcsGroupManager* self, EcsEntity* e);
method bool IsInAnyGroup(EcsGroupManager* self, EcsEntity* e);
method bool IsInGroup(EcsGroupManager* self, EcsEntity* e, char* group);



delegate (EcsGroupManager, New,         EcsGroupManager*, (EcsGroupManager*));
delegate (EcsGroupManager, ToString,    char*,    (const EcsGroupManager* const));
delegate (EcsGroupManager, Initialize,  void, (EcsGroupManager*));
delegate (EcsGroupManager, GetWorld,    EcsWorld*, (EcsGroupManager*));
delegate (EcsGroupManager, SetWorld,    void, (EcsGroupManager*, EcsWorld*));
delegate (EcsGroupManager, Added,       void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Changed,     void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Deleted,     void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Disabled,    void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Enabled,     void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Add,         void, (EcsGroupManager* self, EcsEntity* e, char* group));
delegate (EcsGroupManager, Remove,      void, (EcsGroupManager* self, EcsEntity* e, char* group));
delegate (EcsGroupManager, RemoveFromAllGroups, void, (EcsGroupManager* self, EcsEntity* e));
delegate (EcsGroupManager, GetEntities, Array*, (EcsGroupManager* self, char* group));
delegate (EcsGroupManager, GetGroups,   Array*, (EcsGroupManager* self, EcsEntity* e));
delegate (EcsGroupManager, IsInAnyGroup, bool, (EcsGroupManager* self, EcsEntity* e));
delegate (EcsGroupManager, IsInGroup,   bool, (EcsGroupManager* self, EcsEntity* e, char* group));



/**
 * EcsGroupManager Vtable
 */
vtable (EcsGroupManager) 
{
    const EcsGroupManagerToString   ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const EcsGroupManagerToString   Initialize;
    const EcsGroupManagerGetWorld   GetWorld;
    const EcsGroupManagerSetWorld   SetWorld;
    const EcsGroupManagerAdded      Added;
    const EcsGroupManagerChanged    Changed;
    const EcsGroupManagerDeleted    Deleted;
    const EcsGroupManagerDisabled   Disabled;
    const EcsGroupManagerEnabled    Enabled;
    const EcsGroupManagerAdd        Add;
    const EcsGroupManagerRemove     Remove;
    const EcsGroupManagerRemoveFromAllGroups       RemoveFromAllGroups;
    const EcsGroupManagerGetEntities GetEntities;
    const EcsGroupManagerGetGroups   GetGroups;
    const EcsGroupManagerIsInAnyGroup IsInAnyGroup;
    const EcsGroupManagerIsInGroup   IsInGroup;

};

static inline vptr(EcsGroupManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsGroupManager(Class base) 
{
    Class cls = createClass(base, EcsGroupManager);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsGroupManager, Initialize);
    addMethod(cls, EcsGroupManager, GetWorld);
    addMethod(cls, EcsGroupManager, SetWorld);
    addMethod(cls, EcsGroupManager, Added);
    addMethod(cls, EcsGroupManager, Changed);
    addMethod(cls, EcsGroupManager, Deleted);
    addMethod(cls, EcsGroupManager, Disabled);
    addMethod(cls, EcsGroupManager, Enabled);
    addMethod(cls, EcsGroupManager, Add);
    addMethod(cls, EcsGroupManager, Remove);
    addMethod(cls, EcsGroupManager, RemoveFromAllGroups);
    addMethod(cls, EcsGroupManager, GetEntities);
    addMethod(cls, EcsGroupManager, GetGroups);
    addMethod(cls, EcsGroupManager, IsInAnyGroup);
    addMethod(cls, EcsGroupManager, IsInGroup);

    return cls; 
}

method EcsGroupManager* New(EcsGroupManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsGroupManager);
    self->EntitiesByGroup = new(Map, of(Array));
    self->GroupsByEntity = new(Map, of(Array));
    return self;
}

method void Initialize(EcsGroupManager* self) { virtual(EcsGroupManager)->Initialize(self); }

method void SetWorld(EcsGroupManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsGroupManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Added(self, entity); }

method void Changed(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Changed(self, entity); }

method void Deleted(EcsGroupManager* self, EcsEntity* entity) 
{ 
    RemoveFromAllGroups(self, entity);
}

method void Disabled(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Disabled(self, entity); }

method void Enabled(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Enabled(self, entity); }

/**
 * Set the group of the entity.
*
* @param group group to add the entity into.
* @param e entity to add into the group.
*/
method void Add(EcsGroupManager* self, EcsEntity* e, char* group) {
    Array* entities = Get(self->EntitiesByGroup, group);
    if (entities == nullptr) {
        entities = new(Array, of(EcsEntity*));
        Put(self->EntitiesByGroup, group, entities);
    }
    Add(entities, e);

    Array* groups = Get(self->GroupsByEntity, e->key);
    if (groups == nullptr) {
        groups = new(Array, of(char*));
        Put(self->GroupsByEntity, e->key, groups);
    }
    Add(groups, group);
}

/**
 * Remove the entity from the specified group.
 * @param e
 * @param group
 */
method void Remove(EcsGroupManager* self, EcsEntity* e, char* group) {
    Array* entities = Get(self->EntitiesByGroup, group);
    if (entities != nullptr) {
        Remove(entities, e);
    }

    Array* groups = Get(self->GroupsByEntity, e->key);
    if (groups != nullptr) {
        Remove(groups, (Object*)group);
    }
}

method void RemoveFromAllGroups(EcsGroupManager* self, EcsEntity* e) {
    Array* groups = Get(self->GroupsByEntity, e->key);
    if (groups != nullptr) {
        for(auto i = 0, s = groups->length; s > i; i++) {
            Array* entities = Get(self->EntitiesByGroup, Get(groups, i));
            if (entities != nullptr) {
                Remove(entities, e);
            }
        }
        Clear(groups);
    }
}

/**
 * Get all entities that belong to the provided group.
 * @param group name of the group.
 * @return read-only bag of entities belonging to the group.
 */
method Array* GetEntities(EcsGroupManager* self, char* group) {
    Array* entities = Get(self->EntitiesByGroup, group);
    if (entities == nullptr) {
        entities = new(Array, of(Entity));
        Put(self->EntitiesByGroup, group, entities);
    }
    return entities;
}

/**
 * @param e entity
 * @return the groups the entity belongs to, null if none.
 */
method Array* GetGroups(EcsGroupManager* self, EcsEntity* e)  {
    return Get(self->GroupsByEntity, e->key);
}

/**
 * Checks if the entity belongs to any group.
 * @param e the entity to check.
 * @return true if it is in any group, false if none.
 */
method bool IsInAnyGroup(EcsGroupManager* self, EcsEntity* e) {
    return GetGroups(self, e) != nullptr;
}

/**
 * Check if the entity is in the supplied group.
* @param group the group to check in.
* @param e the entity to check for.
* @return true if the entity is in the supplied group, false if not.
*/
method bool IsInGroup(EcsGroupManager* self, EcsEntity* e, char* group) {
    if (group != nullptr) {
        Array* groups = Get(self->GroupsByEntity, e->key);
        for (auto i = 0, s = groups->length; s > i; i++) {
            char* g = Get(groups, i);
            if (strcmp(group, g) == 0) {
                return true;
            }
        }
    }
    return false;
}



