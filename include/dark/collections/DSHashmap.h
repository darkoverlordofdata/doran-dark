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
/*
 * Copyright (c) 2016-2018 David Leeds <davidesleeds@gmail.com>
 *`
 * Hashmap is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#pragma once
#ifndef _DSHASHMAP_H_
#define _DSHASHMAP_H_
#include "../DSObject.h"
// #include "DSCollection.h"

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */

#define IsDSHashmap(object) _Generic((object), DSHashmap*: true, default: false)
#define AsDSHashmap(object) _Generic((object),                          \
                            DSHashmap*: (DSHashmap *)object,            \
                            default: nullptr)

/*
 * Iterator is a pointer to a function that can take two DSObject* arguments
 * and return an integer. Returns status code..
 */
typedef int (^DSHashmap_Iterator)(DSObject*, DSObject*);

/* We need to keep keys and values */
ivar (DSHashmapNode) {
	char* key;
	int inUse;
	DSObject* data;
};

/* A hashmap has some maximum size and current size,
 * as well as the data to hold. */
ivar (DSHashmap) {
    Class isa;
    Class typeOf;
	int length;
	DSHashmapNode* data;
	int tableSize;
}; 

ctor (DSHashmap);
ctor (DSHashmap, Class);
method (DSHashmap, ToString,    char*,      (const DSHashmap* const) );
method (DSHashmap, Dispose,     void,       (DSHashmap* const) );
method (DSHashmap, Length,      int,        (const DSHashmap* const) );
method (DSHashmap, HashInt,     uint,       (DSHashmap* const, char*) );
method (DSHashmap, Hash,        int,        (DSHashmap* const, char*) );
method (DSHashmap, Rehash,      int,        (DSHashmap* const) );
method (DSHashmap, Put,         Either*,    (DSHashmap* const, char*, DSObject*) );
method (DSHashmap, Get,         DSObject*,  (DSHashmap* const, char*) );
method (DSHashmap, ForEach,     int,        (DSHashmap* const, DSHashmap_Iterator, DSObject*) );
method (DSHashmap, Remove,      int,        (DSHashmap* const, char*) );

vtable (DSHashmap) {
    const DSHashmapToString       ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSHashmapDispose        Dispose;
    const DSHashmapLength         Length;
    const DSHashmapRemove         Remove;
    const DSHashmapForEach        ForEach;
    const DSHashmapPut            Put;
    const DSHashmapGet            Get;
    const DSHashmapHashInt        HashInt;
    const DSHashmapHash           Hash;
    const DSHashmapRehash         Rehash;
} ;


#endif _DSHASHMAP_H_