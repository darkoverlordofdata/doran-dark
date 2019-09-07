#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


// method bool CheckProcessing(EcsIntervalEntityProcessingSystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
type (EcsIntervalEntityProcessingSystem)
{
    Class isa;
    EcsIntervalEntitySystem* base;
    EcsWorld* World;
    int SystemIndex;
    Array* Actives;
    EcsAspect* Aspect;
    BitSet* AllSet;
    BitSet* ExclusionSet;
    BitSet* OneSet;
    bool Passive;
    bool IsDummy;

    float Acc;
    float Interval;

};

delegate (EcsIntervalEntityProcessingSystem, New,                 EcsIntervalEntityProcessingSystem*, (EcsIntervalEntityProcessingSystem*, EcsAspect*, float));
delegate (EcsIntervalEntityProcessingSystem, ToString,            char*,    (const EcsIntervalEntityProcessingSystem* const));
delegate (EcsIntervalEntityProcessingSystem, Added,               void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Changed,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Deleted,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Disabled,            void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Enabled,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Begin,               void, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, End,                 void, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, Process,             void, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, ProcessEntities,     void, (EcsIntervalEntityProcessingSystem*, Array*));
delegate (EcsIntervalEntityProcessingSystem, CheckProcessing,     bool, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, Initialize,          void, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, Inserted,            void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Removed,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Check,               void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, RemoveFromSystem,    void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, InsertToSystem,      void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Added,               void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Changed,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Deleted,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Disabled,            void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, Enabled,             void, (EcsIntervalEntityProcessingSystem*, EcsEntity*));
delegate (EcsIntervalEntityProcessingSystem, SetWorld,            void, (EcsIntervalEntityProcessingSystem*, EcsWorld*));
delegate (EcsIntervalEntityProcessingSystem, IsPassive,           bool, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, SetPassive,          void, (EcsIntervalEntityProcessingSystem*, bool));
delegate (EcsIntervalEntityProcessingSystem, GetActive,           Array*, (EcsIntervalEntityProcessingSystem*));
delegate (EcsIntervalEntityProcessingSystem, ProcessEach, void, (EcsIntervalEntityProcessingSystem* self, EcsEntity* e));


/**
 * EcsIntervalEntityProcessingSystem Vtable
 */
vtable (EcsIntervalEntityProcessingSystem) 
{
    const EcsIntervalEntityProcessingSystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsIntervalEntityProcessingSystemAdded              Added;
    const EcsIntervalEntityProcessingSystemChanged            Changed;
    const EcsIntervalEntityProcessingSystemDeleted            Deleted;
    const EcsIntervalEntityProcessingSystemDisabled           Disabled;
    const EcsIntervalEntityProcessingSystemEnabled            Enabled;
    const EcsIntervalEntityProcessingSystemBegin              Begin;
    const EcsIntervalEntityProcessingSystemBegin              End;
    const EcsIntervalEntityProcessingSystemProcess            Process;
    const EcsIntervalEntityProcessingSystemProcessEntities    ProcessEntities;
    const EcsIntervalEntityProcessingSystemCheckProcessing     CheckProcessing;
    const EcsIntervalEntityProcessingSystemInitialize         Initialize;
    const EcsIntervalEntityProcessingSystemInserted           Inserted;
    const EcsIntervalEntityProcessingSystemRemoved            Removed;
    const EcsIntervalEntityProcessingSystemCheck              Check;
    const EcsIntervalEntityProcessingSystemRemoveFromSystem   RemoveFromSystem;
    const EcsIntervalEntityProcessingSystemInsertToSystem     InsertToSystem;
    const EcsIntervalEntityProcessingSystemSetWorld           SetWorld;
    const EcsIntervalEntityProcessingSystemIsPassive          IsPassive;
    const EcsIntervalEntityProcessingSystemSetPassive         SetPassive;
    const EcsIntervalEntityProcessingSystemGetActive          GetActive;
    const EcsIntervalEntityProcessingSystemProcessEach       ProcessEach;
};


static inline vptr(EcsIntervalEntityProcessingSystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsIntervalEntityProcessingSystem(Class base) 
{
    Class cls = createClass(base, EcsIntervalEntityProcessingSystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Added);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Changed);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Deleted);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Disabled);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Enabled);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Begin);
    addMethod(cls, EcsIntervalEntityProcessingSystem, End);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Process);
    addMethod(cls, EcsIntervalEntityProcessingSystem, ProcessEntities);
    addMethod(cls, EcsIntervalEntityProcessingSystem, CheckProcessing);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Initialize);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Inserted);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Removed);
    addMethod(cls, EcsIntervalEntityProcessingSystem, Check);
    addMethod(cls, EcsIntervalEntityProcessingSystem, RemoveFromSystem);
    addMethod(cls, EcsIntervalEntityProcessingSystem, InsertToSystem);
    addMethod(cls, EcsIntervalEntityProcessingSystem, SetWorld);
    addMethod(cls, EcsIntervalEntityProcessingSystem, IsPassive);
    addMethod(cls, EcsIntervalEntityProcessingSystem, SetPassive);
    addMethod(cls, EcsIntervalEntityProcessingSystem, GetActive);
    addMethod(cls, EcsIntervalEntityProcessingSystem, ProcessEach);
    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsIntervalEntityProcessingSystem* New(EcsIntervalEntityProcessingSystem* self, EcsAspect* aspect, float interval)
{
    self->base = extends(EcsIntervalEntitySystem, aspect, interval);
    self->isa = isa(EcsIntervalEntityProcessingSystem);
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsIntervalEntityProcessingSystem* self) { virtual(EcsIntervalEntityProcessingSystem)->Begin(self); }

method void Process(EcsIntervalEntityProcessingSystem* self)
{   
    Process(self->base);
}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsIntervalEntityProcessingSystem* self) { virtual(EcsIntervalEntityProcessingSystem)->End(self); }

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsIntervalEntityProcessingSystem* self, Array* entities) { 
    for (auto i=0; i<entities->length; i++) {
        ProcessEach(self, Get(entities, i));
    } 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsIntervalEntityProcessingSystem* self) { 
    if ((self->Acc += GetDelta(self->World)) >= self->Interval) {
        self->Acc -= self->Interval;
        return true;
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsIntervalEntityProcessingSystem* self) { virtual(EcsIntervalEntityProcessingSystem)->Initialize(self); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsIntervalEntityProcessingSystem)->Inserted(self, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsIntervalEntityProcessingSystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) { 
    Check(self->base, e);
}

method void RemoveFromSystem(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) 
{
    RemoveFromSystem(self->base, e);
}

method void InsertToSystem(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) 
{
    InsertToSystem(self->base, e);
}

method void Added(EcsIntervalEntityProcessingSystem* self, EcsEntity* entity) { }

method void Changed(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) {
    Check(self, e);
}

method void Deleted(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) {
    Deleted(self->base, e);
}

method void Disabled(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) {
    Disabled(self->base, e);
}

method void Enabled(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) {
    Enabled(self->base, e);
}

method void SetWorld(EcsIntervalEntityProcessingSystem* self, EcsWorld* world) {
    SetWorld(self->base, world);
}

method bool IsPassive(EcsIntervalEntityProcessingSystem* self) {
    return IsPassive(self->base);
}

method void SetPassive(EcsIntervalEntityProcessingSystem* self, bool passive) {
    SetPassive(self->base, passive);
}

method Array* GetActive(EcsIntervalEntityProcessingSystem* self) {
    return GetActive(self);
}

/**
 * Process a entity this system is interested in.
 * @param e the entity to process.
 */
method void ProcessEach(EcsIntervalEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsIntervalEntityProcessingSystem)->ProcessEach(self, e); 
}

