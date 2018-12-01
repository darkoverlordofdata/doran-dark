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
#ifndef _CLASSY_H
#define _CLASSY_H
/**
 * Classy-C
 * 
 * Sort of like the old pre ecmascript5 pseudo classes
 * that half the internet is built on...
 * 
 */

/**
 * MyClass          class name
 * MyClass_t        class record
 * MyClass_auto     initialize singleton members
 * MyClass_ctor     singleton constructor
 * MyClass_dtor     singleton destructor
 */

#ifdef __ARC__
#define retained int RefCount;
#endif
/** 
 * class definition
 * 
 */
#define class(name) \
    typedef struct name##_t name##_t;\
    typedef name##_t* name;\
    typedef struct name##_t

#define cyclic_reference(name) \
    typedef struct name##_t name##_t;\
    typedef name##_t* name;
    
/** 
 * singleton definition
 * defines a global extern class
 * 
 * use in header *.h files
 * ** don't do this at home **
 */
#define singleton(name) \
    typedef struct name##_t name##_t;\
    extern name##_t name;\
    name##_t name;\
    typedef struct name##_t

/** 
 * declare superclass 
 * for loosely coupled superclass
 * use inside of class or singleton definition:
 * 
 * class (Shader) {
 *   extends(DObject);
 *   ...
 */
#define extends(class) class##_t _


/** 
 * register singleton 
 * Registers a singleton to auto initialize
 * Registers a singleton to auto destruct
 * 
 * use in implementation *.c files
 */
#define register(name) \
    void __attribute__((constructor)) name##_ctor();\
    void __attribute__((destructor)) name##_dtor();\
    static const name##_t * name##_auto(name##_t * const this);\
    void name##_ctor(){ name##_auto(&name); }\
    void name##_dtor(){ name.Dispose(); }\
    static const name##_t * name##_auto(name##_t * const this)

/** 
 * Create a new class instance 
 * allocates memory for 1 object
 * 
 */
#ifdef __ARC__
#define new(class) calloc (1, sizeof(class##_t))
#else
#define new(class) tgc_calloc_opt (&dark_gc, 1, sizeof(class##_t), 0, DObject_Dtor)
#endif
/** 
 * Delete an object created with new 
 * deallocates the memory for 1 object
 * 
 */
#ifdef __ARC__
#define delete(x) free(x)
#else
#define delete(x) tgc_free(&dark_gc, x);
#endif
/** 
/** 
 * creates an array of structs
 * 
 * allocates memory for array of struct objects
 */
#ifdef __ARC__
#define allocate(class, n) calloc (n, sizeof(class##_t))
#else
#define allocate(class, n) tgc_calloc (&dark_gc, n, sizeof(class##_t))
#endif

/**
 * A class is a pointer to a struct class_t.
 * 
 * define a class in the header file: 
 * 
 *      class (MyClass) { 
 *          extends(DObject);
 *          int x, y;
 *          ... 
 *      }
 *      
 * each class has a constructor:
 * 
 *      MyClass MyClass_Ctor(MyClass this, int x, int y) 
 *      {
 *	        base(DObject, this);
 *          this.x = x;
 *          this.y = y;
 *          return this;
 *      }
 * 
 * each class has a new (unless it's abstract):
 * 
 * 
 *      MyClass New_MyClass(int x, int y)
 *      {
 *          return MyClass_Ctor(new(MyClass), x, y);
 *      }
 * 
 * 
 *  You can also create a flyweight class that has no inheritance, 
 *  no vtable.
 * 
 *      class (MyStruct) { int x, y; }
 * 
 *      create using a simple constructor:
 *          MyStruct MyStruct_Ctor(MyStruct this, int x, int y)
 *          {
 *              this->x = x;
 *              this->y = y;
 *              return this;
 *          }
 *       
 * To use classes:
 * 
 *  MyClass c = New_MyClass();
 * 
 *  MyStruct s = New_MyStruct(2, 3);
 *  printf("%d, %d\n", s->x, s->y);
 * 
 * the 'new' macro will allocate memory the size of the underlying class struct.
 * for a class named MyClass, the underlying struct is MyClass_t. It then calls
 * MyClass_Ctor, passing in the newly allocated memory address followed by the
 * variadic parameters.
 */

#endif _CLASSY_H 
