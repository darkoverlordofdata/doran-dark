/* ******************************************************************************
 * MIT License
 *
 * Copyright (c) 2019 Bruce Davidson &lt;darkoverlordofdata@gmail.com&gt;
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ****************************************************************************** */
#pragma once
#include "memorypool.h"
#include "rectangle.h"
#include "point.h"
#include "game.h"
#include "resourcemanager.h"
#include "shader.h"
#include "spriterenderer.h"
#include "texture2d.h"
/**
 * 

    Game* game = new(Game, "SdL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        600, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    Run(game);
    Dispose(game);


 * 
 * 
 */
void __attribute__((constructor(102))) XnaLoader() 
{

    Class ObjectClass = GetClass("Object");

    RegisterClass(CreateComponent(MemoryPool));

    Class GameClass = ClassLoadGame(ObjectClass);
    RegisterClass(GameClass);

    Class PointClass = ClassLoadPoint(ObjectClass);
    RegisterClass(PointClass);

    Class RectangleClass = ClassLoadRectangle(ObjectClass);
    RegisterClass(RectangleClass);

    Class ResourceManagerClass = ClassLoadResourceManager(ObjectClass);
    RegisterClass(ResourceManagerClass);

   //  Class ShaderClass = ClassLoadShader(ObjectClass);
   //  RegisterClass(ShaderClass);
    RegisterClass(CreateComponent(Shader));

   //  Class SpriteRendererClass = ClassLoadSpriteRenderer(ObjectClass);
   //  RegisterClass(SpriteRendererClass);
    RegisterClass(CreateComponent(SpriteRenderer));

   //  Class Texture2DClass = ClassLoadTexture2D(ObjectClass);
   //  RegisterClass(Texture2DClass);
    RegisterClass(CreateComponent(Texture2D));
}