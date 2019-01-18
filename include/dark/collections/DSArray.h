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
    Class typeOf;
    void **data;
    int capacity;
};


/**
 * Array API
 */
DSArray* overload NewDSArray(void);
DSArray* overload NewDSArray(Class);
DSArray* overload NewDSArray(Class, int);
DSArray* overload DSArray_init(DSArray* const this);
DSArray* overload DSArray_init(DSArray* const this, Class typeOf);
DSArray* overload DSArray_init(DSArray* const this, Class typeOf, int capacity);
DSArray* Array_Variadic(int, ...);

method (DSArray, ToString,  char*,      (const DSArray* const) );
method (DSArray, Dispose,   void,       (DSArray* const) );
method (DSArray, Length,    int,        (const DSArray* const) );
method (DSArray, IsEmpty,   bool,       (DSArray* const) );
method (DSArray, Contains,  bool,       (DSArray* const, DSObject*) );
method (DSArray, Clear,     void,       (DSArray* const) );
method (DSArray, Add,       Either*,    (DSArray* const, const DSObject*) );
method (DSArray, Remove,    void,       (DSArray* const, int) );
method (DSArray, Resize,    void,       (DSArray* const, int) );
method (DSArray, Set,       Either*,    (DSArray* const, int, const DSObject*) );
method (DSArray, Get,       DSObject*,  (DSArray* const, int) );

typedef DSArray*    (*DSArrayNew)   (Class, int);

/**
 * Array metaclass
 */
vtable (DSArray) {
    const DSArrayToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSArrayLength           Length;
    const DSArrayIsEmpty          IsEmpty;
    const DSArrayContains         Contains;
    const DSArrayClear            Clear;
    const DSArrayAdd              Add;
    const DSArrayRemove           Remove;
    const DSArrayResize           Resize;
    const DSArraySet              Set;
    const DSArrayGet              Get;    
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
