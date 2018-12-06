[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "dark/darkfx.h")]
namespace Dark 
{
	public const int MajorVersion;
	public const int MinorVersion;
	public const int BuildVersion;

	[Compact]
	[CCode (cname = "DObject_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public abstract class Object
	{
		[CCode (cname = "DObject_ToString")]
		public abstract unowned string ToString();
		[CCode (cname = "DObject_Dispose")]
		public abstract void Dispose();
		[CCode (cname = "DObject_GetHashCode")]
		public abstract int GetHashCode();
		[CCode (cname = "DObject_Equals")]
		public abstract bool Equals(Object? other);
		[CCode (cname = "DObject_ReferenceEquals")]
		public static bool ReferenceEquals(Object? objA, Object? objB);
		[CCode (cname = "DObject_InstanceEquals")]
		public static bool InstanceEquals(Object? objA, Object? objB);
	}

	[Compact]
	[CCode (cname = "Comparable_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public abstract class Comparable : Object
	{
		public abstract int CompareTo(Comparable other);
	}
	
	[Compact]
	[CCode (cname = "Number_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public abstract class Number : Comparable
	{
		[CCode (cname = "Number_IntValue")]
        public abstract int IntValue();
		[CCode (cname = "Number_LongValue")]
        public abstract long LongValue();
		[CCode (cname = "Number_FloatValue")]
        public abstract float FloatValue();
		[CCode (cname = "Number_DoubleValue")]
        public abstract double DoubleValue();
		[CCode (cname = "Number_CharValue")]
        public abstract char CharValue();
		[CCode (cname = "Number_ShortValue")]
        public abstract short ShortValue();
	}
	
	[Compact]
	[CCode (cname = "Long_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Long : Number
	{
		[CCode (cname = "LONG_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "LONG_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "LONG_SIZE")]
		public const int Size;
		[CCode (cname = "LONG_BYTES")]
		public const int Bytes;
		[CCode (cname = "LONG_TYPE")]
		public const int Type;

		[CCode (cname = "Long_ParseLong")]
		public static long ParseLong(string s, int radix = 10);

		public long value;
		[CCode (cname = "Long_New")]
		public Long(long value);
		[CCode (cname = "Long_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Long_IntValue")]
        public override int IntValue();
		[CCode (cname = "Long_LongValue")]
        public override long LongValue();
		[CCode (cname = "Long_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Long_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Long_CharValue")]
        public override char CharValue();
		[CCode (cname = "Long_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Long_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Short_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Short : Number
	{
		[CCode (cname = "SHORT_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "SHORT_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "SHORT_SIZE")]
		public const int Size;
		[CCode (cname = "SHORT_BYTES")]
		public const int Bytes;
		[CCode (cname = "SHORT_TYPE")]
		public const int Type;

		[CCode (cname = "Short_ParseLong")]
		public static short ParseShort(string s, int radix = 10);

		public long value;
		[CCode (cname = "Short_New")]
		public Short(short value);
		[CCode (cname = "Short_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Short_IntValue")]
        public override int IntValue();
		[CCode (cname = "Short_LongValue")]
        public override long LongValue();
		[CCode (cname = "Short_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Short_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Short_CharValue")]
        public override char CharValue();
		[CCode (cname = "Short_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Short_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Integer_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Integer : Number
	{
		[CCode (cname = "INTEGER_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "INTEGER_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "INTEGER_SIZE")]
		public const int Size;
		[CCode (cname = "INTEGER_BYTES")]
		public const int Bytes;
		[CCode (cname = "INTEGER_TYPE")]
		public const int Type;

		[CCode (cname = "Integer_ParseInt")]
		public static int ParseInt(string s, int radix = 10);

		public int value;
		[CCode (cname = "Integer_New")]
		public Integer(int value);
		[CCode (cname = "Integer_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Integer_IntValue")]
        public override int IntValue();
		[CCode (cname = "Integer_LongValue")]
        public override long LongValue();
		[CCode (cname = "Integer_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Integer_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Integer_CharValue")]
        public override char CharValue();
		[CCode (cname = "Integer_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Integer_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Char_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Char : Number
	{
		[CCode (cname = "CHAR_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "CHAR_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "CHAR_SIZE")]
		public const int Size;
		[CCode (cname = "CHAR_BYTES")]
		public const int Bytes;
		[CCode (cname = "CHAR_TYPE")]
		public const int Type;

		public int value;
		[CCode (cname = "Char_New")]
		public Char(char value);
		[CCode (cname = "Char_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Char_IntValue")]
        public override int IntValue();
		[CCode (cname = "Char_LongValue")]
        public override long LongValue();
		[CCode (cname = "Char_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Char_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Char_CharValue")]
        public override char CharValue();
		[CCode (cname = "Char_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Char_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Float_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Float : Number
	{
		[CCode (cname = "FLOAT_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "FLOAT_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "FLOAT_SIZE")]
		public const int Size;
		[CCode (cname = "FLOAT_BYTES")]
		public const int Bytes;
		[CCode (cname = "FLOAT_TYPE")]
		public const int Type;

		[CCode (cname = "Float_ParseFloat")]
		public static float ParseFloat(string s);

		public int value;
		[CCode (cname = "Float_New")]
		public Float(float value);
		[CCode (cname = "Float_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Float_IntValue")]
        public override int IntValue();
		[CCode (cname = "Float_LongValue")]
        public override long LongValue();
		[CCode (cname = "Float_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Float_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Float_CharValue")]
        public override char CharValue();
		[CCode (cname = "Float_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Float_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Double_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Double : Number
	{
		[CCode (cname = "DOUBLE_MIN_VALUE")]
		public const int Min;
		[CCode (cname = "DOUBLE_MAX_VALUE")]
		public const int Max;
		[CCode (cname = "DOUBLE_SIZE")]
		public const int Size;
		[CCode (cname = "DOUBLE_BYTES")]
		public const int Bytes;
		[CCode (cname = "DOUBLE_TYPE")]
		public const int Type;

		[CCode (cname = "Double_ParseDouble")]
		public static double ParseDouble(string s);

		public int value;
		[CCode (cname = "Double_New")]
		public Double(double value);
		[CCode (cname = "Double_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Double_IntValue")]
        public override int IntValue();
		[CCode (cname = "Double_LongValue")]
        public override long LongValue();
		[CCode (cname = "Double_FloatValue")]
        public override float FloatValue();
		[CCode (cname = "Double_DoubleValue")]
        public override double DoubleValue();
		[CCode (cname = "Double_CharValue")]
        public override char CharValue();
		[CCode (cname = "Double_ShortValue")]
        public override short ShortValue();
		[CCode (cname = "Double_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Boolean_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Boolean : Comparable
	{
		[CCode (cname = "LONG_SIZE")]
		public const int Size;
		[CCode (cname = "LONG_BYTES")]
		public const int Bytes;
		[CCode (cname = "LONG_TYPE")]
		public const int Type;
		[CCode (cname = "Boolean_ParseBool")]
		public static bool ParseBool(string s);

		public bool value;

		[CCode (cname = "Boolean_New")]
		public Boolean(long value);
		[CCode (cname = "Boolean_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "Boolean_BoolValue")]
		public bool BoolValue();
		[CCode (cname = "Boolean_ToString")]
		public override unowned string ToString();
	}

	[Compact]
	[CCode (cname = "String_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class String : Comparable
	{
		[CCode (cname = "LONG_TYPE")]
		public const int Type;
		[CCode (cname = "String_Format")]
		public static String Format(string format, ...);

		public char* value;
		public int length;

		public string to_string() {
			return (string)this.value;
		}

		[CCode (cname = "String_New")]
		public String(char* value);
		[CCode (cname = "String_CompareTo")]
		public override int CompareTo(Comparable other);
		[CCode (cname = "String_Length")]
		public int Length();
		[CCode (cname = "String_IsEmpty")]
		public bool IsEmpty();
		[CCode (cname = "String_CharAt")]
		public int CharAt(int index);	
		[CCode (cname = "String_ToString")]
		public override unowned string ToString();
		[CCode (cname = "String_CompareToIgnoreCase")]
		public int CompareToIgnoreCase(String other);
		[CCode (cname = "String_Concat")]
		public String Concat(String str);
		[CCode (cname = "String_Contains")]
		public bool Contains(String s);
		[CCode (cname = "String_CopyOf")]
		public String CopyOf(String other);
		[CCode (cname = "String_EndsWith")]
		public bool EndsWith(String suffix);
		[CCode (cname = "String_StartsWith")]
		public bool StartsWith(String prefix, int offset = 0);
		[PrintfFormat]
		[CCode (cname = "String_GetBytes")]
		public char* GetBytes();
		[CCode (cname = "String_IndexOf")]
		public int IndexOf(char* str, int fromIndex = 0);
		[CCode (cname = "String_LastIndexOf")]
		public int LastIndexOf(char* str, int fromIndex = 0);
		[CCode (cname = "String_ToUpperCase")]
		public String ToUpperCase();
		[CCode (cname = "String_ToLowerCase")]
		public String ToLowerCase();
		[CCode (cname = "String_Trim")]
		public String Trim();
		
	}

	[Compact]
	[CCode (cname = "StringBuilder_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class StringBuilder : Object
	{
		[CCode (cname = "StringBuilder_New")]
		public StringBuilder();
		[CCode (cname = "StringBuilder_Empty")]
		public int Empty();
		[CCode (cname = "StringBuilder_Append")]
		public int Append(char* str);
		[PrintfFormat]
		[CCode (cname = "StringBuilder_Appendf")]
		public int Appendf(string format, ...);
		[CCode (cname = "StringBuilder_Concat")]
		public String Concat();
		[CCode (cname = "StringBuilder_Reset")]
		public void Reset();
	}	
	
	namespace Collections
	{

		[CCode (has_target = false)]
		public delegate int Compare<G>(G item1, G item2);

		[CCode (has_target = false)]
		public delegate void ListIterator<G>(G item);

		[CCode (cname ="ListNode_t")]
		public struct ListNode<G> 
		{
			public G data;
			public ListNode<G>* next;
		}
		/**
		 * Generic List
		 */
		[Compact]
		[CCode (cname = "List_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
		public class List<G> : Object
		{
			public ListNode<G>* head;
			[CCode (cname = "List_New")]
			public List();
			[CCode (cname = "List_Add")]
			public int Insert(owned G data, Compare func);
			[CCode (cname = "List_Push")]
			public void Add(owned G data);
			[CCode (cname = "List_Pop")]
			public G Remove();
			[CCode (cname = "List_Iterate")]
			public void Iterate(ListIterator<G> f);
			[CCode (cname = "List_Dispose")]
			public void Dispose();
			[CCode (cname = "List_ToString")]
			public string ToString();
		}

		[CCode (has_target = false)]
		public delegate int MapIterator<G>(G p1, G p2);

		[CCode (cname ="HashmapNode_t")]
		public struct HashmapNode<G> 
		{
			public string key;
			public int inUse;
			public G data;
		}

		/**
		 * Generic Hashmap
		 */
		[Compact]
		[CCode (cname = "Hashmap_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
		public class Hashmap<G> : Object
		{
			public int tableSize;
			public int size;
			public HashmapNode* data;
			[CCode (cname = "Hashmap_New")]
			public Hashmap();
			[CCode (cname = "Hashmap_HashInt")]
			public uint HashInt(string keystring);
			[CCode (cname = "Hashmap_Hash")]
			public int Hash(string key);
			[CCode (cname = "Hashmap_Rehash")]
			public int Rehash();
			[CCode (cname = "Hashmap_Put")]
			public void set(string key, G value);
			[CCode (cname = "Hashmap_Get")]
			public G get(string key);
			[CCode (cname = "Hashmap_Get")]
			public int Hashmap_Iterate(MapIterator f, G item);
			[CCode (cname = "Hashmap_Remove")]
			public int Remove(string key);
			[CCode (cname = "Hashmap_Dispose")]
			public void Dispose();
			[CCode (cname = "Hashmap_Length")]
			public int Length();
			[CCode (cname = "Hashmap_ToString")]
			public string ToString();
		}
		
		/**
		 * Generic Vector
		 */
		[Compact]
		[CCode (cname = "Vector_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
		public class Vector<G> : Object
		{
			public void **data;
			public int capacity;
			public int count;
			[CCode (cname = "Vector_New")]
			public Vector(int capacity = 0);
			[CCode (cname = "Vector_Variadic")]
			public Vector.From(owned G first, ...);
			[CCode (cname = "Vector_Count")]
			public int Count();
			[CCode (cname = "Vector_Resize")]
			public void Resize(int capacity);
			[CCode (cname = "Vector_Add")]
			public void Add(owned G item);
			[CCode (cname = "Vector_Set")]
			public void set(int index, owned G item);
			[CCode (cname = "Vector_Get")]
			public G get(int index);
			[CCode (cname = "Vector_Delete")]
			public void Delete(int index);
			[CCode (cname = "Vector_Dispose")]
			public void Dispose();
			[CCode (cname = "Vector_Clear")]
			public void Clear();
			[CCode (cname = "Vector_ToString")]
			public string ToString();
		}
	}
}
