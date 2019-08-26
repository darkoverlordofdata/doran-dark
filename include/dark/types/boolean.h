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
#include <limits.h>
#include <stdbool.h>
#include <dark/core/comparable.h>

#define BOOLEAN_BYTES      (sizeof(char))
#define BOOLEAN_SIZE       (BOOLEAN_BYTES * CHAR_BIT)
#define BOOLEAN_TYPE       (TYPE_BOOLEAN)

#define IsBoolean(object) _Generic((object), Boolean*: true, default: false)
#define AsBoolean(object) _Generic((object),                          \
                            Boolean*: (Boolean *)object,            \
                            default: nullptr)
/**
 * Boolean instance variables
 */
type (Boolean) 
{
    Class isa;
    bool value;
};

delegate (Boolean, New,          Boolean*, (Boolean*, const bool));
delegate (Boolean, ToString,     char*, (const Boolean* const));
delegate (Boolean, CompareTo,    int, (const Boolean* const, const Boolean* const));
delegate (Boolean, BoolValue,    bool, (const Boolean* const));

/**
 * Boolean vtable
 */
vtable (Boolean) 
{
    const BooleanToString       ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const BooleanCompareTo      CompareTo;
    // const bool    (*ParseBool)    (const char *const);    
};

/**
 * Boolean class methods & vars
 */
class (Boolean) 
{
    int (*Compare) (const bool, const bool);
    bool (*ParseBool) (char const*);
    int  Bytes;
    int  Size;
    int  Type;
    Boolean* True;
    Boolean* False;
};

static inline bool ParseBool(const char * const s);
method int Compare(const bool x, const bool y);
// static inline bool BoolValue(const Boolean*  const self);
/**
 * Put it all together
 */
static inline vptr(Boolean);
/**
 * Class Loader callback
 */
static inline Class ClassLoadBoolean(Class base) 
{
    Class cls = createClass(base, Boolean);
    addMethod(cls, Boolean,    ToString);
    addMethod(cls, Object,     Equals);
    addMethod(cls, Object,     GetHashCode);
    addMethod(cls, Object,     Dispose);
    addMethod(cls, Boolean,    CompareTo);
    /** 
     * Static constructor
     * set class properties 
     * 
     */
    static Boolean True;
    True.isa = cls; 
    True.value = true;

    static Boolean False;
    False.isa = cls;
    False.value = false;

    $Boolean.Bytes = BOOLEAN_BYTES;
    $Boolean.Size = BOOLEAN_SIZE;
    $Boolean.Type = BOOLEAN_TYPE;
    $Boolean.True = &True;
    $Boolean.False = &False;
    $Boolean.ParseBool = ParseBool;
    $Boolean.Compare = Compare;

    return cls;
}


/**
 * Constructor
 * create a new Boolean
 * 
 * @param value of bool
 * 
 */
method Boolean* New(Boolean* self, const bool value) {
    extends(Comparable);
    set_isa(Boolean);
    self->value = value;
    return self;
}


static inline bool ParseBool(const char * const s) {
    if (!strcmpi("y", s) 
    ||  !strcmpi("yes", s) 
    ||  !strcmpi("t", s) 
    ||  !strcmpi("true", s)) return true;
    else return false;
}

/**
 * Compare two boolean primitives.
 *
 * @param  x Boolean to compare
 * @param  y Boolean to compare
 * @return  0 x == y
 *         +1 x is true
 *         -1 y is true
 */
method int Compare(const bool x, const bool y) {
    return (x == y) ? 0 : ( x ? 1 : -1 );
}

/**
 * Compares two Boolean objects .
 *
 * @param   other  Boolean to be compared
 * @return same as Boolean_Compare
 */
method int CompareTo(const Boolean*  const self, const Boolean*  const other) {
    return Compare(self->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
method bool BoolValue(const Boolean*  const self) {
    return (bool)self->value;
}

/**
 * Returns the string value of self Boolean
 */
method char* ToString(const Boolean* const self) {
    return (char*)(self->value ? "true" : "false");
}

