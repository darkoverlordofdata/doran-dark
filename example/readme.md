# daran-dark tdd

## install

after installing doran-dark, reopen the doran-dark/test folder in vdcode, or 

    cd test

then

    doran update
    rm ./lib/dark
    doran install --link dark
    ./configure

the install --link may print some ugly messages as it tries to process the recursive disk structure, but it worked.
from there, use cake tools in vscode, or 

    cd build
    make



### Compile Symbols
use __ARC__ to enable automated reference counting.

combine with GOBJECT_COMPILATION to use GLib g_atomic* functions for reference counting.


set ( INCLUDES "${INCLUDES};C:/Users/darko/Documents/GitHub/bdwgc-8.0.0/include" )
