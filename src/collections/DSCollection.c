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

/**
 * Initialize a new Array
 */
DSCollection* DSCollection_init(DSCollection* const this)
{
    DSObject_init(this);
    this->isa = IZA(DSCollection);
    return this;
}

/**
 * Number of items in collection
 */
int overload Length(DSCollection* const this)
{
    return this->isa->Length(this);
}
int DSCollection_Length(DSCollection* const this)
{
    return DSAbstractMethodException("Collection_Length");
}

void Collection_Add(DSCollection* const this, Any data)
{
    this->isa->Add(this, data);
}
void DSCollection_Add(DSCollection* const this, Any data)
{
    DSAbstractMethodException("Collection_Add");
}

Class implement_DSCollection(Class super) 
{
    Class obj = objc_allocateClassPair(super, "DSCollection", 0);
    class_addMethod(obj, $length, (IMP)DSCollection_Length, "i@:v");
    class_addMethod(obj, $add, (IMP)DSCollection_Add, "v@:@");
    return obj;

}
/**
 * Collection Class Metadata
 */
DSDefine(DSCollection, DSObject, cls, {
    cls->Length         = DSCollection_Length;
    cls->Add            = DSCollection_Add;
});
