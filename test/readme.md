# doran-dark tdd

## install

after installing doran-dark, reopen the doran-dark/test folder in vscode, or 

    cd test

then

    doran update
    rm ./lib/dark
    doran install --link dark
    ./configure

the install --link may print some ugly messages as it tries to process the recursive disk structure, but it worked.
from there, use cmake tools in vscode, or 

    cd build
    make





