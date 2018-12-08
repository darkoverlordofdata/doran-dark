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
#include <dark/collections/Array.h>
/**
 * Generic Array implementation
 */

int overload Length(Array const this)
{
    return this->length;
}
/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
void Resize(Array const this, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", this->capacity, capacity);
    #endif

    void **data = realloc(this->data, sizeof(Any) * capacity);
    if (data) {
        this->data = data;
        this->capacity = capacity;
    }
}

/**
 * Add item to the end of vector
 * 
 * @param item the data to add
 */
void overload Add(Array const this, Any item)
{
    if (this->capacity == this->length) {
        this->isa->Resize(this, this->capacity * 2);
    }
    this->data[this->length++] = item;
}

/**
 * Set vector item at index
 * 
 * @param index to add at
 * @param item the data to add
 */
void Set(Array const this, int index, Any item)
{
    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
Any Get(Array const this, int index)
{
    if (index >= 0 && index < this->length)
        return this->data[index];
    return nullptr;
}

/**
 * Delete vector item at index
 * 
 * @param index to delete
 */
void overload Remove(Array const this, int index)
{
    if (index < 0 || index >= this->length)
        return;

    this->data[index] = nullptr;

    for (int i = index; i < this->length - 1; i++) {
        this->data[i] = this->data[i + 1];
        this->data[i + 1] = nullptr;
    }

    this->length--;

    if (this->length > 0 && this->length == this->capacity / 4)
        this->isa->Resize(this, this->capacity / 2);
}

/**
 * Free the vector
 */
void overload Dispose(Array const this)
{
    // delete(this->data);
}

void overload Clear(Array const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}


/**
 * ToString
 */
const char* overload ToString(Array const this)
{
    return "dark.collections.Array";
}

/**
 * Array Class Metadata
 */
register (Array)
{
    if (ArrayClass.isa == nullptr) {
        ArrayClass = (ArrayClass_t) {
            .isa            = &ArrayClass,
            .superclass     = &CollectionClass,
            .name           = "Array",
            .Equals         = ObjectClass.Equals,
            .GetHashCode    = ObjectClass.GetHashCode,
            .ReferenceEquals= ObjectClass.ReferenceEquals,
            .InstanceEquals = ObjectClass.InstanceEquals,
            .ToString       = ToString,
            .Dispose        = Dispose,
            .Length         = Length,
            .Add            = Add,
            .Remove         = Remove,
            .Resize         = Resize,
            .Set            = Set,
            .Get            = Get,
            .Clear          = Clear,
        };
    }
    return &ArrayClass;
}

/**
 * Initialize a new Array
 */
Array Array_Ctor(Array const this, int capacity)
{
    Collection_Ctor(this);
    this->isa = isa(Array);
    this->capacity = capacity == 0 ? ARRAY_INIT_CAPACITY : capacity;
    this->length = 0;
    this->data = dark_malloc (this->capacity * sizeof(Any));
    return this;
}

/**
 * new Array
 * 
 * allocates room for capacity, sets used to 0
 * 
 * @param capacity initial max size of vector
 * 
 */
Array overload Array_New(int capacity)
{
    return Array_Ctor(new(Array), capacity);
}

Array overload Array_New(void)
{
    return Array_Ctor(new(Array), 4);
}

/**
 * new Array
 * 
 * allocate a vector the size of the param list
 * and then fill values from params.
 * 
 * @param count number of initial values
 * @param ... list of initial values
 * 
 */
Array Array_Variadic(int count, ...)
{
    Array v = Array_Ctor(new(Array), count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        v->data[i] = va_arg(args, Any);
    va_end(args);
    v->length = count;
    return v;
}
