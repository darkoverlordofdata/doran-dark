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
 * Generic hashmap manipulation functions
 *
 * Originally by Elliot C Back - http://elliottback.com/wp/hashmap-implementation-in-c/
 *
 * Modified by Pete Warden to fix a serious performance problem, support strings as keys
 * and removed thread synchronization - http://petewarden.typepad.com
 * 
 * https://petewarden.com/2010/01/07/c-hashmap/
 *
 */
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include "Collection.h"

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */


/*
 * Iterator is a pointer to a function that can take two Any arguments
 * and return an integer. Returns status code..
 */
typedef int (*Hashmap_Iterator)(Any, Any);

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
    Class isa;
	int tableSize;
	int size;
	HashmapNode data;
};

typedef struct HashmapClass_t
{
    union {
        CollectionClass_t base;
        struct 
        {
            Class       isa;
            Class       superclass;
            char*       name;
            const char* (*ToString)     (Hashmap const);
            bool        (*Equals)       (Object const, Object const);
            int         (*GetHashCode)  (Object const);
            void        (*Dispose)      (Hashmap const);
            bool        (*ReferenceEquals) (Object const objA, Object const objB);
            bool        (*InstanceEquals) (Object const objA, Object const objB);
            /*
             * Get the current size of a hashmap
             */
            int         (*Length)       (Hashmap const);
            bool        (*IsEmpty)      (Hashmap const);
            bool        (*Contains)     (Hashmap const, Any value);
            void        (*Clear)        (Hashmap const);
            void        (*Add)          (Hashmap const, Any value);
            /*
             * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
             */
            Any         (*Remove)       (Hashmap const);

        };
    };

    /*
    * Iteratively call func with argument (item, data) for
    * each element data in the hashmap. The function must
    * return a map status code. If it returns anything other
    * than MAP_OK the traversal is terminated. f must
    * not reenter any hashmap functions, or deadlock may arise.
    */
    int (*Iterate)  (Hashmap const, Hashmap_Iterator func, Any item);

    /*
    * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
    */
    int (*Put)      (Hashmap const, char* key, Any value);

    /*
    * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
    */
    // int (*Get)      (Hashmap * const, char* key, Any *arg);
    Any (*Get)      (Hashmap const, char* key);

    /*
     * Hashing function for a string
     */
    UInt (*HashInt) (Hashmap const, char* keystring);
    
    /*
     * Return the integer of the location in data
     * to store the point to the item, or MAP_FULL.
     */
    int (*Hash)     (Hashmap const, char* key);

    /*
     * Doubles the size of the hashmap, and rehashes all the elements
     */
    int (*Rehash)   (Hashmap const);

};

/**
 * Hashmap API
 */
unsigned int overload HashInt(Hashmap const, char* keystring);
int overload Hash(Hashmap const, char* key);
int overload Rehash(Hashmap const);
int overload Put(Hashmap const, char* key, Any value);
Any overload Get(Hashmap const, char* key);
int overload Iterate(Hashmap const, Hashmap_Iterator f, Any item);
int overload Remove(Hashmap const, char* key);
void overload Dispose(Hashmap const);
int overload Length(Hashmap const);
const char* overload ToString(Hashmap const);
Hashmap Hashmap_New();

#endif _HASHMAP_H_