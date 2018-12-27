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

```c
void overload ForEach(List const this, void (^iter)(String))
{
    for (ListNode curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {
    List ls = DSList.Create();
    Add(ls, DSString.Create("first"));
    Add(ls, DSString.Create("second"));


    ForEach(ls, ^(String s) {
        printf("item = %d) %s\n", s->length, s->value);
    });
    return 0;
}

    DSLog($("this string %f"), 20.0f);
    List ls = DSList.Create();

    String s = $$.Join($("string 1"), $("string 2"));
    String ss[] = s.Split(" ");


```

```c

void overload ForEach(List const this, void (^iter)(String))
{
    for (ListNode curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {
    List ls = $List.Create();
    Add(ls, $String.Create("first"));
    Add(ls, $String.Create("second"));


    ForEach(ls, ^(String s) {
        printf("item = %d) %s\n", s->length, s->value);
    });
    return 0;
}
```

```c
    $Log($("this string %f"), 20.0f);
    List ls = $List.Create();

    String s = $$.Join($("string 1"), $("string 2"));
    String ss[] = s.Split(" ");

```