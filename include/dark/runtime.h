/*
 * Copyright (c) 1999-2006 Apple Inc.  All Rights Reserved.
 * Copyright (c) 2018-2019 Dark Overlord of Data - modifications for DaRKStep
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#pragma once
#ifndef _OBJC_CORE_H_
#define _OBJC_CORE_H_
#include "hashmap.h"

#define nil (id)0
#define Nil (Class)0

static __inline void bcopy(const void *src, void *dst, size_t size) { memcpy(dst, src, size); }
static __inline void bzero(void *dst, size_t size) { memset(dst, 0, size); }

/**
 * _objc_inform
 * 
 */
__attribute__((__format__ (__printf__, 1, 2)))
static inline void _objc_inform(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	_vcprintf(fmt, args);
	va_end(args);
	_cprintf("\n");
}


/** NX_hashmap interface for Class objects */
HASHMAP_FUNCS_DECLARE(NX, const char, struct objc_class)

extern struct hashmap* class_hash;

/** ObjC runtime structs */
typedef struct objc_cache 		*Cache;
typedef struct objc_category 	*Category;
typedef struct objc_class 		*Class;
typedef struct objc_ivar 		*ivar;
typedef struct objc_method 		*Method;
typedef struct objc_module 		*Module;
typedef struct objc_selector 	*SEL;
typedef struct objc_symtab 		*Symtab;

typedef struct objc_object 		Protocol;
typedef struct objc_property 	*objc_property_t;

typedef struct objc_object {
	Class isa;
} *id;

// typedef id (*IMP)(id, SEL, ...);
typedef id (*IMP)(id, ...);

struct objc_class {
	Class isa;
	Class super_class;
	char* name;
	long version;
	long info;
	long instance_size;
	struct objc_ivar_list *ivars;
	struct objc_method_list **methodLists;
	// struct objc_cache *cache; /**  cache is replaced with vtable */
	IMP* vtable;
	struct objc_protocol_list *protocols;
};

struct objc_protocol_list {
	struct objc_protocol_list *next;
	long count;
	Protocol *list[1];
};

struct objc_method_description {
	SEL name;
	char *types;
};

struct objc_method_description_list {
	int count;
	struct objc_method_description list[1];
};

struct objc_category {
	char* category_name;
	char* class_name;
	struct objc_method_list* instance_methods;
	struct objc_method_list* class_methods;
	struct objc_protocol_list* protocols; 
};

struct objc_ivar {
	char *ivar_name;
	char *ivar_type;
	int ivar_offset;
};

struct objc_ivar_list {
	int ivar_count;
	struct objc_ivar ivar_list[1];		
};

struct objc_method {
  SEL method_name;
  char * method_types;
  IMP method_imp;
};

struct objc_method_list {
	int method_count;
	struct objc_method method_list[1];	
};

struct objc_symtab {
	unsigned long sel_ref_cnt;
	SEL* refs;
	unsigned short cls_def_cnt;
	unsigned short cat_def_cnt;
	void* defs[1];
};

struct objc_cache {
	unsigned int mask;
	unsigned int occupied;
	Method buckets[1];
};

struct objc_module {
	unsigned long version;
	unsigned long size;
	const char* name;
	Symtab symtab;
};

extern struct hashmap* class_hash;
extern  struct objc_cache _objc_empty_cache;
void objc_init();

id object_copy(id obj, size_t size);
id object_dispose(id obj);

Class object_getClass(id obj);
Class object_setClass(id obj, Class cls);

const char *object_getClassName(id obj);
void *object_getIndexedIvars(id obj);

id object_getIvar(id obj, ivar ivar);
void object_setIvar(id obj, ivar ivar, id value);

ivar object_setInstanceVariable(id obj, const char *name, void *value);
ivar object_getInstanceVariable(id obj, const char *name, void **outValue);

Class objc_getClass(const char *name);
id objc_getMetaClass(const char *name);
id objc_lookUpClass(const char *name);
id objc_getRequiredClass(const char *name);
Class objc_getFutureClass(const char *name);
void objc_setFutureClass(Class cls, const char *name);
int objc_getClassList(Class *buffer, int bufferCount);

Protocol *objc_getProtocol(const char *name);
Protocol **objc_copyProtocolList(unsigned int *outCount);

const char *class_getName(Class cls);
bool class_isMetaClass(Class cls);
Class class_getSuperclass(Class cls);
Class class_setSuperclass(Class cls, Class newSuper);

int class_getVersion(Class cls);
void class_setVersion(Class cls, int version);

size_t class_getInstanceSize(Class cls);
size_t class_getAlignedInstanceSize(Class cls);
Class _calloc_class(size_t size);

ivar class_getInstanceVariable(Class cls, const char *name);
ivar class_getClassVariable(Class cls, const char *name);
ivar class_setClassVariable(Class cls, const char *name);
ivar *class_copyIvarList(Class cls, unsigned int *outCount);

Method class_getInstanceMethod(Class cls, SEL name);
Method class_getClassMethod(Class cls, SEL name);
IMP class_getMethodImplementation(Class cls, SEL name);
IMP class_getMethodImplementation_stret(Class cls, SEL name);
bool class_respondsToSelector(Class cls, SEL sel);
Method *class_copyMethodList(Class cls, unsigned int *outCount);

bool class_conformsToProtocol(Class cls, Protocol *protocol);
Protocol **class_copyProtocolList(Class cls, unsigned int *outCount);

objc_property_t class_getProperty(Class cls, const char *name);
objc_property_t *class_copyPropertyList(Class cls, unsigned int *outCount);

const char *class_getIvarLayout(Class cls);
const char *class_getWeakIvarLayout(Class cls);

id class_createInstance(Class cls, size_t extraBytes);

Class objc_allocateClassPair(Class superclass, const char *name, size_t extraBytes);
void objc_registerClassPair(Class cls);
Class objc_duplicateClass(Class original, const char *name, size_t extraBytes);
void objc_disposeClassPair(Class cls);

bool class_addMethod(Class cls, SEL name, IMP imp, const char *types);
IMP class_replaceMethod(Class cls, SEL name, IMP imp, const char *types);
bool class_addIvar(Class cls, const char *name, size_t size, uint8_t alignment, const char *types);
bool class_addProtocol(Class cls, Protocol *protocol);
void class_setIvarLayout(Class cls, const char *layout);
void class_setWeakIvarLayout(Class cls, const char *layout);
Class methodizeClass(Class cls);


SEL method_getName(Method m);
IMP method_getImplementation(Method m);
const char *method_getTypeEncoding(Method m);

unsigned int method_getNumberOfArguments(Method m);
char *method_copyReturnType(Method m);
char *method_copyArgumentType(Method m, unsigned int index);
void method_getReturnType(Method m, char *dst, size_t dst_len);
void method_getArgumentType(Method m, unsigned int index, 
										char *dst, size_t dst_len);
struct objc_method_description *method_getDescription(Method m);

IMP method_setImplementation(Method m, IMP imp);
void method_exchangeImplementations(Method m1, Method m2);

const char *ivar_getName(ivar v);
const char *ivar_getTypeEncoding(ivar v);
ptrdiff_t ivar_getOffset(ivar v);

const char *property_getName(objc_property_t property);
const char *property_getAttributes(objc_property_t property);

bool protocol_conformsToProtocol(Protocol *proto, Protocol *other);
bool protocol_isEqual(Protocol *proto, Protocol *other);
const char *protocol_getName(Protocol *p);
struct objc_method_description protocol_getMethodDescription(Protocol *p, SEL aSel, bool isRequiredMethod, bool isInstanceMethod);
struct objc_method_description *protocol_copyMethodDescriptionList(Protocol *p, bool isRequiredMethod, bool isInstanceMethod, unsigned int *outCount);
objc_property_t protocol_getProperty(Protocol *proto, const char *name, bool isRequiredProperty, bool isInstanceProperty);
objc_property_t *protocol_copyPropertyList(Protocol *proto, unsigned int *outCount);
Protocol **protocol_copyProtocolList(Protocol *proto, unsigned int *outCount);

const char **objc_copyImageNames(unsigned int *outCount);
const char *class_getImageName(Class cls);
const char **objc_copyClassNamesForImage(const char *image, 
													 unsigned int *outCount);

const char *sel_getName(SEL sel);
SEL sel_getUid(const char *str);
SEL sel_registerName(const char *str);
bool sel_isEqual(SEL lhs, SEL rhs);

void objc_enumerationMutation(id);
void objc_setEnumerationMutationHandler(void (*handler)(id));

void objc_setForwardHandler(void *fwd, void *fwd_stret);

extern void _objc_insertMethods(Class cls, struct objc_method_list *mlist, struct objc_category *cat);

#define _C_ELISIS   '.'
#define _C_STRING   '$'
#define _C_ID	   '@'
#define _C_CLASS	'#'
#define _C_SEL	  ':'
#define _C_CHR	  'c'
#define _C_UCHR	 'C'
#define _C_SHT	  's'
#define _C_USHT	 'S'
#define _C_INT	  'i'
#define _C_UINT	 'I'
#define _C_LNG	  'l'
#define _C_ULNG	 'L'
#define _C_LNG_LNG  'q'
#define _C_ULNG_LNG 'Q'
#define _C_FLT	  'f'
#define _C_DBL	  'd'
#define _C_BFLD	 'b'
#define _C_BOOL	 'B'
#define _C_VOID	 'v'
#define _C_UNDEF	'?'
#define _C_PTR	  '^'
#define _C_CHARPTR  '*'
#define _C_ATOM	 '%'
#define _C_ARY_B	'['
#define _C_ARY_E	']'
#define _C_UNION_B  '('
#define _C_UNION_E  ')'
#define _C_STRUCT_B '{'
#define _C_STRUCT_E '}'
#define _C_VECTOR   '!'
#define _C_CONST	'r'

#define CLS_CLASS		0x1
#define CLS_META		0x2
#define CLS_INITIALIZED		0x4
#define CLS_POSING		0x8
#define CLS_MAPPED		0x10
#define CLS_FLUSH_CACHE		0x20
#define CLS_GROW_CACHE		0x40
#define CLS_NEED_BIND		0x80
#define CLS_METHOD_ARRAY		0x100
// the JavaBridge constructs classes with these markers
#define CLS_JAVA_HYBRID		0x200
#define CLS_JAVA_CLASS		0x400
// thread-safe +initialize
#define CLS_INITIALIZING	0x800
// bundle unloading
#define CLS_FROM_BUNDLE		0x1000
// C++ ivar support
#define CLS_HAS_CXX_STRUCTORS	0x2000
// Lazy method list arrays
#define CLS_NO_METHOD_ARRAY	0x4000
// +load implementation
#define CLS_HAS_LOAD_METHOD	 0x8000
// objc_allocateClassPair API
#define CLS_CONSTRUCTING		0x10000
// visibility=hidden
#define CLS_HIDDEN			  0x20000
// class compiled with bigger class structure
#define CLS_EXT				 0x20000
// GC:  class has unsafe finalize method
#define CLS_FINALIZE_ON_MAIN_THREAD 0x40000
// Lazy property list arrays
#define CLS_NO_PROPERTY_ARRAY	0x80000
// +load implementation
#define CLS_CONNECTED		   0x100000
#define CLS_LOADED			  0x200000
// objc_allocateClassPair API
#define CLS_CONSTRUCTED		 0x400000
// class is leaf for cache flushing
#define CLS_LEAF				0x800000
// class instances may have associative references
#define CLS_INSTANCES_HAVE_ASSOCIATED_OBJECTS 0x1000000
// class has instance-specific GC layout
#define CLS_HAS_INSTANCE_SPECIFIC_LAYOUT 0x2000000

#define END_OF_METHODS_LIST ((struct objc_method_list*)-1)


#define CLS_GETINFO(cls,infomask)	   ((cls)->info & (infomask))
#define CLS_SETINFO(cls,infomask)	   ((cls)->info |= (infomask))
#define ISCLASS(cls)					(((cls)->info & CLS_CLASS) != 0)
#define ISMETA(cls)						(((cls)->info & CLS_META) != 0)
#define GETMETA(cls)					(ISMETA(cls) ? (cls) : (cls)->isa)


static inline char* typename(id obj) { return obj->isa->name; }
static inline UInt64 typeid(id obj) { return (UInt64)obj->isa; }

/** 
 * _();
 * 
 * 'Cartouche' Send Message Notation:
 * 
 *  instead of:
 *	  NSDictionary d* = [[NSDictionary alloc]init];
 *	  [d setObject:anObject forKey:@"foo"];
 * 
 *  use:
 *	  DSDictionary d* = _(_(DSDictionary, $alloc)$init); 
 *	  _(d, $setObject, anObject, $forKey, $("foo"));
 * 
 */
id _(id this, SEL _cmd, ...);

/** builtin selectors */
extern SEL $alloc;
extern SEL $init;
extern SEL $toString;
extern SEL $equals;
extern SEL $getHashCode;
extern SEL $dispose;
extern SEL $referenceEquals;
extern SEL $instanceEquals;
extern SEL $isEmpty;
extern SEL $length;
extern SEL $add;
extern SEL $contains;
extern SEL $remove;
extern SEL $resize;
extern SEL $set;
extern SEL $get;
extern SEL $clear;


#endif _OBJC_CORE_H_ 
