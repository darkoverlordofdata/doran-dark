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

typedef struct Maybe Maybe;

Maybe* Nothing();
Maybe* Just(DSObject*);
Maybe* ret(DSObject*);
Maybe* bind(Maybe*,  Maybe* (*func)(Maybe*));
bool IsNothing(const Maybe*);

/**
 *  <G>enerics Generator
 * 
 */
#define __Maybe__(type, name)                                           \
Maybe* overload Just(type x) {                                          \
    const auto this = alloc(Maybe);                                     \
    this->name = x;                                                     \
    return this;                                                        \
}                                                                       \
type name##Maybe(Maybe* this) { return this->name; }                    \
Maybe* overload ret(type value) { return Just(value); }


/**
 * 
 * 
#define MaybeOp(type, name, code) Maybe* overload name(type x) code

MaybeOp(int, inc, { return Just(x+1); })
MaybeOp(int, dec, { return Just(x-1); })

...
    auto a = bind(bind(ret(2), inc), inc);
    DSLog("inc = %d", IntMaybe(a));

    auto bb = bind(bind(ret(IntMaybe(a)), dec), dec);
    DSLog("dec = %d", IntMaybe(bb));

 * 
 * 
 */
/**
 * 
     return bind(bind(bind(GetCompany(Music, "4ad.com"),
            ^(company){ return GetBand(company); }),   
                ^(band){ return GetMember(band); }), 
                    ^(member){ return GetRole(member); });

*/