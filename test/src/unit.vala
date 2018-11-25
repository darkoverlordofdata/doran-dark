
// Interop with Vala
// generic collections should not be used for primitives - esp. strings and floats.

// strings don't release memory correctly
// floats get a c level error when cast to void*
// floats expand to double when used in variadic argument list

public class Unit {

    static int main (string[] args) {
        stdout.printf("Hello World\n");
        TestOne();
        return 0;
    }
}


