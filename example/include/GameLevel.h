/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <GL/glew.h>
#include <tglm/tglm.h>
#include <dark/Foundation.h>

#include "Game.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

/**
 * BlockType tint color
 */
static const Vec3 COLOR0 = { 0.8f, 0.8f, 0.7f };
static const Vec3 COLOR1 = { 0.2f, 0.6f, 1.0f };
static const Vec3 COLOR2 = { 0.0f, 0.7f, 0.0f };
static const Vec3 COLOR3 = { 0.8f, 0.8f, 0.4f };
static const Vec3 COLOR4 = { 1.0f, 0.5f, 0.0f };
static const Vec3 COLOR5 = { 1.0f, 1.0f, 1.0f };

#define IsGameLevel(object) _Generic((object), GameLevel*: true, default: false)
#define AsGameLevel(object) _Generic((object),                          \
                            GameLevel*: (GameLevel *)object,            \
                            default: nullptr)


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
ivar (GameLevel)
{
    Class isa;
    DSArray* Bricks;
};
/**
 * GameLevel API
 */
GameLevel* NewGameLevel(const GLchar *file, int levelWidth, int levelHeight);
GameLevel* GameLevel_init(GameLevel* const this, const GLchar *file, int levelWidth, int levelHeight);
GameLevel* GameLevel_alloc();

char*       overload ToString(const GameLevel*);
GameLevel*  overload Load(GameLevel*, const GLchar*, int, int);
void        overload Draw(GameLevel* const, SpriteRenderer*);
bool        overload IsCompleted(GameLevel*);

typedef char*       (*GameLevelToString)    (const GameLevel* const);
typedef GameLevel*  (*GameLevelLoad)        (GameLevel*, const GLchar*, int, int);
typedef void        (*GameLevelDraw)        (GameLevel* const, SpriteRenderer* renderer);
typedef bool        (*GameLevelIsCompleted) (GameLevel*);
typedef void        (*GameLevelinit)        (GameLevel *const, DSArray*, GLuint, GLuint);

vtable (GameLevel)
{
    GameLevelToString       ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    GameLevelLoad           Load;
    GameLevelDraw           Draw;
    GameLevelIsCompleted    IsCompleted;
};

/** private */
static 
void        init(GameLevel *const this, DSArray*, GLuint, GLuint);

