/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <dark/darkfx.h>
#include <glm/glm.h>

#include "GameLevel.h"
#include "ResourceManager.h"

// Represents the current state of the game
typedef enum  {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
} GameState;

// Represents the four possible (collision) directions
typedef enum  {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;


// Initial size of the player paddle
static const Vec2 PLAYER_SIZE = { 100, 20 };
// Initial velocity of the player paddle
static const GLfloat PLAYER_VELOCITY = 500.0f;
// Initial velocity of the Ball
static const Vec2 INITIAL_BALL_VELOCITY = { 100.0f, -350.0f };
// Radius of the ball object
static const GLfloat BALL_RADIUS = 12.5f;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class (Game)
{
    struct GameClass * isa;
    GameState   State;	
    GLboolean   Keys[1024];
    GLuint  Width;
    GLuint  Height;
    struct Array * Levels; 
    GLuint  Level;    
};


struct GameClass
{
    union {
        struct ObjectClass base;
        struct 
        {
            struct  Class * isa;
            struct  Class * superclass;
            char*   name;
            char*   (*ToString) (TGame const);
            bool    (*Equals) (TObject const, TObject const);
            int     (*GetHashCode) (TObject const);
            void    (*Dispose) (TObject const);
            bool    (*ReferenceEquals) (TObject const objA, TObject const objB);
            bool    (*InstanceEquals) (TObject const objA, TObject const objB);
        };
    };
    // Initialize game state (load all shaders/textures/levels)
    void (*Start)           (TGame const);
    // GameLoop
    void (*ProcessInput)    (TGame const, GLfloat dt);
    void (*Update)          (TGame const, GLfloat dt);
    void (*Render)          (TGame const);
    void (*DoCollisions)    (TGame const);
    // Reset
    void (*ResetLevel)      (TGame const);
    void (*ResetPlayer)     (TGame const);
};

/**
 * Game API
 */
void overload Start(TGame);
void overload Update(TGame, GLfloat dt);
void overload ProcessInput(TGame, GLfloat dt);
void overload Render(TGame);
void overload ResetLevel(TGame);
void overload ResetPlayer(TGame);
void overload Dispose(TGame);
void overload DoCollisions(TGame);
char* overload ToString(TGame const);
TGame Game_New(int Width, int Height);
TGame Game_Ctor(TGame const this, int Width, int Height);

#endif GAME_H