/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

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
AUTHORS OR COPYRIGHT HOLDERS BE LI  ABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <Breakout.h>

#define DEBUG_ON
/**
 * Class loader
 */
void __attribute__((constructor)) ApplicationLoader() 
{

    Class obj = GetClass("Object");
    Class gameObj;

    RegisterClass(gameObj = ClassLoadGameObject(obj));
    RegisterClass(ClassLoadBallObject(gameObj));
    RegisterClass(ClassLoadGame(obj));
    RegisterClass(ClassLoadGameLevel(obj));
    RegisterClass(ClassLoadParticleGenerator(obj));
    RegisterClass(ClassLoadShader(obj));
    RegisterClass(ClassLoadSpriteRenderer(obj));
    RegisterClass(ClassLoadTexture2D(obj));
    RegisterClass(ClassLoadResourceManager(obj));
}
