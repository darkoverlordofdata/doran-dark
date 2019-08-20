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

#include "GameLevel.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "BallObject.h"

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
type (Game) {
    Class isa;
    GameState State;	
    bool Keys[1024];
    GLuint Width;
    GLuint Height;
    Array* Levels; 
    GLuint Level;    
};    
/**
 * Game API
 */
// Game* NewGame(int Width, int Height);
// Game* Game_alloc();
// Game* Game_init(Game* const self, int, int);

interface (Game, ToString,      char*, (const Game* const));
interface (Game, Start,         void, (Game* const));
interface (Game, ProcessInput,  void, (Game* const, GLfloat dt));
interface (Game, Update,        void, (Game* const, GLfloat dt));
interface (Game, Render,        void, (Game* const));
interface (Game, DoCollisions,  void, (Game* const));
interface (Game, ResetLevel,    void, (Game* const));
interface (Game, ResetPlayer,   void, (Game* const));
interface (Game, SetKey,        void, (Game* const, int key, bool value));
interface (Game, SetState,      void, (Game* const, GameState state));


/**
 * Metadata for the Game class:
 * attributes, vtable, class members
 */
vtable (Game) {
    GameToString            ToString;
    ObjectEquals            Equals;
    ObjectGetHashCode       GetHashCode;
    ObjectDispose           Dispose;
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

/**
 * Put it all together
 */
function vptr(Game);
/**
 * Class Loader callback
 */
function Class objc_loadGame(Class super) 
{
    Class cls = createClass(super, Game);
    addMethod(cls, Game, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Object, Dispose);
    addMethod(cls, Game, Start);
    addMethod(cls, Game, ProcessInput); 
    addMethod(cls, Game, Update);
    addMethod(cls, Game, Render);
    addMethod(cls, Game, DoCollisions);
    addMethod(cls, Game, ResetLevel);
    addMethod(cls, Game, ResetPlayer);
    addMethod(cls, Game, SetKey);
    addMethod(cls, Game, SetState);

    return cls;
}

/** Defines a Collision Result Tuple */
type (Collision) 
{
    bool first;
    Direction second; 
    Vec2 third;
}; 
/**
 * Collision Result Tuple
 * 
 * @param isTrue collided?
 * @param dir direction from
 * @param Vec2 difference point
 */
function Collision* CollisionTuple(bool isTrue, Direction dir, Vec2 vec)
{
    Collision* self = (Collision*)DSmalloc(sizeof(Collision));
    self->first = isTrue;
    self->second = dir;
    self->third = vec;
    return self;
}

/**
 * Create Game instance
 * 
 * @param Width of screen
 * @param Height of screen
 * 
 */
function Game* Game_init(
    Game* const self, 
    int Width, 
    int Height)
{
    self->isa = objc_getClass("Game");
    self->Levels = new(Array, 4);
    self->Level = 0;
    self->State = GAME_ACTIVE;
    self->Width = Width;
    self->Height = Height;
    return self;
}

static const Vec2 ZERO = { 0, 0 };
static const Vec3 WHITE = { 1, 1, 1 };

// Game-related State data
static SpriteRenderer* Renderer;
static GameObject* Player;
static BallObject* Ball;


method void SetKey(Game* self, int key, bool value)
{
    self->Keys[key] = value;
}

method void SetState(Game* self, GameState state)
{
    self->State = state;
}

/**
 * Start the game
 */
method void Start(Game* self)
{
   // Load shaders
    $ResourceManager.LoadShader("shaders/sprite.vs", "shaders/sprite.frag", "sprite");
    // Configure shaders
    Mat projection = glm_ortho(0, (GLfloat)self->Width, (GLfloat)self->Height, 0, -1, 1);
    Shader* shader = $ResourceManager.GetShader("sprite");
    Use(shader);
    SetInteger(shader, "sprite", 0);
    SetMatrix4(shader, "projection", &projection);

    // Load textures
    $ResourceManager.LoadTexture("textures/block.png", false, "block");
    // $ResourceManager.LoadTexture("textures/block.png", false, "paddle");
    $ResourceManager.LoadTexture("textures/paddle.png", false, "paddle");
    $ResourceManager.LoadTexture("textures/block.png", false, "block");
    $ResourceManager.LoadTexture("textures/block_solid.png", false, "block_solid");
    $ResourceManager.LoadTexture("textures/awesomeface.png", false, "face");
    $ResourceManager.LoadTexture("textures/background.png", false, "background");
    // Set render-specific controls
    Renderer = new(SpriteRenderer, $ResourceManager.GetShader("sprite"));
    // Load levels
    Add(self->Levels, (Object*)new (GameLevel, "levels/one.lvl", self->Width, (self->Height * 0.5)));
    Add(self->Levels, (Object*)new (GameLevel, "levels/two.lvl", self->Width, self->Height * 0.5));
    Add(self->Levels, (Object*)new (GameLevel, "levels/three.lvl", self->Width, self->Height * 0.5));
    Add(self->Levels, (Object*)new (GameLevel, "levels/four.lvl", self->Width, self->Height * 0.5));

    // Configure game objects
    Vec2 playerPos = (Vec2){ self->Width / 2 - PLAYER_SIZE.x / 2, self->Height - PLAYER_SIZE.y };
    Player = new(GameObject, "player", playerPos, PLAYER_SIZE, $ResourceManager.GetTexture("paddle"), WHITE);
    Vec2 ballPos = playerPos + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 };
    Ball = new(BallObject, ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, $ResourceManager.GetTexture("face"));
}

/**
 * Update
 * 
 * @param dt deltat time
 */
method void Update(Game* self, GLfloat dt)
{
    // Update objects
    Move(Ball, dt, self->Width);
    // Check for collisions

    DoCollisions(self);
    // Check loss condition
    if (Ball->Position.x >= self->Height) // Did ball reach bottom edge?
    {
        ResetLevel(self);
        ResetPlayer(self);
    }
    DScollect();
}


/**
 * ProcessInput
 * 
 * @param dt deltat time
 */
method void ProcessInput(Game* self, GLfloat dt)
{
    if (self->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (self->Keys[GLFW_KEY_A] || self->Keys[GLFW_KEY_LEFT])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (self->Keys[GLFW_KEY_D] || self->Keys[GLFW_KEY_RIGHT])
        {
            if (Player->Position.x <= self->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (self->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

/**
 * Render
 * 
 */
method void Render(Game* self)
{
    if (self->State == GAME_ACTIVE)
    {
        // Draw background
        Vec2 size = { self->Width, self->Height };
        Draw(Renderer, $ResourceManager.GetTexture("background"), ZERO, size, 0.0f, WHITE);
        GameLevel* level = (GameLevel*)Get(self->Levels, self->Level);
        Draw(level, Renderer);
        Draw(Player, Renderer);
        Draw(Ball, Renderer);
    }
}

/**
 * ResetLevel
 * 
 */
method void ResetLevel(Game* self)
{
    if (self->Level == 0) {
        GameLevel* level = (GameLevel*)(self->Levels->data[0]);
        Load(level, "levels/one.lvl", self->Width, self->Height * 0.5f);
    }
    else if (self->Level == 1)
    {
        GameLevel* level = (GameLevel*)(self->Levels->data[1]);
        Load(level, "levels/two.lvl", self->Width, self->Height * 0.5f);
    }
    else if (self->Level == 2)
    {
        GameLevel* level = (GameLevel*)(self->Levels->data[2]);
        Load(level, "levels/three.lvl", self->Width, self->Height * 0.5f);
    }
    else if (self->Level == 3)
    {
        GameLevel* level = (GameLevel*)(self->Levels->data[3]);
        Load(level, "levels/four.lvl", self->Width, self->Height * 0.5f);
    }
}

/**
 * ResetPlayer
 * 
 */
method void ResetPlayer(Game* self)
{
    Player->Size = PLAYER_SIZE;
    Player->Position = (Vec2){ self->Width / 2 - PLAYER_SIZE.x / 2, self->Height - PLAYER_SIZE.y };
    Reset(Ball, Player->Position + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2) }, INITIAL_BALL_VELOCITY);
}

/**
 * Release game resources
 */
method void Dispose(Game* self)
{
}

//===============================================================//
// -------------------- C O L L I S I O N S -------------------- //
//===============================================================//

/**
 * Calculates which direction a vector is facing (N,E,S or W)
 * 
 */
function Direction ArrayDirection(Vec2 target)
{
    Vec2 compass[4] = {
        { 0.0f, 1.0f },	    // up
        { 1.0f, 0.0f },	    // right
        { 0.0f, -1.0f },	// down
        { -1.0f, 0.0f }	    // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    target = glm_normalize(target);        
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = glm_dot(target, compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}   

/**
 * CheckCollision2
 * 
 * @param one first game object to check
 * @param two second game object to check
 * 
 */
function GLboolean CheckCollision2(Game* self, GameObject* one, GameObject* two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one->Position.x + one->Size.x >= two->Position.x &&
        two->Position.x + two->Size.x >= one->Position.x;
    // Collision y-axis?
    bool collisionY = one->Position.y + one->Size.y >= two->Position.y &&
        two->Position.y + two->Size.y >= one->Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

/**
 * CheckCollision2
 * 
 * @param one first ball object to check
 * @param two second game object to check
 * 
 */
function Collision* CheckCollision(
    Game* self, 
    BallObject* one, 
    GameObject* two) // AABB - Circle collision
{
    // Get center point circle first 
    Vec2 center = { one->Position + one->Radius };
    // Calculate AABB info (center, half-extents)
    Vec2 aabb_half_extents = { two->Size.x / 2, two->Size.y / 2 };
    Vec2 aabb_center = { two->Position.x + aabb_half_extents.x, two->Position.y + aabb_half_extents.y };
    // Get difference vector between both centers
    Vec2 difference = center - aabb_center;

    Vec2 clamped = glm_clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Now that we know the the clamped values, add self to AABB_center and we get the value of box closest to circle
    Vec2 closest = aabb_center + clamped;
    // Now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;
    
    if (glm_length(difference) < one->Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return CollisionTuple(true, ArrayDirection(difference), difference);
    else
        return CollisionTuple(false, UP, (Vec2){ 0, 0 });
}


/**
 * DoCollisions
 * 
 */
method void DoCollisions(Game* self)
{
    GameLevel* level = (GameLevel*)(self->Levels[self->Level].data);
    Array* bricks = level->Bricks;
    
    for (int i=0; i<Length(bricks); i++)
    {
        GameObject* box = (GameObject*)Get(bricks, i);
        // TGameObject box = bricks->data[i];

        if (!box->Destroyed)
        {
            Collision* collision = CheckCollision(self, Ball, box);
            if (collision->first) // If collision is true
            {
                // Destroy block if not solid
                if (!box->IsSolid)
                    box->Destroyed = GL_TRUE;
                // Collision resolution
                Direction dir = collision->second;
                Vec2 diff_vector = collision->third;
                if (dir == LEFT || dir == RIGHT) // Horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration; // Move ball to right
                    else
                        Ball->Position.x -= penetration; // Move ball to left;
                }
                else // Vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - abs(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration; // Move ball bback up
                    else
                        Ball->Position.y += penetration; // Move ball back down
                }
            }
            // DSFree(collision);
        }    
    }
    // Also check collisions for player pad (unless stuck)
    Collision* result = CheckCollision(self, Ball, Player);
    if (!Ball->Stuck && result->first)
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        Vec2 oldVelocity = { Ball->Velocity.x, Ball->Velocity.y };
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm_normalize(Ball->Velocity) * glm_length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
    }
    // DSFree(result);
}

/**
 * ToString
 */
method char* ToString(const Game* const self)
{
    return "Game";
}

