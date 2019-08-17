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
#include "DSObject.h"
#include "DSException.h"

#define IsDSComparable(object) _Generic((object), DSComparable*: true, default: false)
#define AsDSComparable(object) _Generic((object),                   \
                            DSComparable*: (DSComparable *)object,  \
                            default: nullptr)

/**
 * DSComparable Class
 */
type (DSComparable) {
    Class isa;
};

method_proto (DSComparable, ToString,        char*,    (const DSComparable* const));
method_proto (DSComparable, CompareTo,       int,      (const DSComparable* const, const DSComparable* const));


/**
 * DSComparable Vtable
 */
vtable (DSComparable) {
    const DSComparableToString      ToString;
    const DSObjectEquals            Equals;
    const DSObjectGetHashCode       GetHashCode;
    const DSObjectDispose           Dispose;
    const DSComparableCompareTo     CompareTo;
};

/**
 * Create the class loader
 */
class_load(DSComparable);
class_method(ToString,           (DSComparableToString)ToString, "$@:v");
class_method(Equals,             (DSObjectEquals)Equals, "B@:@@");
class_method(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
class_method(Dispose,            (DSObjectDispose)Dispose, "v@:v");
class_method(ReferenceEquals,    ReferenceEquals, "@:v");
class_method(InstanceEquals,     InstanceEquals, "$@:v");
class_method(CompareTo,          (DSComparableCompareTo)CompareTo, "i@:@");
class_fini;

//=======================================================================//
//              I M P L E M E N T A T I O N                              //          
//=======================================================================//

function DSComparable* DSComparable_init(DSComparable* const this)
{
    DSObject_init(this);
    this->isa = objc_getClass("DSComparable");
    return this;
}

method int CompareTo(const DSComparable* const this, const DSComparable* const other) {
    return _vptr(DSComparable)->CompareTo(this, other);
}

method char* ToString(const DSComparable* const this) {
    return "dark.DSComparable";
}

