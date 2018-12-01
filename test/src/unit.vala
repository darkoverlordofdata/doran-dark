using Dark;


public class Unit {

    static int main(string[] args) {
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


