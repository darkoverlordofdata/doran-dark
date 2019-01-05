#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"


void TestHashMap();
char keys[12][7] = {
    "key1", "key2", "AbCdEf",
    "key4", "key5", "key6",
    "key7", "key8", "key9",
    "keyA", "keyB", "keyC",
};
struct hashmap* class_hash;

int main(int argc, char **argv) {


    DSLog("Hello World");
    __block struct DSLong* l = NewDSLong(420);
    __block DSLong* m = NewDSLong(420);
    __block DSBoolean* b = NewDSBoolean(true);
    DSLog("should be DSBoolean: %s", GetClassName(b));

    __block DSString* s = $("Frodo");
    __block DSArray* a = NewDSArray(0);
    __block DSList* q = NewDSList();
    __block DSHashmap* h = NewDSHashmap();

    for (int i=0; i<12; i++)
    {
        DSLog("%s", keys[i]);
        Put(h, keys[i], NewDSLong(i+420));
    }

    for (int i=0; i<12; i++)
    {
        DSLog("Get %d", i);
        DSLong* l1 = Get(h, keys[i]);
        DSLog("Got %d", i);
        int l2 = LongValue(l1);
        DSLog("%d", l2);
    }


    __block DSLong* l0 = NewDSLong(0);
    __block DSLong* l1 = NewDSLong(1);
    __block DSLong* l2 = NewDSLong(2);
    __block DSLong* l3 = NewDSLong(3);
    __block DSLong* l4 = NewDSLong(4);
    __block DSLong* l5 = NewDSLong(5);

    Add(a, l0);
    Add(a, l1);
    Add(a, l2);
    Add(a, l3);
    Add(a, l4);
    Add(a, l5);

    Add(q, l);    
    Add(q, m);

    // // Long ll = Get(a, 0);    
    
    DSLog("=============");
    DSLog("%d", Length(a));
    for (int i=0; i<Length(a); i++) {
        DSLog("%d)", i);
        DSLog("%d) %d", i, LongValue(Get(a, i)));
    }
    DSLog("%s", ToString(q));
    DSLog("Bytes = %d", $DSBoolean.Bytes);
    DSLog("Size = %d", $DSBoolean.Size);
    DSLog("Type = %d", $DSBoolean.Type);
    DSLog("TRUE = %s", ToString($DSBoolean.True));
    DSLog("FALSE = %s", ToString($DSBoolean.False));
    DSLog("=============");
    // __block DSCollection* c = q;

    __block DSChar* zz = NewDSChar('c');


    Describe("Run Tests", ^{

        It("True and True are the same", ^{
            DSLog("True = %d", $DSBoolean.True->value);
            DSLog("False = %d", $DSBoolean.False->value);
            // return 0;
            Expect(CompareTo($DSBoolean.True, $DSBoolean.True) == 0);
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

        It("Should be a Boolean", ^{
            Expect(!strcmp("DSBoolean", GetClassName(b)));
            Expect(!strcmp("DSBoolean", GetClass(b)->name));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        It("keyB is 430", ^{
            Expect(LongValue(Get(h,"keyB")) == 430);
        });

        It("should be a c", ^{
            Expect(LongValue(zz) == 99);
        });



    });

    DSLog("");
    DSLog("Tests run: %d", tests.total);
    DSLog("Tests passed: %d", tests.passed);
    DSLog("Tests failed: %d", tests.failed);
    DSLog("Fini!");
    return 0;

    return tests.failed;
}


