#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>
#include <tglm/tglm.h>

// 100,149,237,255
// #define bgd_r 0.392156f
// #define bgd_g 0.584313f
// #define bgd_b 0.929411f

#undef SUPER
#define SUPER Game
type (Shmupwarz)
{
    Class isa;
    SDL_Window *window;
    SDL_GLContext context;
    char* title;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    double delta;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;
    double factor;
    bool *keys;
    ResourceManager* resource;
    SpriteRenderer* spriteBatch;

    List* Bullets;
    List* Enenmies1;
    List* Enenmies2;
    List* Enenmies3;
    List* Explosions;
    List* Bangs;
    List* Particles;
    Array* Entities;

};

delegate (Shmupwarz, New,           Shmupwarz*, (Shmupwarz*, int, int));
delegate (Shmupwarz, ToString,      char*, (const Shmupwarz* const));
delegate (Shmupwarz, Dispose,       void, (const Shmupwarz* const));
delegate (Shmupwarz, Start,         void, (const Shmupwarz* const));
delegate (Shmupwarz, Run,           void, (const Shmupwarz* const));
delegate (Shmupwarz, Tick,          void, (const Shmupwarz* const));
delegate (Shmupwarz, HandleEvents,  void, (const Shmupwarz* const));
delegate (Shmupwarz, RunLoop,       void, (const Shmupwarz* const));
delegate (Shmupwarz, Draw,          void, (const Shmupwarz* const));
delegate (Shmupwarz, Update,        void, (const Shmupwarz* const));
delegate (Shmupwarz, Initialize,    void, (const Shmupwarz* const));
delegate (Shmupwarz, LoadContent,   void, (Shmupwarz* const));

/**
 * Shmupwarz vtable
 */
vtable (Shmupwarz) 
{
    const ShmupwarzToString     ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ShmupwarzDispose      Dispose;
    const ShmupwarzStart        Start;
    const ShmupwarzRun          Run;
    const ShmupwarzTick         Tick;
    const ShmupwarzHandleEvents HandleEvents;
    const ShmupwarzRunLoop      RunLoop;
    const ShmupwarzDraw         Draw;
    const ShmupwarzUpdate       Update;
    const ShmupwarzInitialize   Initialize;
    const ShmupwarzLoadContent  LoadContent;
};

/**
 * Put it all together
 */
static inline vptr(Shmupwarz);
/**
 * Class Loader callback
 */
static inline Class ClassLoadShmupwarz(Class base) 
{
    Class cls = createClass(base, Shmupwarz);
    addMethod(cls, Shmupwarz,   ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Shmupwarz,   Dispose);
    addMethod(cls, Shmupwarz,   Start);
    addMethod(cls, Shmupwarz,   Run);
    addMethod(cls, Shmupwarz,   Tick);
    addMethod(cls, Shmupwarz,   HandleEvents);
    addMethod(cls, Shmupwarz,   RunLoop);
    addMethod(cls, Shmupwarz,   Draw);
    addMethod(cls, Shmupwarz,   Update);
    addMethod(cls, Shmupwarz,   Initialize);
    addMethod(cls, Shmupwarz,   LoadContent);
    return cls;
}

/**
 * New Shmupwarz game
 * 
 * @param self
 * @param width
 * @param height
 */
method Shmupwarz* New(Shmupwarz* self, int width, int height)
{
	extends(Game, "Shmupwarz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    self->isa = isa(Shmupwarz);
    return self;
}

/**
 * Shmupwarz::ToString
 */
method char* ToString(const Shmupwarz* const self)
{
    static char* toStringCache;

    if (!toStringCache)
        toStringCache = DSsprintf("{ title: %s, width: %d. height: %d }", 
                                    self->title, self->width, self->height);

    return toStringCache;
}

/**
 * Shmupwarz::Dispose
 * 
 */
method void Dispose(const Shmupwarz* const self)
{
    Log("Shmuwarz dispose");
    super(Dispose);
}

/**
 * Shmupwarz::Start
 * 
 */
method void Start(const Shmupwarz* const self)
{
}

/**
 * Shmupwarz::Draw
 * 
 */
method void Draw(const Shmupwarz* const self)
{
    var sprite = GetTexture(self->resource, "background");
    Draw(self->spriteBatch, sprite, 
        (Vec2){ 0, 0 }, (Vec2){ sprite->Width, sprite->Height }, 0, (Vec3){ 1, 1, 1 });
}

/**
 * Shmupwarz::Update
 * 
 */
method void Update(const Shmupwarz* const self)
{
}

/**
 * Shmupwarz::Update
 * 
 */
method void Initialize(const Shmupwarz* const self)
{
    Log("Initialize");
}
/**
 * Shmupwarz::Update
 * 
 */
method void LoadContent(Shmupwarz* const self)
{
    // Load shaders
    LoadShader(self->resource, "assets/shaders/sprite.vs", "assets/shaders/sprite.frag", "sprite");
    LoadShader(self->resource, "assets/shaders/particle.vs", "assets/shaders/particle.frag", "particle");

    // Configure shaders
    Mat projection = glm_ortho(0.0f, self->width, self->height, 0.0f, -1.0f, 1.0f);

    SetInteger(GetShader(self->resource, "sprite"), "sprite", 0, true);
    SetMatrix(GetShader(self->resource, "sprite"), "projection", &projection, true);

    SetInteger(GetShader(self->resource, "particle"), "sprite", 0, true);
    SetMatrix(GetShader(self->resource, "particle"), "projection", &projection, true);

    // Load textures
    LoadTexture(self->resource, "assets/images/background.png", GL_TRUE, "background");
    // self->resources.LoadTexture("assets/images/bang.png", GL_TRUE, "bang");
    // self->resources.LoadTexture("assets/images/bullet.png", GL_TRUE, "bullet");
    // self->resources.LoadTexture("assets/images/enemy1.png", GL_TRUE, "enemy1");
    // self->resources.LoadTexture("assets/images/enemy2.png", GL_TRUE, "enemy2");
    // self->resources.LoadTexture("assets/images/enemy3.png", GL_TRUE, "enemy3");
    // self->resources.LoadTexture("assets/images/explosion.png", GL_TRUE, "explosion");
    // self->resources.LoadTexture("assets/images/particle.png", GL_TRUE, "particle");
    // self->resources.LoadTexture("assets/images/spaceshipspr.png", GL_TRUE, "spaceshipspr");
    // self->resources.LoadTexture("assets/images/star.png", GL_TRUE, "star");

    self->spriteBatch = new(SpriteRenderer, GetShader(self->resource, "sprite"));

}
/**
 * Shmupwarz::Run
 * 
 */
method void Run(const Shmupwarz* const self)
{
    super(Run);
}

/**
 * Shmupwarz::Tick
 * 
 */
method void Tick(const Shmupwarz* const self)
{
    super(Tick);
}

/**
 * Shmupwarz::HandleEvents
 * 
 */
method void HandleEvents(const Shmupwarz* const self)
{
    super(HandleEvents);
}

/**
 * Shmupwarz::RunLoop
 * 
 */
method void RunLoop(const Shmupwarz* const self)
{
    super(RunLoop);
}


