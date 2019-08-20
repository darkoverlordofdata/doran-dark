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

#define IsGameObject(object) _Generic((object), GameObject*: true, default: false)
#define AsGameObject(object) _Generic((object),                          \
                            GameObject*: (GameObject *)object,           \
                            default: nullptr)

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
/**
 * GameObject API
 */
// GameObject* GameObject_init(GameObject* const this, char* name, Vec2 Position, Vec2 Size, Texture2D* Sprite, Vec3 Color);
// GameObject* GameObject_alloc();
// GameObject* NewGameObject(char* name, Vec2 Position, Vec2 Size, Texture2D* Sprite, Vec3 Color);

interface (GameObject, ToString,    char*, (const GameObject* const));
interface (GameObject, Draw,        void, (GameObject* const, const SpriteRenderer*);


vtable (GameObject)
{
    GameObjectToString      ToString;
    ObjectEquals          Equals;
    ObjectGetHashCode     GetHashCode;
    ObjectDispose         Dispose;
    GameObjectDraw          Draw;
};

/**
 * Put it all together
 */
function vptr(GameObject);
/**
 * Class Loader callback
 */
function objc_loadGameObject(Class super) 
{
    Class cls = createClass(super, GameObject);
    addMethod(cls, GameObject, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, GameObject, Draw);
    return cls;
}

/**
 * Constructor
 * 
 * @param Position initial placement
 * @param Size sprite size
 * @param Sprite to display
 * @param Color tiniting color
 */
function GameObject* GameObject_init(
    GameObject* const this, 
    char* name, 
    Vec2 Position, 
    Vec2 Size, 
    Texture2D* Sprite, 
    Vec3 Color)
{
	Object_init(this);
    this->isa = getGameObjectIsa();
    this->IsSolid = false;
    this->Destroyed = false;
    this->Position = Position;
    this->Size = Size;
    this->Sprite = Sprite;
    this->Color = Color;
    this->Name = strdup(name);

    return this;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
method void Draw(
    GameObject* const this, 
    SpriteRenderer* renderer)
{
    Draw(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
method char* ToString(const GameObject* const this)
{
    return "GameObject";
} 


