#include <dark/Foundation.h>
#include <Block.h>


int foobar(int, int, int);
#define foobar(x, ...) foobar_((x), ##__VA_ARGS__, __DEFAULT__, __DEFAULT__)
#define foobar_(x, z, t, ...) (foobar)((x), DEFAULT((z), 42), DEFAULT((t), 36))

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


    var z = new(DSHashmap);

    var y = NewDSHashmap($T(DSLong));

    DSLog("typeof = %s", y->typeOf->name );

    return 0;
}

/**
 * Execute block `lambda` with try/catch
 * return result as Either::Right 
 * return exception as Either::Left
 */
Either* Try(DSObject* (^lambda)(void)) {
    DSException* e;
    try {
        return Right(lambda());
    } catch (e) {
        return Left($(e->msg));
    }
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



void More() {
    auto answer = Try(^{
         return (DSObject*)$(DSParseDouble("frodo")); 
    });

    if (IsRight(answer)) {
        DSLog("answer = %$", GetRight(answer));
    } else {
        DSLog("error is %$", GetLeft(answer));
    }

    // riia:
    {   
        using(DSHashmap) zhsh = new(DSHashmap, of(DSBoolean));

        auto res = Put(zhsh, "test", $(430L));
        if (IsRight(res)) {
            DSLog("Put Succeeded");
        } else {
            DSLog("Error: %$", GetLeft(res));
        }
        Test(zhsh);
    }// dtor is called here as it goes out of scope


}

int (foobar)(int x, int y, int z) {
    DSLog("foobar x:%d", x);
    DSLog("foobar y:%d", y);
    DSLog("foobar z:%d", z);
    return 0;
}


