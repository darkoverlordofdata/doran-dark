# dark overload

generic function runtime inspired by objective-c, with a java/dotnet inspired framework mashup.

clang c99 with extensions:
* BlocksRuntime
* __attribute__((ext_vector_type(n)))
* __attribute__((overloadable))
* __attribute__((constructor(n)))


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
> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup


## example

```c
    TList ls = List.Create();
    Add(ls, String.Create("first"));
    Add(ls, String.Create("second"));

    ForEach(ls, ^(TString s) {
        printf("item = %d) %s\n", s->length, s->value);
    });

```