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

#define OBJECT_TYPE       (TYPE_OBJECT)

/**
 * DObject class
 */
class (DObject) 
{
    retained    // Contains RefCount if __ARC__ set
    char* (*ToString)(DObject const);
    bool (*Equals)(DObject const, DObject const);
    int (*GetHashCode)(DObject const);
    void (*Dispose)(DObject const);
} ;

/**
 * DObject API
 */

DObject DObject_AddRef(DObject const);
DObject DObject_Release(DObject const);

bool DObject_ReferenceEquals(DObject const objA, DObject const objB);
bool DObject_InstanceEquals(DObject const objA, DObject const objB);
const char* DObject_ToString(DObject const);
bool DObject_Equals(DObject const, DObject const that);
int DObject_GetHashCode(DObject const);
void DObject_Dispose(DObject const);
DObject DObject_New();
DObject DObject_Dtor();

#endif _OBJECT_H_ 
