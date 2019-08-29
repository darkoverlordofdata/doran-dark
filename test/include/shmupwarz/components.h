#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>
#include "types.h"


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

typedef enum EFFECT_Component {

    EFFECT_PEW,
    EFFECT_SMALLASPLODE,
    EFFECT_ASPLODE

} EFFECT_Component;


type (Color)
{
    int R;
    int G;
    int B;
    int A;
};

type (Health)
{
    int Current;
    int Maximum;
};

type (Tween)
{
    double Min;
    double Max;
    double Speed;
    bool Repeat;
    bool Active;
};

type (Sprite)
{
    Texture2D* Texture;
    int Width;
    int Height;
};

typedef enum OPTION_MASK 
{
    OPTION_SOUND    = 1,
    OPTION_TINT     = 2,
    OPTION_EXPIRES  = 4,
    OPTION_HEALTH   = 8,
    OPTION_TWEEN    = 16,
    OPTION_VELOCITY = 32
} OPTION_MASK;

type (Entity)
{
    int Id;
    bool Active;
    TYPE_Component Type;
    CATEGORY_Component Category;
    OPTION_MASK Optional;
    EFFECT_Component Sound;
    char* Name;
    Sprite Sprite;

    double Expires;
    Color Tint;
    Health Health;
    SDL_Rect Bounds;
    Tween Tween;
    Vec2 Velocity;
    Vec2 Position;
    Vec2 Scale;
};

