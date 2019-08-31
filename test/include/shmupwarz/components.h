#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

#include "components/transform.h"
#include "components/color.h"
#include "components/expire.h"
#include "components/health.h"
#include "components/sound.h"
#include "components/taxonomy.h"
#include "components/tween.h"
#include "components/velocity.h"


/**
 * Index in the Components array
 */
enum ComponentIDs {
    ColorId,
    ExpireId,
    HealthId,
    SoundId,
    TaxonomyId,
    TweenId,
    VelocityId,
    ComponentCount,
};

/**
 * Entity
 */
type (Entity)
{
    int Id;
    int Active;
    char* Name;
    Transform* Transform;
    void* Components[ComponentCount];
};

/**
 * Entity Collision
 */
method bool Collides (Entity* self, Entity* other) {
    return SDL_HasIntersection(&self->Transform->Bounds, &other->Transform->Bounds);
}

/**
 * Color Component
 */
method void AddColorComponent(Entity* self, int r, int g, int b, int a) {
    self->Components[ColorId] = new(ColorComponent, r, g, b, a);
}
method ColorComponent* GetColorComponent(Entity* self) {
    return self->Components[ColorId];
}

/**
 * Expire Component
 */
method void AddExpireComponent(Entity* self, double value) {
    self->Components[ExpireId] = new(ExpireComponent, value);
}
method ExpireComponent* GetExpireComponent(Entity* self) {
    return self->Components[ExpireId];
}

/**
 * Health Component
 */
method void AddHealthComponent(Entity* self, int current, int maximum) {
    self->Components[HealthId] = new(HealthComponent, current, maximum);
}
method HealthComponent* GetHealthComponent(Entity* self) {
    return self->Components[HealthId];
}

/**
 * Sound Effects Component
 */
method SoundComponent* GetSoundComponent(Entity* self) {
    return self->Components[SoundId];
}
method void AddSoundComponent(Entity* self, SoundEffect value) {
    self->Components[SoundId] = new(SoundComponent, value);
}

/**
 * Taxonomy Component
 */
method TaxonomyComponent* GetTaxonomyComponent(Entity* self) {
    return self->Components[TaxonomyId];
}
method void AddTaxonomyComponent(Entity* self, ComponentType type, ComponentSubtype subtype) {
    self->Components[TaxonomyId] = new(TaxonomyComponent, type, subtype);
}

/**
 * Tween Component
 */
method TweenComponent* GetTweenComponent(Entity* self) {
    return self->Components[TweenId];
}
method void AddTweenComponent(Entity* self, double min, double max, double speed, bool repeat, bool active) {
    self->Components[TweenId] = new(TweenComponent, min, max, speed, repeat, active);
}

/**
 * Velocity Component
 */
method void AddVelocityComponent(Entity* self, int x, int y) {
    self->Components[VelocityId] = new(VelocityComponent, x, y);
}
method VelocityComponent* GetVelocityComponent(Entity* self) {
    return self->Components[VelocityId];
}


