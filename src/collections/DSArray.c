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
#include <dark/collections/DSArray.h>

$implementation(DSArray)

$method(ToString,           (DSArrayToString)ToString, "@@:v");
$method(Equals,             DSObject_Equals, "B@:@@");
$method(GetHashCode,        DSObject_GetHashCode, "l@:v");
$method(Dispose,            (DSArrayDispose)Dispose, "v@:v");
$method(ReferenceEquals,    ReferenceEquals, "@:v");
$method(InstanceEquals,     InstanceEquals, "$@:v");
$method(Length,             (DSArrayLength)Length, "i@:v");
$method(IsEmpty,            (DSArrayIsEmpty)IsEmpty, "B@:v");
$method(Contains,           (DSArrayContains)Contains, "B@:@");
$method(Clear,              (DSArrayClear)Clear, "v@:v");
$method(Add,                (DSArrayAdd)Add, "v@:@");
$method(Remove,             (DSArrayRemove)Remove, "v@:i");
$method(Resize,             (DSArrayResize)Resize, "v@:i");
$method(Set,                (DSArraySet)Set, "v@:i@");
$method(Get,                (DSArrayGet)Get, "@@:i");

$ivar(length, sizeof(int), "i");
$ivar(data, sizeof(void*), "^");
$ivar(capacity, sizeof(int), "i");

$end;
/**
 * new Array
 * 
 * allocates room for capacity, sets used to 0
 * 
 * @param capacity initial max size of vector
 * 
 */
DSArray* overload NewDSArray(int capacity) {
    return DSArray_init(DSArray_alloc(), capacity);
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
DSArray* overload NewDSArray(int count, ...) {
    DSArray* v = DSArray_init(DSArray_alloc(), count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        v->data[i] = va_arg(args, Any);
    va_end(args);
    v->length = count;
    return v;
}

DSArray* overload NewDSArray(void) {
    return DSArray_init(DSArray_alloc(), 4);
}

/**
 * Default Constructor
 */
DSArray* DSArray_init(DSArray* const this, int capacity)
{
    DSObject_init(this);
    this->isa = objc_getClass("DSArray");
    this->capacity = capacity == 0 ? ARRAY_INIT_CAPACITY : capacity;
    this->length = 0;
    this->data = DSCalloc(this->capacity, sizeof(Any));
    return this;
}

DSArray* DSArray_alloc() {
    return DSMalloc(getDSArraySize());
}



int overload Length(const DSArray* const this)
{
    return this->length;
}
/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
void Resize(DSArray* const this, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", this->capacity, capacity);
    #endif

    void **data = DSRealloc(this->data, sizeof(Any) * capacity);
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
void overload Add(DSArray* const this, const Any item)
{
    if (this->capacity == this->length) {
        DSArrayVTable.Resize(this, this->capacity * 2);
    }
    this->data[this->length++] = item;
}

/**
 * Set vector item at index
 * 
 * @param index to add at
 * @param item the data to add
 */
void Set(DSArray* const this, int index, const Any item)
{
    if (index >= 0 && index < this->length)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
Any Get(const DSArray* const this, int index)
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
void overload Remove(DSArray* const this, int index)
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
        DSArrayVTable.Resize(this, this->capacity / 2);
}

/**
 * Free the vector
 */
void overload Dispose(DSArray* const this)
{
    // delete(this->data);
}

void overload Clear(DSArray* const this)
{
    for (int i=0; i < this->length; i++)
        this->data[i] = nullptr;
    this->length = 0;
}

bool overload IsEmpty(const DSArray* const this)
{
    return this->length <= 0;
}

bool overload Contains(const DSArray* const this, Any item)
{
    return false;   
}


/**
 * ToString
 */
char* overload ToString(const DSArray* const this)
{
    return "dark.collections.Array";
}

