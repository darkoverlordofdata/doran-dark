/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <GL/glew.h>
#include <glm/glm.h>
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


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
class (GameLevel)
{
    struct GameLevelClass * isa;
    struct Array * Bricks;
};

struct GameLevelClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TGameLevel const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
        };
    };
    // Loads level from file
    TGameLevel   (*Load)         (TGameLevel const, const GLchar *file, int levelWidth, int levelHeight);
    // Render level
    void        (*Draw)         (TGameLevel const, TSpriteRenderer renderer);
    // Check if the level is completed (all non-solid tiles are des troyed)
    bool        (*IsCompleted)  (TGameLevel const *);
};

/**
 * GameLevel API
 */
TGameLevel overload Load(TGameLevel, const GLchar *file, int levelWidth, int levelHeight);
void overload Draw(TGameLevel const, TSpriteRenderer renderer);
bool overload IsCompleted(TGameLevel);
char* overload ToString(TGameLevel);
TGameLevel GameLevel_New(const GLchar *file, int levelWidth, int levelHeight);
TGameLevel GameLevel_Ctor(TGameLevel const this, const GLchar *file, int levelWidth, int levelHeight);

#endif GAMELEVEL_H