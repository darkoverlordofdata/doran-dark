/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <Game.h>
#include <implementation/Game.h>
/** Defines a Collision Result Tuple */
ivar (Collision) 
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
Collision* CollisionTuple(bool isTrue, Direction dir, Vec2 vec)
{
    Collision* this = DSmalloc(sizeof(Collision));
    this->first = isTrue;
    this->second = dir;
    this->third = vec;
    return this;
}

/**
 * Create Game instance
 * 
 * @param Width of screen
 * @param Height of screen
 * 
 */
Game* Game_init(
    Game* const this, 
    int Width, 
    int Height)
{
	DSObject_init(this);
    this->isa = getGameIsa();
    // DSArray_init()
    this->Levels = new(DSArray, 4);
    this->Level = 0;
    this->State = GAME_ACTIVE;
    this->Width = Width;
    this->Height = Height;
    return this;
}

const Vec2 ZERO = { 0, 0 };
const Vec3 WHITE = { 1, 1, 1 };

// Game-related State data
static SpriteRenderer* Renderer;
static GameObject* Player;
static BallObject* Ball;


overload void SetKey(Game* this, int key, bool value)
{
    this->Keys[key] = value;
}

overload void SetState(Game* this, GameState state)
{
    this->State = state;
}

/**
 * Start the game
 */
overload void Start(Game* this)
{
   // Load shaders
    $ResourceManager.LoadShader("shaders/sprite.vs", "shaders/sprite.frag", "sprite");
    // Configure shaders
    Mat projection = glm_ortho(0, (GLfloat)this->Width, (GLfloat)this->Height, 0, -1, 1);
    Shader* shader = $ResourceManager.GetShader("sprite");
    Use(shader);
    SetInteger(shader, "sprite", 0);
    SetMatrix4(shader, "projection", &projection);
 
    // Load textures
    $ResourceManager.LoadTexture("textures/block.png", false, "block");
    $ResourceManager.LoadTexture("textures/background.jpg", false, "background");
    $ResourceManager.LoadTexture("textures/block.png", false, "block");
    $ResourceManager.LoadTexture("textures/block_solid.png", false, "block_solid");
    $ResourceManager.LoadTexture("textures/awesomeface.png", true, "face");
    $ResourceManager.LoadTexture("textures/paddle.png", true, "paddle");
    // Set render-specific controls
    Renderer = new(SpriteRenderer, $ResourceManager.GetShader("sprite"));
    // Load levels

    Add(this->Levels, new (GameLevel, "levels/one.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, new (GameLevel, "levels/two.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, new (GameLevel, "levels/three.lvl", this->Width, this->Height * 0.5));
    Add(this->Levels, new (GameLevel, "levels/four.lvl", this->Width, this->Height * 0.5));

    // Configure game objects
    Vec2 playerPos = (Vec2){ this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y };
    Player = new(GameObject, "player", playerPos, PLAYER_SIZE, $ResourceManager.GetTexture("paddle"), WHITE);
    Vec2 ballPos = playerPos + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 };
    Ball = new(BallObject, ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, $ResourceManager.GetTexture("face"));
}

/**
 * Update
 * 
 * @param dt deltat time
 */
overload void Update(Game* this, GLfloat dt)
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
    DScollect();
}


/**
 * ProcessInput
 * 
 * @param dt deltat time
 */
overload void ProcessInput(Game* this, GLfloat dt)
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
overload void Render(Game* this)
{
    if (this->State == GAME_ACTIVE)
    {
        // Draw background
        Vec2 size = { this->Width, this->Height };
        Draw(Renderer, $ResourceManager.GetTexture("background"), ZERO, size, 0.0f, WHITE);
        GameLevel* level = Get(this->Levels, this->Level);
        Draw(level, Renderer);
        Draw(Player, Renderer);
        Draw(Ball, Renderer);
    }
}

/**
 * ResetLevel
 * 
 */
overload void ResetLevel(Game* this)
{
    if (this->Level == 0) {
        GameLevel* level = this->Levels->data[0];
        Load(level, "levels/one.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 1)
    {
        GameLevel* level = this->Levels->data[1];
        Load(level, "levels/two.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 2)
    {
        GameLevel* level = this->Levels->data[2];
        Load(level, "levels/three.lvl", this->Width, this->Height * 0.5f);
    }
    else if (this->Level == 3)
    {
        GameLevel* level = this->Levels->data[3];
        Load(level, "levels/four.lvl", this->Width, this->Height * 0.5f);
    }
}

/**
 * ResetPlayer
 * 
 */
overload void ResetPlayer(Game* this)
{
    Player->Size = PLAYER_SIZE;
    Player->Position = (Vec2){ this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y };
    Reset(Ball, Player->Position + (Vec2){ PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2) }, INITIAL_BALL_VELOCITY);
}

/**
 * Release game resources
 */
overload void Dispose(Game* this)
{
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
static GLboolean CheckCollision2(Game* this, GameObject* one, GameObject* two) // AABB - AABB collision
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
static Collision* CheckCollision(
    Game* this, 
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

    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
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
overload void DoCollisions(Game* this)
{
    GameLevel* level = *(this->Levels[this->Level].data);
    DSArray* bricks = level->Bricks;
    
    for (int i=0; i<Length(bricks); i++)
    {
        GameObject* box = Get(bricks, i);
        // TGameObject box = bricks->data[i];

        if (!box->Destroyed)
        {
            Collision* collision = CheckCollision(this, Ball, box);
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
    Collision* result = CheckCollision(this, Ball, Player);
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
overload char* ToString(const Game* const this)
{
    return "Game";
}

