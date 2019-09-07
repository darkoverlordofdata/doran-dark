#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


/**
 * A typical entity system. Use this when you need to process entities possessing the
 * provided component types.
 *
 * @author Arni Arent
 *
 */
type (EcsEntityProcessingSystem)
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

delegate (EcsEntityProcessingSystem, New,                 EcsEntityProcessingSystem*, (EcsEntityProcessingSystem*, EcsAspect*));
delegate (EcsEntityProcessingSystem, ToString,            char*,    (const EcsEntityProcessingSystem* const));
delegate (EcsEntityProcessingSystem, Added,               void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Changed,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Deleted,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Disabled,            void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Enabled,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Begin,               void, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, End,                 void, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, Process,             void, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, ProcessEntities,     void, (EcsEntityProcessingSystem*, Array*));
delegate (EcsEntityProcessingSystem, CheckProcessing,      bool, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, Initialize,          void, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, Inserted,            void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Removed,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Check,               void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, RemoveFromSystem,    void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, InsertToSystem,      void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Added,               void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Changed,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Deleted,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Disabled,            void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, Enabled,             void, (EcsEntityProcessingSystem*, EcsEntity*));
delegate (EcsEntityProcessingSystem, SetWorld,            void, (EcsEntityProcessingSystem*, EcsWorld*));
delegate (EcsEntityProcessingSystem, IsPassive,           bool, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, SetPassive,          void, (EcsEntityProcessingSystem*, bool));
delegate (EcsEntityProcessingSystem, GetActive,           Array*, (EcsEntityProcessingSystem*));
delegate (EcsEntityProcessingSystem, ProcessEach, void, (EcsEntityProcessingSystem* self, EcsEntity* e));


/**
 * EcsEntityProcessingSystem Vtable
 */
vtable (EcsEntityProcessingSystem) 
{
    const EcsEntityProcessingSystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsEntityProcessingSystemAdded              Added;
    const EcsEntityProcessingSystemChanged            Changed;
    const EcsEntityProcessingSystemDeleted            Deleted;
    const EcsEntityProcessingSystemDisabled           Disabled;
    const EcsEntityProcessingSystemEnabled            Enabled;
    const EcsEntityProcessingSystemBegin              Begin;
    const EcsEntityProcessingSystemBegin              End;
    const EcsEntityProcessingSystemProcess            Process;
    const EcsEntityProcessingSystemProcessEntities    ProcessEntities;
    const EcsEntityProcessingSystemCheckProcessing     CheckProcessing;
    const EcsEntityProcessingSystemInitialize         Initialize;
    const EcsEntityProcessingSystemInserted           Inserted;
    const EcsEntityProcessingSystemRemoved            Removed;
    const EcsEntityProcessingSystemCheck              Check;
    const EcsEntityProcessingSystemRemoveFromSystem   RemoveFromSystem;
    const EcsEntityProcessingSystemInsertToSystem     InsertToSystem;
    const EcsEntityProcessingSystemSetWorld           SetWorld;
    const EcsEntityProcessingSystemIsPassive          IsPassive;
    const EcsEntityProcessingSystemSetPassive         SetPassive;
    const EcsEntityProcessingSystemGetActive          GetActive;
    const EcsEntityProcessingSystemProcessEach       ProcessEach;
};


static inline vptr(EcsEntityProcessingSystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsEntityProcessingSystem(Class base) 
{
    Class cls = createClass(base, EcsEntityProcessingSystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsEntityProcessingSystem, Added);
    addMethod(cls, EcsEntityProcessingSystem, Changed);
    addMethod(cls, EcsEntityProcessingSystem, Deleted);
    addMethod(cls, EcsEntityProcessingSystem, Disabled);
    addMethod(cls, EcsEntityProcessingSystem, Enabled);
    addMethod(cls, EcsEntityProcessingSystem, Begin);
    addMethod(cls, EcsEntityProcessingSystem, End);
    addMethod(cls, EcsEntityProcessingSystem, Process);
    addMethod(cls, EcsEntityProcessingSystem, ProcessEntities);
    addMethod(cls, EcsEntityProcessingSystem, CheckProcessing);
    addMethod(cls, EcsEntityProcessingSystem, Initialize);
    addMethod(cls, EcsEntityProcessingSystem, Inserted);
    addMethod(cls, EcsEntityProcessingSystem, Removed);
    addMethod(cls, EcsEntityProcessingSystem, Check);
    addMethod(cls, EcsEntityProcessingSystem, RemoveFromSystem);
    addMethod(cls, EcsEntityProcessingSystem, InsertToSystem);
    addMethod(cls, EcsEntityProcessingSystem, SetWorld);
    addMethod(cls, EcsEntityProcessingSystem, IsPassive);
    addMethod(cls, EcsEntityProcessingSystem, SetPassive);
    addMethod(cls, EcsEntityProcessingSystem, GetActive);
    addMethod(cls, EcsEntityProcessingSystem, ProcessEach);
    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsEntityProcessingSystem* New(EcsEntityProcessingSystem* self, EcsAspect* aspect)
{
    self->base = extends(EcsEntitySystem, aspect);
    self->isa = isa(EcsEntityProcessingSystem                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       );
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsEntityProcessingSystem* self) { 
    virtual(EcsEntityProcessingSystem)->Begin(self); 
}

method void Process(EcsEntityProcessingSystem* self)
{   
    Process(self->base);
}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsEntityProcessingSystem* self) { 
    virtual(EcsEntityProcessingSystem)->End(self); 
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsEntityProcessingSystem* self, Array* entities) {
    for (auto i=0; i<entities->length; i++) {
        ProcessEach(self, Get(entities, i));
    } 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsEntityProcessingSystem* self) { 
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsEntityProcessingSystem* self) { 
    virtual(EcsEntityProcessingSystem)->Initialize(self); 
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsEntityProcessingSystem)->Inserted(self, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsEntityProcessingSystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsEntityProcessingSystem* self, EcsEntity* e) { 
    Check(self->base, e);
}

method void RemoveFromSystem(EcsEntityProcessingSystem* self, EcsEntity* e) {
    RemoveFromSystem(self->base, e);
}

method void InsertToSystem(EcsEntityProcessingSystem* self, EcsEntity* e) {
    InsertToSystem(self->base, e);
}

method void Added(EcsEntityProcessingSystem* self, EcsEntity* entity) { }

method void Changed(EcsEntityProcessingSystem* self, EcsEntity* e) {
    Changed(self->base, e);
}

method void Deleted(EcsEntityProcessingSystem* self, EcsEntity* e) {
    Deleted(self->base, e);
}

method void Disabled(EcsEntityProcessingSystem* self, EcsEntity* e) {
    Disabled(self->base, e);
}

method void Enabled(EcsEntityProcessingSystem* self, EcsEntity* e) {
    Enabled(self->base, e);
}

method void SetWorld(EcsEntityProcessingSystem* self, EcsWorld* world) {
    SetWorld(self->base, world);
}

method bool IsPassive(EcsEntityProcessingSystem* self) {
    return IsPassive(self->base);
}

method void SetPassive(EcsEntityProcessingSystem* self, bool passive) {
    SetPassive(self->base, passive);
}

method Array* GetActive(EcsEntityProcessingSystem* self) {
    return GetActive(self->base);
}

/**
 * Process a entity this system is interested in.
 * @param e the entity to process.
 */
method void ProcessEach(EcsEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsEntityProcessingSystem)->Begin(self); 
}

