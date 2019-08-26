/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <tglm/tglm.h>
#include <dark/Foundation.h>

// #include "Game.h"
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
type (GameLevel)
{
    Class isa;
    Array* Bricks;
};

/**
 * GameLevel
 */
delegate (GameLevel, New,           GameLevel*, (GameLevel* self, const GLchar *file, const int levelWidth, const int levelHeight));
delegate (GameLevel, ToString,      char*, (const GameLevel* const));
delegate (GameLevel, Load,          GameLevel* , (GameLevel*, const GLchar*, int, int));
delegate (GameLevel, Draw,          void, (GameLevel* const, SpriteRenderer* renderer));
delegate (GameLevel, IsCompleted,   bool, (GameLevel*));
delegate (GameLevel, init,          void, (GameLevel *const, Array*, GLuint, GLuint));


vtable (GameLevel)
{
    GameLevelToString       ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
    GameLevelLoad           Load;
    GameLevelDraw           Draw;
    GameLevelIsCompleted    IsCompleted;
};

/**
 * Put it all together
 */
static inline vptr(GameLevel);
/**
 * Class Loader callback
 */
static inline Class ClassLoadGameLevel(Class base) 
{
    Class cls = createClass(base, GameLevel);

    addMethod(cls, GameLevel, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);

    addMethod(cls, GameLevel, Load);
    addMethod(cls, GameLevel, Draw);
    addMethod(cls, GameLevel, IsCompleted);
    return cls;
}

/**
 * GameLevel
 */
method GameLevel* New(
    GameLevel* self, 
    const GLchar *file, 
    const int levelWidth, 
    const int levelHeight)
{
	extends(Object);
    set_isa(GameLevel);
    self->Bricks = new(Array, 200);
    Load(self, file, levelWidth, levelHeight);
    return self;
}




/**
 * Load 
 * 
 * @oaram file  text file with level data
 * @param levelWidth of level in tiles
 * @param levelHeight of level in tiles
 * 
 */
method GameLevel* Load(
    GameLevel* const self, 
    const GLchar *file, 
    int levelWidth, 
    int levelHeight)
{
    // Clear old data
    Clear(self->Bricks);
    // Load from file
    GLuint tileCode;
    GameLevel* level;
   
    char* path = join("assets/", file);
    char* line;
    FILE* fstream = fopen(path, "r");
    Array* tileData = new(Array, 20);
    Array* row = new(Array, 20);
    int i;
    char c;
    if (fstream)
    {
        while (fscanf(fstream, "%d%c", &i, &c) != EOF)
        {
            Add(row, (Object*)new(Integer, i));
            if (c == '\n')
            {
                Add(tileData, (Object*)row);
                row = new(Array, 20);
            }
        }

        if (Length(tileData) > 0) {
            init(self, tileData, levelWidth, levelHeight);
        }
    }
    return self;
}

/**
 * Draw
 * 
 * @param renderer to use
 * 
 */
method void Draw(
    GameLevel* const self, 
    SpriteRenderer* renderer)
{
    for (int i = 0; i < Length(self->Bricks); i++)
    {
        GameObject* tile = self->Bricks->data[i];
        if (!tile->Destroyed)
            Draw(tile, renderer);
    }
}

/**
 * IsCompleted
 * 
 * @returns true when complete
 * 
 */
method bool IsCompleted(GameLevel* const self)
{
    for (int i = 0; i < Length(self->Bricks); i++)
    {
        GameObject* tile = self->Bricks->data[i];
        if (tile->IsSolid && !tile->Destroyed)
            return false;
    }
    return true;
}


/**
 * init
 * 
 * @param tileData array of tiles
 * @param levelWidth of level in tiles
 * @param levelHeight of level in tiles
 *  
 */
method void init(
    GameLevel* const self, 
    Array* tileData, 
    GLuint levelWidth, 
    GLuint levelHeight)
{
    // Calculate dimensions
    GLuint height = Length(tileData);
    Array* row = tileData->data[0];
    GLuint width = Length(row); // Note we can index vector at [0] since self static inline is only called if height > 0
    GLfloat unit_width = levelWidth / (GLfloat)width, unit_height = levelHeight / height; 
    // Initialize level tiles based on tileData		
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            Array* row = tileData->data[y];
            int blockType = IntValue((Integer*)(row->data[x]));

            Vec2 pos = { unit_width * x, unit_height * y };
            Vec2 size = { unit_width, unit_height };
            Vec3 color = { };
            switch(blockType)
            {
                case 1: color = COLOR1; break;
                case 2: color = COLOR2; break;
                case 3: color = COLOR3; break;
                case 4: color = COLOR4; break;
                case 5: color = COLOR5; break;
                default: color = COLOR0;
            }
            
            if (blockType == 1) // Solid
            {
                struct Texture2D *tex = $ResourceManager.GetTexture("block_solid");
                GameObject* obj = new(GameObject, "tile", pos, size, tex, color);
                obj->IsSolid = true;
                Add(self->Bricks, (Object*)obj);
            }
            else if (blockType > 1)	// Non-solid; now determine its color based on level data
            {
                struct Texture2D *tex = $ResourceManager.GetTexture("block");
                GameObject* obj = new(GameObject, "tile", pos, size, tex, color);
                Add(self->Bricks, (Object*)obj);
            }
        }
    }
}

/**
 * ToString
 */
method char* ToString(const GameLevel* const self)
{
    return "GameLevel";
}

