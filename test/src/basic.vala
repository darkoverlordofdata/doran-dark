using System;
using Jasmine;
using Dark;
using Dark.Collections;

public void TestOne()
{
    Hashmap<int> h_int = new Hashmap<int>();
    h_int["intvalue"] = 420;

    Hashmap<Dark.Long> h_Long = new Hashmap<Dark.Long>();
    Dark.Long L = new Dark.Long(420);
    h_Long["longValue"] = L;


    Describe("Hashmap", () => {

        It("Should store int", () => {
            Expect<int>(420).ToBe<int>(h_int["intvalue"]);
        });

        It("Should be a Long", () => {
            // Dark.Long x = new Dark.Long(420);
            var x = h_Long["longValue"];
            Expect<long>(420).ToBe<long>(x.value);

        });

    });

    var env = Jasmine.GetEnv();
    env.AddReporter(new Jasmine.ConsoleReporter());
    env.Execute();

}


