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
#include "Texture.h"
#include "SpriteRenderer.h"


#define IsBallObject(object) _Generic((object), BallObject*: true, default: false)
#define AsBallObject(object) _Generic((object),                         \
                            BallObject*: (BallObject *)object,          \
                            default: nullptr)


// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
type (BallObject)  // extend GameObject
{
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
delegate (BallObject, New,      BallObject*, (BallObject* self, Vec2 Position, float Radius, Vec2 Velocity, Texture2D* Sprite));
delegate (BallObject, ToString, char*, (const BallObject* const));
delegate (BallObject, Draw,     void, (BallObject* const, const SpriteRenderer*));
delegate (BallObject, Move,     void, (BallObject* const, const GLfloat, const GLuint));
delegate (BallObject, Reset,    void, (BallObject* const, const Vec2, const Vec2));


vtable (BallObject) 
{
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
static inline vptr(BallObject);
/**
 * Class Loader callback
 */
static inline Class ClassLoadBallObject(Class base) 
{
    Class cls = createClass(base, BallObject);
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
method BallObject* New(
    BallObject* const self, 
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    Texture2D* Sprite)
{
    Radius = Radius != 0 ? Radius : 12.5f;
    extends(GameObject, "ball", Position, (Vec2){ Radius*2, Radius*2 }, Sprite, (Vec3){ 1, 1, 1 });
    set_isa(BallObject);
    self->Velocity = Velocity;
    self->Radius = Radius;
    return self;
}
/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
method void Draw(BallObject* const self, const SpriteRenderer* renderer)
{
    Draw(renderer, self->Sprite, self->Position, self->Size, self->Rotation, self->Color);
}


/**
 * Move
 * 
 * @param dt delta time
 * @param window_width
 * @returns Vec2 new position
 */
method void Move(BallObject* const self, const GLfloat dt, const GLuint window_width)
{
    // If not stuck to player board
    if (!self->Stuck)
    {
        // Move the ball
        self->Position += self->Velocity * dt;
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (self->Position.x <= 0.0f)
        {
            self->Velocity.x = -self->Velocity.x;
            self->Position.x = 0.0f;
        }
        else if (self->Position.x + self->Size.x >= window_width)
        {
            self->Velocity.x = -self->Velocity.x;
            self->Position.x = window_width - self->Size.x;
        }
        if (self->Position.y <= 0.0f)
        {
            self->Velocity.y = -self->Velocity.y;
            self->Position.y = 0.0f;
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
method void Reset(BallObject* const self, const Vec2 position, const Vec2 velocity)
{
    self->Position = position;
    self->Velocity = velocity;
    self->Stuck = true;
}

/**
 * ToString
 */
method char* ToString(const BallObject*  const self)
{
    return "BallObject";
}

