/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <xna/xna.h>
#include <ecs/ecs.h>
#include <shmupwarz.h>
#include <assert.h>


/**
 * Class loader
 */
void __attribute__((constructor(200))) GameLoader() 
{

    Class GameClass = GetClass("Game");
    RegisterClass(ClassLoadShmupwarz(GameClass));

    RegisterClass(CreateComponent(ColorComponent));
    RegisterClass(CreateComponent(ExpireComponent));
    RegisterClass(CreateComponent(HealthComponent));
    RegisterClass(CreateComponent(SoundComponent));
    RegisterClass(CreateComponent(TaxonomyComponent));
    RegisterClass(CreateComponent(TweenComponent));
    RegisterClass(CreateComponent(VelocityComponent));
    RegisterClass(CreateComponent(Entity));

}

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    Shmupwarz* game = new(Shmupwarz, 900, 600);

    uint64_t h = GetHashCode(game);
    Log("Hash Code = %x", h);

    Log(ToString(game));
    
    Run(game);
    Dispose(game);

    Dispose(GetClasses());


    return 0;
}

