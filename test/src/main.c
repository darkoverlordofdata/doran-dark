#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <Block.h>
#include "darkunit.h"
#include "main.h"

void DSHashmap_dtor(void* this);

void TestHashMap();
char keys[12][7] = {
    "key1", "key2", "AbCdEf",
    "key4", "key5", "key6",
    "key7", "key8", "key9",
    "keyA", "keyB", "keyC",
};

int (foobar)(int x, int y, int z) {
    DSLog("foobar x:%d", x);
    DSLog("foobar y:%d", y);
    DSLog("foobar z:%d", z);
    return 0;
}

void Test(DSHashmap* zhsh);
void Test2(DSHashmap* zhsh);

int main(int argc, char **argv) {

    DSLog("** DaRKSTEP Test** \n");

    auto l = $(420L);
    auto m = $(420L); 
    auto b = $(true); 
    auto s = $("Frodo");
    auto c = $('c');
    auto ary = new(DSArray, 0);
    auto lst = new(DSList);
    auto hsh = new(DSHashmap, of(DSNumber));

    {   // riia:
        DSHashmap* dtor(DSHashmap_dtor) zhsh = new(DSHashmap, of(DSBoolean));

        auto res = Put(zhsh, "test", $(430L));
        if (IsRight(res)) {
            DSLog("Put Succeeded");
        } else {
            DSLog("Error: %$", GetLeft(res));
        }
        Test(zhsh);
    }// dtor is called here as it goes out of scope


    for (int i=0; i<12; i++) {
        Put(hsh, keys[i], $(i+420));
    }


    Add(ary, $(0));
    Add(ary, $(1));
    Add(ary, $(2));
    Add(ary, $(3));
    Add(ary, $(4));
    Add(ary, $(5));

    Add(lst, l);    
    Add(lst, m);


    Describe("Run Tests", ^{

        It("True and True are the same", ^{
            Expect(CompareTo($DSBoolean.True, $DSBoolean.True) == 0);
        });
        
        It("Should be 5", ^{
            Expect(Length(s) == 5);
        });

        It("Should be 6", ^{
            Expect(Length(ary) == 6);
        });

        It("Should be 2", ^{
            Expect(Length(lst) == 2);
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
            DSNumber* n = Get(hsh,"keyB");
            Expect(LongValue(n) == 430);
        });

        It("should be a c", ^{
            Expect(LongValue(c) == 99);
        });
    });

    DSLog("");
    DSLog("Tests run: %d", tests.total);
    DSLog("Tests passed: %d", tests.passed);
    DSLog("Tests failed: %d", tests.failed);
    DSLog("Fini!");

    return tests.failed;
}

/**
 * Deprecated error handling:
 */
void Test(DSHashmap* zhsh) {
    DSException* e;
    try {
        // Adding a long to a collection of DSBoolean -
        // should throw an exception
        auto res = Put(zhsh, "test", $(430L));
        if (!IsRight(res)) throw DSInvalidTypeException(ToString(GetLeft(res)));
    }
    catch (e)  {
        DSLog(e->msg);
    }
}

