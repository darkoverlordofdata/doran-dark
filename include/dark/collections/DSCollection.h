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
#ifndef _DSCOLLECTION_H_
#define _DSCOLLECTION_H_
#include "../DSObject.h"

#define IsDSCollection(x) (x->isa == &DSCollection)
#define AsDSCollection(x) (IsDSCollection(x) ? (DSCollection*)x : nullptr)

/**
 * Base collection interface for sequential collections such as list and array
 */
Ivar (DSCollection) {
    Class isa;
};


/**
 * Collection metaclass
 */
VTable (DSCollection) {
    char*   (*ToString) (DSCollection* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    bool    (*ReferenceEquals) (DSObject* const , DSObject* const);
    bool    (*InstanceEquals) (DSObject* const, DSObject* const);

    // int     (*Length) (DSCollection* const);
    // bool    (*IsEmpty) (DSCollection* const);
    // bool    (*Contains) (DSCollection* const, Any);
    // void    (*Clear) (DSCollection* const);
    // bool    (*Add) (DSCollection* const, Any);
    // bool    (*Remove) (DSCollection* const, Any);
    
};

Singleton ($DSCollection) {
    DSCollection*  (*Create) ();
};

/**
 * Collection API
 */
int overload Length(DSCollection* const);
void overload Add(DSCollection* const, Any);
DSCollection* DSCollection_init(DSCollection* const);
int DSCollection_Length(DSCollection* const);
void DSCollection_Add(DSCollection* const, Any);

/**
 * AddAll
 * ToArray
*/
#endif _DSCOLLECTION_H_
