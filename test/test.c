#include <dark/darkfx.h>

void VectorTest();
void ListTest();
void HashmapTest();

void HashmapTest()
{
    printf("** Map Test\n");
    char* names[] = {
        "Frodo",
        "Bilbo",
        "background",
        "block",
        "block_solid",
        "face",
        "paddle",
        "sprite"
    };

    Hashmap h = new (Hashmap);

    for (int i=0; i<6; i++)
    {
        h->Put(h, names[i], i);
        int x = (int)h->Get(h, names[i]);
        printf("%s = %d\n", names[i], x);
    }

    h->Dispose(h);

}

void Iter(void* data)
{
    printf("%s\n", (char*)data);
}

void ListTest()
{
    printf("** List Test\n");
    List l = new (List);
    l->Push(l, "Barney");
    l->Push(l, "wilma");
    l->Iterate(l, Iter);
    l->Dispose(l);
}

void VectorTest()
{
    printf("** Vector Test\n");



    Vector v = new (Vector);
    v->Add(v, strdup("Bonjour"));
    v->Add(v, strdup("tout"));
    v->Add(v, strdup("le"));
    v->Add(v, strdup("monde"));
    for (int i = 0; i < v->Count(v); i++)
        printf("%s ", (char *) v->data[i]);
        // printf("%s ", (char *) v->Get(v, i));
    printf("\n");
    v->Dispose(v);

    Vector v1 = new (Vector);
    Vector v2 = new (Vector);
    v2->Add(v2, "Frodo");
    v1->Add(v1, v2);
    
    Vector vv = v1->data[0];
    char* s = vv->data[0];
    char* ss = ((Vector)(v1->data[0]))->data[0];
    printf("s = %s\n", s);

}
