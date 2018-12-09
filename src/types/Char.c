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
#include <dark/types/Char.h>
/**
 * Constructor
 * create a new Char
 * 
 * @param value of char
 * 
 */
Char Char_New(char value) {
    return Char_Ctor(new(Char), value);
}

/**
 * Initialize a new Char
 */
Char Char_Ctor(Char const this, char value)
{
    Number_Ctor(this);
    this->isa = isa(Char);
    this->value = value;
    return this;
}

/**
 * Compare two char primitives.
 * @param  x char to compare
 * @param  y char to compare
 * @return  0 x == y
 *         +1 x < y
 *         -1 x > y
 */
int Char_Compare(char x, char y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two Char objects.
 *
 * @param   other  Char to be compared
 * @return same as Char_Compare
 */
int Char_CompareTo(Char this, Char other) {
    return Char_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Char_IntValue(Char const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Char_LongValue(Char const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Char_FloatValue(Char const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Char_DoubleValue(Char const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Char_CharValue(Char const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Char_ShortValue(Char const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
char* Char_ToString(Char const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}

/**
 * Char Class Metadata
 */
register (Char)
{
    if (CharClass.isa == nullptr) {
        CharClass = (CharClass_t) {
            .isa            = &CharClass,
            .superclass     = &NumberClass,
            .name           = "Char",
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .Dispose        = ObjectClass.Dispose,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .ToString       = Char_ToString,
            .CompareTo      = Char_CompareTo,
            .IntValue       = Char_IntValue, 
            .LongValue      = Char_LongValue, 
            .FloatValue     = Char_FloatValue, 
            .DoubleValue    = Char_DoubleValue, 
            .CharValue      = Char_CharValue, 
            .ShortValue     = Char_ShortValue, 
        };
        AddMetadata(Char);
    }
    return &CharClass;
}


