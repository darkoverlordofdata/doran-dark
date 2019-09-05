# DaRKSTEP

A NeXTSTEP-like object system entirely in c11 with clang extensions. This is not objective-c, this is c. Instead of method lists, I'm using vtables. Instead of messages, I'm using the selector as a generic function.

clang c11, using extensions:
* BlocksRuntime
* __attribute__((ext_vector_type(n)))
* __attribute__((overloadable))
* __attribute__((constructor(n)))
* __attribute__((cleaup(destructor)))

## Why?
'I want a new C' - catchy. Maybe I'll write a song. C is simple. It compiles fast. I didn't like Borland C++ 2.0 when it came out - too 'gimicky'. It's gotten better, but I still think it has a noisy syntax.

This library is adequate for non-critical use. Probably 1/2 the internet runs or did run on hacks that emulate classes in javascript.

> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup




### testing

    cd test
    doran update
    mkdir build
    cd build
    make
    ./unit

### example
a port of the breakout game from learnopengl.com

## dependancies (windows)
    pacman -S mingw-w64-x86_64-libblocksruntime
    pacman -S mingw-w64-x86_64-gc

## dependancies (linux)
    sudo apt install libblocksruntime-dev
    sudo apt install libgc-dev

## example
```c
#include <dark/Foundation.h>
/**
 * Extend the List class with an iterator
 */
method void ForEach(List* this, void (^iter)(String*))
{
    for (auto curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {

    Log("Hello World");
    /**
     * $ wraps primitive values with corresponding Type
     */
    auto pi = $(3.1415f);
    Log("pi = %$", pi);
    Log("typeof(pi) = %s", typeof(pi));

    List* ls = new(List);
    Add(ls, $("first"));
    Add(ls, $("second"));
    ForEach(ls, ^(String* s) {
        Log("item = %d) %$", Length(s), s);
    });

    Log("this string %$", $(20.0f));

    auto s = $Join($("the "), $("answer "), $("is "), $(42));
    Log("%$", s);
    Log(ToString(s));

    return 0;
}


```

