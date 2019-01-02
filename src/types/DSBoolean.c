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
#include <dark/types/DSBoolean.h>
/**
 * Constructor
 * create a new DSBoolean
 * 
 * @param value of bool
 * 
 */
DSBoolean* DSBoolean_init(DSBoolean* this, bool value)
{
    DSComparable_init(this);
    this->isa = IZA(DSBoolean);
    this->value = value;
    return this;
}

bool DSParseBool(const char * const s)
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
 * @param  x DSBoolean to compare
 * @param  y DSBoolean to compare
 * @return  0 x == y
 *         +1 x is true
 *         -1 y is true
 */
int overload Compare(bool x, bool y) {
    return (x == y) ? 0 : ( x ? 1 : -1 );
}

/**
 * Compares two DSBoolean objects .
 *
 * @param   other  DSBoolean to be compared
 * @return same as Boolean_Compare
 */
int overload CompareTo(const DSBoolean*  const this, const DSBoolean*  const other) {
    return Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
bool BoolValue(const DSBoolean*  const this) {
    return (bool)this->value;
}

/**
 * Returns the string value of this DSBoolean
 */
char* overload ToString(const DSBoolean*  const this)
{
    return this->value ? "true" : "false";
}


DSBoolean* $DSBoolean(bool value) { 
    return DSBoolean_init(class_alloc(DSBoolean), value); 
}

/** class constant: True */
static const DSBoolean True = {
    .isa  = &DSBooleanClass,
    .value = true
};

/** class constant: False */
static const DSBoolean False = {
    .isa  = &DSBooleanClass,
    .value = false
};

// void implement_DSBoolean(Class obj) 
// {
//     class_addMethod(obj, $toString, (IMP)ToString, "$@:v");
//     class_addMethod(obj, $equals, (IMP)DSObject_Equals, "B@:@@");
//     class_addMethod(obj, $getHashCode, (IMP)DSObject_GetHashCode, "l@:v");
//     class_addMethod(obj, $dispose, (IMP)DSObject_Dispose, "v@:v");
//     class_addMethod(obj, $referenceEquals, (IMP)ReferenceEquals, "$@:v");
//     class_addMethod(obj, $instanceEquals, (IMP)InstanceEquals, "$@:v");
//     class_addMethod(obj, $compareTo, (IMP)DSComparable_CompareTo, "i@:@");

//     class_addIvar(obj, "value", sizeof(int), log2(sizeof(int)), "i");
// }

/**
 * DSBoolean Class Metadata
 */
DSDefine(DSBoolean, DSComparable, cls, {
    cls->ToString       = ToString;
    cls->CompareTo      = CompareTo;
    cls->BoolValue      = BoolValue;
    cls->Bytes          = BOOLEAN_BYTES;
    cls->Size           = BOOLEAN_SIZE;
    cls->Type           = BOOLEAN_TYPE;
    cls->True           = &True;
    cls->False          = &False;
    cls->Create         = $DSBoolean;
});

