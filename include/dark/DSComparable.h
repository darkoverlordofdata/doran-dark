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
#ifndef _DSCOMPARABLE_H_
#define _DSCOMPARABLE_H_
#include "DSObject.h"

// #define IsDSComparable(x) (x->isa == &DSComparableClass)
// #define AsDSComparable(x) (IsDSComparable(x) ? (DSComparable *)x : nullptr)

/**
 * DSComparable Class
 */
Ivar (DSComparable) {
    Class isa;
};

typedef DSComparable* (*DSComparableCreate) ();
typedef char*   (*DSComparableToString)  (const DSComparable* const);
typedef int     (*DSComparableCompareTo)  (const DSComparable* const, const DSComparable* const);

/**
 * DSComparable Vtable
 */
VTable (DSComparable) {
    char*   (*ToString) (const DSComparable* const);
    bool    (*Equals) (DSObject* const, DSObject* const);
    int     (*GetHashCode) (DSObject* const);
    void    (*Dispose) (DSObject* const);
    int     (*CompareTo) (const DSComparable* const, const DSComparable* const);
};


int overload CompareTo(const DSComparable* const, const DSComparable* const);
char* overload ToString(const DSComparable* const this);

#endif _DSCOMPARABLE_H_
