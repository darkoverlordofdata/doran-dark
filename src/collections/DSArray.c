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
#include <dark/Foundation.h>
#include <dark/collections/implementation/DSArray.h>
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
overload DSArray* DSArrayFrom(int count, ...) {
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
overload DSArray* DSArray_init(DSArray* const this) {
    return DSArray_init(this, nullptr);
}

overload DSArray* DSArray_init(DSArray* const this, int capacity) {
    return DSArray_init(this, nullptr, capacity);
}

overload DSArray* DSArray_init(DSArray* const this, Class typeOf) {
    return DSArray_init(this, nullptr, 0);
}
/**
 * Default Constructor
 */
overload DSArray* DSArray_init(DSArray* const this, Class typeOf, int capacity) {
    DSObject_init(this);
    this->isa = getDSArrayIsa();
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
overload void Resize(DSArray* const this, int capacity)
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
overload Either* Add(DSArray* const this, const DSObject* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return Left($("InvalidType"));

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
overload Either* Set(DSArray* const this, int index, const DSObject* item)
{
    if ((this->typeOf) && !InstanceOf(this->typeOf, item)) 
        return Left($("InvalidType"));

    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
overload DSObject* Get(DSArray* const this, int index)
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
overload void Remove(DSArray* const this, int index)
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
overload void Dispose(DSArray* const this)
{
    // delete(this->data);
}

overload void Clear(DSArray* const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}

overload bool IsEmpty(DSArray* const this)
{
    return this->length <= 0;
}

overload bool Contains(DSArray* const this, DSObject* item)
{
    return false;   
}

overload int Length(const DSArray* const this)
{
    return this->length;
}

/**
 * ToString
 */
overload char* ToString(const DSArray* const this)
{
    return "dark.collections.Array";
}

