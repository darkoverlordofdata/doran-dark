# darkstep

generic function runtime inspired by nextstep object. Linked with boehm gc.

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

$(str) - shortcut for DSString.Create(str);
ClassName x = $ClassName();         // - create new object
ClassName x = ClassName.Create();   // - create new object

Other framework functions:

DSLog();
DSFree(void*);
DSMalloc(int);
DSRealloc(void*, int);
DSCalloc(int, int);
DSCollect();


```c
void overload ForEach(DSList const this, void (^iter)(DSString))
{
    for (DSListNode curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {
    DSList ls = DSListClass.Create();
    Add(ls, DSStringClass.Create("first"));
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


