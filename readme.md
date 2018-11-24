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

Why oop in c? Why not just use cpp? I really don't like cpp. I think it's noisy and cluttered. Code get's hard to read, and harder to reason about. Example - stream operators are awkward, they seem to me a gimmick ceated to show what overrides can do. Often the cpp demo's I've tried can be converted to c by simply renaming the extension and refactoring the streaming operators. Until you get to the standard library, I see little advantage to cpp. The cpp standard library is more like a framework. C frameworks are fragmented, and many lack documentation 

I really like Vala, and GLib is probably the closest thing to a c framework. But GLib is not very portable and has a lot of baggage, and both are GPL, and Gnome stewardship has been less than desirable.

> "C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do it blows your whole leg off" -- Bjarne Stroustrup