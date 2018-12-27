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
struct Char *Char_Ctor(struct Char *const this, char value)
{
    Number_Ctor(this);
    this->isa = isa(Char);
    this->value = value;
    return this;
}

static struct Char* Create(char value) { 
    return Char_Ctor(new(Char), value); 
}

/**
 * Char Class Metadata
 */
register (Char)
{
    if (Char.isa == nullptr) {
        Char = (struct CharClass) {
            .isa            = &Char,
            .superclass     = &Number,
            .name           = "Char",
            .Equals         = Object.Equals,
            .GetHashCode    = Object.GetHashCode,
            .Dispose        = Object.Dispose,
            .ReferenceEquals= Object.ReferenceEquals,
            .InstanceEquals = Object.InstanceEquals,
            
            .ToString       = Char_ToString,
            .CompareTo      = Char_CompareTo,
            .IntValue       = Char_IntValue, 
            .LongValue      = Char_LongValue, 
            .FloatValue     = Char_FloatValue, 
            .DoubleValue    = Char_DoubleValue, 
            .CharValue      = Char_CharValue, 
            .ShortValue     = Char_ShortValue, 
            .Create         = Create,
        };
        AddMetadata(Char);
    }
    return &Char;
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
int Char_CompareTo(struct Char *const this, struct Char *const other) {
    return Char_Compare(this->value, other->value);
}

/**
 * Returns the value of this value cast as an int
 */
int Char_IntValue(struct Char *const this) {
    return (int)this->value;
}

/**
 * Returns the value of this value cast as a long
 */
long Char_LongValue(struct Char *const this) {
    return (long)this->value;
}

/**
 * Returns the value of this value cast as a float
 */
float Char_FloatValue(struct Char *const this) {
    return (float)this->value;
}

/**
 * Returns the value of this value cast as a double
 */
double Char_DoubleValue(struct Char *const this) {
    return (double)this->value;
}

/**
 * Returns the value of this value cast as a char
 */
char Char_CharValue(struct Char *const this) {
    return (char)this->value;
}

/**
 * Returns the value of this value cast as a short
 */
short Char_ShortValue(struct Char *const this) {
    return (short)this->value;
}


/**
 * Returns the string value of this Char
 */
char* Char_ToString(struct Char *const this)
{
    static char str[2];
    sprintf(str, "%c", this->value);
    return str;
}


