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
#include "../DObject.h"
/**
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define VECTOR_INIT_CAPACITY 4

class (Vector)
{
    union {
        DObject_t _;
        struct 
        {
            int         RefCount;
            char*       (*ToString)(DObject const);
            bool        (*Equals)(DObject const, DObject const);
            int         (*GetHashCode)(DObject const);
            void        (*Dispose) (DObject const);
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
    void    (*Clear)        (Vector const);
};

/**
 * Vector API
 */
int Vector_Count(Vector const);
void Vector_Resize(Vector const, int capacity);
void Vector_Add(Vector const, Any item);
void Vector_Set(Vector const, int index, Any item);
Any Vector_Get(Vector const, int index);
void Vector_Delete(Vector const, int index);
void Vector_Dispose(Vector const);
void Vector_Clear(Vector const);
const char* Vector_ToString(Vector const);
Vector Vector_New(int capacity);
Vector Vector_Variadic(int count, ...);

/**
 *  Vector v = Vector_From(1, 2, 4, 8);
 * 
 *      expands to:
 *          Vector_Variadic(4, 1, 2, 4, 8);
 *  
 */
#define Vector_From(...) Vector_Variadic(PP_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Vala vararg is broken... it passes the args as is followed by a null.
 * So you can't pass 0 or null as an argument.
 * So we count the args, and forget about the extra null.
 * 
 *  Vector v = Vector_Vala(1, 2, 4, 8, NULL);
 * 
 *      expands to:
 *          Vector_Variadic(4, 1, 2, 4, 8, NULL);
 *  
 */
#define Vector_Vala(...) Vector_Variadic(PP_NARG(__VA_ARGS__)-1, __VA_ARGS__)

#endif _VECTOR_H_
