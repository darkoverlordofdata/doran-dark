## c overloaded


### Wrap a primitive value
```c
    auto pi = $(3.1415f);
```


### Simple join strings. automatically convert primitives:
```c
    auto s = $Join($("the "), $("answer "), $("is "), $(42));
    DSLog("%$", s);
```


### Typed generic hashtable
```c
    auto hsh = new(DSHashmap, of(DSNumber));
```


### Riia pattern, such as using
```c
    {   
        SomeClass* dtor(SomeClass_Dispose) h = new(SomeClass);
        //  do stuff ...
        // at the end of this block, SomeClass_Dispose is called with h.
    } 
```

### Exceptions
```c
    DSException* e;
    try {
        // Adding a long to a collection of DSBoolean -
        // should throw an exception
        Put(zhsh, "test", $(420L));
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


