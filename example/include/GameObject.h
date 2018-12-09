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
    GameObjectClass_t* isa;
    Vec2        Position;
    Vec2        Size;
    Vec2        Velocity;
    Vec3        Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    Texture2D   Sprite;	
    char*       Name;

};

typedef struct GameObjectClass_t
{
        union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (GameObject const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
    // Draw sprite
    void        (*Draw)         (GameObject const, SpriteRenderer *renderer);
};

/**
 * GameObject API
 */
void overload Draw(GameObject, SpriteRenderer renderer);
const char* overload ToString(GameObject);
GameObject GameObject_New(char* name, Vec2 Position, Vec2 Size, Texture2D Sprite, Vec3 Color);
GameObject GameObject_Ctor(GameObject const this, char* name, Vec2 Position, Vec2 Size, Texture2D Sprite, Vec3 Color);

#endif GAMEOBJECT_H