/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <GL/glew.h>
#include <glm/glm.h>
#include <dark/darkfx.h>

#include "GameObject.h"

#define IsBallObject(x) (x->isa == &BallObject)
#define AsBallObject(x) (IsBallObject(x) ? (struct BallObject *)x : nullptr)


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class (BallObject) 
{
    union {
        struct GameObject  base;
        struct 
        {
            struct BallObjectClass * isa;
            Vec2        Position;
            Vec2        Size;
            Vec2        Velocity;
            Vec3        Color;
            GLfloat     Rotation;
            GLboolean   IsSolid;
            GLboolean   Destroyed;
            TTexture2D  Sprite;	
            char*       Name;
        };
    };
    float   Radius;
    bool    Stuck;
};

struct BallObjectClass
{
    union {
        struct GameObjectClass base; //  superclass
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TBallObject const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
            TBallObject  (*Create) (Vec2 Position, float Radius, Vec2 Velocity, TTexture2D Sprite);
            void    (*Draw) (TBallObject const, TSpriteRenderer renderer);
        };
    };
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    void    (*Move)         (TBallObject const, GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void    (*Reset)        (TBallObject const, Vec2 position, Vec2 velocity);
};

/**
 * BallObject API
 */
void overload Move(TBallObject, GLfloat dt, GLuint window_width);
void overload Reset(TBallObject, Vec2 position, Vec2 velocity);
char* overload ToString(TBallObject const this);
TBallObject BallObject_New(Vec2 Position, float Radius, Vec2 Velocity, TTexture2D Sprite);
TBallObject BallObject_Ctor(TBallObject this, Vec2 Position, float Radius, Vec2 Velocity, TTexture2D Sprite);
#endif BALLOBJECT_H

