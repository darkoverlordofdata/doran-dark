using System;
using Jasmine;
using Dark;
using Dark.Collections;

public void TestTypes()
{
    // must be declared in outer scope so lifetime is valid during test
    var lVal = new Dark.Long(420);
    var iVal = new Dark.Integer(420);
    var cVal = new Dark.Char(126);
    var sVal = new Dark.Short(420);
    var fVal = new Dark.Float(420f);
    var dVal = new Dark.Double(420.0);
    var xVal = new Dark.String("Frodo");
        // print("Char = %c\n", s.CharAt(3));
        // return 0;


    Describe("Type Integer", () => {
        It("Bytes should be 4", () => Expect<int>(4).ToBe<int>(Dark.Integer.Bytes));
        It("Size should be 32", () => Expect<int>(32).ToBe<int>(Dark.Integer.Size));
        It("Value should be 420", () => Expect<int>(420).ToBe<int>(iVal.IntValue()));
    });

    Describe("Type Long", () => {
        It("Bytes should be 4", () => Expect<int>(4).ToBe<int>(Dark.Long.Bytes));
        It("Size should be 32", () => Expect<int>(32).ToBe<int>(Dark.Long.Size));
        It("Value should be 420", () => Expect<long>(420).ToBe<long>(lVal.LongValue()));
    });

    Describe("Type Short", () => {
        It("Bytes should be 2", () => Expect<int>(2).ToBe<int>(Dark.Short.Bytes));
        It("Size should be 16", () => Expect<int>(16).ToBe<int>(Dark.Short.Size));
        It("Value should be 420", () => Expect<int>(420).ToBe<int>(sVal.ShortValue()));
    });

    Describe("Type Char", () => {
        It("Bytes should be 1", () => Expect<int>(1).ToBe<int>(Dark.Char.Bytes));
        It("Size should be 8", () => Expect<int>(8).ToBe<int>(Dark.Char.Size));
        It("Value should be 126", () => Expect<char>(126).ToBe<char>(cVal.CharValue()));
    });

    Describe("Type Float", () => {
        It("Bytes should be 4", () => Expect<int>(4).ToBe<int>(Dark.Float.Bytes));
        It("Size should be 32", () => Expect<int>(32).ToBe<int>(Dark.Float.Size));
        It("Value should be 420.0", () => Expect<double?>(420.0).ToBe<double?>(fVal.FloatValue()));
    });

    Describe("Type Double", () => {
        It("Bytes should be 8", () => Expect<int>(8).ToBe<int>(Dark.Double.Bytes));
        It("Size should be 64", () => Expect<int>(64).ToBe<int>(Dark.Double.Size));
        It("Value should be 420.0", () => Expect<double?>(420.0).ToBe<double?>(dVal.DoubleValue()));
    });

    Describe("Type String", () => {
        It("CharAt 3 should be 'd'", () => Expect<char>('d').ToBe<int>(xVal.CharAt(3)));

    });

    var env = Jasmine.GetEnv();
    env.AddReporter(new Jasmine.ConsoleReporter());
    env.Execute();
}


