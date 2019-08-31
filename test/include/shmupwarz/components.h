#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "types.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "components/color.h"
#include "components/health.h"
#include "components/tween.h"
#include "components/velocity.h"
#include "components/expire.h"
#include "components/sound.h"

/**
 * Entity taxonomy
 */
typedef enum TYPE_Component {

    TYPE_BACKGROUND,
    TYPE_TEXT,
    TYPE_LIVES,
    TYPE_ENEMY1,
    TYPE_ENEMY2,
    TYPE_ENEMY3,
    TYPE_PLAYER,
    TYPE_BULLET,
    TYPE_EXPLOSION,
    TYPE_BANG,
    TYPE_PARTICLE,
    TYPE_HUD

} TYPE_Component;

typedef enum CATEGORY_Component {

    CATEGORY_BACKGROUND,
    CATEGORY_BULLET,
    CATEGORY_ENEMY,
    CATEGORY_EXPLOSION,
    CATEGORY_PARTICLE,
    CATEGORY_PLAYER

} CATEGORY_Component;

enum ComponentIDs {
    SOUND = 0,
    TWEEN = 1,
    COLOR = 2,
    EXPIRE = 3,
    HEALTH = 4,
    VELOCITY = 5,
    COMPONENTS = 6
};

type (Entity)
{
    int Id;
    bool Active;
    bool _[3];
    char* Name;
    TYPE_Component Type;
    CATEGORY_Component Category;

    Transform* Transform;
    SoundComponent* Sound;
    TweenComponent* Tween;
    ColorComponent* Tint;
    ExpireComponent* Expires;
    HealthComponent* Health;
    VelocityComponent* Velocity;

    void* Components[COMPONENTS];
};

method bool Collides (Entity* self, Entity* other)
{
    return SDL_HasIntersection(&self->Transform->Bounds, &other->Transform->Bounds);

}


method SoundComponent* GetSound(Entity* self) {
    return self->Components[SOUND];
}
method TweenComponent* GetTween(Entity* self) {
    return self->Components[TWEEN];
}
method ColorComponent* GetColor(Entity* self) {
    return self->Components[COLOR];
}
method ExpireComponent* GetExpire(Entity* self) {
    return self->Components[EXPIRE];
}
method HealthComponent* GetHealth(Entity* self) {
    return self->Components[HEALTH];
}
method VelocityComponent* GetVelocity(Entity* self) {
    return self->Components[VELOCITY];
}

method void AddSound(Entity* self, SoundEffect value) {
    self->Components[SOUND] = new(SoundComponent, value);
}

method void AddTween(Entity* self, double min, double max, double speed, bool repeat, bool active) {
    self->Components[TWEEN] = new(TweenComponent, min, max, speed, repeat, active);
}

method void AddColor(Entity* self, int r, int g, int b, int a) {
    self->Components[COLOR] = new(ColorComponent, r, g, b, a);
}

method void AddExpire(Entity* self, double value) {
    self->Components[EXPIRE] = new(ExpireComponent, value);
}

method void AddHealth(Entity* self, int current, int maximum) {
    self->Components[HEALTH] = new(HealthComponent, current, maximum);
}

method void AddVelocity(Entity* self, int x, int y) {
    self->Components[VELOCITY] = new(VelocityComponent, x, y);
}
