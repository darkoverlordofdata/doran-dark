## C Overloaded

combine clang overload attribute and polymorphic patterns into a 'generic c'.

runtime influences: objective-c, glib, nim, quantumleaps (http://www.state-machine.com/doc/an#Patterns)

framework influnces: java, csharp

ObjC is the opposite of GLib.

GLib attempts to be compatible with every ani-pattern in the wild. It coddles every edge case it can find. ObjC on the other hand forces you to follow a well thought out pattern. This makes it much more simple to understand than the rats nest called GLib.

### Reference
Tne point is not to replicate objc, but to have objc objects available in c.

I'm using this version as a reference: https://opensource.apple.com/source/objc4/objc4-437/runtime/, though there are mods.
prefix old_ is renemmed to objc_, other prefix are dropped. No ->ISA() or ->setIfo(). Always use GC.

I may change IMP:

	typedef id (*IMP)(id self, SEL _cmd, ...);

	typedef id (*IMP)(id self, ...);

there is no reason the reciving method needs to know the _cmd, and forwarding is smoother without it.

### VTables
Tne point is not to replicate objc, but to have objc objects available in c.

That's the mantra. I'm not sole on sendMsg. rather than cacheing selectors, I'm building a vtable when the class is created. My design uses the SEL as a generic function. but I want to support sendMsg, using a 'cartouche':

	_(obj, SEL, ...)







typedef struct objc_object {
    Class isa;
} *id;

typedef struct objc_class {
	Class isa;
	Class super_class;
	char* name;
    long version;
	long info;
    long instance_size;
	struct objc_ivar_list *ivars;
	struct objc_method_list **methodLists;
	struct objc_cache *cache;
	struct objc_protocol_list *protocols;
} *Class;

		  Object   Class    Meta
object => isa 	=> isa 	=>	isa
		  Vtable   
		  Ivar0	   
		  Ivar1	    
		  ...
		  IvarN

objc_ivar_list & objc_method_list are descriptive.

objc_ivar_list list the offsets in the object struct:

vptr => address at &name##Class+32
obj->isa
obj->field1 <== objc_ivar_list
obj->field2
obj->fieldN

objc_method_list is cooalsced into a vtble in memory 

// Freed objects have their isa set to point to this dummy class.
// This avoids the need to check for Nil classes in the messenger.
static const void* freedObjectClass[12] =
{
    Nil,				// isa
    Nil,				// superclass
    "FREED(id)",			// name
    0,				// version
    0,				// info
    0,				// instance_size
    nil,				// ivars
    nil,				// methodLists
    (Cache) &_objc_empty_cache,		// cache
    nil				// protocols
};


