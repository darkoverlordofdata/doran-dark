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

#include "GameObject.h"

#define IsBallObject(object) _Generic((object), BallObject*: true, default: false)
#define AsBallObject(object) _Generic((object),                          \
                            BallObject*: (BallObject *)object,           \
                            default: nullptr)


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
ivar (BallObject) {
    Class       isa;
    Vec2        Position;
    Vec2        Size;
    Vec2        Velocity;
    Vec3        Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    Texture2D*  Sprite;	
    char*       Name;

    float   Radius;
    bool    Stuck;
};

BallObject* NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
BallObject* BallObject_init(BallObject* this, Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
BallObject* BallObject_alloc();

/**
 * BallObject API
 */
char*   overload ToString(const BallObject* const);
void    overload Draw(BallObject* const, const SpriteRenderer*);
void    overload Move(BallObject* const, const GLfloat, const GLuint);
void    overload Reset(BallObject* const, const Vec2, const Vec2);


typedef char*   (*BallObjectToString)   (const BallObject* const);
typedef void    (*BallObjectDraw)       (BallObject* const, const SpriteRenderer*);
typedef void    (*BallObjectMove)       (BallObject* const, const GLfloat, const GLuint);
typedef void    (*BallObjectReset)      (BallObject* const, const Vec2, const Vec2);



vtable (BallObject) {
    BallObjectToString      ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    BallObjectDraw          Draw;
    BallObjectMove          Move;
    BallObjectReset         Reset;
};

class (BallObject) {
    BallObject*  (*Create) (Vec2, float, Vec2, Texture2D*);
};

