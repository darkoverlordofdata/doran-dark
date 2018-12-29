/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <GameLevel.h>

/**
 * GameLevel
 */
GameLevel* GameLevel_Ctor(
    GameLevel* const this, 
    const GLchar *file, 
    int levelWidth, 
    int levelHeight)
{
	DSObject_Ctor(this);
    this->isa = isa(GameLevel);
    this->Bricks = $DSArray(200);
    Load(this, file, levelWidth, levelHeight);
    return this;
}

/**
 * Load 
 * 
 * @oaram file  text file with level data
 * @param levelWidth of level in tiles
 * @param levelHeight of level in tiles
 * 
 */
GameLevel* overload Load(
    GameLevel* const this, 
    const GLchar *file, 
    int levelWidth, 
    int levelHeight)
{
    // Clear old data
    Clear(this->Bricks);
    // Load from file
    GLuint tileCode;
    GameLevel* level;
   
    char* path = join("assets/", file);
    char* line;
    FILE* fstream = fopen(path, "r");
    DSArray* tileData = $DSArray(20);
    DSArray* row = $DSArray(20);
    int i;
    char c;
    if (fstream)
    {
        while (fscanf(fstream, "%d%c", &i, &c) != EOF)
        {
            Add(row, (Any)i);
            if (c == '\n')
            {
                Add(tileData, (Any)row);
                row = $DSArray(20);
            }
        }

        if (Length(tileData) > 0) {
            init(this, tileData, levelWidth, levelHeight);
        }
    }
    return this;
}

/**
 * Draw
 * 
 * @param renderer to use
 * 
 */
void overload Draw(
    GameLevel* const this, 
    SpriteRenderer* renderer)
{
    for (int i = 0; i < Length(this->Bricks); i++)
    {
        GameObject* tile = this->Bricks->data[i];
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
bool overload IsCompleted(GameLevel* const this)
{
    for (int i = 0; i < Length(this->Bricks); i++)
    {
        GameObject* tile = this->Bricks->data[i];
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
static void init(
    GameLevel* const this, 
    DSArray* tileData, 
    GLuint levelWidth, 
    GLuint levelHeight)
{
    // Calculate dimensions
    GLuint height = Length(tileData);
    DSArray* row = tileData->data[0];
    GLuint width = Length(row); // Note we can index vector at [0] since this function is only called if height > 0
    GLfloat unit_width = levelWidth / (GLfloat)width, unit_height = levelHeight / height; 
    // Initialize level tiles based on tileData		
    printf("(%d,%d)\n", height, width);
    for (GLuint y = 0; y < height; ++y)
    {
        for (GLuint x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            DSArray* row = tileData->data[y];
            int blockType = (int)(row->data[x]);

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
                struct Texture2D *tex = Resources->GetTexture("block_solid");
                GameObject* obj = $GameObject("tile", pos, size, tex, color);
                obj->IsSolid = true;
                Add(this->Bricks, obj);
            }
            else if (blockType > 1)	// Non-solid; now determine its color based on level data
            {
                struct Texture2D *tex = Resources->GetTexture("block");
                GameObject* obj = $GameObject("tile", pos, size, tex, color);
                Add(this->Bricks, obj);
            }
        }
    }
}

/**
 * ToString
 */
char* overload ToString(GameLevel* const this)
{
    return "GameLevel";
}

GameLevel* $GameLevel(
    const GLchar *file, 
    int levelWidth, 
    int levelHeight) { 
    return GameLevel_Ctor(new(GameLevel), file, levelWidth, levelHeight); 
}
/**
 * Register the GameLevel Class runtime Metadata
 */
register (GameLevel)
{
    if (GameLevelClass.isa == nullptr) {
        GameLevelClass = (struct GameLevelClass) {
            .isa            = &GameLevelClass,
            .superclass     = &DSObjectClass,
            .name           = "GameLevel",
            .Create         = $GameLevel,
            .ToString       = ToString,
            .Equals         = DSObjectClass.Equals,
            .GetHashCode    = DSObjectClass.GetHashCode,
            .Dispose        = DSObjectClass.Dispose,
            .ReferenceEquals= DSObjectClass.ReferenceEquals,
            .InstanceEquals = DSObjectClass.InstanceEquals,
            .Load           = Load,
            .Draw           = Draw,
            .IsCompleted    = IsCompleted,
        };
        AddMetadata(GameLevelClass);
    }
    return &GameLevelClass;
}

