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
#include <dark/types/Boolean.h>
/* 
 * Boolean implementation
 */

bool ParseBool(char* s)
{
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
int overload Compare(bool x, bool y) {
    return (x == y) ? 0 : ( x ? 1 : -1 );
}

/**
 * Compares two Boolean objects .
 *
 * @param   other  Boolean to be compared
 * @return same as Boolean_Compare
 */
int overload CompareTo(Boolean this, Boolean other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
bool BoolValue(Boolean const this) {
    return (bool)this->value;
}

/**
 * Returns the string value of this Boolean
 */
char* overload ToString(Boolean const this)
{
    return this->value ? "true" : "false";
}

/**
 * Boolean Class Metadata
 */
register (Boolean)
{
    /** class constant: True */
    static const Boolean_t True = {
        .isa  = &BooleanClass,
        .value = true
    };
    /** class constant: False */
    static const Boolean_t False = {
        .isa  = &BooleanClass,
        .value = false
    };

    if (BooleanClass.isa == nullptr) {
        BooleanClass = (BooleanClass_t) {
            .isa            = &BooleanClass,
            .superclass     = &ComparableClass,
            .name           = "Boolean",
            /** Instance members */
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .Dispose        = ObjectClass.Dispose,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .ToString       = ToString,
            .CompareTo      = CompareTo,
            /** Class members */
            .BoolValue      = BoolValue,
            .Bytes          = BOOLEAN_BYTES,
            .Size           = BOOLEAN_SIZE,
            .Type           = BOOLEAN_TYPE,
            .True           = &True,
            .False          = &False,
        };
    }
    return &BooleanClass;
}

/**
 * Initialize a new Boolean
 */
Boolean Boolean_Ctor(Boolean const this, bool value)
{
    Comparable_Ctor(this);
    this->isa = isa(Boolean);
    this->value = value;
    return this;
}

/**
 * new Boolean
 * 
 * create a new Boolean
 * 
 * @param value of bool
 * 
 */
Boolean Boolean_New(bool value)
{
    return Boolean_Ctor(new(Boolean), value);
}

