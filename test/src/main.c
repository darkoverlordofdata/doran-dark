#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <Block.h>
#include "darkunit.h"
#include "main.h"

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

    var l = $(420L);
    var m = $(420L); 
    var b = $(true); 
    var s = $("Frodo");
    var c = $('c');
    var ary = new(DSArray, 0);
    var lst = new(DSList);
    // var hsh = new(DSHashmap, of(DSBoolean));
    // var hsh = new(DSHashmap);
    var hsh = new(DSHashmap, of(DSNumber));
    var zhsh = new(DSHashmap, of(DSBoolean));

    Try Put(zhsh, "forodo", l);
    Catch (e) DSLog(e->msg);



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


