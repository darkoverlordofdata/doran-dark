/*******************************************************************
**
MIT License

Copyright (c) 2019 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
/**
 * Artemis inspired ECS library
 * 
 */
typedef struct EcsComponent EcsComponent;
typedef struct EcsAspect EcsAspect;
typedef struct EcsEntityObserver EcsEntityObserver;
typedef struct EcsManager EcsManager;
typedef struct EcsComponentManager EcsComponentManager;
typedef struct EcsComponentType EcsComponentType;
typedef struct EcsComponentTypeFactory EcsComponentTypeFactory;
typedef struct EcsEntity EcsEntity;
typedef struct EcsEntityManager EcsEntityManager;
typedef struct EcsEntitySystem EcsEntitySystem;
typedef struct EcsWorld EcsWorld;

typedef struct EcsGroupManager;
typedef struct EcsPlayerManager;
typedef struct EcsTagManager;
typedef struct EcsTeamManager;

typedef struct EcsDelayedEntityProcessingSystem;
typedef struct EcsEntityProcessingSystem;
typedef struct EcsIntervalEntityProcessingSystem;
typedef struct EcsIntervalEntitySystem;
typedef struct EcsVoidEntitySystem;


method bool Remove(Array* self, Object* e)
{
    for (auto i=0; i<self->length; i++)
    {
        auto e2 = self->data[i];
        if (e == e2) {
            Remove(self, i);
            return true;
        }
    }
    return false;
}

#include "blackboard/blackboard.h"
#include "blackboard/blackboard.h"
#include "blackboard/trigger.h"
#include "blackboard/triggermulticondition.h"
#include "blackboard/triggerstatetype.h"
#include "core/component.h"
#include "core/aspect.h"
#include "core/entityobserver.h"
#include "core/manager.h"
#include "core/componenttype.h"
#include "core/componenttypefactory.h"
#include "core/componentmanager.h"
#include "core/entity.h"
#include "core/entitymanager.h"
#include "core/entitysystem.h"
#include "core/world.h"
#include "managers/groupmanager.h"
#include "managers/playermanager.h"
#include "managers/tagmanager.h"
#include "managers/teammanager.h"
#include "systems/delayedentityprocessingsystem.h"
#include "systems/entityprocessingsystem.h"
#include "systems/intervalentitysystem.h"
#include "systems/voidentitysystem.h"
#include "systems/intervalentityprocessingsystem.h"

void __attribute__((constructor(102))) EcsLoader() 
{

    Class ObjectClass = GetClass("Object");
    RegisterClass(CreateComponent(EcsComponent));
    RegisterClass(CreateComponent(EcsEntity));

    Class EcsWorld = ClassLoadEcsWorld(ObjectClass);
    RegisterClass(EcsWorld);

    Class EcsAspect = ClassLoadEcsAspect(ObjectClass);
    RegisterClass(EcsAspect);

    Class EcsComponentType = ClassLoadEcsComponentType(ObjectClass);
    RegisterClass(EcsComponentType);

    Class EcsComponentTypeFactory = ClassLoadEcsComponentTypeFactory(ObjectClass);
    RegisterClass(EcsComponentTypeFactory);

    Class EcsEntityObserverClass = ClassLoadEcsEntityObserver(ObjectClass);
    RegisterClass(EcsEntityObserverClass);

    Class EcsEntitySystemClass = ClassLoadEcsEntitySystem(EcsEntityObserverClass);
    RegisterClass(EcsEntitySystemClass);

    Class EcsManagerClass = ClassLoadEcsManager(EcsEntityObserverClass);
    RegisterClass(EcsManagerClass);
 
    Class EcsComponentManagerClass = ClassLoadEcsComponentManager(EcsManagerClass);
    RegisterClass(EcsComponentManagerClass);
    
    Class EcsEntityManagerClass = ClassLoadEcsEntityManager(EcsManagerClass);
    RegisterClass(EcsEntityManagerClass);

    Class EcsGroupManagerClass = ClassLoadEcsGroupManager(EcsManagerClass);
    RegisterClass(EcsGroupManagerClass);
 
    Class EcsPlayerManagerClass = ClassLoadEcsPlayerManager(EcsManagerClass);
    RegisterClass(EcsPlayerManagerClass);
 
    Class EcsTagManagerClass = ClassLoadEcsTagManager(EcsManagerClass);
    RegisterClass(EcsTagManagerClass);
 
    Class EcsTeamManagerClass = ClassLoadEcsTeamManager(EcsManagerClass);
    RegisterClass(EcsTeamManagerClass);
 
    Class EcsEntityProcessingSystemClass = ClassLoadEcsEntityProcessingSystem(EcsEntitySystemClass);
    RegisterClass(EcsEntityProcessingSystemClass);

    Class EcsDelayedEntityProcessingSystemClass = ClassLoadEcsDelayedEntityProcessingSystem(EcsEntitySystemClass);
    RegisterClass(EcsDelayedEntityProcessingSystemClass);

    Class EcsIntervalEntitySystemClass = ClassLoadEcsIntervalEntitySystem(EcsEntitySystemClass);
    RegisterClass(EcsIntervalEntitySystemClass);

    Class EcsVoidEntitySystemClass = ClassLoadEcsVoidEntitySystem(EcsEntitySystemClass);
    RegisterClass(EcsVoidEntitySystemClass);

    Class EcsIntervalEntityProcessingSystemClass = ClassLoadEcsIntervalEntityProcessingSystem(EcsIntervalEntitySystemClass);
    RegisterClass(EcsIntervalEntityProcessingSystemClass);
}
