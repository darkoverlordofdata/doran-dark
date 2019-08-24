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


delegate (Array, New,       Array*,     (Array*, Class, int));
delegate (Array, ToString,  char*,      (const Array* const) );
delegate (Array, Dispose,   void,       (Array* const) );
delegate (Array, Length,    int,        (const Array* const) );
delegate (Array, IsEmpty,   bool,       (Array* const) );
delegate (Array, Contains,  bool,       (Array* const, Object*) );
delegate (Array, Clear,     void,       (Array* const) );
delegate (Array, Add,       Either*,    (Array* const, const Object*) );
delegate (Array, Remove,    void,       (Array* const, int) );
delegate (Array, Resize,    void,       (Array* const, int) );
delegate (Array, Set,       Either*,    (Array* const, int, const Object*) );
delegate (Array, Get,       Object*,  (Array* const, int) );

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

static inline vptr(Array);
/**
 * 
 * Class Loader callback
 */
static inline Class objc_loadArray(Class base) 
{
    Class cls = createClass(base, Array);
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
    Array* self = Array_ctor(alloc(Array), nullptr, count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        self->data[i] = va_arg(args, Object*);
    Object* elem = self->data[0];
    self->typeOf = elem->isa;
    va_end(args);
    self->length = count;
    return self;
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
method Array* New(Array*  self, int capacity) {
    return New(self, nullptr, capacity);
}

method Array* New(Array* self, Class typeOf) {
    return New(self, nullptr, 0);
}

method Array* New(Array*  self) {
    return New(self, nullptr);
}

/**
 * Default Constructor
 */
method Array* New(Array* self, Class typeOf, int capacity) {
    extends(Object);
    // extend(Object, self);

    self->isa = objc_getClass("Array");
    self->capacity = capacity == 0 ? ARRAY_INIT_CAPACITY : capacity;
    self->length = 0;
    self->data = DScalloc(self->capacity, sizeof(Object*));
    return self;
}


/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
method void Resize(Array* const self, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", self->capacity, capacity);
    #endif

    void **data = DSrealloc(self->data, sizeof(Object*) * capacity);
    if (data) {
        self->data = data;
        self->capacity = capacity;
    }
}

/**
 * Add item to the end of vector
 * 
 * @param item the data to add
 */
method Either* Add(Array* const self, const Object* item)
{
    if ((self->typeOf) && !InstanceOf(self->typeOf, item)) 
        return left(new(String, "InvalidType"));

    if (self->capacity == self->length) {
        Resize(self, self->capacity * 2);
    }
    self->data[self->length++] = item;
}

/**
 * Set vector item at index
 * 
 * @param index to add at
 * @param item the data to add
 */
method Either* Set(Array* const self, int index, const Object* item)
{
    if ((self->typeOf) && !InstanceOf(self->typeOf, item)) 
        return left(new(String, "InvalidType"));

    if (index >= 0 && index < self->length)
        self->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
method Object* Get(Array* const self, int index)
{
    if (index >= 0 && index < self->length)
        return self->data[index];
    return nullptr;
}

/**
 * Delete vector item at index
 * 
 * @param index to delete
 */
method void Remove(Array* const self, int index)
{
    if (index < 0 || index >= self->length)
        return;

    self->data[index] = nullptr;

    for (int i = index; i < self->length - 1; i++) {
        self->data[i] = self->data[i + 1];
        self->data[i + 1] = nullptr;
    }

    self->length--;

    if (self->length > 0 && self->length == self->capacity / 4)
        Resize(self, self->capacity / 2);
}

/**
 * Free the vector
 */
method void Dispose(Array* const self)
{
    // delete(self->data);
}

method void Clear(Array* const self)
{
    for (int i=0; i < self->length; i++)
        self->data[i] = nullptr;
    self->length = 0;
}

method bool IsEmpty(Array* const self)
{
    return self->length <= 0;
}

method bool Contains(Array* const self, Object* item)
{
    return false;   
}

method int Length(const Array* const self)
{
    return self->length;
}

/**
 * ToString
 */
method char* ToString(const Array* const self)
{
    return "dark.collections.Array";
}
