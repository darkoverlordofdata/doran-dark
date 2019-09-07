#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


// method bool CheckProcessing(EcsEntitySystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
struct EcsSystemIndexManager EcsSystemIndexManager;
struct EcsSystemIndexManager
{
    int Index;
    Map* Indices;
};

method int GetIndexFor(Class es) 
{
    static bool first = true;
    if (first) {
        first = false;
        EcsSystemIndexManager.Index = 0;
        EcsSystemIndexManager.Indices = new(Array, of(Integer));
    }

    auto index = 0;
    if (Get(EcsSystemIndexManager.Indices, es->name) == nullptr)
    {
        index = EcsSystemIndexManager.Index++;
        Put(EcsSystemIndexManager.Indices, es->name, new(Integer, index));
    }
    else
    {
        index = IntValue((Number*)Get(EcsSystemIndexManager.Indices, es->name));
    }
    return index;
}

type (EcsEntitySystem)
{
    Class isa;
    EcsEntityObserver* base;
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

delegate (EcsEntitySystem, New,                 EcsEntitySystem*, (EcsEntitySystem*, EcsAspect*));
delegate (EcsEntitySystem, ToString,            char*,    (const EcsEntitySystem* const));
delegate (EcsEntitySystem, Added,               void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Changed,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Deleted,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Disabled,            void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Enabled,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Begin,               void, (EcsEntitySystem*));
delegate (EcsEntitySystem, End,                 void, (EcsEntitySystem*));
delegate (EcsEntitySystem, Process,             void, (EcsEntitySystem*));
delegate (EcsEntitySystem, ProcessEntities,     void, (EcsEntitySystem*, Array*));
delegate (EcsEntitySystem, CheckProcessing,      bool, (EcsEntitySystem*));
delegate (EcsEntitySystem, Initialize,          void, (EcsEntitySystem*));
delegate (EcsEntitySystem, Inserted,            void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Removed,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Check,               void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, RemoveFromSystem,    void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, InsertToSystem,      void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Added,               void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Changed,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Deleted,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Disabled,            void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, Enabled,             void, (EcsEntitySystem*, EcsEntity*));
delegate (EcsEntitySystem, SetWorld,            void, (EcsEntitySystem*, EcsWorld*));
delegate (EcsEntitySystem, IsPassive,           bool, (EcsEntitySystem*));
delegate (EcsEntitySystem, SetPassive,          void, (EcsEntitySystem*, bool));
delegate (EcsEntitySystem, GetActive,           Array*, (EcsEntitySystem*));


/**
 * EcsEntitySystem Vtable
 */
vtable (EcsEntitySystem) 
{
    const EcsEntitySystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsEntitySystemAdded              Added;
    const EcsEntitySystemChanged            Changed;
    const EcsEntitySystemDeleted            Deleted;
    const EcsEntitySystemDisabled           Disabled;
    const EcsEntitySystemEnabled            Enabled;
    const EcsEntitySystemBegin              Begin;
    const EcsEntitySystemBegin              End;
    const EcsEntitySystemProcess            Process;
    const EcsEntitySystemProcessEntities    ProcessEntities;
    const EcsEntitySystemCheckProcessing     CheckProcessing;
    const EcsEntitySystemInitialize         Initialize;
    const EcsEntitySystemInserted           Inserted;
    const EcsEntitySystemRemoved            Removed;
    const EcsEntitySystemCheck              Check;
    const EcsEntitySystemRemoveFromSystem   RemoveFromSystem;
    const EcsEntitySystemInsertToSystem     InsertToSystem;
    const EcsEntitySystemSetWorld           SetWorld;
    const EcsEntitySystemIsPassive          IsPassive;
    const EcsEntitySystemSetPassive         SetPassive;
    const EcsEntitySystemGetActive          GetActive;
};


static inline vptr(EcsEntitySystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsEntitySystem(Class base) 
{
    Class cls = createClass(base, EcsEntitySystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsEntitySystem, Added);
    addMethod(cls, EcsEntitySystem, Changed);
    addMethod(cls, EcsEntitySystem, Deleted);
    addMethod(cls, EcsEntitySystem, Disabled);
    addMethod(cls, EcsEntitySystem, Enabled);
    addMethod(cls, EcsEntitySystem, Begin);
    addMethod(cls, EcsEntitySystem, End);
    addMethod(cls, EcsEntitySystem, Process);
    addMethod(cls, EcsEntitySystem, ProcessEntities);
    addMethod(cls, EcsEntitySystem, CheckProcessing);
    addMethod(cls, EcsEntitySystem, Initialize);
    addMethod(cls, EcsEntitySystem, Inserted);
    addMethod(cls, EcsEntitySystem, Removed);
    addMethod(cls, EcsEntitySystem, Check);
    addMethod(cls, EcsEntitySystem, RemoveFromSystem);
    addMethod(cls, EcsEntitySystem, InsertToSystem);
    addMethod(cls, EcsEntitySystem, SetWorld);
    addMethod(cls, EcsEntitySystem, IsPassive);
    addMethod(cls, EcsEntitySystem, SetPassive);
    addMethod(cls, EcsEntitySystem, GetActive);
    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsEntitySystem* New(EcsEntitySystem* self, EcsAspect* aspect)
{
    self->base = extends(EcsEntityObserver);
    self->isa = isa(EcsEntitySystem);
    self->Actives = new(Array, of(EcsEntity));
    self->Aspect = aspect;
    self->SystemIndex = GetIndexFor(self->isa);
    self->AllSet = GetAllSet(self->Aspect);
    self->AllSet = GetExclusionSet(self->Aspect);
    self->AllSet = GetOneSet(self->Aspect);
    self->IsDummy = IsEmpty(self->AllSet) && IsEmpty(self->OneSet);
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsEntitySystem* self) { virtual(EcsEntitySystem)->Begin(self); }

method void Process(EcsEntitySystem* self)
{   
    if (CheckProcessing(self))
    {
        Begin(self);
        ProcessEntities(self, self->Actives);
        End(self);
    }

}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsEntitySystem* self) { virtual(EcsEntitySystem)->End(self); }

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsEntitySystem* self, Array* entities) { 
    virtual(EcsEntitySystem)->ProcessEntities(self, entities); 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsEntitySystem* self) { 
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsEntitySystem* self) { virtual(EcsEntitySystem)->Initialize(self); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsEntitySystem* self, EcsEntity* e) { 
    virtual(EcsEntitySystem)->Inserted(self, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsEntitySystem* self, EcsEntity* e) { 
    virtual(EcsEntitySystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsEntitySystem* self, EcsEntity* e) { 
    if (self->IsDummy) return;

    auto contains = Get(GetSystemBits(e), self->SystemIndex);
    auto interested = true; // possibly interested, let's try to prove it wrong.

    auto componentBits = e->ComponentBits;
    // Check if the entity possesses ALL of the components defined in the aspect.
    if (!IsEmpty(self->AllSet)) {
        for (auto i = NextSetBit(self->AllSet, 0); i >= 0; NextSetBit(self->AllSet, i+1)) {
            if (!Get(componentBits, i)) {
                interested = false;
                break;
            }
        }
    }

    // Check if the entity possesses ANY of the exclusion components, if it does then the system is not interested.
    if (!IsEmpty(self->ExclusionSet) && interested) {
        interested = !Intersects(self->ExclusionSet, componentBits);
    }
    
    // Check if the entity possesses ANY of the components in the oneSet. If so, the system is interested.
    if(!IsEmpty(self->OneSet)) {
        interested = Intersects(self->OneSet, componentBits);
    }

    if (interested && !contains) 
    {
        InsertToSystem(self, e);
    } 
    else if (!interested && contains) 
    {
        RemoveFromSystem(self, e);
    }
}

method void RemoveFromSystem(EcsEntitySystem* self, EcsEntity* e) 
{
    Remove(self->Actives, e);
    Clear(e->SystemBits, self->SystemIndex);
    Removed(self, e);
}

method void InsertToSystem(EcsEntitySystem* self, EcsEntity* e) 
{
    Add(self->Actives, e);
    Set(GetSystemBits(e), self->SystemIndex, true);
    Inserted(self, e);
}

method void Added(EcsEntitySystem* self, EcsEntity* entity) { }

method void Changed(EcsEntitySystem* self, EcsEntity* e) {
    Check(self, e);
}

method void Deleted(EcsEntitySystem* self, EcsEntity* e) {
    if (Get(GetSystemBits(e), self->SystemIndex)) {
        RemoveFromSystem(self, e);
    }
}

method void Disabled(EcsEntitySystem* self, EcsEntity* e) {
    if (Get(GetSystemBits(e), self->SystemIndex)) {
        RemoveFromSystem(self, e);
    }
}

method void Enabled(EcsEntitySystem* self, EcsEntity* e) {
    Check(self, e);
}

method void SetWorld(EcsEntitySystem* self, EcsWorld* world) {
    self->World = world;
}

method bool IsPassive(EcsEntitySystem* self) {
    return self->Passive;
}

method void SetPassive(EcsEntitySystem* self, bool passive) {
    self->Passive = passive;
}

method Array* GetActive(EcsEntitySystem* self) {
    return self->Actives;
}

