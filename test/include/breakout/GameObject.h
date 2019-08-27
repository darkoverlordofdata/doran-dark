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
type (GameObject)
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
delegate (GameObject, New,      GameObject*, (GameObject*, char*, Vec2, Vec2, Texture2D*, Vec3));
delegate (GameObject, ToString, char*, (const GameObject* const));
delegate (GameObject, Draw,     void, (GameObject* const, const SpriteRenderer*));


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
static inline vptr(GameObject);
/**
 * Class Loader callback
 */
static inline Class ClassLoadGameObject(Class base) 
{
    Class cls = createClass(base, GameObject);
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
method GameObject* New(
    GameObject* self, 
    char* name, 
    Vec2 Position, 
    Vec2 Size, 
    Texture2D* Sprite, 
    Vec3 Color)
{
	New((Object*)self);
    self->isa = isa(GameObject);
    self->IsSolid = false;
    self->Destroyed = false;
    self->Position = Position;
    self->Size = Size;
    self->Sprite = Sprite;
    self->Color = Color;
    self->Name = strdup(name);

    return self;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
method void Draw(
    GameObject* const self, 
    const SpriteRenderer* renderer)
{
    Draw(renderer, self->Sprite, self->Position, self->Size, self->Rotation, self->Color);
}

/**
 * ToString
 */
method char* ToString(const GameObject* const self)
{
    return "GameObject";
} 


