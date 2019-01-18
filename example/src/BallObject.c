/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <BallObject.h>
#include "private/BallObject.h"
/**
 * Create new instance
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
BallObject* NewBallObject(
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    Texture2D* Sprite) {
    return BallObject_init(alloc(BallObject), Position, Radius, Velocity, Sprite); 
    // return BallObject_init(BallObject_alloc(), Position, Radius, Velocity, Sprite); 
}


/**
 * BallObject
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
BallObject* BallObject_init(
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

BallObject* BallObject_alloc() {
    return DSMalloc(getBallObjectSize());
}


/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
void overload Draw(BallObject* const this, const SpriteRenderer* renderer)
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
void overload Move(BallObject* const this, const GLfloat dt, const GLuint window_width)
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
void overload Reset(BallObject* const this, const Vec2 position, const Vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}

/**
 * ToString
 */
char* overload ToString(const BallObject*  const this)
{
    return "BallObject";
}

