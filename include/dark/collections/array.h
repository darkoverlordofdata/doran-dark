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
#pragma once
#include <dark/types.h>
#include <dark/core/object.h>
#include <dark/types/string.h>
#include <dark/functional/either.h>
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4


#define IsArray(object) _Generic((object), Array*: true, default: false)
#define AsArray(object) _Generic((object),                            \
                            Array*: (Array *)object,                \
                            default: nullptr)


type (Array) {
    Class isa;
    Class typeOf;
    int length;
    // void **data;
    uchar **data;
    int capacity;
};


ctor_proto(Array);
ctor_proto(Array, int);
ctor_proto(Array, Class);
ctor_proto(Array, Class, int);

interface (Array, ToString,  char*,      (const Array* const) );
interface (Array, Dispose,   void,       (Array* const) );
interface (Array, Length,    int,        (const Array* const) );
interface (Array, IsEmpty,   bool,       (Array* const) );
interface (Array, Contains,  bool,       (Array* const, Object*) );
interface (Array, Clear,     void,       (Array* const) );
interface (Array, Add,       Either*,    (Array* const, const Object*) );
interface (Array, Remove,    void,       (Array* const, int) );
interface (Array, Resize,    void,       (Array* const, int) );
interface (Array, Set,       Either*,    (Array* const, int, const Object*) );
interface (Array, Get,       Object*,  (Array* const, int) );

vtable (Array) {
    const ArrayToString         ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const ArrayLength           Length;
    const ArrayIsEmpty          IsEmpty;
    const ArrayContains         Contains;
    const ArrayClear            Clear;
    const ArrayAdd              Add;
    const ArrayRemove           Remove;
    const ArrayResize           Resize;
    const ArraySet              Set;
    const ArrayGet              Get;    
};

function vptr(Array);
/**
 * 
 * Class Loader callback
 */
function objc_loadArray(Class super) 
{
    Class cls = createClass(super, Array);
    addMethod(cls, Array, ToString);
    addMethod(cls, Object, Equals);
    addMethod(cls, Object, GetHashCode);
    addMethod(cls, Array, Dispose);
    addMethod(cls, Array, Length);
    addMethod(cls, Array, IsEmpty);
    addMethod(cls, Array, Contains);
    addMethod(cls, Array, Clear);
    addMethod(cls, Array, Add);
    addMethod(cls, Array, Remove);
    addMethod(cls, Array, Resize);
    addMethod(cls, Array, Set);
    addMethod(cls, Array, Get);
    
    return cls;
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
method Array* ArrayFrom(int count, ...) {
    Array* this = Array_init(alloc(Array), nullptr, count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        this->data[i] = va_arg(args, Object*);
    Object* elem = this->data[0];
    this->typeOf = elem->isa;
    va_end(args);
    this->length = count;
    return this;
}

/**
 * new Array
 * 
 * allocates room for capacity, sets used to 0
 * 
 * @param typeOf type constraint for items in array
 * @param capacity initial max size of vectorO
 * 
 */
method Array* Array_init(Array* const this) {
    return Array_init(this, nullptr);
}

method Array* Array_init(Array* const this, int capacity) {
    return Array_init(this, nullptr, capacity);
}

method Array* Array_init(Array* const this, Class typeOf) {
    return Array_init(this, nullptr, 0);
}
/**
 * Default Constructor
 */
method Array* Array_init(Array* const this, Class typeOf, int capacity) {
    Object_init(this);
    this->isa = objc_getClass("Array");
    this->capacity = capacity == 0 ? ARRAY_INIT_CAPACITY : capacity;
    this->length = 0;
    this->data = DScalloc(this->capacity, sizeof(Object*));
    return this;
}

/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
method void Resize(Array* const this, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", this->capacity, capacity);
    #endif

    void **data = DSrealloc(this->data, sizeof(Object*) * capacity);
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
method Either* Add(Array* const this, const Object* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return left(NewString("InvalidType"));

    if (this->capacity == this->length) {
        Resize(this, this->capacity * 2);
    }
    this->data[this->length++] = item;
}

/**
 * Set vector item at index
 * 
 * @param index to add at
 * @param item the data to add
 */
method Either* Set(Array* const this, int index, const Object* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return left(NewString("InvalidType"));

    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
method Object* Get(Array* const this, int index)
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
method void Remove(Array* const this, int index)
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
        Resize(this, this->capacity / 2);
}

/**
 * Free the vector
 */
method void Dispose(Array* const this)
{
    // delete(this->data);
}

method void Clear(Array* const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}

method bool IsEmpty(Array* const this)
{
    return this->length <= 0;
}

method bool Contains(Array* const this, Object* item)
{
    return false;   
}

method int Length(const Array* const this)
{
    return this->length;
}

/**
 * ToString
 */
method char* ToString(const Array* const this)
{
    return "dark.collections.Array";
}
