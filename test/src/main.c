/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <xna/xna.h>
#include <shmupwarz.h>
#include <assert.h>

/**
 * Class loader
 */
void __attribute__((constructor(200))) GameLoader() 
{

    _objc_inform("Load game classes");
    Class obj = objc_getClass("Object");
    assert(obj != nullptr);
    Class gameClass;

    Log("gameClass = objc_loadGame(obj)");
    gameClass = objc_loadGame(obj);
    assert(gameClass != nullptr);

    objc_registerClassPair(gameClass);
    Log("schmupwarzClass objc_loadShmupwarz");
    Class schmupwarzClass = objc_loadShmupwarz(gameClass);
    assert(schmupwarzClass != nullptr);

    objc_registerClassPair(schmupwarzClass);


}

int main(int argc, char *argv[])
{

    // Game* game = new(Game, "SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    //                     600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    // Run(game);
    // Dispose(game);

    Shmupwarz* game = new(Shmupwarz, 600, 480);
    
    Run(game);
    Dispose(game);

    return 0;
}

