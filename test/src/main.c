#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/darkfx.h>
#include <Block.h>
#include "darkunit.h"


void TestHashMap();
char keys[12][7] = {
    "key1", "key2", "AbCdEf",
    "key4", "key5", "key6",
    "key7", "key8", "key9",
    "keyA", "keyB", "keyC",
};
struct hashmap* class_hash;

int main(int argc, char **argv) {

    __block struct DSLong* l = $DSLong(420);
    __block DSLong* m = $DSLong(420);
    __block DSBoolean* b = $DSBoolean(true);
    DSLog("should be DSBoolean: %s", GetClassName(b));

    // Class klass =  NX_hashmap_get(class_hash, "DSArray");
    // DSLog("%s length = %d", klass->name, klass->instance_size);
    return 0;
    __block DSString* s = $("Frodo");
    __block DSArray* a = $DSArray(0);
    __block DSList* q = $DSList();
    __block DSHashmap* h = $DSHashmap();

    for (int i=0; i<12; i++)
    {
        DSLog("%s", keys[i]);
        Put(h, keys[i], $DSLong(i+420));
    }

    for (int i=0; i<12; i++)
    {
        DSLog("%d", LongValue(Get(h, keys[i])));
    }

    __block DSLong* l0 = $DSLong(0);
    __block DSLong* l1 = $DSLong(1);
    __block DSLong* l2 = $DSLong(2);
    __block DSLong* l3 = $DSLong(3);
    __block DSLong* l4 = $DSLong(4);
    __block DSLong* l5 = $DSLong(5);

    Add(a, l0);
    Add(a, l1);
    Add(a, l2);
    Add(a, l3);
    Add(a, l4);
    Add(a, l5);

    Add(q, l);    
    Add(q, m);

    // Long ll = Get(a, 0);    
    
    DSLog("=============");
    DSLog("%d", Length(a));
    for (int i=0; i<Length(a); i++) {
        DSLog("%d)", i);
        DSLog("%d) %d", i, LongValue(Get(a, i)));
    }
    DSLog("%s", ToString(q));
    DSLog("Bytes = %d", DSBooleanClass.Bytes);
    DSLog("Size = %d", DSBooleanClass.Size);
    DSLog("Type = %d", DSBooleanClass.Type);
    DSLog("TRUE = %s", ToString(DSBooleanClass.True));
    DSLog("FALSE = %s", ToString(DSBooleanClass.False));
    DSLog("=============");
    __block DSCollection* c = q;

    __block DSChar* zz = $DSChar('c');

    Describe("Run Tests", ^{

        It("True and True are the same", ^{
            Expect(CompareTo(DSBooleanClass.True, DSBooleanClass.True) == 0);
        });
        
        It("Should be 5", ^{
            Expect(Length(s) == 5);
        });

        It("Should be 6", ^{
            Expect(Length(a) == 6);
        });

        It("Should be 2", ^{
            Expect(Length(q) == 2);
        });

        It("Should be 2", ^{
            Expect(Length(c) == 2);
        });

        It("Should equal 420", ^{
            Expect(LongValue(l) == 420);
        });

        It("Should equal another instance", ^{
            Expect(Equals(l, m));
        });

        It("Should be a Long", ^{
            Expect(!strcmp("DSLong", GetClassName(l)));
            Expect(!strcmp("DSLong", GetClass(l)->name));
        });

        It("Should be a Boolean", ^{
            Expect(!strcmp("DSBoolean", GetClassName(b)));
            Expect(!strcmp("DSBoolean", GetClass(b)->name));
        });

        It("Should be true", ^{
            Expect(BoolValue(b) == true);
        });

        It("keyB is 430", ^{
            Expect(LongValue(Get(h,"keyB")) == 430);
        });

        It("should be a c", ^{
            Expect(LongValue(zz) == 99);
        });

    });
    DSLog("");
    DSLog("Tests run: %d", tests.total);
    DSLog("Tests passed: %d", tests.passed);
    DSLog("Tests failed: %d", tests.failed);

    SEL _Add = "Add";
    DSLog("SEL = %s", _Add);

    TestHashMap();
    DSLog("sizeof(DSObject) = %d", sizeof(DSObject));
    DSLog("sizeof(id) = %d", sizeof(id));
    return tests.failed;
}
/* Some sample data structure with a string key */
struct blob {
  char key[32];
  size_t data_len;
  unsigned char data[1024];
};

HASHMAP_FUNCS_CREATE(DX, const char, struct blob)

struct blob *blob_load(void)
{ 
    static k = 0;
    struct blob *b;

    if (k < 12) {
        b = DSMalloc(sizeof(struct blob));
        b->data_len = strlen(keys[k]);
        memcpy(&b->key, &keys[k], b->data_len);
        memcpy(&b->data, &keys[k], b->data_len);
        k++;
    }

    /*
    * Hypothetical function that allocates and loads blob structures
    * from somewhere.  Returns NULL when there are no more blobs to load.
    */
    return b;
}

/* Hashmap structure */
struct hashmap map;

void TestHashMap() {
    struct blob *b;
    struct hashmap_iter *iter;

    /* Initialize with default string key functions and init size */
    hashmap_init(&map, hashmap_hash_string, hashmap_compare_string, 0);

    /* Load some sample data into the map and discard duplicates */
    while ((b = blob_load()) != NULL) {
        if (DX_hashmap_put(&map, b->key, b) != b) {
            DSLog("discarding blob with duplicate key: %s", b->key);
            free(b);
        }
    }

    /* Lookup a blob with key "AbCdEf" */
    b = DX_hashmap_get(&map, "AbCdEf");
    if (b) {
        DSLog("Found blob[%s]", b->key);
    }

    /* Iterate through all blobs and print each one */
    for (iter = hashmap_iter(&map); iter; iter = hashmap_iter_next(&map, iter)) {
        DSLog("blob[%s]: data_len %u bytes", DX_hashmap_iter_get_key(iter),
        DX_hashmap_iter_get_data(iter)->data_len);
    }

    /* Remove all blobs with no data */
    iter = hashmap_iter(&map);
    while (iter) {
        b = DX_hashmap_iter_get_data(iter);
        if (b->data_len == 0) {
            iter = hashmap_iter_remove(&map, iter);
            free(b);
        } else {
            iter = hashmap_iter_next(&map, iter);
        }
    }

    /* Free all allocated resources associated with map and reset its state */
    hashmap_destroy(&map);


}

typedef struct Person {
    Class isa;
    DSString* firstName;
    DSString* lastName;
    DSInteger* age;
} Person;

//https://www.cocoawithlove.com/2010/01/what-is-meta-class-in-objective-c.html

void makeClass() {
    // Class c = objc_allocateClassPair(&DSObjectClass, "Person", 0);
    // class_addIvar(c, "firstName", sizeof(id), log2(sizeof(id)), '@');
    // class_addIvar(c, "lastName", sizeof(id), log2(sizeof(id)), '@');
    // class_addIvar(c, "age", sizeof(DSInteger), log2(sizeof(DSInteger)), 'i');

    // Ivar firstNameIvar = class_getInstanceVariable(c, "firstName");
    // Ivar lastNameIvar = class_getInstanceVariable(c, "lastName");
    // int ageOffset = ivar_getOffset(class_getInstanceVariable(c, "age"));

    // objc_registerClassPair(c);

    // Class PersonClass = DSClassFromString("Person");
    // Person* alex = _(_(PersonClass, $alloc),$init);
}