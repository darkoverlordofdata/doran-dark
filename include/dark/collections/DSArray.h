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
#ifndef _DSARRAY_H_
#define _DSARRAY_H_
#include "DSCollection.h"
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4

#define IsDSArray(x) (x->isa == &DSArrayClass)
#define AsDSArray(x) (IsDSArray(x) ? (DSArray*)x : nullptr)

class (DSArray)
{
    struct DSArrayClass* isa;
    int length;
    void **data;
    int capacity;
};

/**
 * Array metaclass
 */
struct DSArrayClass
{
    Class*  isa;
    Class*  superclass;
    char*   name;
    long    info, instance_size;
    char*   (*ToString) (const DSArray* const);
    bool    (*Equals) (const DSObject* const, struct Object  *const);
    int     (*GetHashCode) (const DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (const DSObject* const, DSObject* const);
    bool    (*InstanceEquals) (const DSObject* const, DSObject* const);
    DSArray*  (*Create) (int);
    int     (*Length)       (const DSArray* const);
    bool    (*IsEmpty)      (const DSArray* const);
    bool    (*Contains)     (const DSArray* const, Any);
    void    (*Clear)        (DSArray* const);
    void    (*Add)          (DSArray* const, Any);
    void    (*Remove)       (DSArray* const, int);

    void    (*Resize)       (DSArray* const, int);
    void    (*Set)          (DSArray* const, int, Any);
    Any     (*Get)          (const DSArray* const, int);
    
} DSArrayClass;



/**
 * Array API
 */
DSArray* overload Array_New(void);
DSArray* overload Array_New(int);

char* overload ToString(const DSArray* const);
void overload Dispose(DSArray* const);
int overload Length(const DSArray* const);
bool overload IsEmpty(const DSArray* const);
bool overload Contains(const DSArray* const, Any);
void overload Clear(DSArray* const);
void overload Add(DSArray* const, Any);
void overload Remove(DSArray* const, int);
void Resize(DSArray* const, int);
void Set(DSArray* const, int, const Any);
Any Get(const DSArray* const, int);
DSArray* Array_Variadic(int, ...);

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

#endif _DSARRAY_H_
