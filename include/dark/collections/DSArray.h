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


IVAR (DSArray) {
    Class isa;
    Class typeOf;
    int length;
    // void **data;
    uchar **data;
    int capacity;
};


CTOR(DSArray);
CTOR(DSArray, int);
CTOR(DSArray, Class);
CTOR(DSArray, Class, int);

METHOD (DSArray, ToString,  char*,      (const DSArray* const) );
METHOD (DSArray, Dispose,   void,       (DSArray* const) );
METHOD (DSArray, Length,    int,        (const DSArray* const) );
METHOD (DSArray, IsEmpty,   bool,       (DSArray* const) );
METHOD (DSArray, Contains,  bool,       (DSArray* const, DSObject*) );
METHOD (DSArray, Clear,     void,       (DSArray* const) );
METHOD (DSArray, Add,       Either*,    (DSArray* const, const DSObject*) );
METHOD (DSArray, Remove,    void,       (DSArray* const, int) );
METHOD (DSArray, Resize,    void,       (DSArray* const, int) );
METHOD (DSArray, Set,       Either*,    (DSArray* const, int, const DSObject*) );
METHOD (DSArray, Get,       DSObject*,  (DSArray* const, int) );

VTABLE (DSArray) {
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

DEF_VPTR(DSArray);

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
static inline overload DSArray* DSArrayFrom(int count, ...) {
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
static inline overload DSArray* DSArray_init(DSArray* const this) {
    return DSArray_init(this, nullptr);
}

static inline overload DSArray* DSArray_init(DSArray* const this, int capacity) {
    return DSArray_init(this, nullptr, capacity);
}

static inline overload DSArray* DSArray_init(DSArray* const this, Class typeOf) {
    return DSArray_init(this, nullptr, 0);
}
/**
 * Default Constructor
 */
static inline overload DSArray* DSArray_init(DSArray* const this, Class typeOf, int capacity) {
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
static inline overload void Resize(DSArray* const this, int capacity)
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
static inline overload Either* Add(DSArray* const this, const DSObject* item)
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
static inline overload Either* Set(DSArray* const this, int index, const DSObject* item)
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
static inline overload DSObject* Get(DSArray* const this, int index)
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
static inline overload void Remove(DSArray* const this, int index)
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
static inline overload void Dispose(DSArray* const this)
{
    // delete(this->data);
}

static inline overload void Clear(DSArray* const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}

static inline overload bool IsEmpty(DSArray* const this)
{
    return this->length <= 0;
}

static inline overload bool Contains(DSArray* const this, DSObject* item)
{
    return false;   
}

static inline overload int Length(const DSArray* const this)
{
    return this->length;
}

/**
 * ToString
 */
static inline overload char* ToString(const DSArray* const this)
{
    return "dark.collections.Array";
}

VTABLE_BIND(DSArray);

VTABLE_METHOD(ToString,           (DSArrayToString)ToString, "@@:v");
VTABLE_METHOD(Equals,             (DSObjectEquals)Equals, "B@:@@");
VTABLE_METHOD(GetHashCode,        (DSObjectGetHashCode)GetHashCode, "l@:v");
VTABLE_METHOD(Dispose,            (DSArrayDispose)Dispose, "v@:v");
VTABLE_METHOD(Length,             (DSArrayLength)Length, "i@:v");
VTABLE_METHOD(IsEmpty,            (DSArrayIsEmpty)IsEmpty, "B@:v");
VTABLE_METHOD(Contains,           (DSArrayContains)Contains, "B@:@");
VTABLE_METHOD(Clear,              (DSArrayClear)Clear, "v@:v");
VTABLE_METHOD(Add,                (DSArrayAdd)Add, "v@:@");
VTABLE_METHOD(Remove,             (DSArrayRemove)Remove, "v@:i");
VTABLE_METHOD(Resize,             (DSArrayResize)Resize, "v@:i");
VTABLE_METHOD(Set,                (DSArraySet)Set, "v@:i@");
VTABLE_METHOD(Get,                (DSArrayGet)Get, "@@:i");

VTABLE_IVAR(typeof, sizeof(id), "@");
VTABLE_IVAR(length, sizeof(int), "i");
VTABLE_IVAR(data, sizeof(void*), "^");
VTABLE_IVAR(capacity, sizeof(int), "i");

VTABLE_METHODIZE;

#endif _DSARRAY_H_
