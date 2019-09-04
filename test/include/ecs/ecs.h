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

method bool Contains(Array* self, Object* e)
{
    for (auto i=0; i<self->length; i++)
    {
        if (e == self->data[i])
            return true;
    }
    return false;
}

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

#include "component.h"
#include "aspect.h"
#include "entityobserver.h"
#include "manager.h"
#include "componenttype.h"
#include "componenttypefactory.h"
#include "componentmanager.h"
#include "entity.h"
#include "entitymanager.h"
#include "entitysystem.h"
#include "world.h"
