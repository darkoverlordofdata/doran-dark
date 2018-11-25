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
#include <dark/types/Number.h>
#include <dark/types/Long.h>
/* 
 * Long implementation
 */

/**
 * Compares two {@code long} values numerically.
 * The value returned is identical to what would be returned by:
 * <pre>
 *    Long.valueOf(x).compareTo(Long.valueOf(y))
 * </pre>
 *
 * @param  x the first {@code long} to compare
 * @param  y the second {@code long} to compare
 * @return the value {@code 0} if {@code x == y};
 *         a value less than {@code 0} if {@code x < y}; and
 *         a value greater than {@code 0} if {@code x > y}
 */
int Long_Compare(long x, long y) {
    return (x < y) ? -1 : (( x == y ) ? 0 : 1);
}

/**
 * Compares two {@code Long} objects numerically.
 *
 * @param   anotherLong   the {@code Long} to be compared.
 * @return  the value {@code 0} if this {@code Long} is
 *          equal to the argument {@code Long}; a value less than
 *          {@code 0} if this {@code Long} is numerically less
 *          than the argument {@code Long}; and a value greater
 *          than {@code 0} if this {@code Long} is numerically
 *           greater than the argument {@code Long} (signed
 *           comparison).
 */
int Long_CompareTo(Long this, Long other) {
    return Long_Compare(this->value, other->value);
}

/**
 * Returns the value of this {@code Long} as an {@code int} after
 * a narrowing primitive conversion.
 */
int Long_IntValue(Long const this) {
    return (int)this->value;
}

/**
 * Returns the value of this {@code Long} as a
 * {@code long} value.
 */
long Long_LongValue(Long const this) {
    return (long)this->value;
}

/**
 * Returns the value of this {@code Long} as a {@code float} after
 * a widening primitive conversion.
 */
float Long_FloatValue(Long const this) {
    return (float)this->value;
}

/**
 * Returns the value of this {@code Long} as a {@code double}
 * after a widening primitive conversion.
 */
double Long_DoubleValue(Long const this) {
    return (double)this->value;
}

/**
 * Returns the value of this {@code Long} as a {@code byte} after
 * a narrowing primitive conversion.
 */
char Long_CharValue(Long const this) {
    return (char)this->value;
}

/**
 * Returns the value of this {@code Long} as a {@code short} after
 * a narrowing primitive conversion.
 */
short Long_ShortValue(Long const this) {
    return (short)this->value;
}


/**
 * Initialize a new Long
 */
Long Long_Ctor(Long const this, long value)
{
    DObject_Ctor(this);

    // this->ToString      = &Long_ToString;
    this->CompareTo     = &Long_CompareTo;
    this->IntValue      = &Long_IntValue; 
    this->LongValue     = &Long_LongValue; 
    this->FloatValue    = &Long_FloatValue; 
    this->DoubleValue   = &Long_DoubleValue; 
    this->CharValue     = &Long_CharValue; 
    this->ShortValue    = &Long_ShortValue; 

    this->value = value;
    return this;
}

/**
 * new Long
 * 
 * create a new long
 * 
 * @param value of long
 * 
 */
Long Long_New(long value)
{
    return Long_Ctor(new(Long), value);
}
