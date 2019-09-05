#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsManager)
{
    Class isa;
    EcsEntityObserver* base;
    EcsWorld* World;
};

delegate (EcsManager, New,          EcsManager*, (EcsManager*));
delegate (EcsManager, ToString,     char*,    (const EcsManager* const));
delegate (EcsManager, Initialize,   void, (EcsManager*));
delegate (EcsManager, GetWorld,     EcsWorld*, (EcsManager*));
delegate (EcsManager, SetWorld,     void, (EcsManager*, EcsWorld*));
delegate (EcsManager, Added,        void, (EcsManager*, EcsEntity*));
delegate (EcsManager, Changed,      void, (EcsManager*, EcsEntity*));
delegate (EcsManager, Deleted,      void, (EcsManager*, EcsEntity*));
delegate (EcsManager, Disabled,     void, (EcsManager*, EcsEntity*));
delegate (EcsManager, Enabled,      void, (EcsManager*, EcsEntity*));


/**
 * EcsManager Vtable
 */
vtable (EcsManager) 
{
    const EcsManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsManagerToString    Initialize;
    const EcsManagerGetWorld    GetWorld;
    const EcsManagerSetWorld    SetWorld;
    const EcsManagerAdded       Added;
    const EcsManagerChanged     Changed;
    const EcsManagerDeleted     Deleted;
    const EcsManagerDisabled    Disabled;
    const EcsManagerEnabled     Enabled;
};

static inline vptr(EcsManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsManager(Class base) 
{
    Class cls = createClass(base, EcsManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsManager,  Initialize);
    addMethod(cls, EcsManager,  GetWorld);
    addMethod(cls, EcsManager,  SetWorld);
    addMethod(cls, EcsManager,  Added);
    addMethod(cls, EcsManager,  Changed);
    addMethod(cls, EcsManager,  Deleted);
    addMethod(cls, EcsManager,  Disabled);
    addMethod(cls, EcsManager,  Enabled);
    return cls; 
}

method EcsManager* New(EcsManager* self)
{
    self->base = extends(EcsEntityObserver);
    self->isa = isa(EcsManager);
    return self;
}

method void Initialize(EcsManager* self) { virtual(EcsManager)->Initialize(self); }

method void SetWorld(EcsManager* self, EcsWorld* world)
{
    self->World = world;
}

method EcsWorld* GetWorld(EcsManager* self)
{
    return self->World;
}

method void Added(EcsManager* self, EcsEntity* entity) { virtual(EcsManager)->Added(self, entity); }

method void Changed(EcsManager* self, EcsEntity* entity) { virtual(EcsManager)->Changed(self, entity); }

method void Deleted(EcsManager* self, EcsEntity* entity) { virtual(EcsManager)->Deleted(self, entity); }

method void Disabled(EcsManager* self, EcsEntity* entity) { virtual(EcsManager)->Disabled(self, entity); }

method void Enabled(EcsManager* self, EcsEntity* entity) { virtual(EcsManager)->Enabled(self, entity); }
