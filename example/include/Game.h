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
#include <GLFW/glfw3.h>
#include <dark/Foundation.h>
#include <tglm/tglm.h>

#include <GameLevel.h>
#include <ResourceManager.h>
#include <SpriteRenderer.h>
#include <GameObject.h>
#include <BallObject.h>

#define IsGame(object) _Generic((object), Game*: true, default: false)
#define AsGame(object) _Generic((object),                               \
                            Game*: (Game *)object,                      \
                            default: nullptr)


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
ivar (Game) {
    Class isa;
    GameState State;	
    bool Keys[1024];
    GLuint Width;
    GLuint Height;
    DSArray* Levels; 
    GLuint Level;    
};    
/**
 * Game API
 */
Game* NewGame(int Width, int Height);
Game* Game_alloc();
Game* Game_init(Game* const this, int, int);

char*   overload ToString(const Game* const);
void    overload Start(Game*);
void    overload Update(Game*, GLfloat dt);
void    overload ProcessInput(Game*, GLfloat dt);
void    overload Render(Game*);
void    overload ResetLevel(Game*);
void    overload ResetPlayer(Game*);
void    overload Dispose(Game*);
void    overload DoCollisions(Game*);
void    overload SetKey(Game* this, int key, bool value);
void    overload SetState(Game* this, GameState state);

typedef char*   (*GameToString)     (const Game* const);
typedef void    (*GameStart)        (Game* const);
typedef void    (*GameProcessInput) (Game* const, GLfloat dt);
typedef void    (*GameUpdate)       (Game* const, GLfloat dt);
typedef void    (*GameRender)       (Game* const);
typedef void    (*GameDoCollisions) (Game* const);
typedef void    (*GameResetLevel)   (Game* const);
typedef void    (*GameResetPlayer)  (Game* const);
typedef void    (*GameSetKey)       (Game* const, int key, bool value);
typedef void    (*GameSetState)     (Game* const, GameState state);
/**
 * Metadata for the Game class:
 * attributes, vtable, class members
 */
vtable (Game) {
    GameToString            ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    GameStart               Start;
    GameProcessInput        ProcessInput;
    GameUpdate              Update;
    GameRender              Render;
    GameDoCollisions        DoCollisions;
    GameResetLevel          ResetLevel;
    GameResetPlayer         ResetPlayer;
    GameSetKey              SetKey;
    GameSetState            SetState;
};

