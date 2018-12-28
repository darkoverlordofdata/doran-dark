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
#ifndef _CLASSY_H
#define _CLASSY_H

/**
 * overload
 * 
 * shortcut for declaring the overloadable attribute
 */
#define overload __attribute__((overloadable))


/** 
 * class (Name)
 * 
 * defines type for class: DSName_t
 * defines struct metaclass: DSName
 * defines metadata reference function: IsaName()
 * defines metadata singleton: DSName
 * start class struct definition: DSName_t
 * 
 */
// #define class(name) \
//     typedef struct name##_t* name; \
//     struct DS##name; \
//     Class Isa##name(); \
//     extern struct DS##name DS##name; \
//     struct name##_t 
#define class(name) \
    struct DS##name; \
    typedef struct name name; \
    Class* Isa##name(); \
    extern struct DS##name DS##name; \
    struct name

/** 
 * register class
 * 
 * declares the metaclass implementation
 * declares the Isa implementation
 */
#define register(name) \
    Class* Isa##name()

/**
 *  returns a reference to the class name 
 */
#define isa(name) Isa##name()

#define AddMetadata(name) (DSClass.classes[DSClass.count++] = &name)


/** 
 * Create a new class instance 
 * allocates memory for 1 object
 * 
 */
#define new(class) DSMalloc (sizeof(class))

/** 
 * Delete an object created with new 
 * deallocates the memory for 1 object
 * 
 */
#define delete(x) DSFree(x)

/** 
 * creates an array of structs
 * 
 * allocates memory for array of struct objects
 */
#define allocate(class, n) DSMalloc (n * sizeof(struct class))


#endif _CLASSY_H 
