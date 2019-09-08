#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



/**
 * An Aspects is used by systems as a matcher against entities, to check if a system is
 * interested in an entity. Aspects define what sort of component types an entity must
 * possess, or not possess.
 *
 * This creates an aspect where an entity must possess A and B and C:
 * Aspect.getAspectForAll(A.class, B.class, C.class)
 *
 * This creates an aspect where an entity must possess A and B and C, but must not possess U or V.
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class)
 *
 * This creates an aspect where an entity must possess A and B and C, but must not possess U or V, but must possess one of X or Y or Z.
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
 *
 * You can create and compose aspects in many ways:
 * Aspect.getEmpty().one(X.class, Y.class, Z.class).all(A.class, B.class, C.class).exclude(U.class, V.class)
 * is the same as:
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
 *
 * @author Arni Arent
 *
 */

method int GetIndexFor(EcsComponentTypeFactory*, Class);

type (EcsAspect)
{
    Class isa;
    Object* base;
    BitSet* AllSet;
    BitSet* ExclusionSet;
    BitSet* OneSet;
    EcsWorld* World;

};

method void SetWorld(EcsAspect* self, EcsWorld* world);
method BitSet* GetAllSet(EcsAspect* self);
method BitSet* GetExclusionSet(EcsAspect* self);
method BitSet* GetOneSet(EcsAspect* self);
method EcsAspect* All(EcsAspect* self, int count, va_list _args);
method EcsAspect* Exclude(EcsAspect* self, int count, va_list _args);
method EcsAspect* One(EcsAspect* self, int count, va_list _args);


class (EcsAspect)
{
    EcsComponentTypeFactory* TypeFactory;
};


delegate (EcsAspect, SetWorld, void, (EcsAspect* self, EcsWorld* world));
delegate (EcsAspect, GetAllSet, BitSet*, (EcsAspect* self));
delegate (EcsAspect, GetExclusionSet, BitSet*, (EcsAspect* self));
delegate (EcsAspect, GetOneSet, BitSet*, (EcsAspect* self));
delegate (EcsAspect, All, EcsAspect*, (EcsAspect* self, int count, va_list _args));
delegate (EcsAspect, Exclude, EcsAspect*, (EcsAspect* self, int count, va_list _args));
delegate (EcsAspect, One, EcsAspect*, (EcsAspect* self, int count, va_list _args));


/**
 * EcsAspect Vtable
 */
vtable (EcsAspect) 
{
    const ObjectToString        ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsAspectSetWorld     SetWorld;
    const EcsAspectGetAllSet    GetAllSet;
    const EcsAspectGetExclusionSet       GetExclusionSet;
    const EcsAspectGetOneSet    GetOneSet;
    const EcsAspectAll          All;
    const EcsAspectExclude      Exclude;
    const EcsAspectOne          One;

};

static inline vptr(EcsAspect);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsAspect(Class base) 
{
    Class cls = createClass(base, EcsAspect);
    addMethod(cls, Object, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, EcsAspect, SetWorld);
    addMethod(cls, EcsAspect, GetAllSet);
    addMethod(cls, EcsAspect, GetExclusionSet);
    addMethod(cls, EcsAspect, GetOneSet);
    addMethod(cls, EcsAspect, All);
    addMethod(cls, EcsAspect, Exclude);
    addMethod(cls, EcsAspect, One);
    return cls; 
}



method void SetTypeFactory(EcsComponentTypeFactory* typeFactory)
{
    $EcsAspect.TypeFactory = typeFactory;
}

method EcsAspect* New(EcsAspect* self)
{
    self->base = extends(Object);
    self->isa = isa(EcsAspect);
    self->AllSet = new(BitSet);
    self->ExclusionSet = new(BitSet);
    self->OneSet = new(BitSet);
    return self;
}

method void SetWorld(EcsAspect* self, EcsWorld* world)
{
    self->World = world;
}

method BitSet* GetAllSet(EcsAspect* self)
{
    return self->AllSet;
}

method BitSet* GetExclusionSet(EcsAspect* self)
{
    return self->ExclusionSet;
}

method BitSet* GetOneSet(EcsAspect* self)
{
    return self->OneSet;
}


/**
 * Returns an aspect where an entity must possess all of the specified component types.
 * @param {Type} type a required component type
 * @param {Array<Type>} types a required component type
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method EcsAspect* All(EcsAspect* self, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) 
    {
        EcsComponent* t = va_arg(args, EcsComponent*);
        auto index = GetIndexFor($EcsAspect.TypeFactory, t);
        Set(self->AllSet, index, true);
    }
    va_end(args);
    return self;
}

/**
 * Excludes all of the specified component types from the aspect. A system will not be
 * interested in an entity that possesses one of the specified exclusion component types.
 *
 * @param {Type} type component type to exclude
 * @param {Array<Type>} types component type to exclude
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method EcsAspect* Exclude(EcsAspect* self, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) 
    {
        EcsComponent* t = va_arg(args, EcsComponent*);
        auto index = GetIndexFor($EcsAspect.TypeFactory, t);
        Set(self->ExclusionSet, index, true);
    }
    va_end(args);
    return self;
}

/**
 * Returns an aspect where an entity must possess one of the specified component types.
 * @param {Type} type one of the types the entity must possess
 * @param {Array<Type>} types one of the types the entity must possess
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method EcsAspect* One(EcsAspect* self, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) 
    {
        EcsComponent* t = va_arg(args, Object*);
        auto index = GetIndexFor($EcsAspect.TypeFactory, t);
        Set(self->OneSet, index, true);
    }
    va_end(args);
    return self;
}


/**
 * Creates an aspect where an entity must possess all of the specified component types.
 *
 * @param {Type} type a required component type
 * @param {Array<Type>} types a required component type
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
#define GetAspectForAll(...) _GetAspectForAll(PP_NARG(__VA_ARGS__), __VA_ARGS__)
method EcsAspect* _GetAspectForAll(int count, ...) 
{
    auto aspect = new(EcsAspect);

    va_list args;
    va_start(args, count);
    All(aspect, count, args);
    va_end(args);

    return aspect;
}

/**
 * Creates an aspect where an entity must possess one of the specified component types.
 *
 * @param {Type} type one of the types the entity must possess
 * @param {Array<Type>} types one of the types the entity must possess
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
#define GetAspectForOne(...) _GetAspectForOne(PP_NARG(__VA_ARGS__), __VA_ARGS__)
method EcsAspect* _GetAspectForOne(int count, ...) 
{
    auto aspect = new(EcsAspect);

    va_list args;
    va_start(args, count);
    One(aspect, count, args);
    va_end(args);

    return aspect;
}

/**
 * Creates and returns an empty aspect. This can be used if you want a system that processes no entities, but
 * still gets invoked. Typical usages is when you need to create special purpose systems for debug rendering,
 * like rendering FPS, how many entities are active in the world, etc.
 *
 * You can also use the all, one and exclude methods on this aspect, so if you wanted to create a system that
 * processes only entities possessing just one of the components A or B or C, then you can do:
 * Aspect.getEmpty().one(A,B,C);
 *
 * @return {artemis.Aspect} an empty Aspect that will reject all entities.
 */
method EcsAspect* GetAspectForNone(void)
{
    return new(EcsAspect);
} 
