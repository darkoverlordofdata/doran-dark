## gc

Uses [tgc](https://github.com/orangeduck/tgc)

Why not [Boehme](https://github.com/ivmai/bdwgc)? 
I can't get a good build.
many of the build instructions don't match the content
the main makefile for windows, MAKEFILE_NT has syntax errors
I finally fot a cmake build to work, but it gives me 
a wierd ntdll runtime error when I link to it.

### alternate syntax


```c
struct Class {
	struct Class * isa;
	struct Class * super;
	char* name;
};

struct ObjectClass;
struct Object {
	struct ObjectClass* isa;
};
typedef struct Object* TObject;


struct ObjectClass {
	struct Class * isa;
	const char* ToString(struct Object*);
	const char* ToString(TObject);
};

ObjectClass Object;

struct BooleanClass;
struct Boolean {
	struct BooleanClass* isa;
	bool value;
}

struct BooleanClass {
	struct Class * isa;
	const char* ToString(struct Object*);
};

BooleanClass Boolean;

```