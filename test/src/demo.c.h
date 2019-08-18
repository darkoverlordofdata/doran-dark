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

    Log("Hello World");
    /**
     * $ wraps primitive values with corresponding Type
     */
    var pi = $(3.1415f);
    Log("pi = %$", pi);
    Log("typeof(pi) = %s", typeof(pi));

    DSList* ls = new(DSList);
    Add(ls, $("first"));
    Add(ls, $("second"));
    ForEach(ls, ^(DSString* s) {
        Log("item = %d) %$", Length(s), s);
    });

    Log("this string %$", $(20.0f));

    var s = $Join($("the "), $("answer "), $("is "), $(42));
    Log("%$", s);
    Log(ToString(s));
    // DSString** ss = Split(s, " ");


    var z = new(DSMap);

    var y = NewDSMap($T(DSLong));

    Log("typeof = %s", y->typeOf->name );

    return 0;
}

/**
 * Execute block `lambda` with try/catch
 * return result as Either::Right 
 * return exception as Either::Left
 */
Either* Try(Object* (^lambda)(void)) {
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
void Test(DSMap* zhsh) {
    DSException* e;
    try {
        // Adding a long to a collection of Boolean -
        // should throw an exception
        auto res = Put(zhsh, "test", $(430L));
        if (!IsRight(res)) throw DSInvalidTypeException(ToString(GetLeft(res)));
    }
    catch (e)  {
        Log(e->msg);
    }
}



void More() {
    auto answer = Try(^{
         return (Object*)$(DSParseDouble("frodo")); 
    });

    if (IsRight(answer)) {
        Log("answer = %$", GetRight(answer));
    } else {
        Log("error is %$", GetLeft(answer));
    }

    // riia:
    {   
        using(DSMap) zhsh = new(DSMap, of(Boolean));

        auto res = Put(zhsh, "test", $(430L));
        if (IsRight(res)) {
            Log("Put Succeeded");
        } else {
            Log("Error: %$", GetLeft(res));
        }
        Test(zhsh);
    }// dtor is called here as it goes out of scope


}

int (foobar)(int x, int y, int z) {
    Log("foobar x:%d", x);
    Log("foobar y:%d", y);
    Log("foobar z:%d", z);
    return 0;
}


