#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/time.h>
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <dark/Foundation.h>
#include "resourcemanager.h"

#define TicksPerMillisecond  10000.0
#define MillisecondsPerTick 1.0 / (TicksPerMillisecond)

#define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
#define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
// #include "tglm.h"

#define bgd_r 0.392156f
#define bgd_g 0.584313f
#define bgd_b 0.929411f

/**
 * The game type
 */
#undef SUPER
#define SUPER Object
type (Game)
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
};

delegate (Game, New,            Game*, (Game* self, char* title, int x, int y, int width, int height, int flags));
delegate (Game, ToString,       char*, (const Game* const));
delegate (Game, Dispose,        void, (Game* const));
delegate (Game, Start,          void, (Game* const));
delegate (Game, Run,            void, (Game* const));
delegate (Game, Tick,           void, (Game* const));
delegate (Game, HandleEvents,   void, (Game* const));
delegate (Game, RunLoop,        void, (Game* const));
delegate (Game, Draw,           void, (Game* const));
delegate (Game, Update,         void, (Game* const));
delegate (Game, Initialize,     void, (Game* const));
delegate (Game, LoadContent,    void, (Game* const));

vtable (Game) 
{
    const GameToString      ToString;
    const ObjectEquals      Equals;
    const ObjectGetHashCode GetHashCode;
    const GameDispose       Dispose;
    const GameStart         Start;
    const GameRun           Run;
    const GameTick          Tick;
    const GameHandleEvents  HandleEvents;
    const GameRunLoop       RunLoop;
    const GameDraw          Draw;
    const GameUpdate        Update;
    const GameInitialize    Initialize;
    const GameLoadContent   LoadContent;
};

/**
 * Put it all together
 */
static inline vptr(Game);
/**
 * Class Loader callback
 */
static inline Class ClassLoadGame(Class base) 
{
    Class cls = createClass(base, Game);
    addMethod(cls, Game,    ToString);
    addMethod(cls, Object,  Equals);
    addMethod(cls, Object,  GetHashCode);
    addMethod(cls, Game,    Dispose);
    addMethod(cls, Game,    Start);
    addMethod(cls, Game,    Run);
    addMethod(cls, Game,    Tick);
    addMethod(cls, Game,    HandleEvents);
    addMethod(cls, Game,    RunLoop);
    addMethod(cls, Game,    Draw);
    addMethod(cls, Game,    Update);
    addMethod(cls, Game,    Initialize);
    addMethod(cls, Game,    LoadContent);
    return cls;
}

static inline uint64_t GetTicks() { 
    struct timeval t;     
    gettimeofday(&t, nullptr);

    uint64_t ts = t.tv_sec;
    uint64_t us = t.tv_usec;
    return ((ts * 1000000L) + us) * 10;
}


static inline void LogSDLError(const char* msg)
{
    Log("%s error: %s", msg, SDL_GetError());
}


method char* ToString(const Game* const self)
{
    static char* toStringCache;

    if (!toStringCache)
        toStringCache = DSsprintf("title { %s }", self->title);

    return toStringCache;

}


/**
 * New Base Game
 * 
 * @param self
 * @paran title
 * @param x
 * @param y
 * @param width
 * @param height
 * @param SDL flags
 */
method Game* New(Game* self, char* title, int x, int y, int width, int height, int flags)
{
	extends(Object);
    self->isa = isa(Game);
    self->title = strdup(title);
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->flags = flags;

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0) {
        LogSDLError("Unable to initialize SDL2");
        return nullptr;
    }
    SDL_version sversion;
    SDL_GetVersion(&sversion);
    int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
    if (version <= 204) {
        printf("Please use SDL 2.0.5 or higher.\n");
    } else {
        printf("Using SDL Vesion %d.%d.%d\n", sversion.major, sversion.minor, sversion.patch);
    }
    
    self->frameSkip = 0;
    self->isRunning = false;
    self->previousTicks = 0;
    self->isFixedTimeStep = true;
    self->shouldExit = false;
    self->suppressDraw = false;
    self->maxElapsedTime = 500 * TicksPerMillisecond; 
    self->targetElapsedTime = 166667;
    self->accumulatedElapsedTime = 0;
    self->currentTime = GetTicks();
    self->keys = calloc(256, sizeof(bool));
    self->sdlVersion = version;
    self->gl_major_version = 3;
    #ifdef __EMSCRIPTEN__
    self->gl_minor_version = 0;
    #else
    self->gl_minor_version = 3;
    #endif

    /* Request opengl 3.3 context.*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, self->gl_major_version);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, self->gl_minor_version);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    self->window = SDL_CreateWindow(self->title, 
                                    self->x, 
                                    self->y, 
                                    self->width, 
                                    self->height, 
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
    self->context = SDL_GL_CreateContext(self->window);

    #ifdef __EMSCRIPTEN__
    const int img_flags = IMG_INIT_PNG;
    #else
    const int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    #endif
    if (IMG_Init(img_flags) != img_flags) { 
        LogSDLError("Init image");
    }
    TTF_Init();
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        LogSDLError("Init mixer");
    }

    #ifndef __EMSCRIPTEN__
    // Load OpenGL EntryPoints for desktop
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
    #endif

    // OpenGL configuration
    glViewport(0, 0, self->width, self->height);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return self;
}



/**
 * Game::Initialize
 */
method void Initialize(Game* const self)
{ 
    virtual(Game)->Initialize(self);
}
/**
 * Game::LoadContent
 */
method void LoadContent(Game* const self)
{ 
    Log("Load Content");
    self->resource = new(ResourceManager);
    assert(self->resource != nullptr);
    virtual(Game)->LoadContent(self);
}

/**
 * Game::Update
 */
method void Update(Game* const self)
{ 
    virtual(Game)->Update(self);
}

/**
 * Game::Draw
 */
method void Draw(Game* const self) 
{
    glClearColor(bgd_r, bgd_g, bgd_b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
            
    virtual(Game)->Draw(self);

    SDL_GL_SwapWindow(self->window);
}

/**
 * Game::HandleEvents
 */
method void HandleEvents(Game* const self) 
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                self->isRunning = false;
                return;
                break;
            case SDL_KEYDOWN: 
                self->keys[ event.key.keysym.sym & 0xff ] = true;
                break;
            case SDL_KEYUP:   
                self->keys[ event.key.keysym.sym & 0xff ] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                self->mouseDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                self->mouseDown = false;
                break;
            case SDL_MOUSEMOTION:
                self->mouseX = event.motion.x;
                self->mouseY = event.motion.y;
                break;
        }
    }
}


/**
 * Game::Start
 */
method void Start(Game* const self) 
{
    self->isRunning = true;
    virtual(Game)->Start(self);
}

/**
 * Game::Tick
 */
method void Tick(Game* const self) 
{
    while (true) {
        // Advance the accumulated elapsed time.
        long currentTicks = (GetTicks() - self->currentTime);//*10;
        self->accumulatedElapsedTime = self->accumulatedElapsedTime + currentTicks - self->previousTicks;
        self->previousTicks = (long)currentTicks;

        // If we're in the fixed timestep mode and not enough time has elapsed
        // to perform an update we sleep off the the remaining time to save battery
        // life and/or release CPU time to other threads and processes.
        if (self->isFixedTimeStep && self->accumulatedElapsedTime < self->targetElapsedTime)
        {
            int sleepTime = (int)((self->targetElapsedTime - self->accumulatedElapsedTime) * MillisecondsPerTick ); //).TotalMilliseconds();
            if (sleepTime < 1) { break; }
            // NOTE: While sleep can be inaccurate in general it is 
            // accurate enough for frame limiting purposes if some
            // fluctuation is an acceptable result.
            #ifndef usleep
            SDL_Delay(sleepTime);
            #else
            usleep(sleepTime*1000);
            #endif
            // goto RetryTick;
        }
        else break;
    }    
    // Do not allow any update to take longer than our maximum.
    if (self->accumulatedElapsedTime > self->maxElapsedTime)
        self->accumulatedElapsedTime = self->maxElapsedTime;

    if (self->isFixedTimeStep)
    {
        self->elapsedGameTime = self->targetElapsedTime;
        int stepCount = 0;

        // Perform as many full fixed length time steps as we can.
        while (self->accumulatedElapsedTime >= self->targetElapsedTime && !self->shouldExit)
        {
            self->totalGameTime += self->targetElapsedTime;
            self->accumulatedElapsedTime -= self->targetElapsedTime;
            ++stepCount;
            self->delta = (double)self->elapsedGameTime * SecondsPerTick;
            Update(self);
            // virtual(Game)->Update(self);
        }
        //Every update after the first accumulates lag
        self->updateFrameLag += Max(0, stepCount - 1);
        //If we think we are isRunning slowly, wait until the lag clears before resetting it
        if (self->isRunningSlowly)
        {
            if (self->updateFrameLag == 0)
            
                self->isRunningSlowly = false;
        }
        else if (self->updateFrameLag >= 5)
        {
            //If we lag more than 5 frames, start thinking we are isRunning slowly
            self->isRunningSlowly = true;
        }
        //Every time we just do one update and one draw, then we are not isRunning slowly, so decrease the lag
        if (stepCount == 1 && self->updateFrameLag > 0)
            self->updateFrameLag--;

        // Draw needs to know the total elapsed time
        // that occured for the fixed length updates.
        self->elapsedGameTime = self->targetElapsedTime * stepCount;
    }
    else
    {
        // Perform a single variable length update.
        self->elapsedGameTime = self->accumulatedElapsedTime;
        self->totalGameTime += self->accumulatedElapsedTime;
        self->accumulatedElapsedTime = 0;
        
        self->delta = (double)self->elapsedGameTime * SecondsPerTick;
        Update(self);
        // virtual(Game)->Update(self);
    }
    // Draw unless the update suppressed it.
    if (self->suppressDraw)
        self->suppressDraw = false;
    else
    {
        Draw(self);
        // virtual(Game)->Draw(self);
    }

    if (self->shouldExit) 
        self->isRunning = false;
        // Platform.Exit();
}

/**
 * Game::Dispose
 */
method void Dispose(Game* const self) 
{
    SDL_DestroyWindow(self->window);
    if (!_use_gc) {
        free(self->title);
        free(self->keys);
    }
    IMG_Quit();
    SDL_Quit();
    Log("Game dispose");
    super(Dispose);
}

/**
 * Game::RunLoop
 */
method void RunLoop(Game* const self)
{
    HandleEvents(self);
    if (self->keys[SDLK_ESCAPE]) {
        self->shouldExit = true;
    }
    Tick(self);
}

/**
 * Game::Run
 */
method void Run(Game* const self) 
{
    Initialize(self);
    LoadContent(self);
    Start(self);
#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg((em_arg_callback_func)RunLoop, (void*)self, -1, 1);
#else
    while (self->isRunning) {
        /** call the most derived virtual method: RunLoop */
        virtual(Game)->RunLoop(self);
    }
#endif
}


