## C Overloaded

combine clang overload attribute and polymorphic patterns into a 'generic c'.

runtime influences: objective-c, glib, nim, quantumleaps (http://www.state-machine.com/doc/an#Patterns)

framework influnces: java, csharp

both early and late binding may be invoked:

### early bindng (overload name mangling):
    In this case, there are 2 different 'Add' functions

    TArray a = Array_New();
    TList b = List_New();
    Add(a, "frodo"); // adds "Frodo" to array a
    Add(b, "frodo"); // appends "Frodo" to list b


### late binding (vtable polymorphism):
    int hsi case, there is 1 function that dispatches by base type.

    TLong a = Long_New(20);
    TInteger b  = Integer_ New(20);
    float x = FloatValue(a) + FloatValue(b);


ISA_MASK 9 - 0x0000000ffffffff8UL
ISA_MASK 8 - 0x00000001fffffff8UL