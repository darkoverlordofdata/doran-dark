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
#include "../DSObject.h"
// #include "DSCollection.h"
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4


#define IsDSArray(object) _Generic((object), DSArray*: true, default: false)
#define AsDSArray(object) _Generic((object),                            \
                            DSArray*: (DSArray *)object,                \
                            default: nullptr)


ivar (DSArray) {
    Class isa;
    int length;
    void **data;
    int capacity;
};

/**
 * Array API
 */
DSArray* overload NewDSArray(void);
DSArray* overload NewDSArray(int);
DSArray* DSArray_init(DSArray* const this, int capacity);
DSArray* DSArray_alloc();
DSArray* Array_Variadic(int, ...);

char*   overload ToString(const DSArray* const);
void    overload Dispose(DSArray* const);
int     overload Length(const DSArray* const);
bool    overload IsEmpty(DSArray* const);
bool    overload Contains(DSArray* const, DSObject*);
void    overload Clear(DSArray* const);
void    overload Add(DSArray* const, const DSObject*);
void    overload Remove(DSArray* const, int);
void    overload Resize(DSArray* const, int);
void    overload Set(DSArray* const, int, const DSObject*);
DSObject* overload Get(DSArray* const, int);

typedef char*   (*DSArrayToString)  (const DSArray* const);
typedef void    (*DSArrayDispose)   (DSArray* const);
typedef int     (*DSArrayLength)    (const DSArray* const);
typedef bool    (*DSArrayIsEmpty)   (DSArray* const);
typedef bool    (*DSArrayContains)  (DSArray* const,  DSObject*);
typedef void    (*DSArrayClear)     (DSArray* const);
typedef void    (*DSArrayAdd)       (DSArray* const, const DSObject*);
typedef void    (*DSArrayRemove)    (DSArray* const, int);
typedef void    (*DSArrayResize)    (DSArray* const, int);
typedef void    (*DSArraySet)       (DSArray* const, int, const DSObject*);
typedef DSObject*     (*DSArrayGet)       (DSArray* const, int);

/**
 * Array metaclass
 */
vtable (DSArray) {
    DSArrayToString         ToString;
    DSObjectEquals          Equals;
    DSObjectGetHashCode     GetHashCode;
    DSObjectDispose         Dispose;
    DSArrayLength           Length;
    DSArrayIsEmpty          IsEmpty;
    DSArrayContains         Contains;
    DSArrayClear            Clear;
    DSArrayAdd              Add;
    DSArrayRemove           Remove;
    DSArrayResize           Resize;
    DSArraySet              Set;
    DSArrayGet              Get;    
};

class (DSArray) {
    DSArray*  (*Create) (int);
};



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
