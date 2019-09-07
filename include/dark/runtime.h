#pragma once

#define nil (id)0
#define Nil (Class)0

// static __inline void bcopy(const void *src, void *dst, size_t size) { memcpy(dst, src, size); }
// static __inline void bzero(void *dst, size_t size) { memset(dst, 0, size); }
/**
 * println
 * 
 */
__attribute__((__format__ (__printf__, 1, 2)))
static inline void println(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	#ifndef _WIN64
	vprintf(fmt, args);
	#else 
	_vcprintf(fmt, args);
	#endif
	va_end(args);
	#ifndef _WIN64
	printf("\n");
	#else 
	_cprintf("\n");
	#endif
}

#ifdef USE_GC
static bool _use_gc = true;
#else
static bool _use_gc = false;
#endif
static int _id = 1;

/** NX_hashmap interface for Class objects */
// HASHMAP_FUNCS_DECLARE(NX, const char, struct _class)

// extern struct hashmap* class_hash;

typedef struct _class 		*Class;

typedef struct dark_object {
	Class isa;
} *id;

typedef id (*IMP)(id, ...);

struct _class {
	Class isa;			// pointer to metaclass
	Class super_class;	// pointer to superclass
	char* name;			// name
	long id;			// unique id
	long version;		// version 1
	long flags;			// lifecycle flags
	long size;			// size of struct
	long count;			// count of methods in vtable
	IMP* vtable;		// pointer to vtable
};


extern struct hashmap* class_hash;

static inline Class GetClass(const char *name);
static inline Class CreateClass(Class superclass, const char *name, const int size, IMP* extVtable);
static inline void RegisterClass(Class cls);
static inline overload bool Add(Class cls, char* name, IMP imp);



#define CLS_CLASS				0x01
#define CLS_META				0x02
#define CLS_CONSTRUCTING		0x10
#define CLS_CONSTRUCTED		 	0x20

#define ISCLASS(cls)					(((cls)->flags & CLS_CLASS) != 0)
#define ISMETA(cls)						(((cls)->flags & CLS_META) != 0)
#define GETMETA(cls)					(ISMETA(cls) ? (cls) : (cls)->isa)


static inline char* typename(id obj) { return obj->isa->name; }
static inline UInt64 typeid(id obj) { return (UInt64)obj->isa; }

