#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


/**
 * The entity class. Cannot be instantiated outside the framework, you must
 * create new entities using World.
 * 
 * @author Arni Arent
 * 
 */
type (EcsEntity)
{
    Class isa;
    char* Name;
    int Id;
    UUID* uuid;
    char* key;
    BitSet* ComponentBits;
    BitSet* SystemBits;
    EcsWorld* World;
    EcsEntityManager* EntityManager;
    EcsComponentManager* ComponentManager;
};

method void Reset(EcsEntity* self);
method bool IsActive(EcsEntityManager* self, int entityId);
method bool IsEnabled(EcsEntityManager* self, int entityId);
method void Enable(EcsWorld* self, EcsEntity* e);
method void Disable(EcsWorld* self, EcsEntity* e);
method EcsEntityManager* GetEntityManager(EcsWorld* self);
method EcsComponentManager* GetComponentManager(EcsWorld* self);
method void AddEntity(EcsWorld* self, EcsEntity* e);
method void ChangedEntity(EcsWorld* self, EcsEntity* e);
method void DeleteEntity(EcsWorld* self, EcsEntity* e);
method EcsEntity* CreateEntity(EcsWorld* self, char* name);
method EcsEntity* RemoveComponent(EcsEntity* self, EcsComponentType* type);


method EcsEntity* New(EcsEntity* self, EcsWorld* world, int id, char* name)
{
    self->isa = isa(EcsEntity);
    self->World = world;
    self->Id = id;
    self->uuid = new(UUID);
    self->key = strdup(ToString(self->uuid));
    self->Name = strdup(name);
    self->EntityManager = GetEntityManager(world);
    self->ComponentManager = GetComponentManager(world);
    self->ComponentBits = new(BitSet);
    self->SystemBits = new(BitSet);
    Reset(self);
    return self;
}


method BitSet* GetComponentBits(EcsEntity* self) {
    return self->ComponentBits;
}
method BitSet* GetSystemBits(EcsEntity* self) {
    return self->SystemBits;
}
method int GetId(EcsEntity* self) {
    return self->Id;
}
method UUID* GetUUID(EcsEntity* self) {
    return self->uuid;
}

/**
 * Make entity ready for re-use.
 * Will generate a new uuid for the entity.
 */
method void Reset(EcsEntity* self)
{
    Clear(self->SystemBits);
    Clear(self->ComponentBits);
}

/**
 * Faster adding of components into the entity. Not neccessery to use this, but
 * in some cases you might need the extra performance.
 * 
 * @param component the component to add
 * @param args of the component
 * 
 * @return this entity for chaining.
 */
method EcsEntity* AddComponent(EcsEntity* self, EcsComponent* component)
{
    auto type = component->isa;
    auto tf = GetTypeFactory(GetComponentManager(self->World));
    auto componentType = GetTypeFor(self, tf);
    Set(self->ComponentBits, GetIndex(componentType), true);
    AddComponent(self->ComponentManager, self, componentType, component);
    return self;
}

method EcsComponentType* GetTypeFor(EcsEntity* self, Class c)
{
    return GetTypeFor(GetTypeFactory(GetComponentManager(self->World)), c);
}

/**
 * Removes the component from this entity.
 * 
 * @param component to remove from this entity.
 * 
 * @return this entity for chaining.
 */
method EcsEntity* RemoveComponentInstance(EcsEntity* self, EcsComponent* component)
{
    EcsComponentType* type = GetTypeFor(self, component->isa);
    RemoveComponent(self, type);
    return self;
}

/**
 * Faster removal of components from a entity.
 * 
 * @param type to remove from this entity.
 * 
 * @return this entity for chaining.
 */
method EcsEntity* RemoveComponent(EcsEntity* self, EcsComponentType* type)
{
    RemoveComponent(self->ComponentManager, self, type);
    return self;
}

/**
 * Remove component by its type.
 * @param type
 * 
 * @return this entity for chaining.
 */
method EcsEntity* RemoveComponentByType(EcsEntity* self, Class type)
{
    RemoveComponent(self, GetTypeFor(self, type));
    return self;
}

/**
 * Checks if the entity has been added to the world and has not been deleted from it.
 * If the entity has been disabled this will still return true.
 * 
 * @return if it's active.
 */
method bool IsActive(EcsEntity* self)
{
    return IsActive(self->EntityManager, self->Id);
}

/**
 * Will check if the entity is enabled in the world.
 * By default all entities that are added to world are enabled,
 * this will only return false if an entity has been explicitly disabled.
 * 
 * @return if it's enabled
 */
method bool IsEnabled(EcsEntity* self)
{
    return IsEnabled(self->EntityManager, self->Id);
}


/**
 * This is the preferred method to use when retrieving a component from a
 * entity. It will provide good performance.
 * But the recommended way to retrieve components from an entity is using
 * the ComponentMapper.
 * 
 * @param type
 *            in order to retrieve the component fast you must provide a
 *            ComponentType instance for the expected component.
 * @return
 */
method EcsComponent* GetComponent(EcsEntity* self, EcsComponentType* type)
{
    return GetCompoment(self->ComponentManager, self, type);
}


/**
 * Slower retrieval of components from this entity. Minimize usage of this,
 * but is fine to use e.g. when creating new entities and setting data in
 * components.
 * 
 * @param <T>
 *            the expected return component type.
 * @param type
 *            the expected return component type.
 * @return component that matches, or null if none is found.
 */
method EcsComponent* GetComponentByType(EcsEntity* self, Class type)
{
    return GetCompoment(self->ComponentManager, self, GetTypeFor(self, type));
}


/**
 * Returns a bag of all components this entity has.
 * You need to reset the bag yourself if you intend to fill it more than once.
 * 
 * @param fillBag the bag to put the components into.
 * @return the fillBag with the components in.
 */
method Array* GetCompoments(EcsEntity* self, Array* fillBag)
{
    return GetComponentsFor(self->ComponentManager, self, fillBag);
}

/**
 * Refresh all changes to components for this entity. After adding or
 * removing components, you must call this method. It will update all
 * relevant systems. It is typical to call this after adding components to a
 * newly created entity.
 */
method void AddToWorld(EcsEntity* self)
{
    AddEntity(self->World, self);
}

/**
 * This entity has changed, a component added or deleted.
 */
method void ChangedInWorld(EcsEntity* self)
{
    ChangedEntity(self->World, self);
}

/**
 * Delete this entity from the world.
 */
method void DeleteFromWorld(EcsEntity* self)
{
    DeleteEntity(self->World, self);
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
 * Won't do anything unless it was already disabled.
 */
method void Enable(EcsEntity* self)
{
    Enable(self->World, self);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
 * continue to exist but won't get processed.
 */
method void Disable(EcsEntity* self)
{
    Disable(self->World, self);
}

/**
 * Returns the world this entity belongs to.
 * @return world of entity.
 */
method EcsWorld* GetWorld(EcsEntity* self)
{
    return self->World;
}