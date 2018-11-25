[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "dark/darkfx.h")]
namespace Dark 
{
	public const int MajorVersion;
	public const int MinorVersion;
	public const int BuildVersion;

	[Compact]
	[CCode (cname = "DObject_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class DObject
	{
		[CCode (cname = "DObject_New")]
		public DObject();
		[CCode (cname = "DObject_ToString")]
		public unowned string ToString();
		[CCode (cname = "DObject_GetHashCode")]
		public int GetHashCode();
		[CCode (cname = "DObject_Equals")]
		public bool Equals(DObject? other);
		[CCode (cname = "DObject_ReferenceEquals")]
		public static bool ReferenceEquals(DObject? objA, DObject? objB);
		[CCode (cname = "DObject_InstanceEquals")]
		public static bool InstanceEquals(DObject? objA, DObject? objB);
	}

	[Compact]
	[CCode (cname = "Compareable_t")]
	public abstract class Compareable : DObject
	{
		public abstract int CompareTo(Compareable other);
	}
	
	[Compact]
	[CCode (cname = "Number_t")]
	public abstract class Number : Compareable
	{
        public abstract int IntValue();
        public abstract long LongValue();
        public abstract float FloatValue();
        public abstract double DoubleValue();
        public abstract char CharValue();
        public abstract short ShortValue();
	}
	
	[Compact]
	[CCode (cname = "Long_t", ref_function = "DObject_AddRef", unref_function = "DObject_Release")]
	public class Long : Number
	{
		public long value;
		[CCode (cname = "Long_New")]
		public Long(long value);
		[CCode (cname = "Long_CompareTo")]
		public int CompareTo(Compareable other);
		[CCode (cname = "Long_IntValue")]
        public int IntValue();
		[CCode (cname = "Long_LongValue")]
        public long LongValue();
		[CCode (cname = "Long_FloatValue")]
        public float FloatValue();
		[CCode (cname = "Long_DoubleValue")]
        public double DoubleValue();
		[CCode (cname = "Long_CharValue")]
        public char CharValue();
		[CCode (cname = "Long_ShortValue")]
        public short ShortValue();

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
		public class List<G> : DObject
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
		public class Hashmap<G> : DObject
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
		public class Vector<G> : DObject
		{
			public void **data;
			public int capacity;
			public int count;
			[CCode (cname = "Vector_New")]
			public Vector(int capacity = 0);
			[CCode (cname = "Vector_Vala")]
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
