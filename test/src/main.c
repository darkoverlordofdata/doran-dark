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

int main(int argc, char **argv) {

    DSException* e;

    DSLog("** DaRKSTEP Test** \n");

    int xx = foobar(1);

    auto l = $(420L);
    auto m = $(420L); 
    auto b = $(true); 
    auto s = $("Frodo");
    auto c = $('c');
    auto ary = new(DSArray, 0);
    auto lst = new(DSList);
    auto hsh = new(DSHashmap, of(DSNumber));
    {
        DSHashmap* dispose(DSHashmap_dtor) zhsh = new(DSHashmap, of(DSBoolean));

        try {
            // Adding a long to a collection of DSBoolean -
            // should throw an exception
            Put(zhsh, "test", l);
        }
        catch (e)  {
            DSLog(e->msg);
        }
        DSLog("end of block");
    }// dtor is called here as it goes out of scope
    DSLog("after end of block");

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


