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
#pragma once
#ifndef DARK_ARRAY_H_
#define DARK_ARRAY_H_
#include "Collection.h"
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4

#define IsArray(x) (x->isa == &Array)
#define AsArray(x) (IsArray(x) ? (struct Array *)x : nullptr)

class (Array)
{
    struct ArrayClass * isa;
    int length;
    void **data;
    int capacity;
};

/**
 * Object metaclass
 */
struct ArrayClass
{
    union {
        struct Collection base;
        struct 
        {
            struct Class * isa;
            struct Class * superclass;
            char* name;
            char*   (*ToString) (const struct Array *const);
            bool    (*Equals) (const struct Object *const, struct Object  *const);
            int     (*GetHashCode) (const struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (const struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (const struct Object *const, struct Object *const);
            struct Array * (*Create) (int);
            int     (*Length)       (const struct Array *const);
            bool    (*IsEmpty)      (const struct Array *const);
            bool    (*Contains)     (const struct Array *const, Any);
            void    (*Clear)        (struct Array *const);
            void    (*Add)          (struct Array *const, Any);
            void    (*Remove)       (struct Array *const, int);
        };
    };
    void    (*Resize)       (struct Array *const, int);
    void    (*Set)          (struct Array *const, int, Any);
    Any     (*Get)          (const struct Array *const, int);
};



/**
 * Array API
 */
struct Array *overload Array_New(void);
struct Array *overload Array_New(int);

char* overload ToString(const struct Array *const);
void overload Dispose(struct Array *const);
int overload Length(const struct Array *const);
bool overload IsEmpty(const struct Array *const);
bool overload Contains(const struct Array *const, Any);
void overload Clear(struct Array *const);
void overload Add(struct Array *const, Any);
void overload Remove(struct Array *const, int);
void Resize(struct Array *const, int);
void Set(struct Array *const, int, const Any);
Any Get(const struct Array *const, int);
struct Array *Array_Variadic(int, ...);

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

#endif DARK_ARRAY_H_
