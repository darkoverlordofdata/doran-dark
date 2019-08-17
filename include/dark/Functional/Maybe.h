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
#include "../DSObject.h"

/** 
 * I'm not sure that generics are needed. Monad binding is 
 * useful in Haskel because is't not procedural. But c is, 
 * so bind is not so useful, instead it's just awkward.
 * 
*/
// #define __MAYBE_GENERICS__
#ifdef __MAYBE_GENERICS__
/**
 *  <G>enerics Generator
 * 
 */
#define __Maybe__(type, name)                                           \
static inline overload Maybe* Just(type x) {                                          \
    const auto this = alloc(Maybe);                                     \
    this->name = x;                                                     \
    return this;                                                        \
}                                                                       \
type name##Maybe(Maybe* this) { return this->name; }                    \
static inline overload Maybe* ret(type value) { return Just(value); }
#endif


typedef struct Maybe Maybe;


#ifdef __MAYBE_GENERICS__
IVAR (Maybe) {
    union {
        int Int;
        long Long;
        short Short;
        float Float;
        double Double;
        char Char;
        bool Bool;
        char* Str;
        void* Ptr;
        DSObject* value;
    };
};

__Maybe__(int, Int);
__Maybe__(long, Long);
__Maybe__(short, Short);
__Maybe__(float, Float);
__Maybe__(double, Double);
__Maybe__(char, Char);
__Maybe__(bool, Bool);
__Maybe__(char*, Str);
__Maybe__(void*, Ptr);
#else
IVAR (Maybe) {
    DSObject* value;
};
#endif

static inline Maybe* Nothing() {
    const auto this = alloc(Maybe);
    this->value = nullptr;
}

static inline Maybe* Just(DSObject* x) {
    const auto this = alloc(Maybe);
    this->value = x;
    return this;
}

static inline Maybe* ret(DSObject* this) {
    return Just(this);
}

static inline Maybe* bind(Maybe* this,  Maybe* (*func)(Maybe*)) {
    if (this->value == nullptr) 
        return Nothing();
    else
        return func(this->value);
}

static inline bool IsNothing(const Maybe* this) {
    return this->value == nullptr;
}
