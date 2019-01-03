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
#include <dark/DSComparable.h>
/* 
 * Abstract Comparable
 */

static DSException(AbstractMethod);
begin_class(DSComparable) 

    method("ToString", (DSComparableToString)ToString, "$@:v");
    method("CompareTo", (DSComparableCompareTo)CompareTo, "i@:@");

end_class

/**
 * Initialize a new DSComparable
 */
DSComparable* DSComparable_init(DSComparable* const this)
{
    DSObject_init(this);
    this->isa = &DSComparableClass;
    return this;
}

int overload CompareTo(const DSComparable* const this, const DSComparable* const other) {
    return this->isa->CompareTo(this, other);
}

int DSComparable_CompareTo(const DSComparable* const this, const DSComparable* const other) {
    return DSAbstractMethodException("Comparable_CompareTo");
}

char* DSComparable_ToString(const DSComparable* const this) {
    return this->isa->ToString(this);
}

char* overload ToString(const DSComparable* const this) {
    return "dark.DSComparable";
}

/**
 * DSComparable Class Metadata
 */
DSDefine(DSComparable, DSObject, cls, {
    cls->ToString        = DSComparable_ToString;
    cls->CompareTo       = DSComparable_CompareTo;
});

