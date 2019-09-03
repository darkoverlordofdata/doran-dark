#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "../components.h"

typedef enum ComponentType {

    TypeBackground,
    TypePlayer,
    TypeBullet,
    TypeEnemy,
    TypeExplosion,
    TypeParticle,

} ComponentType;


typedef enum ComponentSubtype {

    SubtypeBackground,
    SubtypePlayer,
    SubtypeBullet,
    SubtypeEnemy1,
    SubtypeEnemy2,
    SubtypeEnemy3,
    SubtypeExplosion1,
    SubtypeExplosion2,
    SubtypeParticle,

} ComponentSubtype;

type (TaxonomyComponent)
{
    Class isa;
    ComponentType Type;
    ComponentSubtype Subtype;
};


method TaxonomyComponent* New(TaxonomyComponent* self, ComponentType type, ComponentSubtype subtype)
{
    self->isa = isa(TaxonomyComponent);
    self->Type = type;
    self->Subtype = subtype;
    return self;
}

