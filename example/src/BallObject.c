/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <BallObject.h>
/**
 * BallObject
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
struct BallObject *BallObject_Ctor(
    struct BallObject *this, 
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    struct Texture2D *Sprite)
{
    Radius = Radius != 0 ? Radius : 12.5f;
    GameObject_Ctor(this, "ball", Position, (Vec2){ Radius*2, Radius*2 }, Sprite, (Vec3){ 1, 1, 1 });
    this->isa = isa(BallObject);
    this->Velocity = Velocity;
    this->Radius = Radius;
    return this;
}


/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
void overload Draw(struct BallObject * const this, TSpriteRenderer renderer)
{
    DrawSprite(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}


/**
 * Move
 * 
 * @param dt delta time
 * @param window_width
 * @returns Vec2 new position
 */
void overload Move(struct BallObject * this, GLfloat dt, GLuint window_width)
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
void overload Reset(struct BallObject * const this, Vec2 position, Vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}

/**
 * ToString
 */
char* overload ToString(struct BallObject * const this)
{
    return "BallObject";
}

/**
 * Create new instance
 * 
 * @param Position initial placement of ball 
 * @param Radius size of ball
 * @param Velocity initial speed of ball
 * @param Sprite to display
 */
static struct BallObject* Create(
    Vec2 Position, 
    float Radius, 
    Vec2 Velocity, 
    struct Texture2D *Sprite) {
    return BallObject_Ctor(new(BallObject), Position, Radius, Velocity, Sprite); 
}

/**
 * BallObject Class Metadata
 */
register (BallObject)
{
    if (BallObject.isa == nullptr) {
        BallObject = (struct BallObjectClass) {
            .isa            = &BallObject,
            .superclass     = &GameObject,
            .name           = "BallObject",
            .ToString       = ToString,
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .Move           = Move,
            .Reset          = Reset,
            .Draw           = Draw,
            .Create         = Create,
        };
        AddMetadata(BallObject);
    }
    return &BallObject;
}
