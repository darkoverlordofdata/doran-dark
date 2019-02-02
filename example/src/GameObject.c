/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <GameObject.h>
#include <ResourceManager.h>
#include <implementation/GameObject.h>
/**
 * Constructor
 * 
 * @param Position initial placement
 * @param Size sprite size
 * @param Sprite to display
 * @param Color tiniting color
 */
GameObject* GameObject_init(
    GameObject* const this, 
    char* name, 
    Vec2 Position, 
    Vec2 Size, 
    Texture2D* Sprite, 
    Vec3 Color)
{
	DSObject_init(this);
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
overload void Draw(
    GameObject* const this, 
    SpriteRenderer* renderer)
{
    Draw(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
overload char* ToString(const GameObject* const this)
{
    return "GameObject";
} 


