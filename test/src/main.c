#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <dark/unit.h>

void Map_dtor(void* this);

char keys[12][7] = {
    "key1", "key2", "AbCdEf",
    "key4", "key5", "key6",
    "key7", "key8", "key9",
    "keyA", "keyB", "keyC",
};

int main(int argc, char **argv) {

    const char* unc = "C:\\Users\\darko\\Documents\\GitHub\\doran-dark\\test\\license.md";

    Log("** DaRKSTEP Test** \n");

    auto l = $(420L);
    auto m = $(420L); 
    auto b = $(true); 
    auto s = $("Frodo");
    auto c = $('c');

    auto numArray = new(Array);//, of(Number));
    auto numList = new(List);//, of(Number));
    auto numHash = new(Map, of(Number));
    auto f1 = new(File, unc);

    for (int i=0; i<12; i++) {
        Put(numHash, keys[i], $(i+420));
    }

    Add(numArray, $(0));
    Add(numArray, $(1));
    Add(numArray, $(2));
    Add(numArray, $(3));
    Add(numArray, $(4));
    Add(numArray, $(5));

    Add(numList, l);    
    Add(numList, m);

    Describe("Run Tests", ^{

        It("Should be an error", ^{
            auto r = Put(numHash, "Frodo", $("Baggins"));
            Log(ToString(getLeft(r)));
            Expect(!isRight(r));
        });

        It("True and True are the same", ^{
            Expect(CompareTo($Boolean.True, $Boolean.True) == 0);
        });
        
        It("Should be 5", ^{
            Expect(Length(s) == 5);
        });

        It("Should be 6", ^{
            Expect(Length(numArray) == 6);
        });

        It("Should be 2", ^{
            Expect(Length(numList) == 2);
        });

        It("Should equal 420", ^{
            Expect(LongValue(l) == 420);
        });

        // It("Should equal another instance", ^{
        //     Expect(Equals((Object*)l, (Object*)m));
        // });

        It("Should be a Long", ^{
            Expect(Equals($("Long"), $(GetClassName(l))));
        });

        It("Should be a Boolean", ^{
            Expect(!strcmp("Boolean", GetClassName(b)));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        // It("keyB is 430", ^{
        //     Number* n = Get(numHash,"keyB");
        //     Expect(LongValue(n) == 430);
        // });

        It("should be a c", ^{
            Expect(LongValue(c) == 99);
        });

        It("File exists", ^{
            Expect(Exists(f1) == true);
        });

        It("filename is 'license.md'", ^{
            Expect(!strcmp(GetName(f1)->value, "license.md"));
        });

        It("size is 1090 bytes", ^{
            Expect(GetLength(f1) == 1090);
        });

        It("canon equals original unc", ^{
            Expect(!strcmp(GetPath(GetCanonicalFile(f1))->value,unc));
        });
        

    });
    Log("Done");

    return 0; //Summary();
}

