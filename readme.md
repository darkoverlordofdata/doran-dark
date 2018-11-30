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


### dependancies
DarkFx uses garbage collection. I am using https://github.com/orangeduck/tgc
because it leaves vala created objects alone.

To use reference counting, compile with -D__ARC__. This will enable vala style reference counting, and define arc hooks in the vapi.