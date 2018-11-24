[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "dark/darkfx.h")]
namespace Dark 
{
	public const int MajorVersion;
	public const int MinorVersion;
	public const int BuildVersion;

	[Compact]
	[CCode (cname = "Object_t", ref_function = "Object_AddRef", unref_function = "Object_Release")]
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
	[CCode (cname = "List_t", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class List<G> : DKObject
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
	[CCode (cname = "Hashmap_t", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class Hashmap<G> : DKObject
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
	[CCode (cname = "Vector_t", ref_function = "Object_AddRef", unref_function = "Object_Release")]
	public class Vector<G> : DKObject
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
