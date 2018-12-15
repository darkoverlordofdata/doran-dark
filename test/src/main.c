#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"

void overload ForEach(TList const this, void (^iter)(TString))
{
    for (TListNode curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}


// 
int main(int argc, char **argv) {

    printf("Hello World\n");

    id l = Long.Create(420);
    long v = LongValue(l);
    printf("v = %d\n", v);

    id a = Array.Create(4);

    TArray a1 = AsArray(a);
    printf("%d - %s\n", typeid(a1), typename(a1));

    TList ls = List.Create();
    Add(ls, String.Create("first"));
    Add(ls, String.Create("second"));

    ForEach(ls, ^(TString s) {
        printf("item = %d) %s\n", s->length, s->value);
    });

    return 0;
}


