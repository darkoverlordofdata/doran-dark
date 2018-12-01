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
#include <dark/Comparable.h>
/* 
 * Abstract Comparable
 */

static Exception(AbstractMethod);


int Comparable_CompareTo(Comparable this, Comparable other) {
    return this->CompareTo(this, other);
}
static short Abstract_CompareTo(Comparable const this, Comparable other) {
    return AbstractMethodException("Comparable_CompareTo");
}

char* Comparable_ToString(Comparable const this) {
    return this->ToString(this);
}
static char* Virtual_ToString(Comparable const this) {
    return "dark.Comparable";
}

/**
 * Initialize a new Comparable
 */
Comparable Comparable_Ctor(Comparable const this)
{
    DObject_Ctor(this);

    this->ToString      = &Virtual_ToString;
    this->CompareTo     = &Abstract_CompareTo;

    return this;
}

