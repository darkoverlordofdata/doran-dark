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
#include "DSCollection.h"

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */

#define IsDSHashmap(x) (x->isa == &$DSHashmap)
#define AsDSHashmap(x) (IsDSHashmap(x) ? (DSHashmap*)x : nullptr)

/*
 * Iterator is a pointer to a function that can take two Any arguments
 * and return an integer. Returns status code..
 */
typedef int (^DSHashmap_Iterator)(Any, Any);

/* We need to keep keys and values */
class (DSHashmapNode)
{
	char* key;
	int inUse;
	Any data;
};

/* A hashmap has some maximum size and current size,
 * as well as the data to hold. */
Ivar (DSHashmap) {
    Class isa;
	int tableSize;
	int size;
	DSHashmapNode* data;
}; 

/** Interface */
typedef char*   (*DSHashmapToString)    (const DSHashmap* const);
typedef int     (*DSHashmapForEach)     (DSHashmap* const this, DSHashmap_Iterator f, Any item);
typedef void    (*DSHashmapPut)         (const DSHashmap* const, int, const Any);
typedef Any     (*DSHashmapGet)         (const DSHashmap* const, int);
typedef void    (*DSHashmapRemove)      (const DSHashmap* const, int);
typedef void    (*DSHashmapDispose)     (DSHashmap* const);
typedef int     (*DSHashmapLength)      (const DSHashmap* const);
typedef UInt    (*DSHashmapHashInt)     (const DSHashmap* const, char*);
typedef int     (*DSHashmapHash)        (const DSHashmap* const, char*);
typedef int     (*DSHashmapRehash)      (const DSHashmap* const);

VTable (DSHashmap) {
    char*   (*ToString) (const DSHashmap* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    // bool    (*ReferenceEquals) (DSObject* const, DSObject* const);
    // bool    (*InstanceEquals) (DSObject* const, DSObject* const);
    /*
        * Get the current size of a hashmap
        */
    int         (*Length)       (const DSHashmap* const);
    // bool        (*IsEmpty)      (DSHashmap* const);
    // bool        (*Contains)     (DSHashmap* const, Any);
    // void        (*Clear)        (DSHashmap* const);
    // void        (*Add)          (DSHashmap* const, Any);
    /*
        * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
        */
    Any         (*Remove)       (DSHashmap* const);
    /*
    * Iteratively call func with argument (item, data) for
    * each element data in the hashmap. The function must
    * return a map status code. If it returns anything other
    * than MAP_OK the traversal is terminated. f must
    * not reenter any hashmap functions, or deadlock may arise.
    */
    int (*ForEach)  (DSHashmap* const, DSHashmap_Iterator, Any);

    /*
    * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
    */
    int (*Put)      (DSHashmap* const, char*, Any);

    /*
    * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
    */
    // int (*Get)      (Hashmap * const, char* key, Any *arg);
    Any (*Get)      (DSHashmap* const, char*);

    /*
     * Hashing function for a string
     */
    UInt (*HashInt) (DSHashmap* const, char*);
    
    /*
     * Return the integer of the location in data
     * to store the point to the item, or MAP_FULL.
     */
    int (*Hash)     (DSHashmap* const, char*);

    /*
     * Doubles the size of the hashmap, and rehashes all the elements
     */
    int (*Rehash)   (DSHashmap* const);

} ;

Singleton ($DSHashmap) {
    DSHashmap*(*Create) ();
};

/**
 * Hashmap API
 */
unsigned int overload HashInt(DSHashmap* const, char*);
int overload Hash(DSHashmap* const, char*);
int overload Rehash(DSHashmap* const);
int overload Put(DSHashmap* const, char*, Any);
Any overload Get(DSHashmap* const, char*);
int overload ForEach(DSHashmap* const, DSHashmap_Iterator, Any);
int overload Remove(DSHashmap* const, char*);
void overload Dispose(DSHashmap* const);
int overload Length(const DSHashmap* const);
char* overload ToString(const DSHashmap* const);
DSHashmap* DSHashmap_init(DSHashmap* const this);
DSHashmap* DSHashmap_alloc();
DSHashmap* NewDSHashmap();

#endif _DSHASHMAP_H_