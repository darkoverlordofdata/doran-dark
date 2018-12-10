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
#ifndef _CLASS_H_
#define _CLASS_H_
#include "core.h"

struct Class {
	struct Class * isa;
	struct Class * superclass;
	char* name;
};

typedef struct Class* TClass;

struct Metadata {
    int count;
    struct Class * classes[100];
};

struct Metadata Metadata;

/**
 * based on this Objective-C core pattern:
 * 
 
typedef struct objc_class *Class;

struct objc_class {
    Class isa;
    Class super_class;
    // followed by runtime specific details...
};

typedef struct objc_object {
    Class isa;
    // ... 
} *id;

*/

#endif _CLASS_H_ 
