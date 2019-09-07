#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsPlayerManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
};

delegate (EcsPlayerManager, New,          EcsPlayerManager*, (EcsPlayerManager*));
delegate (EcsPlayerManager, ToString,     char*,    (const EcsPlayerManager* const));
delegate (EcsPlayerManager, Initialize,   void, (EcsPlayerManager*));
delegate (EcsPlayerManager, GetWorld,     EcsWorld*, (EcsPlayerManager*));
delegate (EcsPlayerManager, SetWorld,     void, (EcsPlayerManager*, EcsWorld*));
delegate (EcsPlayerManager, Added,        void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Changed,      void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Deleted,      void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Disabled,     void, (EcsPlayerManager*, EcsEntity*));
delegate (EcsPlayerManager, Enabled,      void, (EcsPlayerManager*, EcsEntity*));


/**
 * EcsPlayerManager Vtable
 */
vtable (EcsPlayerManager) 
{
    const EcsPlayerManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsPlayerManagerToString    Initialize;
    const EcsPlayerManagerGetWorld    GetWorld;
    const EcsPlayerManagerSetWorld    SetWorld;
    const EcsPlayerManagerAdded       Added;
    const EcsPlayerManagerChanged     Changed;
    const EcsPlayerManagerDeleted     Deleted;
    const EcsPlayerManagerDisabled    Disabled;
    const EcsPlayerManagerEnabled     Enabled;
};

static inline vptr(EcsPlayerManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsPlayerManager(Class base) 
{
    Class cls = createClass(base, EcsPlayerManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsPlayerManager,  Initialize);
    addMethod(cls, EcsPlayerManager,  GetWorld);
    addMethod(cls, EcsPlayerManager,  SetWorld);
    addMethod(cls, EcsPlayerManager,  Added);
    addMethod(cls, EcsPlayerManager,  Changed);
    addMethod(cls, EcsPlayerManager,  Deleted);
    addMethod(cls, EcsPlayerManager,  Disabled);
    addMethod(cls, EcsPlayerManager,  Enabled);
    return cls; 
}

method EcsPlayerManager* New(EcsPlayerManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsPlayerManager);
    return self;
}

method void Initialize(EcsPlayerManager* self) { virtual(EcsPlayerManager)->Initialize(self); }

method void SetWorld(EcsPlayerManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsPlayerManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Added(self, entity); }

method void Changed(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Changed(self, entity); }

method void Deleted(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Deleted(self, entity); }

method void Disabled(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Disabled(self, entity); }

method void Enabled(EcsPlayerManager* self, EcsEntity* entity) { virtual(EcsPlayerManager)->Enabled(self, entity); }
