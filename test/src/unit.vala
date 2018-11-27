using Dark;

// Interop with Vala
// generic collections should not be used for primitives - esp. strings and floats.

// strings don't release memory correctly
// floats get a c level error when cast to void*
// floats expand to double when used in variadic argument list
// short has a problem allso ... <short> fails

public class Unit {

    static int main (string[] args) {
        print("Dark Framework Test Suite\n");
        print("=========================\n");
        TestTypes();

        return 0;
    }
}


