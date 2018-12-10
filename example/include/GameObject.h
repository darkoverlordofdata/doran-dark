/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.h>
#include <dark/darkfx.h>

#include "Texture.h"
#include "SpriteRenderer.h"

#define IsGameObject(x) (x->isa == &GameObject)
#define AsGameObject(x) (IsGameObject(x) ? (struct GameObject *)x : nullptr)

/** Default values */
static const Vec2 GAME_OBJECT_POSITION = { 0.0f, 0.0f };
static const Vec2 GAME_OBJECT_SIZE     = { 1.0f, 1.0f };
static const Vec2 GAME_OBJECT_VELOCITY = { 0.0f, 0.0f };
static const Vec3 GAME_OBJECT_COLOR    = { 1.0f, 1.0f, 1.0f };

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class (GameObject)
{
    struct GameObjectClass * isa;
    Vec2        Position;
    Vec2        Size;
    Vec2        Velocity;
    Vec3        Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    struct Texture2D *  Sprite;	
    char*       Name;

};

struct GameObjectClass
{
        union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TGameObject const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TGameObject  (*Create) (char* name, Vec2 Position, Vec2 Size, TTexture2D Sprite, Vec3 Color);
        };
    };
    // Draw sprite
    void        (*Draw)         (TGameObject const, TSpriteRenderer renderer);
};

/**
 * GameObject API
 */
void overload Draw(TGameObject, TSpriteRenderer renderer);
char* overload ToString(TGameObject);
TGameObject GameObject_New(char* name, Vec2 Position, Vec2 Size, TTexture2D Sprite, Vec3 Color);
TGameObject GameObject_Ctor(TGameObject const this, char* name, Vec2 Position, Vec2 Size, TTexture2D Sprite, Vec3 Color);

#endif GAMEOBJECT_H

