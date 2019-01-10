#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <Block.h>
#include "darkunit.h"

void TestHashMap();
char keys[12][7] = {
    "key1", "key2", "AbCdEf",
    "key4", "key5", "key6",
    "key7", "key8", "key9",
    "keyA", "keyB", "keyC",
};

int overload MyFunc(int test) {
    return test;
}

int overload MyFunc(float test) {
    return MyFunc((int)test);
}

int main(int argc, char **argv) {

    auto C = new(DSChar, 'a');
    DSLog("C = %s", ToString(C)); 
    long lzx = LongValue(C);
    DSNumber* N = C;
    DSLog("N = %s", ToString(N)); 
    long qZx = LongValue(N);

    DSBoolean* IS = $DSBoolean.True;
    bool is = IsDSBoolean(IS);
    DSLog("is boolean? %s", ToString(new(DSBoolean, is)));

    DSBoolean* T1 = IS;
    DSString* T2 =$("test");


    if (AsDSBoolean(T1) == nullptr) DSLog("Q1 is null"); else DSLog("Q1 is %s", ToString(T1));
    if (AsDSBoolean(T2) == nullptr) DSLog("Q2 is null"); else DSLog("Q2 is %s", ToString(T2));

    __block auto l = new(DSLong, 420);
    __block auto m = new(DSLong, 420); 
    __block auto b = new(DSBoolean, true); 

    DSLog("should be DSBoolean: %s", GetClassName(b));

    __block auto s = $("Frodo");
    __block auto a = new(DSArray, 0);
    __block auto q = new(DSList);
    __block auto h = new(DSHashmap);

    for (int i=0; i<12; i++)
    {
        DSLog("%s", keys[i]);
        Put(h, keys[i], new(DSLong, i+420));
    }

    for (int i=0; i<12; i++)
    {
        DSLog("Get %d", i);
        DSLong* l1 = Get(h, keys[i]);
        DSLog("Got %d", i);
        long l2 = LongValue(l1);
        DSLog("%d", l2);
    }


    __block auto l0 = $DSLong.Create(0);
    __block auto l1 = new(DSLong, 1);
    __block auto l2 = new(DSLong, 2);
    __block auto l3 = new(DSLong, 3);
    __block auto l4 = new(DSLong, 4);
    __block auto l5 = new(DSLong, 5);

    Add(a, l0);
    Add(a, l1);
    Add(a, l2);
    Add(a, l3);
    Add(a, l4);
    Add(a, l5);

    Add(q, l);    
    Add(q, m);


    DSLog("=============");
    DSLog("%d", Length(a));
    for (int i=0; i<Length(a); i++) {
        DSLog("%d)", i);
        DSLog("%d) %d", i, LongValue((DSNumber*)Get(a,i)));
    }
    DSLog("%s", ToString(q));
    DSLog("Bytes = %d", $DSBoolean.Bytes);
    DSLog("Size = %d", $DSBoolean.Size);
    DSLog("Type = %d", $DSBoolean.Type);
    DSLog("TRUE = %s", ToString($DSBoolean.True));
    DSLog("FALSE = %s", ToString($DSBoolean.False));
    DSLog("=============");

    __block DSChar* zz = new(DSChar, 'c');


    Describe("Run Tests", ^{

        It("True and True are the same", ^{
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

        // It("Should equal another instance", ^{
        //     Expect(Equals((DSObject*)l, (DSObject*)m));
        // });

        It("Should be a Long", ^{
            Expect(Equals($("DSLong"), $(GetClassName(l))));
            Expect(Equals($("DSLong"), $(GetClass(l)->name)));
        });

        It("Should be a Boolean", ^{
            Expect(!strcmp("DSBoolean", GetClassName(b)));
            Expect(!strcmp("DSBoolean", GetClass(b)->name));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        It("keyB is 430", ^{
            DSNumber* n = Get(h,"keyB");
            Expect(LongValue(n) == 430);
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
    // return 0;

    return tests.failed;
}


