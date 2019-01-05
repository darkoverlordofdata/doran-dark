# DaRKSTEP

NeXTSTEP-like object system entirely in c11 with clang extensions. This is not objective-c, this is c. Instead of method lists, I'm using vtables. Instead of messages, I'm using the selector as a generic function via the overloadable attribute.

The object system is mainly used for metadata and the ability to define classes at runtime. 

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
wip:
<del>a port of the breakout game from learnopengl.com<del>

## Why?
> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup



## example


```c
void overload ForEach(DSList* const this, void (^iter)(DSString))
{
    for (DSListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {

    DSList* ls = NewDSList();
    Add(ls, $("first"));
    Add(ls, $("second"));


    ForEach(ls, ^(DSString* s) {
        printf("item = %d) %s\n", s->length, s->value);
    });
    return 0;
}

    DSLog($("this string %f"), 20.0f);
    List* ls = DSList.Create();

    String* s = $$.Join($("string 1"), $("string 2"));
    String* ss[] = s.Split(" ");


```


