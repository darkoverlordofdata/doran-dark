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
#ifndef _DSBOOLEAN_H_
#define _DSBOOLEAN_H_
#include <limits.h>
#include "../DSComparable.h"

#define BOOLEAN_BYTES      (sizeof(char))
#define BOOLEAN_SIZE       (BOOLEAN_BYTES * CHAR_BIT)
#define BOOLEAN_TYPE       (TYPE_BOOLEAN)

#define IsDSBoolean(object) _Generic((object), DSBoolean*: true, default: false)
#define AsDSBoolean(object) _Generic((object),                          \
                            DSBoolean*: (DSBoolean *)object,            \
                            default: nullptr)
/**
 * DSBoolean instance variables
 */
type (DSBoolean) {
    Class isa;
    bool value;
};

method_proto (DSBoolean, ToString,     char*, (const DSBoolean* const));
method_proto (DSBoolean, CompareTo,    int, (const DSBoolean* const, const DSBoolean* const));

/**
 * DSBoolean vtable
 */
vtable (DSBoolean) {
    const DSBooleanToString       ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSBooleanCompareTo      CompareTo;
    const bool    (*ParseBool)    (const char *const);    
};

/**
 * DSBoolean class methods & vars
 */
class (DSBoolean) {
    int (*Compare) (const bool, const bool);
    bool (*ParseBool) (char const*);
    int  Bytes;
    int  Size;
    int  Type;
    DSBoolean* True;
    DSBoolean* False;
};
function bool ParseBool(const char * const s);
method int Compare(bool x, bool y);
function bool BoolValue(const DSBoolean*  const this);


/**
 * Put it all together
 */
class_bind( DSBoolean );
class_override( ToString,         (DSBooleanToString)ToString, "$@:v" );
class_method( Equals,             (DSObjectEquals)Equals, "B@:@@" );
class_method( GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v" );
class_method( Dispose,            (DSObjectDispose)Dispose, "v@:v" );
class_override( CompareTo,        (DSBooleanCompareTo)CompareTo, "i@:@" );
class_method( BoolValue,          BoolValue, "B@:v" );
class_member( value, sizeof( int ), "B" );

/** 
 * Static constructor
 * set class properties 
 * 
 */
static DSBoolean True;
True.isa = isa; 
True.value = true;

static DSBoolean False;
False.isa = isa;
False.value = false;

$DSBoolean.Bytes = BOOLEAN_BYTES;
$DSBoolean.Size = BOOLEAN_SIZE;
$DSBoolean.Type = BOOLEAN_TYPE;
$DSBoolean.True = &True;
$DSBoolean.False = &False;
$DSBoolean.ParseBool = ParseBool;
$DSBoolean.Compare = Compare;
    
class_methodize;

/**
 * Constructor
 * create a new DSBoolean
 * 
 * @param value of bool
 * 
 */
function DSBoolean* DSBoolean_init(DSBoolean* this, const bool value) {
    DSComparable_init(this);
    this->isa = objc_getClass("DSBoolean");
    this->value = value;
    return this;
}

function DSBoolean* NewDSBoolean(const bool value) { 
    return DSBoolean_init(alloc(DSBoolean), value); }

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
 * @param  x DSBoolean to compare
 * @param  y DSBoolean to compare
 * @return  0 x == y
 *         +1 x is true
 *         -1 y is true
 */
method int Compare(bool x, bool y) {
    return (x == y) ? 0 : ( x ? 1 : -1 );
}

/**
 * Compares two DSBoolean objects .
 *
 * @param   other  DSBoolean to be compared
 * @return same as Boolean_Compare
 */
method int CompareTo(const DSBoolean*  const this, const DSBoolean*  const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
function bool BoolValue(const DSBoolean*  const this) {
    return (bool)this->value;
}

/**
 * Returns the string value of this DSBoolean
 */
method char* ToString(const DSBoolean* const this) {
    return this->value ? "true" : "false";
}

#endif // _DSBOOLEAN_H_
