#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>

/** complete - phase I */


type (EcsComponentTypeFactory)
{
    Class isa;
    Map* ComponentTypes;
    int ComponentTypeCount;
    Array* Types;
};

/**
 * Contains all generated component types, newly generated component types
 * will be stored here.
 */
method EcsComponentTypeFactory* New(EcsComponentTypeFactory* self)
{
    extends(Object);
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


