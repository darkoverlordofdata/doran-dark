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
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "Object.h"
/**
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define VECTOR_INIT_CAPACITY 4

class (Vector)
{
    union {
        Object_t _;
        struct 
        {
            int         RefCount;
            char*       (*ToString)(Object const);
            bool        (*Equals)(Object const, Object const);
            int         (*GetHashCode)(Object const);
        };
    };
    void **data;
    int capacity;
    int count;

    int     (*Count)        (Vector const);
    void    (*Resize)       (Vector const, int);
    void    (*Add)          (Vector const, Any);
    void    (*Set)          (Vector const, int, Any);
    Any     (*Get)          (Vector const, int);
    void    (*Delete)       (Vector const, int);
    void    (*Dispose)      (Vector const);
    void    (*Clear)        (Vector const);
};

/**
 * Vector API
 */
int Vector_Count(Vector const this);
void Vector_Resize(Vector const this, int capacity);
void Vector_Add(Vector const this, Any item);
void Vector_Set(Vector const this, int index, Any item);
Any Vector_Get(Vector const this, int index);
void Vector_Delete(Vector const this, int index);
void Vector_Dispose(Vector const this);
void Vector_Clear(Vector const this);
const char* Vector_ToString(Vector const this);
Vector Vector_New();

#endif _VECTOR_H_
