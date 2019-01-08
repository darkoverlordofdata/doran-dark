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

#define IsBallObject(x) (x->isa == &$BallObject)
#define AsBallObject(x) (IsBallObject(x) ? (BallObject*)x : nullptr)

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

typedef char*   (*BallObjectToString)  (const BallObject* const);
typedef void    (*BallObjectDraw)  (BallObject* const, SpriteRenderer*);


class (BallObject) {
    BallObject*  (*Create) (Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
};

vtable (BallObject) {
    char*   (*ToString) (const BallObject* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    void    (*Draw) (BallObject* const, SpriteRenderer* renderer);

    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    void    (*Move)         (BallObject* const, const GLfloat dt, const GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void    (*Reset)        (BallObject* const, const Vec2 position, const Vec2 velocity);
    
};

/**
 * BallObject API
 */
void overload Draw(BallObject* const, SpriteRenderer* renderer);
void overload Move(BallObject* const, const GLfloat dt, const GLuint window_width);
void overload Reset(BallObject*, const Vec2 position, const Vec2 velocity);
char* overload ToString(const BallObject* const this);
BallObject* NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
BallObject* BallObject_alloc();
BallObject* BallObject_init(BallObject* this, Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
