[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "dark/darkfx.h")]
namespace Dark 
{
	public const int MajorVersion;
	public const int MinorVersion;
	public const int BuildVersion;

	[SimpleType]
	[CCode (cname = "Any")]
	public Any { }

	[Compact]
	[CCode (cname = "Object", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class DKObject
	{
		[CCode (cname = "Object_New")]
		public DKObject();
		[CCode (cname = "Object_ToString")]
		public unowned string ToString();
		[CCode (cname = "Object_GetHashCode")]
		public int GetHashCode();
		[CCode (cname = "Object_Equals")]
		public bool Equals(DKObject? other);
		[CCode (cname = "Object_ReferenceEquals")]
		public static bool ReferenceEquals(DKObject? objA, DKObject? objB);
		[CCode (cname = "Object_InstanceEquals")]
		public static bool InstanceEquals(DKObject? objA, DKObject? objB);
	}

	public delegate Compare int(Any item1, Any item2);

	public delegate ListIterator void(Any item);

	[Compact]
	[CCode (cname = "List", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class List : DKObject
	{
		[CCode (cname = "List_New")]
		public List();
		[CCode (cname = "List_Add")]
		int Add(Any data, Compare f);
		[CCode (cname = "List_Push")]
		void Push(Any data);
		[CCode (cname = "List_Pop")]
		Any Pop();
		[CCode (cname = "List_Iterate")]
		void Iterate(ListIterator f);
		[CCode (cname = "List_Dispose")]
		void Dispose();
		[CCode (cname = "List_ToString")]
		string ToString();
	}

	public delegate MapIterator int(Any p1, Any p2);

	[Compact]
	[CCode (cname = "Hashmap", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class Hashmap : DKObject
	{
		[CCode (cname = "Hashmap_New")]
		public Hashmap();
		[CCode (cname = "Hashmap_HashInt")]
		public HashInt(string keystring);
		[CCode (cname = "Hashmap_Hash")]
		public int Hash(string key);
		[CCode (cname = "Hashmap_Rehash")]
		public int Rehash();
		[CCode (cname = "Hashmap_Put")]
		public int Put(string key, Any value);
		[CCode (cname = "Hashmap_Get")]
		public Any Get(string key);
		[CCode (cname = "Hashmap_Get")]
		public int Hashmap_Iterate(MapIterator f, Any item);
		[CCode (cname = "Hashmap_Remove")]
		public int Remove(string key);
		[CCode (cname = "Hashmap_Dispose")]
		public void Dispose();
		[CCode (cname = "Hashmap_Length")]
		public int Length();
		[CCode (cname = "Hashmap_ToString")]
		public string ToString();
	}
	
	[Compact]
	[CCode (cname = "Vector", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class Vector : DKObject
	{
		[CCode (cname = "Vector_New")]
		public Vector();
		[CCode (cname = "Vector_Count")]
		public int Count();
		[CCode (cname = "Vector_Resize")]
		public void Resize(int capacity);
		[CCode (cname = "Vector_Add")]
		public void Add(Any item);
		[CCode (cname = "Vector_Set")]
		public void Set(int index, Any item);
		[CCode (cname = "Vector_Get")]
		public Any Get(int index);
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
