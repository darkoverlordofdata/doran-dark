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
    EcsWorld* world = new(EcsWorld);
    EcsEntity* e1 = new(EcsEntity, world, 1, "Entity1");
    EcsEntity* e2 = new(EcsEntity, world, 2, "Entity2");
    EcsEntity* e3 = new(EcsEntity, world, 3, "Entity3");

    auto es = new(Map, of(Integer));

    Put(es, ToString(e1->uuid), new(Integer, 1));
    Put(es, ToString(e2->uuid), new(Integer, 2));
    Put(es, ToString(e3->uuid), new(Integer, 3));

    Number* n1 = Get(es, ToString(e1->uuid));
    Log("Got %s -> %d", ToString(e1->uuid), IntValue(n1));
    Number* n2 = Get(es, ToString(e2->uuid));
    Log("Got %s -> %d", ToString(e2->uuid), IntValue(n2));
    Number* n3 = Get(es, ToString(e3->uuid));
    Log("Got %s -> %d", ToString(e3->uuid), IntValue(n3));


    return 0;

    auto game = new(Shmupwarz, 900, 600);
    Log(ToString(game));
    
    Run(game);
    Dispose(game);

    Dispose(GetClasses());


    return 0;
}

