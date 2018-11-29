# dark framework

a java/dotnet mashup inspired framework in c.

designed to be called directly from c or vala.


### testing

    cd test
    doran update
    mkdir build
    cd build
    make
    ./unit

## Why?
> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup


## Lifetime

DarkFx uses either gc or ref counting. If the object is created using the 'new' kwyword
in vala, then reference counting is used. If the object is not created from Vala, then it is garbage collected. In this case, object->refCount is set to -1. This will cause it to be skipped if passed to the vala unref function.