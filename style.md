## dark overload 


### Wrap a primitive value
```c
    String* Hobbit = $("Frodo");
    Float* pi = $(3.1415f);
    auto count = $(0L);
```


### Join string objects
```c
    auto s = $Join($("the "), $("answer "), $("is "), $(42));
    Log("%$", s);
```

### New object
```c
    auto g = new(Game, 600, 800);
```

### Riia pattern
```c
    { 
        using(Game) g = new(Game, 600, 800);
        //  Main game loop
        //  ...
        
    } //  at the end of this block, Game_dtor is called with g.
```

### Generic hashtable 
```c
    auto hsh = new(Map);
```

### Typed generic hashtable (runtime constraint)
```c
    auto hsh = new(Map, of(Number));
```

### Exceptions - no lngjmp
```c
    Either* result = Put(zhsh, "test", $(430L));
    if (isRight(result)) {
        Log("Put Succeeded");
    } else {
        Log("Error: %$", getLeft(result));
    }

```
### Exceptions - uses lngjmp
```c
    Exception* e;
    try {
        ...
    }
    catch (e)  {
        Log(e->msg);
    }
```


### Extend a class with an iterator
 ```c
method void ForEach(List* const this, void (^iter)(String*))
{
    for (auto curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}
```


