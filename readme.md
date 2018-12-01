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


### gc
DObjects created in Vala are unreachable by the gc. This requires duplicates of some functions for both managed and unmanaged memory. That doesn't scale well.

So, for vala interop, define the __ARC__ symbol for both valac and c compilers. If all c code, you can leave __ARC__ out and use gc. This will use only 1 memory at a time. 