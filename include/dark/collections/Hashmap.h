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
 *
 * Hashmap is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#pragma once
#ifndef DARK_HASHMAP_H_
#define DARK_HASHMAP_H_
#include "Collection.h"

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */

#define IsHashmap(x) (x->isa == &Hashmap)
#define AsHashmap(x) (IsHashmap(x) ? (struct Hashmap *)x : nullptr)

/*
 * Iterator is a pointer to a function that can take two Any arguments
 * and return an integer. Returns status code..
 */
typedef int (^Hashmap_Iterator)(Any, Any);

/* We need to keep keys and values */
class (HashmapNode)
{
	char* key;
	int inUse;
	Any data;
};

/* A hashmap has some maximum size and current size,
 * as well as the data to hold. */
class (Hashmap)
{
    struct HashmapClass * isa;
	int tableSize;
	int size;
	struct HashmapNode * data;
};

struct HashmapClass
{
    union {
        struct CollectionClass base;
        struct 
        {
            struct Class * isa;
            struct Class * superclass;
            char* name;
            char*   (*ToString) (struct Hashmap *const);
            bool    (*Equals) (struct Object *const, struct Object *const);
            int     (*GetHashCode) (struct Object *const);
            void    (*Dispose) (struct Object *const);
            bool    (*ReferenceEquals) (struct Object *const, struct Object *const);
            bool    (*InstanceEquals) (struct Object *const, struct Object *const);
            THashmap(*Create) ();
            /*
             * Get the current size of a hashmap
             */
            int         (*Length)       (struct Hashmap *const);
            bool        (*IsEmpty)      (struct Hashmap *const);
            bool        (*Contains)     (struct Hashmap *const, Any);
            void        (*Clear)        (struct Hashmap *const);
            void        (*Add)          (struct Hashmap *const, Any);
            /*
             * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
             */
            Any         (*Remove)       (struct Hashmap *const);

        };
    };

    /*
    * Iteratively call func with argument (item, data) for
    * each element data in the hashmap. The function must
    * return a map status code. If it returns anything other
    * than MAP_OK the traversal is terminated. f must
    * not reenter any hashmap functions, or deadlock may arise.
    */
    int (*ForEach)  (struct Hashmap *const, Hashmap_Iterator, Any);

    /*
    * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
    */
    int (*Put)      (struct Hashmap *const, char*, Any);

    /*
    * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
    */
    // int (*Get)      (Hashmap * const, char* key, Any *arg);
    Any (*Get)      (struct Hashmap *const, char*);

    /*
     * Hashing function for a string
     */
    UInt (*HashInt) (struct Hashmap *const, char*);
    
    /*
     * Return the integer of the location in data
     * to store the point to the item, or MAP_FULL.
     */
    int (*Hash)     (struct Hashmap *const, char*);

    /*
     * Doubles the size of the hashmap, and rehashes all the elements
     */
    int (*Rehash)   (struct Hashmap *const);

};

/**
 * Hashmap API
 */
unsigned int overload HashInt(struct Hashmap *const, char*);
int overload Hash(struct Hashmap *const, char*);
int overload Rehash(struct Hashmap *const);
int overload Put(struct Hashmap *const, char*, Any);
Any overload Get(struct Hashmap *const, char*);
int overload ForEach(struct Hashmap *const, Hashmap_Iterator, Any);
int overload Remove(struct Hashmap *const, char*);
void overload Dispose(struct Hashmap *const);
int overload Length(struct Hashmap *const);
char* overload ToString(struct Hashmap *const);

#endif DARK_HASHMAP_H_