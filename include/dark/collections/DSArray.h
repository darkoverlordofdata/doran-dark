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
#ifndef _DSARRAY_H_
#define _DSARRAY_H_
#include <dark/types.h>
#include <dark/DSObject.h>
#include <dark/types/DSString.h>
#include <dark/Functional/Either.h>
// #include "DSCollection.h"
/**
 * An ArrayList based on:
 * @see https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
 */
#define ARRAY_INIT_CAPACITY 4


#define IsDSArray(object) _Generic((object), DSArray*: true, default: false)
#define AsDSArray(object) _Generic((object),                            \
                            DSArray*: (DSArray *)object,                \
                            default: nullptr)


type (DSArray) {
    Class isa;
    Class typeOf;
    int length;
    // void **data;
    uchar **data;
    int capacity;
};


def_ctor(DSArray);
def_ctor(DSArray, int);
def_ctor(DSArray, Class);
def_ctor(DSArray, Class, int);

def_method (DSArray, ToString,  char*,      (const DSArray* const) );
def_method (DSArray, Dispose,   void,       (DSArray* const) );
def_method (DSArray, Length,    int,        (const DSArray* const) );
def_method (DSArray, IsEmpty,   bool,       (DSArray* const) );
def_method (DSArray, Contains,  bool,       (DSArray* const, DSObject*) );
def_method (DSArray, Clear,     void,       (DSArray* const) );
def_method (DSArray, Add,       Either*,    (DSArray* const, const DSObject*) );
def_method (DSArray, Remove,    void,       (DSArray* const, int) );
def_method (DSArray, Resize,    void,       (DSArray* const, int) );
def_method (DSArray, Set,       Either*,    (DSArray* const, int, const DSObject*) );
def_method (DSArray, Get,       DSObject*,  (DSArray* const, int) );

vtable (DSArray) {
    const DSArrayToString         ToString;
    const DSObjectEquals          Equals;
    const DSObjectGetHashCode     GetHashCode;
    const DSObjectDispose         Dispose;
    const DSArrayLength           Length;
    const DSArrayIsEmpty          IsEmpty;
    const DSArrayContains         Contains;
    const DSArrayClear            Clear;
    const DSArrayAdd              Add;
    const DSArrayRemove           Remove;
    const DSArrayResize           Resize;
    const DSArraySet              Set;
    const DSArrayGet              Get;    
};

vtable_ptr(DSArray);

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
method DSArray* DSArrayFrom(int count, ...) {
    DSArray* this = DSArray_init(alloc(DSArray), nullptr, count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        this->data[i] = va_arg(args, DSObject*);
    DSObject* elem = this->data[0];
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
method DSArray* DSArray_init(DSArray* const this) {
    return DSArray_init(this, nullptr);
}

method DSArray* DSArray_init(DSArray* const this, int capacity) {
    return DSArray_init(this, nullptr, capacity);
}

method DSArray* DSArray_init(DSArray* const this, Class typeOf) {
    return DSArray_init(this, nullptr, 0);
}
/**
 * Default Constructor
 */
method DSArray* DSArray_init(DSArray* const this, Class typeOf, int capacity) {
    DSObject_init(this);
    this->isa = objc_getClass("DSArray");
    this->capacity = capacity == 0 ? ARRAY_INIT_CAPACITY : capacity;
    this->length = 0;
    this->data = DScalloc(this->capacity, sizeof(DSObject*));
    return this;
}

/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
method void Resize(DSArray* const this, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", this->capacity, capacity);
    #endif

    void **data = DSrealloc(this->data, sizeof(DSObject*) * capacity);
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
method Either* Add(DSArray* const this, const DSObject* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return Left(NewDSString("InvalidType"));

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
method Either* Set(DSArray* const this, int index, const DSObject* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return Left(NewDSString("InvalidType"));

    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
method DSObject* Get(DSArray* const this, int index)
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
method void Remove(DSArray* const this, int index)
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
method void Dispose(DSArray* const this)
{
    // delete(this->data);
}

method void Clear(DSArray* const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}

method bool IsEmpty(DSArray* const this)
{
    return this->length <= 0;
}

method bool Contains(DSArray* const this, DSObject* item)
{
    return false;   
}

method int Length(const DSArray* const this)
{
    return this->length;
}

/**
 * ToString
 */
method char* ToString(const DSArray* const this)
{
    return "dark.collections.Array";
}

class_bind(DSArray);

class_method(ToString,           (DSArrayToString)ToString, "@@:v");
class_method(Equals,             (DSObjectEquals)Equals, "B@:@@");
class_method(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
class_method(Dispose,            (DSArrayDispose)Dispose, "v@:v");
class_method(Length,             (DSArrayLength)Length, "i@:v");
class_method(IsEmpty,            (DSArrayIsEmpty)IsEmpty, "B@:v");
class_method(Contains,           (DSArrayContains)Contains, "B@:@");
class_method(Clear,              (DSArrayClear)Clear, "v@:v");
class_method(Add,                (DSArrayAdd)Add, "v@:@");
class_method(Remove,             (DSArrayRemove)Remove, "v@:i");
class_method(Resize,             (DSArrayResize)Resize, "v@:i");
class_method(Set,                (DSArraySet)Set, "v@:i@");
class_method(Get,                (DSArrayGet)Get, "@@:i");

class_member(typeof, sizeof(id), "@");
class_member(length, sizeof(int), "i");
class_member(data, sizeof(void*), "^");
class_member(capacity, sizeof(int), "i");

class_methodize;

#endif _DSARRAY_H_
