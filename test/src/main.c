#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"


int main(int argc, char **argv) {


    __block Long l = Long_New(420);
    __block Long m = Long_New(420);
    __block Boolean b = Boolean_New(true);

    __block String s = String_New("Frodo");
    __block Array a = Array_New();
    __block List q = List_New();
    __block Hashmap h = Hashmap_New();

    char keys[12][5] = {
        "key1", "key2", "key3",
        "key4", "key5", "key6",
        "key7", "key8", "key9",
        "keyA", "keyB", "keyC",
    };

    for (int i=0; i<12; i++)
    {
        printf("%s\n", keys[i]);
        Put(h, keys[i], Long_New(i+420));
    }
    for (int i=0; i<12; i++)
    {
        printf("%d\n", LongValue(Get(h, keys[i])));
    }

    __block Long l0 = Long_New(0);
    __block Long l1 = Long_New(1);
    __block Long l2 = Long_New(2);
    __block Long l3 = Long_New(3);
    __block Long l4 = Long_New(4);
    __block Long l5 = Long_New(5);

    Add(a, l0);
    Add(a, l1);
    Add(a, l2);
    Add(a, l3);
    Add(a, l4);
    Add(a, l5);

    Add(q, l);    
    Add(q, m);

    // Long ll = Get(a, 0);    
    
    printf("=============\n");
    printf("%d\n", Length(a));
    for (int i=0; i<Length(a); i++) {
        printf("%d)\n", i);
        printf("%d) %d\n", i, LongValue(Get(a, i)));
    }
    printf("%s\n", ToString(q));
    printf("Bytes = %d\n", BooleanClass.Bytes);
    printf("Size = %d\n", BooleanClass.Size);
    printf("Type = %d\n", BooleanClass.Type);
    printf("TRUE = %s\n", ToString(BooleanClass.True));
    printf("FALSE = %s\n", ToString(BooleanClass.False));
    printf("=============\n");
    __block Collection c = q;




    Describe("Run Tests", ^{

        It("True and True are the same", ^{
            Expect(CompareTo(BooleanClass.True, BooleanClass.True) == 0);
        });
        
        It("Should be 5", ^{
            Expect(Length(s) == 5);
        });

        It("Should be 1", ^{
            Expect(Length(a) == 1);
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
            Expect(!strcmp("Long", GetClassName(l)));
            Expect(!strcmp("Long", GetClass(l)->name));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        It("keyB is 430", ^{
            Expect(LongValue(Get(h,"keyB")) == 430);
        });

    });
    printf("\n");
    printf("Tests run: %d\n", tests.total);
    printf("Tests passed: %d\n", tests.passed);
    printf("Tests failed: %d\n", tests.failed);
    return tests.failed;
}

