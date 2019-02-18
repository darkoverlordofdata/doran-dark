# DaRKSTEP

NeXTSTEP-like object system entirely in c11 with clang extensions. This is not objective-c, this is c. Instead of method lists, I'm using vtables. Instead of messages, I'm using the selector as a generic function.

clang c11 with extensions:
* BlocksRuntime
* __attribute__((ext_vector_type(n)))
* __attribute__((overloadable))
* __attribute__((constructor(n)))
* __attribute__((cleaup(destructor)))


### testing

    cd test
    doran update
    mkdir build
    cd build
    make
    ./unit

### example
a port of the breakout game from learnopengl.com

## Why?
I want a new C. C is simple. It compiles fast. I didn't like Borland C++ 2.0 when it came out - too 'gimicky'. It's gotten better, but I still think it has a noisy syntax. 

This library is adequate for non-critical use. Probably 1/2 the internet runs or did run on hacks that emulate classes in javascript.

> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup

## dependancies (windows)
    pacman -S mingw-w64-x86_64-libblocksruntime
    pacman -S mingw-w64-x86_64-gc

## dependancies (linux)
    sudo apt install libblocksruntime-dev
    sudo apt install libgc-dev

## example
```c
#include <dark/Foundation.h>
#include <Block.h>
/**
 * Extend the DSList class with an iterator
 */
void overload ForEach(DSList* const this, void (^iter)(DSString*))
{
    for (var curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {

    DSLog("Hello World");
    /**
     * $ wraps primitive values with corresponding Type
     */
    var pi = $(3.1415f);
    DSLog("pi = %$", pi);
    DSLog("typeof(pi) = %s", typeof(pi));

    DSList* ls = new(DSList);
    Add(ls, $("first"));
    Add(ls, $("second"));
    ForEach(ls, ^(DSString* s) {
        DSLog("item = %d) %$", Length(s), s);
    });

    DSLog("this string %$", $(20.0f));

    var s = $Join($("the "), $("answer "), $("is "), $(42));
    DSLog("%$", s);
    DSLog(ToString(s));

    // DSString** ss = Split(s, " ");

    return 0;
}


```

## example
Some contrived error handling

```c
Either* Try(DSObject* (^lambda)(void)) {
    DSException* e;
    try {
        return Right(lambda());
    } catch (e) {
        return Left($(e->msg));
    }
}

...
    auto answer = Try(^{
         return (DSObject*)$(DSParseDouble("frodo")); 
    });

    if (IsRight(answer)) {
        DSLog("answer = %$", GetRight(answer));
    } else {
        DSLog("error is %$", GetLeft(answer));
    }

```

> error is NumberFormatException Invalid input. Value:"frodo"