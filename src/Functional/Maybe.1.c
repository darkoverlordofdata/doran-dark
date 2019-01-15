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
#include <dark/Functional/Maybe.h>

ivar (Maybe) {
    DSObject* value;
};

const DSObject* _(const Maybe* const this) {
    return this->value;
}

Maybe* Nothing() {
    const auto this = alloc(Maybe);
    this->value = nullptr;
}

Maybe* Just(DSObject* x) {
    const auto this = alloc(Maybe);
    this->value = x;
    return this;
}

Maybe* ret(DSObject* this) {
    return Just(this);
}

Maybe* overload Just(int x) {
    const auto this = alloc(Maybe);
    this->value = x;
    return this;
}

Maybe* overload ret(int value) {

}

Maybe* bind(Maybe* this,  Maybe* (*func)(Maybe*)) {
    if (this->value == nullptr) 
        return Nothing();
    else
        return func(_(this));
}

bool IsNothing(const Maybe* this) {
    return _(this) == nullptr;
}