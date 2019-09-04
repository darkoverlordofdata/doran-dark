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
    EcsEntityManager Em;
    EcsComponentManager Cm;
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

method EcsWorld* New(EcsWorld* self)
{
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
    SetManager(self, Cm);
    
    self->Em = new(EcsEntityManager);
    SetManager(self, Em);

}

/**
 * Makes sure all managers systems are initialized in the order they were added.
 */
method void Initialize(EcsWorld* self) 
{
    for (auto i=0; i<self->Managers->Length, i++)
        Initialize(Get(self->Managers, i));

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
method EcsComponentManager GetComponentManager(EcsWorld* self) 
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
    return Get(self->managers, type->name);
}

/**
 * Deletes the manager from this world.
 * @param manager to delete.
 */
method void DeleteManager(EcsWorld* self, EcsManager manager) 
{
    Remove(managers, manager->isa->name);
    Remove(managersBag, manager);
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
method Entity CreateEntity(EcsWorld* self, char* name) 
{
    return CreateEntityInstance(self->Em, name);
}

/**
 * Get a entity having the specified id.
* 
* @param entityId
* @return entity
*/
method Entity GetEntity(EcsWorld* self, int entityId) 
{
    return GetEntity(self->Em, entityId);
}

/**
 * Gives you all the systems in this world for possible iteration.
* 
* @return all entity systems in world.
*/
method Array* GetSystems(EcsWorld* self, ) 
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
method EcsSystem* SetSystem(EcsWorld* self, EcsEntitySystem system, bool passive) 
{
    SetWorld(self->System, self);
    SetPassive(self->System, passive);
    
    Get(self->System, system->isa->name, system);
    Add(self->SystemsBag, system);
    
    return system;
}
method EcsSystem* SetSystem(EcsWorld* self, EcsEntitySystem system) 
{
    SetSystem(self, system, false);
}