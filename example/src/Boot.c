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
#include <dark/DSClass.h>
#include <dark/Foundation.h>

#define DEBUG_ON
/**
 * Class loader
 */
void __attribute__((constructor)) ApplicationLoader() 
{

    Class obj = objc_getClass("DSObject");
    Class gameObj;

    objc_registerClassPair(gameObj = GameObjectImplementation(obj));
    objc_registerClassPair(BallObjectImplementation(gameObj));
    objc_registerClassPair(GameImplementation(obj));
    objc_registerClassPair(GameLevelImplementation(obj));
    objc_registerClassPair(ParticleGeneratorImplementation(obj));
    objc_registerClassPair(ShaderImplementation(obj));
    objc_registerClassPair(SpriteRendererImplementation(obj));
    objc_registerClassPair(Texture2DImplementation(obj));
    objc_registerClassPair(ResourceManagerImplementation(obj));
}
