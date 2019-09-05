#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsEntityObserver)
{
    Class isa;
    Object* base;
};

delegate (EcsEntityObserver, New,          EcsEntityObserver*, (EcsEntityObserver*));
delegate (EcsEntityObserver, ToString,     char*,    (const EcsEntityObserver* const));
delegate (EcsEntityObserver, Added,        void, (EcsEntityObserver*, EcsEntity*));
delegate (EcsEntityObserver, Changed,      void, (EcsEntityObserver*, EcsEntity*));
delegate (EcsEntityObserver, Deleted,      void, (EcsEntityObserver*, EcsEntity*));
delegate (EcsEntityObserver, Disabled,     void, (EcsEntityObserver*, EcsEntity*));
delegate (EcsEntityObserver, Enabled,      void, (EcsEntityObserver*, EcsEntity*));


/**
 * EcsEntityObserver Vtable
 */
vtable (EcsEntityObserver) 
{
    const EcsEntityObserverToString     ToString;
    const ObjectEquals                  Equals;
    const ObjectGetHashCode             GetHashCode;
    const ObjectDispose                 Dispose;
    const EcsEntityObserverAdded        Added;
    const EcsEntityObserverChanged      Changed;
    const EcsEntityObserverDeleted      Deleted;
    const EcsEntityObserverDisabled     Disabled;
    const EcsEntityObserverEnabled      Enabled;
};

static inline vptr(EcsEntityObserver);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsEntityObserver(Class base) 
{
    Class cls = createClass(base, EcsEntityObserver);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsEntityObserver, Added);
    addMethod(cls, EcsEntityObserver, Changed);
    addMethod(cls, EcsEntityObserver, Deleted);
    addMethod(cls, EcsEntityObserver, Disabled);
    addMethod(cls, EcsEntityObserver, Enabled);
    return cls;
}

method EcsEntityObserver* New(EcsEntityObserver* self)
{
    self->base = extends(Object);
    self->isa = isa(EcsEntityObserver);
    return self;
}


method void Added(EcsEntityObserver* self, EcsEntity* entity)
{
    virtual(EcsEntityObserver)->Added(self, entity);
}
method void Changed(EcsEntityObserver* self, EcsEntity* entity)
{
    virtual(EcsEntityObserver)->Changed(self, entity);
}
method void Deleted(EcsEntityObserver* self, EcsEntity* entity)
{
    virtual(EcsEntityObserver)->Deleted(self, entity);
}
method void Disabled(EcsEntityObserver* self, EcsEntity* entity)
{
    virtual(EcsEntityObserver)->Disabled(self, entity);
}
method void Enabled(EcsEntityObserver* self, EcsEntity* entity)
{
    virtual(EcsEntityObserver)->Enabled(self, entity);
}
