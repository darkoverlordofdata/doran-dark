#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"

void overload ForEach(DSList* this, void (^iter)(DSString*))
{
    for (DSListNode* curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}


// 
int main(int argc, char **argv) {

    printf("Hello World\n");

    // id* l = DSLongClass.Create(420);
    id* l = $DSLong(420);
    printf("Created...\n");
    long v = LongValue(l);
    printf("v = %d\n", v);

    id* a = $DSArray(4);

    DSArray* a1 = AsDSArray(a);
    printf("%d - %s\n", typeid(a1), typename(a1));

    DSList* ls = $DSList();
    Add(ls, $("first"));
    Add(ls, $("second"));

    ForEach(ls, ^(DSString* s) {
        printf("item = %d) %s\n", s->length, s->value);
    });

    return 0;
}


