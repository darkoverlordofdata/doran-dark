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
#define AsBallObject(object) _Generic((object),                         \
                            BallObject*: (BallObject *)object,          \
                            default: nullptr)


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
type (BallObject) {
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
/**
 * BallObject API
 */
interface (BallObject, ToString,    char*, (const BallObject* const));
interface (BallObject, Draw,        void, (BallObject* const, const SpriteRenderer*);
interface (BallObject, Move         void, (BallObject* const, const GLfloat, const GLuint);
interface (BallObject, Reset,       void, (BallObject* const, const Vec2, const Vec2);

// BallObject* NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
// BallObject* BallObject_init(BallObject* this, Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite);
// BallObject* BallObject_alloc();



vtable (BallObject) {
    const BallObjectToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const BallObjectDraw        Draw;
    const BallObjectMove        Move;
    const BallObjectReset       Reset;
};

/**
 * Put it all together
 */
function vptr(BallObject);
/**
 * Class Loader callback
 */
function objc_loadBallObject(Class super) 
{
    Class cls = createClass(super, BallObject);
    addMethod(cls, BallObject,  ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, BallObject,  Draw);
    addMethod(cls, BallObject,  Move);
    addMethod(cls, BallObject,  Reset);
    return cls;
}


/**
 * BallObject
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
function BallObject* BallObject_init(
    BallObject* this, 
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    Texture2D* Sprite)
{
    Radius = Radius != 0 ? Radius : 12.5f;
    GameObject_init(this, "ball", Position, (Vec2){ Radius*2, Radius*2 }, Sprite, (Vec3){ 1, 1, 1 });
    this->isa = getBallObjectIsa();
    this->Velocity = Velocity;
    this->Radius = Radius;
    return this;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
method void Draw(BallObject* const this, const SpriteRenderer* renderer)
{
    Draw(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}


/**
 * Move
 * 
 * @param dt delta time
 * @param window_width
 * @returns Vec2 new position
 */
method void Move(BallObject* const this, const GLfloat dt, const GLuint window_width)
{
    // If not stuck to player board
    if (!this->Stuck)
    {
        // Move the ball
        this->Position += this->Velocity * dt;
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
}

/**
 * Resets the ball to initial Stuck Position (if ball is outside window bounds)
 * 
 * @param position to reset to
 * @param velocity to reset to
 * 
 */
method void Reset(BallObject* const this, const Vec2 position, const Vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}

/**
 * ToString
 */
method char* ToString(const BallObject*  const this)
{
    return "BallObject";
}

