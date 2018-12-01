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
#include <dark/collections/Vector.h>
/**
 * Generic Vector implementation
 */

/**
 * Number of items in vector
 */
int Vector_Count(Vector const this)
{
    return this->count;
}

/**
 * Resize the vector
 * 
 * @param capacity the new size
 */
void Vector_Resize(Vector const this, int capacity)
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
// void Add(Vector const this, Any item)
void Vector_Add(Vector const this, Any item)
{
    if (this->capacity == this->count)
        this->Resize(this, this->capacity * 2);
    this->data[this->count++] = item;
}

/**
 * Set vector item at index
 * 
 * @param index to add at
 * @param item the data to add
 */
void Vector_Set(Vector const this, int index, Any item)
{
    if (index >= 0 && index < this->count)
        this->data[index] = item;
}

/**
 * Get vector item at index
 * 
 * @param index to get
 */
Any Vector_Get(Vector const this, int index)
{
    if (index >= 0 && index < this->count)
        return this->data[index];
    return nullptr;
}

/**
 * Delete vector item at index
 * 
 * @param index to delete
 */
void Vector_Delete(Vector const this, int index)
{
    if (index < 0 || index >= this->count)
        return;

    this->data[index] = nullptr;

    for (int i = index; i < this->count - 1; i++) {
        this->data[i] = this->data[i + 1];
        this->data[i + 1] = nullptr;
    }

    this->count--;

    if (this->count > 0 && this->count == this->capacity / 4)
        this->Resize(this, this->capacity / 2);
}

/**
 * Free the vector
 */
void Vector_Dispose(Vector const this)
{
    delete(this->data);
}

void Vector_Clear(Vector const this)
{
    for (int i=0; i < this->count; i++)
        this->data[i] = nullptr;
    this->count = 0;
}


/**
 * ToString
 */
const char* Vector_ToString(Vector const this)
{
    return "dark.collections.Vector";
}

/**
 * Initialize a new Vector
 */
Vector Vector_Ctor(Vector const this, int capacity)
{
    DObject_Ctor(this);

    this->ToString      = &Vector_ToString;
    this->Count         = &Vector_Count;
    this->Resize        = &Vector_Resize;
    this->Add           = &Vector_Add;
    this->Set           = &Vector_Set;
    this->Get           = &Vector_Get;
    this->Delete        = &Vector_Delete;
    this->Dispose       = &Vector_Dispose;
    this->Clear         = &Vector_Clear;

    this->capacity = capacity == 0 ? VECTOR_INIT_CAPACITY : capacity;
    this->count = 0;
    this->data = calloc(this->capacity, sizeof(Any));

    return this;
}

/**
 * new Vector
 * 
 * allocates room for capacity, sets used to 0
 * 
 * @param capacity initial max size of vector
 * 
 */
Vector Vector_New(int capacity)
{
    return Vector_Ctor(new(Vector), capacity);
}


/**
 * new Vector
 * 
 * allocate a vector the size of the param list
 * and then fill values from params.
 * 
 * @param count number of initial values
 * @param ... list of initial values
 * 
 */
Vector Vector_Variadic(int count, ...)
{
    Vector v = Vector_Ctor(new(Vector), count);
    va_list args;
    va_start(args, count);
    for (int i=0; i<count; i++)
        v->data[i] = va_arg(args, Any);
    va_end(args);
    v->count = count;
    return v;
}

