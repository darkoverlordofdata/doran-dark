#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"


int main(int argc, char **argv) {

    __block struct DSLong* l = $DSLong(420);
    __block DSLong* m = $DSLong(420);
    __block DSBoolean* b = $DSBoolean(true);

    __block DSString* s = $("Frodo");
    __block DSArray* a = $DSArray(0);
    __block DSList* q = $DSList();
    __block DSHashmap* h = $DSHashmap();

    char keys[12][5] = {
        "key1", "key2", "key3",
        "key4", "key5", "key6",
        "key7", "key8", "key9",
        "keyA", "keyB", "keyC",
    };
    for (int i=0; i<12; i++)
    {
        DSLog("%s", keys[i]);
        Put(h, keys[i], $DSLong(i+420));
    }

    for (int i=0; i<12; i++)
    {
        DSLog("%d", LongValue(Get(h, keys[i])));
    }

    __block DSLong* l0 = $DSLong(0);
    __block DSLong* l1 = $DSLong(1);
    __block DSLong* l2 = $DSLong(2);
    __block DSLong* l3 = $DSLong(3);
    __block DSLong* l4 = $DSLong(4);
    __block DSLong* l5 = $DSLong(5);

    Add(a, l0);
    Add(a, l1);
    Add(a, l2);
    Add(a, l3);
    Add(a, l4);
    Add(a, l5);

    Add(q, l);    
    Add(q, m);

    // Long ll = Get(a, 0);    
    
    DSLog("=============");
    DSLog("%d", Length(a));
    for (int i=0; i<Length(a); i++) {
        DSLog("%d)", i);
        DSLog("%d) %d", i, LongValue(Get(a, i)));
    }
    DSLog("%s", ToString(q));
    DSLog("Bytes = %d", DSBooleanClass.Bytes);
    DSLog("Size = %d", DSBooleanClass.Size);
    DSLog("Type = %d", DSBooleanClass.Type);
    DSLog("TRUE = %s", ToString(DSBooleanClass.True));
    DSLog("FALSE = %s", ToString(DSBooleanClass.False));
    DSLog("=============");
    __block DSCollection* c = q;


    Describe("Run Tests", ^{

        It("True and True are the same", ^{
            Expect(CompareTo(DSBooleanClass.True, DSBooleanClass.True) == 0);
        });
        
        It("Should be 5", ^{
            Expect(Length(s) == 5);
        });

        It("Should be 6", ^{
            Expect(Length(a) == 6);
        });

        It("Should be 2", ^{
            Expect(Length(q) == 2);
        });

        It("Should be 2", ^{
            Expect(Length(c) == 2);
        });

        It("Should equal 420", ^{
            Expect(LongValue(l) == 420);
        });

        It("Should equal another instance", ^{
            Expect(Equals(l, m));
        });

        It("Should be a Long", ^{
            Expect(!strcmp("DSLong", GetClassName(l)));
            Expect(!strcmp("DSLong", GetClass(l)->name));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        It("keyB is 430", ^{
            Expect(LongValue(Get(h,"keyB")) == 430);
        });

    });
    DSLog("");
    DSLog("Tests run: %d", tests.total);
    DSLog("Tests passed: %d", tests.passed);
    DSLog("Tests failed: %d", tests.failed);
    return tests.failed;
    DSLog("Hello World");

    return 0;
}


