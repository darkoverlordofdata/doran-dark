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

/**
 * Constructor
 * 
 * @param Position initial placement
 * @param Size sprite size
 * @param Sprite to display
 * @param Color tiniting color
 */
TGameObject GameObject_Ctor(TGameObject const this, char* name, Vec2 Position, Vec2 Size, TTexture2D Sprite, Vec3 Color)
{
	Object_Ctor(this);
    this->isa = isa(GameObject);
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
 * GameObject Class Metadata
 */
register (GameObject)
{
    if (GameObject.isa == nullptr) {
        GameObject = (struct GameObjectClass) {
            .isa        = &GameObject,
            .superclass = &Object,
            .name       = "GameObject",
            /** VTable */
            .ToString       = ToString,
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .Draw           = Draw,
            .Create         = ^(char* name, Vec2 Position, Vec2 Size, TTexture2D Sprite, Vec3 Color) { return GameObject_Ctor(new(GameObject), name, Position, Size, Sprite, Color);},
        };
        AddMetadata(GameObject);
    }
    return &GameObject;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
void overload Draw(TGameObject const this, TSpriteRenderer renderer)
{
    DrawSprite(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
char* overload ToString(TGameObject const this)
{
    return "GameObject";
} 

