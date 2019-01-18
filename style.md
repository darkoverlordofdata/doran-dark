## dark overload 


### Wrap a primitive value
```c
    DSString* Hobbit = $("Frodo");
    DSFloat* pi = $(3.1415f);
    auto count = $(0L);
```


### Join string objects
```c
    auto s = $Join($("the "), $("answer "), $("is "), $(42));
    DSLog("%$", s);
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
    auto hsh = new(DSHashmap);
```

### Typed generic hashtable (runtime constraint)
```c
    auto hsh = new(DSHashmap, of(DSNumber));
```

### Exceptions - no lngjmp
```c
    Either* result = Put(zhsh, "test", $(430L));
    if (IsRight(result)) {
        DSLog("Put Succeeded");
    } else {
        DSLog("Error: %$", GetLeft(result));
    }

```
### Exceptions - uses lngjmp
```c
    DSException* e;
    try {
        ...
    }
    catch (e)  {
        DSLog(e->msg);
    }
```


### Extend a class with an iterator
 ```c
void overload ForEach(DSList* const this, void (^iter)(DSString*))
{
    for (auto curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}
```


