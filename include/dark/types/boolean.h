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
type (Boolean) {
    Class isa;
    bool value;
};

method_proto (Boolean, ToString,     char*, (const Boolean* const));
method_proto (Boolean, CompareTo,    int, (const Boolean* const, const Boolean* const));

/**
 * Boolean vtable
 */
vtable (Boolean) {
    const BooleanToString       ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const BooleanCompareTo      CompareTo;
    const bool    (*ParseBool)    (const char *const);    
};

/**
 * Boolean class methods & vars
 */
class (Boolean) {
    int (*Compare) (const bool, const bool);
    bool (*ParseBool) (char const*);
    int  Bytes;
    int  Size;
    int  Type;
    Boolean* True;
    Boolean* False;
};
function bool ParseBool(const char * const s);
method int Compare(bool x, bool y);
function bool BoolValue(const Boolean*  const this);
/**
 * Put it all together
 */
class_load( Boolean );
class_override( ToString,   (BooleanToString)ToString, "$@:v" );
class_method( Equals,       (ObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,  (ObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,      (ObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,  (BooleanCompareTo)CompareTo, "i@:@" );
class_method( BoolValue,    BoolValue, "B@:v" );
class_member( value,        sizeof( int ), "B" );

/** 
 * Static constructor
 * set class properties 
 * 
 */
static Boolean True;
True.isa = isa; 
True.value = true;

static Boolean False;
False.isa = isa;
False.value = false;

$Boolean.Bytes = BOOLEAN_BYTES;
$Boolean.Size = BOOLEAN_SIZE;
$Boolean.Type = BOOLEAN_TYPE;
$Boolean.True = &True;
$Boolean.False = &False;
$Boolean.ParseBool = ParseBool;
$Boolean.Compare = Compare;
    
class_fini;

/**
 * Constructor
 * create a new Boolean
 * 
 * @param value of bool
 * 
 */
function Boolean* Boolean_init(Boolean* this, const bool value) {
    Comparable_init(this);
    this->isa = objc_getClass("Boolean");
    this->value = value;
    return this;
}

function Boolean* NewBoolean(const bool value) { 
    return Boolean_init(alloc(Boolean), value); }

function bool ParseBool(const char * const s) {
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
method int Compare(bool x, bool y) {
    return (x == y) ? 0 : ( x ? 1 : -1 );
}

/**
 * Compares two Boolean objects .
 *
 * @param   other  Boolean to be compared
 * @return same as Boolean_Compare
 */
method int CompareTo(const Boolean*  const this, const Boolean*  const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
function bool BoolValue(const Boolean*  const this) {
    return (bool)this->value;
}

/**
 * Returns the string value of this Boolean
 */
method char* ToString(const Boolean* const this) {
    return this->value ? "true" : "false";
}

