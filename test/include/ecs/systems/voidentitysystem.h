#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


// method bool CheckProcessing(EcsVoidEntitySystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
type (EcsVoidEntitySystem)
{
    Class isa;
    EcsEntitySystem* base;
    EcsWorld* World;
    int SystemIndex;
    Array* Actives;
    EcsAspect* Aspect;
    BitSet* AllSet;
    BitSet* ExclusionSet;
    BitSet* OneSet;
    bool Passive;
    bool IsDummy;


};

delegate (EcsVoidEntitySystem, New,                 EcsVoidEntitySystem*, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, ToString,            char*,    (const EcsVoidEntitySystem* const));
delegate (EcsVoidEntitySystem, Added,               void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Changed,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Deleted,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Disabled,            void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Enabled,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Begin,               void, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, End,                 void, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, Process,             void, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, ProcessEntities,     void, (EcsVoidEntitySystem*, Array*));
delegate (EcsVoidEntitySystem, CheckProcessing,      bool, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, Initialize,          void, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, Inserted,            void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Removed,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Check,               void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, RemoveFromSystem,    void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, InsertToSystem,      void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Added,               void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Changed,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Deleted,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Disabled,            void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, Enabled,             void, (EcsVoidEntitySystem*, EcsEntity*));
delegate (EcsVoidEntitySystem, SetWorld,            void, (EcsVoidEntitySystem*, EcsWorld*));
delegate (EcsVoidEntitySystem, IsPassive,           bool, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, SetPassive,          void, (EcsVoidEntitySystem*, bool));
delegate (EcsVoidEntitySystem, GetActive,           Array*, (EcsVoidEntitySystem*));
delegate (EcsVoidEntitySystem, ProcessSystem, void, (EcsVoidEntitySystem* self));


/**
 * EcsVoidEntitySystem Vtable
 */
vtable (EcsVoidEntitySystem) 
{
    const EcsVoidEntitySystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsVoidEntitySystemAdded              Added;
    const EcsVoidEntitySystemChanged            Changed;
    const EcsVoidEntitySystemDeleted            Deleted;
    const EcsVoidEntitySystemDisabled           Disabled;
    const EcsVoidEntitySystemEnabled            Enabled;
    const EcsVoidEntitySystemBegin              Begin;
    const EcsVoidEntitySystemBegin              End;
    const EcsVoidEntitySystemProcess            Process;
    const EcsVoidEntitySystemProcessEntities    ProcessEntities;
    const EcsVoidEntitySystemCheckProcessing     CheckProcessing;
    const EcsVoidEntitySystemInitialize         Initialize;
    const EcsVoidEntitySystemInserted           Inserted;
    const EcsVoidEntitySystemRemoved            Removed;
    const EcsVoidEntitySystemCheck              Check;
    const EcsVoidEntitySystemRemoveFromSystem   RemoveFromSystem;
    const EcsVoidEntitySystemInsertToSystem     InsertToSystem;
    const EcsVoidEntitySystemSetWorld           SetWorld;
    const EcsVoidEntitySystemIsPassive          IsPassive;
    const EcsVoidEntitySystemSetPassive         SetPassive;
    const EcsVoidEntitySystemGetActive          GetActive;
    const EcsVoidEntitySystemProcessSystem       ProcessSystem;

};


static inline vptr(EcsVoidEntitySystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsVoidEntitySystem(Class base) 
{
    Class cls = createClass(base, EcsVoidEntitySystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsVoidEntitySystem, Added);
    addMethod(cls, EcsVoidEntitySystem, Changed);
    addMethod(cls, EcsVoidEntitySystem, Deleted);
    addMethod(cls, EcsVoidEntitySystem, Disabled);
    addMethod(cls, EcsVoidEntitySystem, Enabled);
    addMethod(cls, EcsVoidEntitySystem, Begin);
    addMethod(cls, EcsVoidEntitySystem, End);
    addMethod(cls, EcsVoidEntitySystem, Process);
    addMethod(cls, EcsVoidEntitySystem, ProcessEntities);
    addMethod(cls, EcsVoidEntitySystem, CheckProcessing);
    addMethod(cls, EcsVoidEntitySystem, Initialize);
    addMethod(cls, EcsVoidEntitySystem, Inserted);
    addMethod(cls, EcsVoidEntitySystem, Removed);
    addMethod(cls, EcsVoidEntitySystem, Check);
    addMethod(cls, EcsVoidEntitySystem, RemoveFromSystem);
    addMethod(cls, EcsVoidEntitySystem, InsertToSystem);
    addMethod(cls, EcsVoidEntitySystem, SetWorld);
    addMethod(cls, EcsVoidEntitySystem, IsPassive);
    addMethod(cls, EcsVoidEntitySystem, SetPassive);
    addMethod(cls, EcsVoidEntitySystem, GetActive);
    addMethod(cls, EcsVoidEntitySystem, ProcessSystem);

    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsVoidEntitySystem* New(EcsVoidEntitySystem* self)
{
    self->base = extends(EcsEntitySystem, GetAspectForNone());
    self->isa = isa(EcsVoidEntitySystem);
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsVoidEntitySystem* self) { virtual(EcsVoidEntitySystem)->Begin(self); }

method void Process(EcsVoidEntitySystem* self)
{   
    Process(self->base);
}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsVoidEntitySystem* self) { virtual(EcsVoidEntitySystem)->End(self); }

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsVoidEntitySystem* self, Array* entities) { 
    ProcessSystem(self);
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsVoidEntitySystem* self) { 
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsVoidEntitySystem* self) { virtual(EcsVoidEntitySystem)->Initialize(self); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsVoidEntitySystem* self, EcsEntity* e) { 
    virtual(EcsVoidEntitySystem)->Inserted(self, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsVoidEntitySystem* self, EcsEntity* e) { 
    virtual(EcsVoidEntitySystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsVoidEntitySystem* self, EcsEntity* e) { 
    Check(self->base, e);
}

method void RemoveFromSystem(EcsVoidEntitySystem* self, EcsEntity* e) 
{
    RemoveFromSystem(self->base, e);
}

method void InsertToSystem(EcsVoidEntitySystem* self, EcsEntity* e) 
{
    InsertToSystem(self->base, e);
}

method void Added(EcsVoidEntitySystem* self, EcsEntity* entity) { }

method void Changed(EcsVoidEntitySystem* self, EcsEntity* e) {
    Check(self, e);
}

method void Deleted(EcsVoidEntitySystem* self, EcsEntity* e) {
    Deleted(self->base, e);
}

method void Disabled(EcsVoidEntitySystem* self, EcsEntity* e) {
    Disabled(self->base, e);
}

method void Enabled(EcsVoidEntitySystem* self, EcsEntity* e) {
    Enabled(self->base, e);
}

method void SetWorld(EcsVoidEntitySystem* self, EcsWorld* world) {
    SetWorld(self->base, world);
}

method bool IsPassive(EcsVoidEntitySystem* self) {
    return IsPassive(self->base);
}

method void SetPassive(EcsVoidEntitySystem* self, bool passive) {
    SetPassive(self->base, passive);
}

method Array* GetActive(EcsVoidEntitySystem* self) {
    return GetActive(self);
}

method void ProcessSystem(EcsVoidEntitySystem* self) { 
    virtual(EcsVoidEntitySystem)->ProcessSystem(self); 
    
}
