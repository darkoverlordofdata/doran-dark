#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


// method bool CheckProcessing(EcsIntervalEntitySystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
type (EcsIntervalEntitySystem)
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

    float Acc;
    float Interval;

};

delegate (EcsIntervalEntitySystem, New,                 EcsIntervalEntitySystem*, (EcsIntervalEntitySystem*, EcsAspect*, float));
delegate (EcsIntervalEntitySystem, ToString,            char*,    (const EcsIntervalEntitySystem* const));
delegate (EcsIntervalEntitySystem, Added,               void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Changed,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Deleted,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Disabled,            void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Enabled,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Begin,               void, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, End,                 void, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, Process,             void, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, ProcessEntities,     void, (EcsIntervalEntitySystem*, Array*));
delegate (EcsIntervalEntitySystem, CheckProcessing,      bool, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, Initialize,          void, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, Inserted,            void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Removed,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Check,               void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, RemoveFromSystem,    void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, InsertToSystem,      void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Added,               void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Changed,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Deleted,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Disabled,            void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, Enabled,             void, (EcsIntervalEntitySystem*, EcsEntity*));
delegate (EcsIntervalEntitySystem, SetWorld,            void, (EcsIntervalEntitySystem*, EcsWorld*));
delegate (EcsIntervalEntitySystem, IsPassive,           bool, (EcsIntervalEntitySystem*));
delegate (EcsIntervalEntitySystem, SetPassive,          void, (EcsIntervalEntitySystem*, bool));
delegate (EcsIntervalEntitySystem, GetActive,           Array*, (EcsIntervalEntitySystem*));


/**
 * EcsIntervalEntitySystem Vtable
 */
vtable (EcsIntervalEntitySystem) 
{
    const EcsIntervalEntitySystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsIntervalEntitySystemAdded              Added;
    const EcsIntervalEntitySystemChanged            Changed;
    const EcsIntervalEntitySystemDeleted            Deleted;
    const EcsIntervalEntitySystemDisabled           Disabled;
    const EcsIntervalEntitySystemEnabled            Enabled;
    const EcsIntervalEntitySystemBegin              Begin;
    const EcsIntervalEntitySystemBegin              End;
    const EcsIntervalEntitySystemProcess            Process;
    const EcsIntervalEntitySystemProcessEntities    ProcessEntities;
    const EcsIntervalEntitySystemCheckProcessing     CheckProcessing;
    const EcsIntervalEntitySystemInitialize         Initialize;
    const EcsIntervalEntitySystemInserted           Inserted;
    const EcsIntervalEntitySystemRemoved            Removed;
    const EcsIntervalEntitySystemCheck              Check;
    const EcsIntervalEntitySystemRemoveFromSystem   RemoveFromSystem;
    const EcsIntervalEntitySystemInsertToSystem     InsertToSystem;
    const EcsIntervalEntitySystemSetWorld           SetWorld;
    const EcsIntervalEntitySystemIsPassive          IsPassive;
    const EcsIntervalEntitySystemSetPassive         SetPassive;
    const EcsIntervalEntitySystemGetActive          GetActive;
};


static inline vptr(EcsIntervalEntitySystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsIntervalEntitySystem(Class base) 
{
    Class cls = createClass(base, EcsIntervalEntitySystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsIntervalEntitySystem, Added);
    addMethod(cls, EcsIntervalEntitySystem, Changed);
    addMethod(cls, EcsIntervalEntitySystem, Deleted);
    addMethod(cls, EcsIntervalEntitySystem, Disabled);
    addMethod(cls, EcsIntervalEntitySystem, Enabled);
    addMethod(cls, EcsIntervalEntitySystem, Begin);
    addMethod(cls, EcsIntervalEntitySystem, End);
    addMethod(cls, EcsIntervalEntitySystem, Process);
    addMethod(cls, EcsIntervalEntitySystem, ProcessEntities);
    addMethod(cls, EcsIntervalEntitySystem, CheckProcessing);
    addMethod(cls, EcsIntervalEntitySystem, Initialize);
    addMethod(cls, EcsIntervalEntitySystem, Inserted);
    addMethod(cls, EcsIntervalEntitySystem, Removed);
    addMethod(cls, EcsIntervalEntitySystem, Check);
    addMethod(cls, EcsIntervalEntitySystem, RemoveFromSystem);
    addMethod(cls, EcsIntervalEntitySystem, InsertToSystem);
    addMethod(cls, EcsIntervalEntitySystem, SetWorld);
    addMethod(cls, EcsIntervalEntitySystem, IsPassive);
    addMethod(cls, EcsIntervalEntitySystem, SetPassive);
    addMethod(cls, EcsIntervalEntitySystem, GetActive);
    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsIntervalEntitySystem* New(EcsIntervalEntitySystem* self, EcsAspect* aspect, float interval)
{
    self->base = extends(EcsEntitySystem, aspect);
    self->isa = isa(EcsIntervalEntitySystem);
    self->Acc = 0;
    self->Interval = interval;
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsIntervalEntitySystem* self) { virtual(EcsIntervalEntitySystem)->Begin(self); }

method void Process(EcsIntervalEntitySystem* self)
{   
    Process(self->base);
}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsIntervalEntitySystem* self) { virtual(EcsIntervalEntitySystem)->End(self); }

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsIntervalEntitySystem* self, Array* entities) { 
    virtual(EcsIntervalEntitySystem)->ProcessEntities(self, entities); 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsIntervalEntitySystem* self) { 
    if ((self->Acc += GetDelta(self->World)) >= self->Interval) {
        self->Acc -= self->Interval;
        return true;
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsIntervalEntitySystem* self) { virtual(EcsIntervalEntitySystem)->Initialize(self); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsIntervalEntitySystem* self, EcsEntity* e) { 
    virtual(EcsIntervalEntitySystem)->Inserted(self, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsIntervalEntitySystem* self, EcsEntity* e) { 
    virtual(EcsIntervalEntitySystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsIntervalEntitySystem* self, EcsEntity* e) { 
    Check(self->base, e);
}

method void RemoveFromSystem(EcsIntervalEntitySystem* self, EcsEntity* e) 
{
    RemoveFromSystem(self->base, e);
}

method void InsertToSystem(EcsIntervalEntitySystem* self, EcsEntity* e) 
{
    InsertToSystem(self->base, e);
}

method void Added(EcsIntervalEntitySystem* self, EcsEntity* entity) { }

method void Changed(EcsIntervalEntitySystem* self, EcsEntity* e) {
    Check(self, e);
}

method void Deleted(EcsIntervalEntitySystem* self, EcsEntity* e) {
    Deleted(self->base, e);
}

method void Disabled(EcsIntervalEntitySystem* self, EcsEntity* e) {
    Disabled(self->base, e);
}

method void Enabled(EcsIntervalEntitySystem* self, EcsEntity* e) {
    Enabled(self->base, e);
}

method void SetWorld(EcsIntervalEntitySystem* self, EcsWorld* world) {
    SetWorld(self->base, world);
}

method bool IsPassive(EcsIntervalEntitySystem* self) {
    return IsPassive(self->base);
}

method void SetPassive(EcsIntervalEntitySystem* self, bool passive) {
    SetPassive(self->base, passive);
}

method Array* GetActive(EcsIntervalEntitySystem* self) {
    return GetActive(self);
}

