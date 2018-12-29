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

#include "GameObject.h"

#define IsBallObject(x) (x->isa == &BallObjectClass)
#define AsBallObject(x) (IsBallObject(x) ? (BallObject*)x : nullptr)


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class (BallObject) 
{
    struct BallObjectClass* isa;
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


struct BallObjectClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    char*   (*ToString) (BallObject* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const objA, DSObject* const objB);
    bool    (*InstanceEquals) (DSObject* const objA, DSObject* const objB);
    BallObject*  (*Create) (Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
    void    (*Draw) (BallObject* const, SpriteRenderer* renderer);

    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    void    (*Move)         (BallObject* const, GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void    (*Reset)        (BallObject* const, Vec2 position, Vec2 velocity);
} BallObjectClass;

/**
 * BallObject API
 */
void overload Draw(BallObject*, SpriteRenderer* renderer);
void overload Move(BallObject*, GLfloat dt, GLuint window_width);
void overload Reset(BallObject*, Vec2 position, Vec2 velocity);
char* overload ToString(BallObject* const this);


