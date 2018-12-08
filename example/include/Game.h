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
    GameClass_t* isa;
    GameState   State;	
    GLboolean   Keys[1024];
    GLuint  Width;
    GLuint  Height;
    Array   Levels; 
    GLuint  Level;    
};


typedef struct GameClass_t
{
    union {
        ObjectClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString) (Game const);
            bool        (*Equals) (Object const, Object const);
            int         (*GetHashCode) (Object const);
            void        (*Dispose) (Object const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
        };
    };
    // Initialize game state (load all shaders/textures/levels)
    void (*Start)           (Game const);
    // GameLoop
    void (*ProcessInput)    (Game const, GLfloat dt);
    void (*Update)          (Game const, GLfloat dt);
    void (*Render)          (Game const);
    void (*DoCollisions)    (Game const);
    // Reset
    void (*ResetLevel)      (Game const);
    void (*ResetPlayer)     (Game const);
};

/**
 * Game API
 */
void overload Start(Game);
void overload Update(Game, GLfloat dt);
void overload ProcessInput(Game, GLfloat dt);
void overload Render(Game);
void overload ResetLevel(Game);
void overload ResetPlayer(Game);
void overload Dispose(Game);
void overload DoCollisions(Game);
const char* overload ToString(Game const);
Game Game_New(int Width, int Height);

#endif GAME_H