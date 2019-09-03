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

#include "aspect.h"
#include "entityobserver.h"
#include "manager.h"
#include "componentmanager.h"
#include "componenttype.h"
#include "componenttypefactory.h"
#include "entity.h"
#include "entitymanager.h"
#include "entitysystem.h"
#include "world.h"
