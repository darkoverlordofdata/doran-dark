using Dark;

// Interop with Vala
// generic collections should not be used for primitives - esp. strings and floats.

// strings don't release memory correctly
// floats get a c level error when cast to void*
// floats expand to double when used in variadic argument list
// short has a problem allso ... <short> fails

// ulong addressof(char* s)
// {
//     return (ulong)s;
// }
void* addressof(void* s)
{
    return (void*)s;
}

public class Unit {

    // public static void unittest() {
    static int main (string[] args) {
        print("Dark Framework %d.%d.%d Test Suite\n", Dark.MajorVersion, Dark.MinorVersion, Dark.BuildVersion);
        print("================================================================\n\n");
        TestTypes();

        var m = new String("this quick brown fox");
        print(@"$m\n");

        var sb = new Dark.StringBuilder();

        sb.Append("this ");
        sb.Append("is ");
        sb.Append("a ");
        sb.Append("test.");

        Dark.String s = sb.Concat();
        print(@"concat = $s\n");

        var x = new Dark.StringBuilder();
        x.Append("Old record speeds: ");
        x.Appendf("%f %d", 33.3, 45);
        print(@"$(x.Concat())\n");

        var v = new Dark.Collections.Vector<int>();
        v.Add(1);


        print("bye\n");
        return 0;

    }
}


