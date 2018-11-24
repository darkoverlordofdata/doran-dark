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
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "core.h"

/**
 * Object class
 */
class (Object) 
{
    int RefCount;

    char* (*ToString)(Object const);
    bool (*Equals)(Object const, Object const);
    int (*GetHashCode)(Object const);
    void (*Dispose)(Object const);
} ;

/**
 * Object API
 */
Object Object_AddRef(Object const);
Object Object_Release(Object const);
bool Object_ReferenceEquals(Object const objA, Object const objB);
bool Object_InstanceEquals(Object const objA, Object const objB);
const char* Object_ToString(Object const);
bool Object_Equals(Object const, Object const that);
int Object_GetHashCode(Object const);
void Object_Dispose(Object const);
Object Object_New();

#endif _OBJECT_H_ 
