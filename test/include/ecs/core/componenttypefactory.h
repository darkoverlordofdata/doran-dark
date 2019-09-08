#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>




type (EcsComponentTypeFactory)
{
    Class isa;
    Object* base;
    Map* ComponentTypes;
    int ComponentTypeCount;
    Array* Types;
};

method EcsComponentType* GetTypeFor(EcsComponentTypeFactory* self, Class c);
method int GetIndexFor(EcsComponentTypeFactory* self, Class c);


delegate (EcsComponentTypeFactory, GetTypeFor, EcsComponentType*, (EcsComponentTypeFactory* self, Class c));
delegate (EcsComponentTypeFactory, GetIndexFor, int, (EcsComponentTypeFactory* self, Class c));


/**
 * EcsComponentTypeFactory Vtable
 */
vtable (EcsComponentTypeFactory) 
{
    const ObjectToString        ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsComponentTypeFactoryGetTypeFor       GetTypeFor;
    const EcsComponentTypeFactoryGetIndexFor       GetIndexFor;
};

static inline vptr(EcsComponentTypeFactory);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsComponentTypeFactory(Class base) 
{
    Class cls = createClass(base, EcsComponentTypeFactory);
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, EcsComponentTypeFactory, GetTypeFor);
    addMethod(cls, EcsComponentTypeFactory, GetIndexFor);
    return cls; 
}



/**
 * Contains all generated component types, newly generated component types
 * will be stored here.
 */
method EcsComponentTypeFactory* New(EcsComponentTypeFactory* self)
{
    self->base = extends(Object);
    self->isa = isa(EcsComponentTypeFactory);
    self->ComponentTypes = new(Map, of(EcsComponentType));
    self->Types = new(Array, of(ComponentType));
    SetTypeFactory(self);
    return self;
}

/**
 * Gets the component type for the given component class.
 * <p>
 * If no component type exists yet, a new one will be created and stored
 * for later retrieval.
 * </p>
 *
 * @param c
 *			the component's class to get the type for
*
* @return the component's {@link ComponentType}l
*/
method EcsComponentType* GetTypeFor(EcsComponentTypeFactory* self, Class c)
{

    auto type = Get(self->ComponentTypes, c->name);

    if (type == nullptr) {
        auto index = self->ComponentTypeCount++;
        type = new(EcsComponentType, c, index);
        Put(self->ComponentTypes, c->name, type);
        Put(self->Types, index, type);
    }
    return type;

}

/**
 * Get the index of the component type of given component class.
 *
 * @param c
 *			the component class to get the type index for
 *
 * @return the component type's index
 */
method int GetIndexFor(EcsComponentTypeFactory* self, Class c) 
{
    return GetIndex(GetTypeFor(self, c));
}


