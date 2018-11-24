# dark framework

    Object
    List
    Vector
    Hashmap

## oop in c

Prior to ecma5, you had to 'roll your own' classes in javascript.  There were many ways to implements this, in the end the simplest way won the day - (https://johnresig.com/blog/simple-javascript-inheritance/). 

In the c world there are also many ways to implement oop. This is my own, and I've tried to keep it simple, and it is based in part on the old js classes.

### ClassyC
   A class is a pointer to a struct class_t.
   Macros hide class_t, you only see class.

### define a class in the header file: 

```c
    class (MyClass) { 
        extends(Object);
        int x, y;
        ... 
    }
```
        
### each class must have a constructor:

```c
    MyClass MyClass_Ctor(MyClass this, int x, int y) {
        base(Object, this);
        this->Equals        = &_.Equals;
        this->GetHashCode   = &_.GetHashCode;
        this->ToString      = &MyClass_ToString;
        ...
        this.x = x;
        this.y = y;
        return this;
    }
```
### lightweight classes

You can also create a flyweight object that has no inheritance, 
no vtable.

MyStruct.h:
```c

    class (MyStruct) { int x, y; }
```

    MyStruct.c:

```c
    MyStruct MyStruct_Ctor(MyStruct this, int x, int y)
    {
        this->x = x;
        this->y = y;
        return this;
    }
```
Create an array of lightweights:

```c
    MyStruct data = allocate(MyStruct, count);
```
    MyStruct points to the first struct in the array
        
### To use classes:

```c
    MyClass c = new (MyClass);

    MyStruct s = new (MyStruct, 2, 3);
    printf("%s = (%d, %d)\n", s->ToString(), s->x, s->y);
```
For ease of use, vTables are not separate, so methods and
properties are on the same struct, like javascript objects.

So it allows usage like this:
```c
if (s1->Equals(s2)) { ... }
```
not like this:
```c
if (s1->vptr->_._.Equals(s2)) { ... }
```

## Why?
> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup