#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>

/**
 * The primary instance for the framework. It contains all the managers.
 * 
 * You must use this to create, delete and retrieve entities.
 * 
 * It is also important to set the delta each game loop iteration, and initialize before game loop.
 * 
 * @author Arni Arent
 * 
 */
type (EcsWorld)
{
    Class isa;
    Object* base;
    EcsEntityManager* Em;
    EcsComponentManager* Cm;
    float Delta;
    Array* Added;
    Array* Changed;
    Array* Deleted;
    Array* Enable;
    Array* Disable;
    Map* Managers;
    Array* ManagersBag;
    Map* Systems;
    Array* SystemsBag;
    // Map* EcsEntityTemplates;
};

typedef void (*EcsPerformer)(EcsEntityObserver* observer, EcsEntity* e);

method EcsWorld* New(EcsWorld* self);
method void Initialize(EcsWorld* self);
method EcsEntityManager* GetEntityManager(EcsWorld* self);
method EcsComponentManager* GetComponentManager(EcsWorld* self);
method EcsManager* SetManager(EcsWorld* self, EcsManager* manager);
method EcsManager* GetManager(EcsWorld* self, Class type);
method void DeleteManager(EcsWorld* self, EcsManager* manager);
method float GetDelta(EcsWorld* self);
method void SetDelta(EcsWorld* self, float delta);
method void AddEntity(EcsWorld* self, EcsEntity* e);
method void ChangedEntity(EcsWorld* self, EcsEntity* e);
method void DeleteEntity(EcsWorld* self, EcsEntity* e);
method void Enable(EcsWorld* self, EcsEntity* e);
method void Disable(EcsWorld* self, EcsEntity* e);
method EcsEntity* CreateEntity(EcsWorld* self, char* name);
method EcsEntity* GetEntity(EcsWorld* self, int entityId);
method Array* GetSystems(EcsWorld* self);
method EcsEntitySystem* SetSystem(EcsWorld* self, EcsEntitySystem* system, bool passive);
method void DeleteSystem(EcsWorld* self, EcsEntitySystem* system);
method void NotifySystems(EcsWorld* self, EcsPerformer perform, EcsEntity* e);
method void NotifyManagers(EcsWorld* self, EcsPerformer perform, EcsEntity* e); 
method EcsEntitySystem* GetSystem(EcsWorld* self, Class type);
method void Check(EcsWorld* self, Array* entities, EcsPerformer perform);
method void Update(EcsWorld* self);
method void Draw(EcsWorld* self);

delegate (EcsWorld, New, EcsWorld*, (EcsWorld* self));
delegate (EcsWorld, Initialize, void, (EcsWorld* self));
delegate (EcsWorld, GetEntityManager, EcsEntityManager*, (EcsWorld* self));
delegate (EcsWorld, GetComponentManager, EcsComponentManager*, (EcsWorld* self));
delegate (EcsWorld, SetManager, EcsManager*, (EcsWorld* self, EcsManager* manager));
delegate (EcsWorld, GetManager, EcsManager*, (EcsWorld* self, Class type));
delegate (EcsWorld, DeleteManager, void, (EcsWorld* self, EcsManager* manager));
delegate (EcsWorld, GetDelta, float, (EcsWorld* self));
delegate (EcsWorld, SetDelta, void, (EcsWorld* self, float delta));
delegate (EcsWorld, AddEntity, void, (EcsWorld* self, EcsEntity* e));
delegate (EcsWorld, ChangedEntity, void, (EcsWorld* self, EcsEntity* e));
delegate (EcsWorld, DeleteEntity, void, (EcsWorld* self, EcsEntity* e));
delegate (EcsWorld, Enable, void, (EcsWorld* self, EcsEntity* e));
delegate (EcsWorld, Disable, void, (EcsWorld* self, EcsEntity* e));
delegate (EcsWorld, CreateEntity, EcsEntity*, (EcsWorld* self, char* name));
delegate (EcsWorld, GetEntity, EcsEntity*, (EcsWorld* self, int entityId));
delegate (EcsWorld, GetSystems, Array*, (EcsWorld* self));
delegate (EcsWorld, SetSystem, EcsEntitySystem*, (EcsWorld* self, EcsEntitySystem* system, bool passive));
delegate (EcsWorld, DeleteSystem, void, (EcsWorld* self, EcsEntitySystem* system));
delegate (EcsWorld, NotifySystems, void, (EcsWorld* self, EcsPerformer perform, EcsEntity* e));
delegate (EcsWorld, NotifyManagers, void, (EcsWorld* self, EcsPerformer perform, EcsEntity* e)); 
delegate (EcsWorld, GetSystem, EcsEntitySystem*, (EcsWorld* self, Class type));
delegate (EcsWorld, Check, void, (EcsWorld* self, Array* entities, EcsPerformer perform));
delegate (EcsWorld, Update, void, (EcsWorld* self));
delegate (EcsWorld, Draw, void, (EcsWorld* self));
/**
 * EcsWorld Vtable
 */
vtable (EcsWorld) 
{
    const ObjectToString            ToString;
    const ObjectEquals              Equals;
    const ObjectGetHashCode         GetHashCode;
    const ObjectDispose             Dispose;
    const EcsWorldInitialize        Initialize;
    const EcsWorldGetEntityManager  GetEntityManager;
    const EcsWorldGetComponentManager       GetComponentManager;
    const EcsWorldSetManager        SetManager;
    const EcsWorldGetManager        GetManager;
    const EcsWorldDeleteManager     DeleteManager;
    const EcsWorldGetDelta          GetDelta;
    const EcsWorldSetDelta          SetDelta;
    const EcsWorldAddEntity         AddEntity;
    const EcsWorldChangedEntity     ChangedEntity;
    const EcsWorldDeleteEntity      DeleteEntity;
    const EcsWorldEnable            Enable;
    const EcsWorldDisable           Disable;
    const EcsWorldCreateEntity      CreateEntity;
    const EcsWorldGetEntity         GetEntity;
    const EcsWorldGetSystems        GetSystems;
    const EcsWorldSetSystem         SetSystem;
    const EcsWorldDeleteSystem      DeleteSystem;
    const EcsWorldNotifySystems     NotifySystems;
    const EcsWorldNotifyManagers    NotifyManagers; 
    const EcsWorldGetSystem         GetSystem;
    const EcsWorldCheck             Check;
    const EcsWorldUpdate            Update;
    const EcsWorldDraw              Draw;
};

static inline vptr(EcsWorld);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsWorld(Class base) 
{
    Class cls = createClass(base, EcsWorld);
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, EcsWorld, Initialize);
    addMethod(cls, EcsWorld, GetEntityManager);
    addMethod(cls, EcsWorld, GetComponentManager);
    addMethod(cls, EcsWorld, SetManager);
    addMethod(cls, EcsWorld, GetManager);
    addMethod(cls, EcsWorld, DeleteManager);
    addMethod(cls, EcsWorld, GetDelta);
    addMethod(cls, EcsWorld, SetDelta);
    addMethod(cls, EcsWorld, AddEntity);
    addMethod(cls, EcsWorld, ChangedEntity);
    addMethod(cls, EcsWorld, DeleteEntity);
    addMethod(cls, EcsWorld, Enable);
    addMethod(cls, EcsWorld, Disable);
    addMethod(cls, EcsWorld, CreateEntity);
    addMethod(cls, EcsWorld, GetEntity);
    addMethod(cls, EcsWorld, GetSystems);
    addMethod(cls, EcsWorld, SetSystem);
    addMethod(cls, EcsWorld, DeleteSystem);
    addMethod(cls, EcsWorld, NotifySystems);
    addMethod(cls, EcsWorld, NotifyManagers); 
    addMethod(cls, EcsWorld, GetSystem);
    addMethod(cls, EcsWorld, Check);
    addMethod(cls, EcsWorld, Update);
    addMethod(cls, EcsWorld, Draw);
    return cls; 
}


method EcsWorld* New(EcsWorld* self)
{
    self->base = extends(Object);
    self->isa = isa(EcsWorld);
    self->Managers = new(Map, of(EcsManager));
    self->ManagersBag = new(Array, of(Manage));
    
    self->Systems = new(Map, of(EcsEntitySystem));
    self->SystemsBag = new(Array, of(EntitySystem));

    self->Added = new(Array, of(EcsEntity));
    self->Changed = new(Array, of(EcsEntity));
    self->Deleted = new(Array, of(EcsEntity));
    self->Enable = new(Array, of(EcsEntity));
    self->Disable = new(Array, of(EcsEntity));

    self->Cm = new(EcsComponentManager);
    assert(self != nullptr);
    assert(self->Cm != nullptr);
    SetManager(self, self->Cm);
    
    self->Em = new(EcsEntityManager);
    SetManager(self, self->Em);
    return self;

}

/**
 * Makes sure all managers systems are initialized in the order they were added.
 */
method void Initialize(EcsWorld* self) 
{
    for (auto i=0; i<self->ManagersBag->length; i++)
        Initialize((EcsManager*)Get(self->ManagersBag, i));

    /** 
     * annotaions.EntityTemplate 
     * 
     * Collect the entity templates
     */
    // self->EntityTemplates = new(Map, of(EcsEntityTemplate));
    // if (EntityTemplate.entityTemplates.Keys != null)
    // {
    //     foreach (var entityName in EntityTemplate.entityTemplates.Keys) 
    //     {
    //         var Template = (Type)EntityTemplate.entityTemplates[entityName];
    //         SetEntityTemplate(entityName, (EntityTemplate)GLib.Object.new(Template));
    //     }
    // }
    /** 
     * annotations.Mapper 
     *
     * Collect the component mappers
     */
    // foreach (var system in systemsBag)
    // {
    //     /** Inject the component mappers into each system */
    //     ComponentMapperInitHelper.Config(system, this);
    //     system.Initialize();
    // }
}


/**
 * Returns a manager that takes care of all the entities in the world.
 * entities of this world.
 * 
 * @return entity manager.
 */
method EcsEntityManager* GetEntityManager(EcsWorld* self) 
{
    return self->Em;
}

/**
 * Returns a manager that takes care of all the components in the world.
 * 
 * @return component manager.
 */
method EcsComponentManager* GetComponentManager(EcsWorld* self) 
{
    return self->Cm;
}

/**
 * Add a manager into this world. It can be retrieved later.
 * World will notify this manager of changes to entity.
 * 
 * @param manager to be added
 */
method EcsManager* SetManager(EcsWorld* self, EcsManager* manager) 
{
    Put(self->Managers, manager->isa->name, manager);
    Add(self->ManagersBag, manager);
    SetWorld(manager, self);
    return manager;
}

/**
 * Returns a manager of the specified type.
* 
* @param <T>
* @param managerType
*            class type of the manager
* @return the manager
*/
method EcsManager* GetManager(EcsWorld* self, Class type) 
{
    return Get(self->Managers, type->name);
}

/**
 * Deletes the manager from this world.
 * @param manager to delete.
 */
method void DeleteManager(EcsWorld* self, EcsManager* manager) 
{
    Remove(self->Managers, manager->isa->name);
    Remove(self->ManagersBag, manager);
}

/**
 * Time since last game loop.
* 
* @return delta time since last game loop.
*/
method float GetDelta(EcsWorld* self) 
{
    return self->Delta;
}

/**
 * You must specify the delta for the game here.
* 
* @param delta time since last game loop.
*/
method void SetDelta(EcsWorld* self, float delta) 
{
    self->Delta = delta;
}

/**
 * Adds a entity to this world.
* 
* @param e entity
*/
method void AddEntity(EcsWorld* self, EcsEntity* e) 
{
    Add(self->Added, e);
}

/**
 * Ensure all systems are notified of changes to this entity.
* If you're adding a component to an entity after it's been
* added to the world, then you need to invoke this method.
* 
* @param e entity
*/
method void ChangedEntity(EcsWorld* self, EcsEntity* e) 
{
    Add(self->Changed, e);
}

/**
 * Delete the entity from the world.
* 
* @param e entity
*/
method void DeleteEntity(EcsWorld* self, EcsEntity* e) 
{
    if (!Contains(self->Deleted, e)) 
    {
        Add(self->Deleted, e);
    }
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
* Won't do anything unless it was already disabled.
*/
method void Enable(EcsWorld* self, EcsEntity* e) 
{
    Add(self->Enable, e);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
* continue to exist but won't get processed.
*/
method void Disable(EcsWorld* self, EcsEntity* e) 
{
    Add(self->Disable, e);
}


/**
 * Create and return a new or reused entity instance.
* Will NOT add the entity to the world, use World.addEntity(Entity) for that.
*
* @param name optional name for debugging
* @return entity
*/
method EcsEntity* CreateEntity(EcsWorld* self, char* name) 
{
    return CreateEntityInstance(self->Em, name);
}

/**
 * Get a entity having the specified id.
* 
* @param entityId
* @return entity
*/
method EcsEntity* GetEntity(EcsWorld* self, int entityId) 
{
    return GetEntity(self->Em, entityId);
}

/**
 * Gives you all the systems in this world for possible iteration.
* 
* @return all entity systems in world.
*/
method Array* GetSystems(EcsWorld* self) 
{
    return self->SystemsBag;
}

/**
 * Will add a system to this world.
*  
* @param system the system to add.
* @param passive wether or not this system will be processed by World.process()
* @return the added system.
*/
method EcsEntitySystem* SetSystem(EcsWorld* self, EcsEntitySystem* system, bool passive) 
{
    SetWorld(system, self);
    SetPassive(system, passive);
    
    Put(self->Systems, system->isa->name, system);
    Add(self->SystemsBag, system);
    
    return system;
}
method EcsEntitySystem* SetSystem(EcsWorld* self, EcsEntitySystem* system) 
{
    return SetSystem(self, system, false);
}
/**
 * Removed the specified system from the world.
* @param system to be deleted from world.
*/
method void DeleteSystem(EcsWorld* self, EcsEntitySystem* system) 
{
    Remove(self->Systems, system->isa->name);
    Remove(self->SystemsBag, system);
}

method void NotifySystems(EcsWorld* self, EcsPerformer perform, EcsEntity* e) 
{
    for (auto i=0; i<self->SystemsBag->length; i++) {
        auto system = Get(self->SystemsBag, i);
        perform(system, e);
    }
}

method void NotifyManagers(EcsWorld* self, EcsPerformer perform, EcsEntity* e) 
{
    for (auto i=0; i<self->ManagersBag->length; i++) {
        auto manager = Get(self->ManagersBag, i);
        perform(manager, e);

    }
}

/**
 * Retrieve a system for specified system type.
* 
* @param type type of system.
* @return instance of the system in this world.
*/
method EcsEntitySystem* GetSystem(EcsWorld* self, Class type) 
{
    return Get(self->Systems, type->name);
}

/**
 * Performs an action on each entity.
* @param entities
* @param performer
*/
method void Check(EcsWorld* self, Array* entities, EcsPerformer perform) 
{
    if (!IsEmpty(entities)) 
    {
        for (auto i=0; i<entities->length; i++)
        {
            auto e = Get(entities, i);
            NotifyManagers(self, perform, e);
            NotifySystems(self, perform, e);
        }
        Clear(entities);
    }
}

/**
 * Process all non-passive systems.
*/
method void Update(EcsWorld* self) 
{
    Check(self, self->Added,   Added);
    Check(self, self->Changed, Changed);
    Check(self, self->Disable, Disabled);
    Check(self, self->Enable,  Enabled);
    Check(self, self->Deleted, Deleted);
    
    Clean(self->Cm);

    for (auto i = 0; i<self->SystemsBag->length; i++)
    {
        auto system = Get(self->SystemsBag, i);
        if (!IsPassive(system)) {
            Process(system);
        }
    }
}

method void Draw(EcsWorld* self)
{
    for (auto i = 0; i<self->SystemsBag->length; i++)
    {
        auto system = Get(self->SystemsBag, i);
        if (IsPassive(system)) {
            Process(system);
        }
    }
}
/**
 * Retrieves a ComponentMapper instance for fast retrieval of components from entities.
* 
* @param type of component to get mapper for.
* @return mapper for specified component type.
*/
// method ComponentMapper<T> GetMapper<T>(Type type) 
// method ComponentMapper<T> GetMapper<T>(EcsWorld* self) 
// {
//     return ComponentMapper.GetFor<T>(typeof(T), this);
// }


/**
 * Set an Entity Template
 *
 * @param entityTag
 * @param entityTemplate
 */
// method void SetEntityTemplate(EcsWorld* self, char* entityTag, EntityTemplate entityTemplate) 
// {
//     entityTemplates[entityTag] = entityTemplate;
// }
/**
 * Creates a entity from template.
 *
 * @param name
 * @param args
 * @returns {Entity}
 * EntityTemplate
 */
// method Entity CreateEntityFromTemplate(EcsWorld* self, string name, ...) 
// {
//     var list = va_list();
//     return entityTemplates[name].BuildEntity(CreateEntity(name), this, list);
// }
