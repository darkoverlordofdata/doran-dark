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
#include <dark/collections/Collection.h>
/**
 * Generic Collection implementation
 */
static Exception(AbstractMethod);

/**
 * Initialize a new Array
 */
Collection Collection_Ctor(Collection const this)
{
    Object_Ctor(this);
    this->isa = isa(Collection);
    return this;
}

/**
 * Number of items in collection
 */
int overload Length(Collection const this)
{
    return this->isa->Length(this);
}
static int Abstract_Length(Collection const this)
{
    return AbstractMethodException("Collection_Length");
}

void Collection_Add(Collection const this, Any data)
{
    this->isa->Add(this, data);
}
static void Abstract_Add(Collection const this, Any data)
{
    AbstractMethodException("Collection_Add");
}

/**
 * Collection Class Metadata
 */
register (Collection)
{
    if (CollectionClass.isa == nullptr) {
        CollectionClass = (CollectionClass_t) {
            .isa            = &CollectionClass,
            .superclass     = &ObjectClass,
            .name           = "Collection",
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .Dispose        = ObjectClass.Dispose,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .Length         = Abstract_Length,
            .Add            = Abstract_Add,
        };
        AddMetadata(Collection);
    }
    return &CollectionClass;
}

