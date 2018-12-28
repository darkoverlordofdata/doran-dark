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
class (GameLevel)
{
    struct GameLevelClass* isa;
    DSArray* Bricks;
};

struct GameLevelClass
{
    union {
        struct DSObjectClass base;
        struct 
        {
            Class*  isa;
            Class*  superclass;
            char*   name;
            char*   (*ToString) (GameLevel* const);
            bool    (*Equals) (DSObject* const, DSObject* const);
            int     (*GetHashCode) (DSObject* const);
            void    (*Dispose) (DSObject* const);
            bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
            bool    (*InstanceEquals) (DSObject* const, DSObject* const);
            GameLevel*  (*Create) (const GLchar *file, int levelWidth, int levelHeight);
        };
    };
    // Loads level from file
    GameLevel*   (*Load)         (GameLevel* const, const GLchar *file, int levelWidth, int levelHeight);
    // Render level
    void        (*Draw)         (GameLevel* const, SpriteRenderer* renderer);
    // Check if the level is completed (all non-solid tiles are des troyed)
    bool        (*IsCompleted)  (GameLevel* const *);
} GameLevelClass;

/**
 * GameLevel API
 */
GameLevel* overload Load(GameLevel*, const GLchar *file, int levelWidth, int levelHeight);
void overload Draw(GameLevel* const, SpriteRenderer* renderer);
bool overload IsCompleted(GameLevel*);
char* overload ToString(GameLevel*);
static void init(struct GameLevel *const this, DSArray* tileData, GLuint levelWidth, GLuint levelHeight);
GameLevel* $GameLevel(const GLchar *file, int levelWidth, int levelHeight); 

