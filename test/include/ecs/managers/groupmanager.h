#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsGroupManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
};

delegate (EcsGroupManager, New,          EcsGroupManager*, (EcsGroupManager*));
delegate (EcsGroupManager, ToString,     char*,    (const EcsGroupManager* const));
delegate (EcsGroupManager, Initialize,   void, (EcsGroupManager*));
delegate (EcsGroupManager, GetWorld,     EcsWorld*, (EcsGroupManager*));
delegate (EcsGroupManager, SetWorld,     void, (EcsGroupManager*, EcsWorld*));
delegate (EcsGroupManager, Added,        void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Changed,      void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Deleted,      void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Disabled,     void, (EcsGroupManager*, EcsEntity*));
delegate (EcsGroupManager, Enabled,      void, (EcsGroupManager*, EcsEntity*));


/**
 * EcsGroupManager Vtable
 */
vtable (EcsGroupManager) 
{
    const EcsGroupManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsGroupManagerToString    Initialize;
    const EcsGroupManagerGetWorld    GetWorld;
    const EcsGroupManagerSetWorld    SetWorld;
    const EcsGroupManagerAdded       Added;
    const EcsGroupManagerChanged     Changed;
    const EcsGroupManagerDeleted     Deleted;
    const EcsGroupManagerDisabled    Disabled;
    const EcsGroupManagerEnabled     Enabled;
};

static inline vptr(EcsGroupManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsGroupManager(Class base) 
{
    Class cls = createClass(base, EcsGroupManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsGroupManager,  Initialize);
    addMethod(cls, EcsGroupManager,  GetWorld);
    addMethod(cls, EcsGroupManager,  SetWorld);
    addMethod(cls, EcsGroupManager,  Added);
    addMethod(cls, EcsGroupManager,  Changed);
    addMethod(cls, EcsGroupManager,  Deleted);
    addMethod(cls, EcsGroupManager,  Disabled);
    addMethod(cls, EcsGroupManager,  Enabled);
    return cls; 
}

method EcsGroupManager* New(EcsGroupManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsGroupManager);
    return self;
}

method void Initialize(EcsGroupManager* self) { virtual(EcsGroupManager)->Initialize(self); }

method void SetWorld(EcsGroupManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsGroupManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Added(self, entity); }

method void Changed(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Changed(self, entity); }

method void Deleted(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Deleted(self, entity); }

method void Disabled(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Disabled(self, entity); }

method void Enabled(EcsGroupManager* self, EcsEntity* entity) { virtual(EcsGroupManager)->Enabled(self, entity); }
