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
#include <dark/darkfx.h>

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

#define IsGameLevel(x) (x->isa == &GameLevelClass)
#define AsGameLevel(x) (IsGameLevel(x) ? (GameLevel*)x : nullptr)


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
ivar (GameLevel)
{
    Class isa;
    DSArray* Bricks;
};

typedef char*   (*GameLevelToString)  (const GameLevel* const);
typedef void   (*GameLevelDraw)  (GameLevel* const, SpriteRenderer* renderer);


class (GameLevel) {
    GameLevel*  (*Create) (const GLchar *file, int levelWidth, int levelHeight);
};

vtable (GameLevel)
{
    char*   (*ToString) (const GameLevel* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    // Loads level from file
    GameLevel*   (*Load)         (GameLevel* const, const GLchar *file, int levelWidth, int levelHeight);
    // Render level
    void        (*Draw)         (GameLevel* const, SpriteRenderer* renderer);
    // Check if the level is completed (all non-solid tiles are des troyed)
    bool        (*IsCompleted)  (GameLevel* const *);
    
};

/**
 * GameLevel API
 */
GameLevel* overload Load(GameLevel*, const GLchar *file, int levelWidth, int levelHeight);
void overload Draw(GameLevel* const, SpriteRenderer* renderer);
bool overload IsCompleted(GameLevel*);
char* overload ToString(const GameLevel*);
static void init(struct GameLevel *const this, DSArray* tileData, GLuint levelWidth, GLuint levelHeight);
GameLevel* NewGameLevel(const GLchar *file, int levelWidth, int levelHeight); 
GameLevel* GameLevel_init(GameLevel* const this, const GLchar *file, int levelWidth, int levelHeight);
GameLevel* GameLevel_alloc();
GameLevel* NewGameLevel(const GLchar *file, int levelWidth, int levelHeight);
