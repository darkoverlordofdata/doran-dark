#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>


/**
 * The purpose of this class is to allow systems to execute at varying intervals.
 *
 * An example system would be an ExpirationSystem, that deletes entities after a certain
 * lifetime. Instead of running a system that decrements a timeLeft value for each
 * entity, you can simply use this system to execute in a future at a time of the shortest
 * lived entity, and then reset the system to run at a time in a future at a time of the
 * shortest lived entity, etc.
 *
 * Another example system would be an AnimationSystem. You know when you have to animate
 * a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
 * to perform the animation.
 *
 * This will save CPU cycles in some scenarios.
 *
 * Implementation notes:
 * In order to start the system you need to override the inserted(Entity e) method,
 * look up the delay time from that entity and offer it to the system by using the
 * offerDelay(float delay) method.
 * Also, when processing the entities you must also call offerDelay(float delay)
 * for all valid entities.
 *
 * @author Arni Arent
 *
 */
type (EcsDelayedEntityProcessingSystem)
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
    /** The time until an entity should be processed. */
    float Delay;
    /**	If the system is running and counting down delays. */
    bool Running;
    /** The countdown, accumulates world deltas. */
    float Acc;
};

/** */

delegate (EcsDelayedEntityProcessingSystem, New,                 EcsDelayedEntityProcessingSystem*, (EcsDelayedEntityProcessingSystem*, EcsAspect*));
delegate (EcsDelayedEntityProcessingSystem, ToString,            char*,    (const EcsDelayedEntityProcessingSystem* const));
delegate (EcsDelayedEntityProcessingSystem, Added,               void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Changed,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Deleted,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Disabled,            void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Enabled,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Begin,               void, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, End,                 void, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, Process,             void, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, ProcessEntities,     void, (EcsDelayedEntityProcessingSystem*, Array*));
delegate (EcsDelayedEntityProcessingSystem, CheckProcessing,      bool, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, Initialize,          void, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, Inserted,            void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Removed,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Check,               void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, RemoveFromSystem,    void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, InsertToSystem,      void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Added,               void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Changed,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Deleted,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Disabled,            void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, Enabled,             void, (EcsDelayedEntityProcessingSystem*, EcsEntity*));
delegate (EcsDelayedEntityProcessingSystem, SetWorld,            void, (EcsDelayedEntityProcessingSystem*, EcsWorld*));
delegate (EcsDelayedEntityProcessingSystem, IsPassive,           bool, (EcsDelayedEntityProcessingSystem*));
delegate (EcsDelayedEntityProcessingSystem, SetPassive,          void, (EcsDelayedEntityProcessingSystem*, bool));
delegate (EcsDelayedEntityProcessingSystem, GetActive,           Array*, (EcsDelayedEntityProcessingSystem*));

delegate (EcsDelayedEntityProcessingSystem, GetRemainingDelay,  float, (EcsDelayedEntityProcessingSystem* self, EcsEntity* e));
delegate (EcsDelayedEntityProcessingSystem, ProcessDelta,       void, (EcsDelayedEntityProcessingSystem* self, EcsEntity* e, float accumulatedDelta));
delegate (EcsDelayedEntityProcessingSystem, ProcessExpired,     void, (EcsDelayedEntityProcessingSystem* self, EcsEntity* e));
delegate (EcsDelayedEntityProcessingSystem, Restart,            void, (EcsDelayedEntityProcessingSystem* self, float delay));
delegate (EcsDelayedEntityProcessingSystem, OfferDelay,         void, (EcsDelayedEntityProcessingSystem* self, float delay));
delegate (EcsDelayedEntityProcessingSystem, GetInitialTimeDelay, float, (EcsDelayedEntityProcessingSystem* self));
delegate (EcsDelayedEntityProcessingSystem, GetRemainingTimeUntilProcessing, float, (EcsDelayedEntityProcessingSystem* self));
delegate (EcsDelayedEntityProcessingSystem, IsRunning,          bool, (EcsDelayedEntityProcessingSystem* self));
delegate (EcsDelayedEntityProcessingSystem, Stop,               void, (EcsDelayedEntityProcessingSystem* self));


/**
 * EcsDelayedEntityProcessingSystem Vtable
 */
vtable (EcsDelayedEntityProcessingSystem) 
{
    const EcsDelayedEntityProcessingSystemToString           ToString;
    const ObjectEquals                      Equals;
    const ObjectGetHashCode                 GetHashCode;
    const ObjectDispose                     Dispose;
    const EcsDelayedEntityProcessingSystemAdded             Added;
    const EcsDelayedEntityProcessingSystemChanged           Changed;
    const EcsDelayedEntityProcessingSystemDeleted           Deleted;
    const EcsDelayedEntityProcessingSystemDisabled          Disabled;
    const EcsDelayedEntityProcessingSystemEnabled           Enabled;
    const EcsDelayedEntityProcessingSystemBegin             Begin;
    const EcsDelayedEntityProcessingSystemBegin             End;
    const EcsDelayedEntityProcessingSystemProcess           Process;
    const EcsDelayedEntityProcessingSystemProcessEntities   ProcessEntities;
    const EcsDelayedEntityProcessingSystemCheckProcessing   CheckProcessing;
    const EcsDelayedEntityProcessingSystemInitialize        Initialize;
    const EcsDelayedEntityProcessingSystemInserted          Inserted;
    const EcsDelayedEntityProcessingSystemRemoved           Removed;
    const EcsDelayedEntityProcessingSystemCheck             Check;
    const EcsDelayedEntityProcessingSystemRemoveFromSystem  RemoveFromSystem;
    const EcsDelayedEntityProcessingSystemInsertToSystem    InsertToSystem;
    const EcsDelayedEntityProcessingSystemSetWorld          SetWorld;
    const EcsDelayedEntityProcessingSystemIsPassive         IsPassive;
    const EcsDelayedEntityProcessingSystemSetPassive        SetPassive;
    const EcsDelayedEntityProcessingSystemGetActive         GetActive;
    const EcsDelayedEntityProcessingSystemGetRemainingDelay GetRemainingDelay;
    const EcsDelayedEntityProcessingSystemProcessDelta      ProcessDelta;
    const EcsDelayedEntityProcessingSystemProcessExpired    ProcessExpired;
    const EcsDelayedEntityProcessingSystemRestart           Restart;
    const EcsDelayedEntityProcessingSystemOfferDelay        OfferDelay;
    const EcsDelayedEntityProcessingSystemGetInitialTimeDelay       GetInitialTimeDelay;
    const EcsDelayedEntityProcessingSystemGetRemainingTimeUntilProcessing       GetRemainingTimeUntilProcessing;
    const EcsDelayedEntityProcessingSystemIsRunning         IsRunning;
    const EcsDelayedEntityProcessingSystemStop              Stop;

};


static inline vptr(EcsDelayedEntityProcessingSystem);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsDelayedEntityProcessingSystem(Class base) 
{
    Class cls = createClass(base, EcsDelayedEntityProcessingSystem);
    addMethod(cls, Object,          ToString);
    addMethod(cls, Object,          Equals);
    addMethod(cls, Object,          GetHashCode);
    addMethod(cls, Object,          Dispose);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Added);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Changed);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Deleted);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Disabled);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Enabled);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Begin);
    addMethod(cls, EcsDelayedEntityProcessingSystem, End);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Process);
    addMethod(cls, EcsDelayedEntityProcessingSystem, ProcessEntities);
    addMethod(cls, EcsDelayedEntityProcessingSystem, CheckProcessing);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Initialize);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Inserted);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Removed);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Check);
    addMethod(cls, EcsDelayedEntityProcessingSystem, RemoveFromSystem);
    addMethod(cls, EcsDelayedEntityProcessingSystem, InsertToSystem);
    addMethod(cls, EcsDelayedEntityProcessingSystem, SetWorld);
    addMethod(cls, EcsDelayedEntityProcessingSystem, IsPassive);
    addMethod(cls, EcsDelayedEntityProcessingSystem, SetPassive);
    addMethod(cls, EcsDelayedEntityProcessingSystem, GetActive);
    addMethod(cls, EcsDelayedEntityProcessingSystem, GetRemainingDelay);
    addMethod(cls, EcsDelayedEntityProcessingSystem, ProcessDelta);
    addMethod(cls, EcsDelayedEntityProcessingSystem, ProcessExpired);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Restart);
    addMethod(cls, EcsDelayedEntityProcessingSystem, OfferDelay);
    addMethod(cls, EcsDelayedEntityProcessingSystem, GetInitialTimeDelay);
    addMethod(cls, EcsDelayedEntityProcessingSystem, GetRemainingTimeUntilProcessing);
    addMethod(cls, EcsDelayedEntityProcessingSystem, IsRunning);
    addMethod(cls, EcsDelayedEntityProcessingSystem, Stop);
    return cls;
}

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method EcsDelayedEntityProcessingSystem* New(EcsDelayedEntityProcessingSystem* self, EcsAspect* aspect)
{
    self->base = extends(EcsEntitySystem, aspect);
    self->isa = isa(EcsDelayedEntityProcessingSystem);
    return self;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(EcsDelayedEntityProcessingSystem* self) { virtual(EcsDelayedEntityProcessingSystem)->Begin(self); }

method void Process(EcsDelayedEntityProcessingSystem* self)
{   
    Process(self->base);
}

/**
 * Called after the processing of entities ends.
 */
method void End(EcsDelayedEntityProcessingSystem* self) { virtual(EcsDelayedEntityProcessingSystem)->End(self); }

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(EcsDelayedEntityProcessingSystem* self, Array* entities) { 
    for (auto i=0; i<entities->length; i++) {
        auto entity = Get(entities, i);
        ProcessDelta(self, entity, self->Acc);
        auto remaining = GetRemainingDelay(self, entity);
        if (remaining <= 0) {
            ProcessExpired(self, entity);
        } else {
            OfferDelay(self, remaining);
        }
    } 
    Stop(self);
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(EcsDelayedEntityProcessingSystem* self) { 
    if (self->Running) {
        self->Acc += GetDelta(self->World);
        if (self->Acc >= self->Delay) {
            return true;
        }
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(EcsDelayedEntityProcessingSystem* self) { virtual(EcsDelayedEntityProcessingSystem)->Initialize(self); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) { 
    auto delay = GetRemainingDelay(self, e);
    if (delay > 0) {
        OfferDelay(self, delay);
    }
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) { 
    virtual(EcsDelayedEntityProcessingSystem)->Removed(self, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) { 
    Check(self->base, e);
}

method void RemoveFromSystem(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) 
{
    RemoveFromSystem(self->base, e);
}

method void InsertToSystem(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) 
{
    InsertToSystem(self->base, e);
}

method void Added(EcsDelayedEntityProcessingSystem* self, EcsEntity* entity) { }

method void Changed(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    Check(self->base, e);
}

method void Deleted(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    Deleted(self->base, e);
}

method void Disabled(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    Disabled(self->base, e);
}

method void Enabled(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    Enabled(self->base, e);
}

method void SetWorld(EcsDelayedEntityProcessingSystem* self, EcsWorld* world) {
    SetWorld(self->base, world);
}

method bool IsPassive(EcsDelayedEntityProcessingSystem* self) {
    return IsPassive(self->base);
}

method void SetPassive(EcsDelayedEntityProcessingSystem* self, bool passive) {
    SetPassive(self->base, passive);
}

method Array* GetActive(EcsDelayedEntityProcessingSystem* self) {
    return GetActive(self->base);
}

/**
 * Return the delay until this entity should be processed.
 *
 * @param e entity
 * @return delay
 */
method float GetRemainingDelay(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    virtual(EcsDelayedEntityProcessingSystem)->GetRemainingDelay(self, e); 
}

/**
 * Process a entity this system is interested in. Substract the accumulatedDelta
* from the entities defined delay.
*
* @param e the entity to process.
* @param accumulatedDelta the delta time since this system was last executed.
*/
method void ProcessDelta(EcsDelayedEntityProcessingSystem* self, EcsEntity* e, float accumulatedDelta) {
    virtual(EcsDelayedEntityProcessingSystem)->ProcessDelta(self, e, accumulatedDelta); 
}

method void ProcessExpired(EcsDelayedEntityProcessingSystem* self, EcsEntity* e) {
    virtual(EcsDelayedEntityProcessingSystem)->ProcessExpired(self, e); 
}


/**
 * Start processing of entities after a certain amount of delta time.
*
* Cancels current delayed run and starts a new one.
*
* @param delta time delay until processing starts.
*/
method void Restart(EcsDelayedEntityProcessingSystem* self, float delay) {
    self->Delay = delay;
    self->Acc = 0;
    self->Running = true;
}

/**
 * Restarts the system only if the delay offered is shorter than the
* time that the system is currently scheduled to execute at.
* If the system is already stopped (not running) then the offered
*
* delay will be used to restart the system with no matter its value.
*
* If the system is already counting down, and the offered delay is
* larger than the time remaining, the system will ignore it. If the
* offered delay is shorter than the time remaining, the system will
* restart itself to run at the offered delay.
*
* @param delay
*/
method void OfferDelay(EcsDelayedEntityProcessingSystem* self, float delay) {
    if(!self->Running || delay < GetRemainingTimeUntilProcessing(self)) {
        Restart(self, delay);
    }
}


/**
 * Get the initial delay that the system was ordered to process entities after.
*
* @return the originally set delay.
*/
method float GetInitialTimeDelay(EcsDelayedEntityProcessingSystem* self) {
    return self->Delay;
}

/**
 * Get the time until the system is scheduled to run at.
* Returns zero (0) if the system is not running.
* Use isRunning() before checking this value.
*
* @return time when system will run at.
*/
method float GetRemainingTimeUntilProcessing(EcsDelayedEntityProcessingSystem* self) {
    if(self->Running) {
        return self->Delay-self->Acc;
    }
    return 0;
}

/**
 * Check if the system is counting down towards processing.
*
* @return true if it's counting down, false if it's not running.
*/
method bool IsRunning(EcsDelayedEntityProcessingSystem* self) {
    return self->Running;
}

/**
 * Stops the system from running, aborts current countdown.
* Call offerDelay or restart to run it again.
*/
method void Stop(EcsDelayedEntityProcessingSystem* self) {
    self->Running = false;
    self->Acc = 0;
}

