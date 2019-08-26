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
#include <dark/core/object.h>
#include <dark/core/exception.h>

#define IsComparable(object) _Generic((object), Comparable*: true, default: false)
#define AsComparable(object) _Generic((object),                   \
                            Comparable*: (Comparable *)object,  \
                            default: nullptr)

/**
 * Comparable Class
 */
type (Comparable) 
{
    Class isa;
};

delegate (Comparable, New,             Comparable*, (Comparable*));
delegate (Comparable, ToString,        char*,    (const Comparable* const));
delegate (Comparable, CompareTo,       int,      (const Comparable* const, const Comparable* const));


/**
 * Comparable Vtable
 */
vtable (Comparable) 
{
    const ComparableToString      ToString;
    const ObjectEquals            Equals;
    const ObjectGetHashCode       GetHashCode;
    const ObjectDispose           Dispose;
    const ComparableCompareTo     CompareTo;
};

static inline vptr(Comparable);
/**
 * Create the class loader
 */
static inline Class ClassLoadComparable(Class base) 
{
    Class cls = createClass(base, Comparable);
    addMethod(cls, Comparable, ToString);
    addMethod(cls, Object,     Equals);
    addMethod(cls, Object,     GetHashCode);
    addMethod(cls, Object,     Dispose);
    addMethod(cls, Object,     ReferenceEquals);
    addMethod(cls, Object,     InstanceEquals);
    addMethod(cls, Comparable, CompareTo);
    return cls;
}

//=======================================================================//
//              I M P L E M E N T A T I O N                              //          
//=======================================================================//

method Comparable* New(Comparable* const self)
{
    extends(Object);
    set_isa(Comparable);
    return self;
}

method int CompareTo(const Comparable* const self, const Comparable* const other) {
    return virtual(Comparable)->CompareTo(self, other);
}

method char* ToString(const Comparable* const self) {
    return "dark.Comparable";
}

