#include <dark/Foundation.h>
#include <Block.h>
#include "darkunit.h"
/**
 * Extend the DSList class with an iterator
 */
void overload ForEach(DSList* const this, void (^iter)(DSString*))
{
    for (var curr = this->head; curr != nullptr; curr = curr->next) {
        iter(curr->data);
    }
}

int main(int argc, char **argv) {

    DSLog("Hello World");
    /**
     * $ wraps primitive values with corresponding Type
     */
    var pi = $(3.1415f);
    DSLog("pi = %$", pi);
    DSLog("typeof(pi) = %s", typeof(pi));

    DSList* ls = new(DSList);
    Add(ls, $("first"));
    Add(ls, $("second"));
    ForEach(ls, ^(DSString* s) {
        DSLog("item = %d) %$", Length(s), s);
    });

    DSLog("this string %$", $(20.0f));

    var s = $Join($("the "), $("answer "), $("is "), $(42));
    DSLog("%$", s);
    DSLog(ToString(s));
    // DSString** ss = Split(s, " ");

    return 0;
}


