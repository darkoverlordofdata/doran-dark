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

#include "Texture.h"
#include "SpriteRenderer.h"

#define IsGameObject(x) (x->isa == &GameObjectClass)
#define AsGameObject(x) (IsGameObject(x) ? (GameObject*)x : nullptr)

/** Default values */
static const Vec2 GAME_OBJECT_POSITION = { 0.0f, 0.0f };
static const Vec2 GAME_OBJECT_SIZE     = { 1.0f, 1.0f };
static const Vec2 GAME_OBJECT_VELOCITY = { 0.0f, 0.0f };
static const Vec3 GAME_OBJECT_COLOR    = { 1.0f, 1.0f, 1.0f };

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
ivar (GameObject)
{
    Class isa;
    Vec2        Position;
    Vec2        Size;
    Vec2        Velocity;
    Vec3        Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    Texture2D*  Sprite;	
    char*       Name;

};

typedef char*   (*GameObjectToString)  (const GameObject* const);
typedef void    (*GameObjectDraw)  (GameObject* const, SpriteRenderer*);

class (GameObject) {
    GameObject*  (*Create) (char* name, Vec2 Position, Vec2 Size, Texture2D* Sprite, Vec3 Color);
};

vtable (GameObject)
{
    char*   (*ToString) (const GameObject* const);
    bool    (*Equals)   (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose)  (DSObject* const);

    // Draw sprite
    void    (*Draw)     (GameObject* const, SpriteRenderer* renderer);
    
};

/**
 * GameObject API
 */
void overload Draw(GameObject*, SpriteRenderer* renderer);
char* overload ToString(const GameObject*);
GameObject* GameObject_init(GameObject* const this, char* name, Vec2 Position, Vec2 Size, Texture2D* Sprite, Vec3 Color);
GameObject* GameObject_alloc();
GameObject* NewGameObject(char* name, Vec2 Position, Vec2 Size, Texture2D* Sprite, Vec3 Color);

