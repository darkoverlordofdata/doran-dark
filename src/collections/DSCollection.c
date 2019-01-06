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
#include <stdarg.h>
#include <dark/collections/DSCollection.h>
/**
 * Generic Collection implementation
 */
static DSException(AbstractMethod);
$implementation(DSCollection)

$method(ToString,           DSObject_ToString, "$@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            DSObject_Dispose, "v@:v");
// $method(Length,             (IMP)DSCollection_Length, "i@:v");
// $method(Add,                (IMP)DSCollection_Add, "v@:@");

$end;

/**
 * Initialize a new Array
 */
DSCollection* DSCollection_init(DSCollection* const this)
{
    DSObject_init(this);
    this->isa = getDSCollectionIsa();
    return this;
}

/**
 * Number of items in collection
 */
int overload Length(DSCollection* const this)
{
    return _vptr(this)->Length(this);
}
int DSCollection_Length(DSCollection* const this)
{
    return DSAbstractMethodException("Collection_Length");
}

void Collection_Add(DSCollection* const this, Any data)
{
    _vptr(this)->Add(this, data);
}
void DSCollection_Add(DSCollection* const this, Any data)
{
    DSAbstractMethodException("Collection_Add");
}

