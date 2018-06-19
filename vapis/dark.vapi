[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "darkfx.h")]
namespace Dark 
{
	public const int MajorVersion;
	public const int MinorVersion;
	public const int BuildVersion;


	[Compact]
	[CCode (cname = "Dark_Object", ref_function = "Dark_Object_AddRef", unref_function = "Dark_Object_Release")]
	public class Object
	{
		[CCode (cname = "Dark_Object_New")]
		public Object();
		[CCode (cname = "Dark_Object_ToString")]
		public unowned string ToString();
		[CCode (cname = "Dark_Object_GetHashCode")]
		public int GetHashCode();
		[CCode (cname = "Dark_Object_Equals")]
		public bool Equals(Object? other);
		[CCode (cname = "Dark_Object_ReferenceEquals")]
		public static bool ReferenceEquals(Object? objA, Object? objB);
		[CCode (cname = "Dark_Object_InstanceEquals")]
		public static bool InstanceEquals(Object? objA, Object? objB);
	}

	[Compact]
	[CCode (cname = "Dark_Shape", ref_function = "Dark_Object_AddRef", unref_function = "Dark_Object_Release")]
	public abstract class Shape : Object
	{
		[CCode (cname = "Dark_Shape_New")]
		public Shape();
		[CCode (cname = "Dark_Shape_Area")]
		public abstract int Area();
		[CCode (cname = "Dark_Shape_Draw")]
		public abstract int Draw();
		[CCode (cname = "Dark_Shape_MoveBy")]
		public int MoveBy(int dx, int dy);
		[CCode (cname = "Dark_Shape_ToString")]
		public abstract unowned string ToString();
	}

	[Compact]
	[CCode (cname = "Dark_Rect", ref_function = "Dark_Object_AddRef", unref_function = "Dark_Object_Release")]
	public class Rect : Shape
	{
		[CCode (cname = "Dark_Rect_New")]
		public Rect(int x, int y, int width, int height);
	}

	[Compact]
	[CCode (cname = "Dark_Circle", ref_function = "Dark_Object_AddRef", unref_function = "Dark_Object_Release")]
	public class Circle : Shape
	{
		[CCode (cname = "Dark_Circle_New")]
		public Circle(int x, int y, int radius);
	}

}
