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

    Class obj = GetClass("Object");
    Class gameClass = ClassLoadGame(obj);

    RegisterClass(gameClass);
    RegisterClass(ClassLoadShmupwarz(gameClass));
}

int main(int argc, char *argv[])
{
    var zz = new(Boolean, true);
    Class cc = Get(GetClasses(), "Object");
    assert(cc != nullptr);
    Log("Name = %s", cc->name);
    Class bb = Get(GetClasses(), "Boolean");
    Log("Name = %s", bb->name);


    // Game* game = new(Game, "SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    //                     600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    // Run(game);
    // Dispose(game);

    Shmupwarz* game = new(Shmupwarz, 600, 480);
    Log(ToString(game));
    
    Run(game);
    Dispose(game);

    Dispose(GetClasses());

    return 0;
}

