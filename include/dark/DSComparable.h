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
#include "DSException.h"

#define IsDSComparable(object) _Generic((object), DSComparable*: true, default: false)
#define AsDSComparable(object) _Generic((object),                   \
                            DSComparable*: (DSComparable *)object,  \
                            default: nullptr)

/**
 * DSComparable Class
 */
ivar (DSComparable) {
    Class isa;
};

// typedef DSComparable* (*DSComparableCreate) ();
// typedef char*   (*DSComparableToString)  (const DSComparable* const);
// typedef int     (*DSComparableCompareTo)  (const DSComparable* const, const DSComparable* const);

method (DSComparable, ToString,        char*,    (const DSComparable* const));
method (DSComparable, CompareTo,       int,      (const DSComparable* const, const DSComparable* const));


/**
 * DSComparable Vtable
 */
vtable (DSComparable) {
    const DSComparableToString      ToString;
    const DSObjectEquals            Equals;
    const DSObjectGetHashCode       GetHashCode;
    const DSObjectDispose           Dispose;
    const DSComparableCompareTo     CompareTo;

    // const char*   (*ToString)     (const DSComparable* const);
    // const bool    (*Equals)       (const DSObject* const, DSObject* const);
    // const int     (*GetHashCode)  (const DSObject* const);
    // const void    (*Dispose)      (const DSObject* const);
    // const int     (*CompareTo)    (const DSComparable* const, const DSComparable* const);
};


// int overload CompareTo(const DSComparable* const, const DSComparable* const);
// char* overload ToString(const DSComparable* const this);

#endif _DSCOMPARABLE_H_
