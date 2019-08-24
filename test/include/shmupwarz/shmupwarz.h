#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>

// 100,149,237,255
#define bgd_r 0.392156f
#define bgd_g 0.584313f
#define bgd_b 0.929411f

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
    ResourceManager resource;
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
};

/**
 * Put it all together
 */
static inline vptr(Shmupwarz);
/**
 * Class Loader callback
 */
static inline Class objc_loadShmupwarz(Class base) 
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
    self->isa = objc_getClass("Shmupwarz");
    return self;
}

/**
 * Shmupwarz::ToString
 */
method char* ToString(const Shmupwarz* const self)
{
    return super(ToString);
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
    super(Start);
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


/**
 * Shmupwarz::Draw
 * 
 */
method void Draw(const Shmupwarz* const self)
{
    glClearColor(bgd_r, bgd_g, bgd_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    super(Draw);
}

/**
 * Shmupwarz::Update
 * 
 */
method void Update(const Shmupwarz* const self)
{
    super(Update);
}