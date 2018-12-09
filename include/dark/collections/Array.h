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
#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "Collection.h"
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4

class (Array)
{
    ArrayClass_t* isa;
    int length;
    void **data;
    int capacity;
};

/**
 * Object metaclass
 */
typedef struct ArrayClass_t
{
    union {
        Collection_t base;
        struct 
        {
            Class   isa;
            Class   superclass;
            char*   name;
            const char*   (*ToString)     (Array const);
            bool    (*Equals)       (Object const, Object const);
            int     (*GetHashCode)  (Object const);
            void    (*Dispose)      (Array const);
            bool    (*ReferenceEquals) (Object const objA, Object const objB);
            bool    (*InstanceEquals) (Object const objA, Object const objB);
            int     (*Length)       (Array const);
            bool    (*IsEmpty)      (Array const);
            bool    (*Contains)     (Array const, Any value);
            void    (*Clear)        (Array const);
            void    (*Add)          (Array const, Any value);
            void    (*Remove)       (Array const, int index);
        };
    };
    void    (*Resize)       (Array const, int);
    void    (*Set)          (Array const, int, Any);
    Any     (*Get)          (Array const, int);
};



/**
 * Array API
 */
Array overload Array_New(void);
Array overload Array_New(int capacity);

const char* overload ToString(Array const);
void overload Dispose(Array const);
int overload Length(Array const);
bool overload IsEmpty(Array const);
bool overload Contains(Array const, Any item);
void overload Clear(Array const);
void overload Add(Array const, Any item);
void overload Remove(Array const, int index);
void Resize(Array const, int capacity);
void Set(Array const, int index, Any item);
Any Get(Array const, int index);
Array Array_Ctor(Array const this, int capacity);
Array Array_Variadic(int count, ...);

/**
 *  Array v = Array_From(1, 2, 4, 8);
 * 
 *      expands to:
 *          Array_Variadic(4, 1, 2, 4, 8);
 *  
 */
#define Array_From(...) Array_Variadic(PP_NARG(__VA_ARGS__), __VA_ARGS__)

/**
 * Vala vararg is broken... it passes the args as is followed by a null.
 * So you can't pass 0 or null as an argument.
 * So we count the args, and ignore the trailing null.
 * 
 *  Array v = Array_Vala(1, 2, 4, 8, NULL);
 * 
 *      expands to:
 *          Array_Variadic(4, 1, 2, 4, 8, NULL);
 *  
 */
#define Array_Vala(...) Array_Variadic(PP_NARG(__VA_ARGS__)-1, __VA_ARGS__)

#endif _ARRAY_H_
