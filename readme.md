# DaRKSTEP

generic function runtime inspired by NSObject. Linked with boehm gc.
reimplements NeXTSTEP object system entirely in c11 with clang extensions.

message notation ObjC:

    [object selector param];

DarkC uses 'cartouche':

    _(object, $selector, param);



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
each class 
    Object - type 
    ObjectClass - metaclass

Class x = $Class();         // - create new object
Class x = ClassName.Create();   // - create new object

Other framework functions:

DSLog();
DSFree(void*);
DSMalloc(int);
DSRealloc(void*, int);
DSCalloc(int, int);
DSCollect();
DSParseBool(char*);
DSParseShort(char*);
DSParseInt(char*);
DSParseLong(char*);
DSParseFloat(char*);
DSParseDouble(char*);


```c
void overload ForEach(DSList const this, void (^iter)(DSString))
{
    for (DSListNode curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {

    // message semantics
    // $DSList is &DSListClass
    DSList ls = _(_($DSList, $alloc)$init);
    _(ls, $add, $("first"));
    _(ls, $add, $("second"));

    // classic semantics
    DSList ls = $DSList->alloc()->init();
    Add(ls, $("first"));
    Add(ls, $("second"));


    ForEach(ls, ^(DSString s) {
        printf("item = %d) %s\n", s->length, s->value);
    });
    return 0;
}

    DSLog($("this string %f"), 20.0f);
    List ls = DSList.Create();

    String s = $$.Join($("string 1"), $("string 2"));
    String ss[] = s.Split(" ");


```


