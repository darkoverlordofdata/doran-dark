#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>

method BitSet* GetComponentBits(EcsEntity* self);
method int GetId(EcsEntity* self);


type (EcsComponentManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Array* ComponentsByType; // Array of Array
    Array* Deleted;
    EcsComponentTypeFactory* TypeFactory;
};

delegate (EcsComponentManager, New,          EcsComponentManager*, (EcsComponentManager*));
delegate (EcsComponentManager, ToString,     char*,    (const EcsComponentManager* const));
delegate (EcsComponentManager, GetWorld,     EcsWorld*, (EcsComponentManager*));
delegate (EcsComponentManager, SetWorld,     void, (EcsComponentManager*, EcsWorld*));
delegate (EcsComponentManager, Added,        void, (EcsComponentManager*, EcsEntity*));
delegate (EcsComponentManager, Changed,      void, (EcsComponentManager*, EcsEntity*));
delegate (EcsComponentManager, Deleted,      void, (EcsComponentManager*, EcsEntity*));
delegate (EcsComponentManager, Disabled,     void, (EcsComponentManager*, EcsEntity*));
delegate (EcsComponentManager, Enabled,      void, (EcsComponentManager*, EcsEntity*));


/**
 * EcsComponentManager Vtable
 */
vtable (EcsComponentManager) 
{
    const EcsComponentManagerToString   ToString;
    const ObjectEquals                  Equals;
    const ObjectGetHashCode             GetHashCode;
    const ObjectDispose                 Dispose;
    const EcsManagerGetWorld            GetWorld;
    const EcsManagerSetWorld            SetWorld;
    const EcsComponentManagerAdded      Added;
    const EcsComponentManagerChanged    Changed;
    const EcsComponentManagerDeleted    Deleted;
    const EcsComponentManagerDisabled   Disabled;
    const EcsComponentManagerEnabled    Enabled;
};

static inline vptr(EcsComponentManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsComponentManager(Class base) 
{
    Class cls = createClass(base, EcsComponentManager);
    addMethod(cls, Object,              ToString);
    addMethod(cls, Object,              Equals);
    addMethod(cls, Object,              GetHashCode);
    addMethod(cls, Object,              Dispose);
    addMethod(cls, EcsManager,          GetWorld);
    addMethod(cls, EcsManager,          SetWorld);
    addMethod(cls, EcsComponentManager, Added);
    addMethod(cls, EcsComponentManager, Changed);
    addMethod(cls, EcsComponentManager, Deleted);
    addMethod(cls, EcsComponentManager, Disabled);
    addMethod(cls, EcsComponentManager, Enabled);
    return cls;
}


method EcsComponentManager* New(EcsComponentManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsComponentManager);
    self->ComponentsByType = new(Array, of(Array));
    self->Deleted = new(Array, of(EcsEntity));
    self->TypeFactory = new(EcsComponentTypeFactory);
    return self;
}

method EcsComponentTypeFactory* GetTypeFactory(EcsComponentManager* self)
{
    return self->TypeFactory;
}
/**
 * Removes all components from the entity associated in this manager.
 *
 * @param e
 *			the entity to remove components from
 */
method void RemoveComponentsOfEntity(EcsComponentManager* self, EcsEntity* e)
{
    auto componentBits = GetComponentBits(e);
    for (auto index = NextSetBit(componentBits, 0); index >= 0; NextSetBit(componentBits, index+1)) {
        auto components = Get(self->ComponentsByType, index);
        Put(components, GetId(e), nullptr);
    }
}

/**
 * Adds the component of the given type to the entity.
 * <p>
 * Only one component of given type can be associated with a entity at the
 * same time.
 * </p>
 *
 * @param e
 *			the entity to add to
 * @param type
 *			the type of component being added
 * @param component
 *			the component to add
 */
method void AddComponent(EcsComponentManager* self, EcsEntity* e, EcsComponentType* type, EcsComponent* component)
{
    Array* components = Get(self->ComponentsByType, GetIndex(type));
    if (components == nullptr) {
        components = new(Array, of(EcsComponent));
        Put(self->ComponentsByType, GetIndex(type), components);
    }
    Put(components, GetId(e), component);
    Set(GetComponentBits(e), GetIndex(type), true);
}


/**
 * Removes the component of given type from the entity.
 *
 * @param e
 *			the entity to remove from
 * @param type
 *			the type of component being removed
 */
method void RemoveComponent(EcsComponentManager* self, EcsEntity* e, EcsComponentType* type)
{
    auto index = GetIndex(type);
    Put(self->ComponentsByType, index, nullptr);
    Clear(GetComponentBits(e), GetIndex(type));

}

/**
 * Get all components from all entities for a given type.
 *
 * @param type
 *			the type of components to get
 * @return a bag containing all components of the given type
 */
method Array* GetComponentsByType(EcsComponentManager* self, EcsComponentType* type)
{
    Array* components = Get(self->ComponentsByType, GetIndex(type));
    if(components == nullptr) components = new(Array, of(EcsComponent));
    return components;

}
/**
 * Get a component of an entity.
 *
 * @param e
 *			the entity associated with the component
 * @param type
 *			the type of component to get
 * @return the component of given type
 */
method EcsComponent* GetComponent(EcsComponentManager* self, EcsEntity* e, EcsComponentType* type)
{
    Array* components = Get(self->ComponentsByType, GetIndex(type));
    if (components != nullptr)
        return Get(components, GetId(e));
    return nullptr;
}

/**
 * Get all component associated with an entity.
 *
 * @param e
 *			the entity to get components from
 * @param fillBag
 *			a bag to be filled with components
 * @return the {@code fillBag}, filled with the entities components
 */
method Array* GetComponentsFor(EcsComponentManager* self, EcsEntity* e, Array* fillBag)
{
    auto componentBits = GetComponentBits(e);

    for (auto i = NextSetBit(componentBits, 0); i >= 0; i = NextSetBit(componentBits, i+1)) {
        Array* components = Get(self->ComponentsByType, i);
        Add(components, (Object*)GetId(e));
    }
    return fillBag;
}


method void Deleted(EcsComponentManager* self, EcsEntity* e)
{
    Add(self->Deleted, e);
}

method void Clean(EcsComponentManager* self)
{
    if (self->Deleted->length > 0) {
        for (auto i=0; self->Deleted->length > i; i++) {
            RemoveComponentsOfEntity(self, Get(self->Deleted, i));
        }
        Clear(self->Deleted);
    }   
}

method void Added(EcsComponentManager* self, EcsEntity* entity) { }

method void Changed(EcsComponentManager* self, EcsEntity* entity) { }


method void Disabled(EcsComponentManager* self, EcsEntity* entity) { }

method void Enabled(EcsComponentManager* self, EcsEntity* entity) { }
