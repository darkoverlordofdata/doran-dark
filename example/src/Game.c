/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Game.h>
#include <ResourceManager.h>
#include <SpriteRenderer.h>
#include <GameObject.h>
#include <BallObject.h>

const Vec2 ZERO = { 0, 0 };
const Vec3 WHITE = { 1, 1, 1 };

// Game-related State data
TSpriteRenderer  Renderer;
TGameObject      Player;
TBallObject      Ball;

// Defines a Collision Result Tuple
class (Collision) 
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
static const TCollision Collision_Ctor(TCollision this, bool isTrue, Direction dir, Vec2 vec)
{
    this->first = isTrue;
    this->second = dir;
    this->third = vec;
    return this;
}

TCollision New_Collision(bool first, Direction second, Vec2 third)
{
    return Collision_Ctor(new(Collision), first, second, third);
}

/**
 * Constructor
 * 
 * @param Width of screen
 * @param Height of screen
 * 
 */
TGame Game_New(int Width, int Height) {
    return Game_Ctor(new(Game), Width, Height);
}

TGame Game_Ctor(TGame const this, int Width, int Height)
{
	Object_Ctor(this);
    this->isa = isa(Game);
    this->Levels = Array.Create(4);
    this->Level = 0;
    this->State = GAME_ACTIVE;
    this->Width = Width;
    this->Height = Height;

    return this;
}

/**
 * Game Class Metadata
 */
register (Game)
{
    if (Game.isa == nullptr) {
        Game = (struct GameClass) {
            .isa        = &Game,
            .superclass = &Object,
            .name       = "Game",
            /** VTable */
            .ToString       = ToString,
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            .Start          = Start,
            .ProcessInput   = ProcessInput,
            .Update         = Update,
            .Render         = Render,
            .DoCollisions   = DoCollisions,
            .ResetLevel     = ResetLevel,
            .ResetPlayer    = ResetPlayer,
            .Create         = Game_New,
        };
        AddMetadata(Game);
    }
    return &Game;
}


/**
 * Start the game
 */
void overload Start(TGame this)
{
    if (ResourceManager.Shaders == nullptr) 
        IsaResourceManager();
        
    // Load shaders
    ResourceManager.LoadShader("shaders/sprite.vs", "shaders/sprite.frag", "sprite");
    // Configure shaders
    Mat projection = ortho(0, (GLfloat)this->Width, (GLfloat)this->Height, 0, -1, 1);
    TShader shader = ResourceManager.GetShader("sprite");
    Use(shader);
    SetInteger(shader, "sprite", 0);
    SetMatrix4(shader, "projection", &projection);
 
    // Load textures
    ResourceManager.LoadTexture("textures/block.png", false, "block");
    ResourceManager.LoadTexture("textures/background.jpg", false, "background");
    ResourceManager.LoadTexture("textures/block.png", false, "block");
    ResourceManager.LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager.LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager.LoadTexture("textures/paddle.png", true, "paddle");
    // Set render-specific controls
    Renderer = SpriteRenderer.Create(ResourceManager.GetShader("sprite"));
    // Load levels

    Add(this->Levels, GameLevel.Create("levels/one.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, GameLevel.Create("levels/two.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, GameLevel.Create("levels/three.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, GameLevel.Create("levels/four.lvl", this->Width, this->Height * 0.5));
    this->Level = 0;


    // Configure game objects
    Vec2 playerPos = (Vec2){ this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y };
    Player = GameObject.Create("player", playerPos, PLAYER_SIZE, ResourceManager.GetTexture("paddle"), WHITE);
    Vec2 ballPos = playerPos + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 };
    Ball = BallObject.Create(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager.GetTexture("face"));
}

/**
 * Update
 * 
 * @param dt deltat time
 */
void overload Update(TGame this, GLfloat dt)
{
    // Update objects
    Move(Ball, dt, this->Width);
    // Check for collisions

    DoCollisions(this);
    // Check loss condition
    if (Ball->Position.x >= this->Height) // Did ball reach bottom edge?
    {
        ResetLevel(this);
        ResetPlayer(this);
    }
}


/**
 * ProcessInput
 * 
 * @param dt deltat time
 */
void overload ProcessInput(TGame this, GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

/**
 * Render
 * 
 */
void overload Render(TGame this)
{
    if (this->State == GAME_ACTIVE)
    {
        // Draw background
        Vec2 size = { this->Width, this->Height };
        DrawSprite(Renderer, ResourceManager.GetTexture("background"), ZERO, size, 0.0f, WHITE);
        // Draw level
        TGameLevel level = this->Levels->data[this->Level];
        Draw(level, Renderer);
        // Draw player
        Draw(Player, Renderer);
        // Draw ball
        Draw((TGameObject)Ball, Renderer);
    }
}

/**
 * ResetLevel
 * 
 */
void overload ResetLevel(TGame this)
{
    if (this->Level == 0) {
        TGameLevel level = this->Levels->data[0];
        Load(level, "levels/one.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 1)
    {
        TGameLevel level = this->Levels->data[1];
        Load(level, "levels/two.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 2)
    {
        TGameLevel level = this->Levels->data[2];
        Load(level, "levels/three.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 3)
    {
        TGameLevel level = this->Levels->data[3];
        Load(level, "levels/four.lvl", this->Width, this->Height * 0.5f);
    }
}

/**
 * ResetPlayer
 * 
 */
void overload ResetPlayer(TGame this)
{
    Player->Size = PLAYER_SIZE;
    Player->Position = (Vec2){ this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y };
    Reset(Ball, Player->Position + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2) }, INITIAL_BALL_VELOCITY);
}

/**
 * Release game resources
 */
void overload Dispose(TGame this)
{
    // tgc_free(&gc, Renderer);
    // tgc_free(&gc, Player);
    // tgc_free(&gc, Ball);
}

//===============================================================//
// -------------------- C O L L I S I O N S -------------------- //
//===============================================================//

/**
 * Calculates which direction a vector is facing (N,E,S or W)
 * 
 */
static Direction ArrayDirection(Vec2 target)
{
    Vec2 compass[4] = {
        { 0.0f, 1.0f },	    // up
        { 1.0f, 0.0f },	    // right
        { 0.0f, -1.0f },	// down
        { -1.0f, 0.0f }	    // left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    target = normalize(target);        
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = dot(target, compass[i]);
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
static GLboolean CheckCollision2(TGame this, TGameObject one, TGameObject two) // AABB - AABB collision
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
static TCollision CheckCollision(TGame this, TBallObject one, TGameObject two) // AABB - Circle collision
{
    // Get center point circle first 
    Vec2 center = { one->Position + one->Radius };
    // Calculate AABB info (center, half-extents)
    Vec2 aabb_half_extents = { two->Size.x / 2, two->Size.y / 2 };
    Vec2 aabb_center = { two->Position.x + aabb_half_extents.x, two->Position.y + aabb_half_extents.y };
    // Get difference vector between both centers
    Vec2 difference = center - aabb_center;

    Vec2 clamped = clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    Vec2 closest = aabb_center + clamped;
    // Now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;
    
    if (length(difference) < one->Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return New_Collision(true, ArrayDirection(difference), difference);
    else
        return New_Collision(false, UP, (Vec2){ 0, 0 });
}


/**
 * DoCollisions
 * 
 */
void overload DoCollisions(TGame this)
{
    TGameLevel level = *(this->Levels[this->Level].data);
    TArray bricks = level->Bricks;
    
    for (int i=0; i<Length(bricks); i++)
    {
        TGameObject box = bricks->data[i];

        if (!box->Destroyed)
        {
            TCollision collision = CheckCollision(this, Ball, box);
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
            delete(collision);
        }    
    }
    // Also check collisions for player pad (unless stuck)
    TCollision result = CheckCollision(this, Ball, Player);
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
        Ball->Velocity = normalize(Ball->Velocity) * length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
    }
    delete(result);
}

/**
 * ToString
 */
char* overload ToString(TGame const this)
{
    return "Game";
}

