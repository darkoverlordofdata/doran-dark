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
GameObject GameObject_New(char* name, Vec2 Position, Vec2 Size, Texture2D Sprite, Vec3 Color) {
    return GameObject_Ctor(new(GameObject), name, Position, Size, Sprite, Color);
}

GameObject GameObject_Ctor(GameObject const this, char* name, Vec2 Position, Vec2 Size, Texture2D Sprite, Vec3 Color)
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
    if (GameObjectClass.isa == nullptr) {
    GameObjectClass = (GameObjectClass_t) {
            .isa        = &GameObjectClass,
            .superclass = &ObjectClass,
            .name       = "GameObject",
            /** VTable */
            .ToString       = ToString,
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .Dispose        = ObjectClass.Dispose,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .Draw           = Draw,
        };
        AddMetadata(GameObject);
    }
    return &GameObjectClass;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
void overload Draw(GameObject const this, SpriteRenderer renderer)
{
    DrawSprite(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
const char* overload ToString(GameObject const this)
{
    return "GameObject";
} 

