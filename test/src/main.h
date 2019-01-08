
#define qvec_base       \
    struct {            \
        size_t cap, len;\
    }

#define qvec(T)         \
    struct qvec_##T {   \
        qvec_base;      \
        T data[];       \
    }

// struct qvec_base {
//     size_t cap, len;
// };

// #define qvec(T)             \
//     struct qvec_##T {       \
//         struct qvec_base;   \
//         T data[];           \
//     }    

#define qvec_new(T)                                                           \
({                                                                            \
    const size_t initial_size = 16;                                           \
    struct qvec_##T *v = malloc(sizeof(qvec(T)) + sizeof(T) * initial_size);  \
    v->cap = initial_size;                                                    \
    v->len = 0;                                                               \
    v;                                                                        \
})

#define qvec_pop(v) (v->data[--v->len])

#define qvec_ref(v, i) (&v->data[i])

#define qvec_at(v, i) (*(qvec_ref(v, i)))

#define qvec_push(v, i)                                 \
({                                                      \
    if (v->len >= v->cap) {                             \
        v->cap *= 2;                                    \
        v = realloc(v, sizeof(?) + v->cap * sizeof(?)); \
    }                                                   \
    v->data[v->len++] = (i);                            \
})

#define qvec_push(v, i)                                                 \
({                                                                      \
    if (v->len >= v->cap) {                                             \
        v->cap *= 2;                                                    \
        v = realloc(v, sizeof(qvec_base) + v->cap * sizeof(*v->data));  \
    }                                                                   \
    v->data[v->len++] = (i);                                            \
})

#define qvec_free(v) free(v)

#define GET_FMT_SPEC(x) _Generic((x), int: "%d", float: "%f", char*: "%s")

#define qvec_print(v)                   \
({                                      \
    printf("[");                        \
    for (int i = 0; i < v->len; ++i) {  \
        printf(GET_FMT_SPEC(v->data[i]), v->data[i]);\
        if (i + 1 < v->len)             \
            printf(", ");               \
    }                                   \
    printf("]\n");                      \
 })

#define getType(T) _Generic((T),        /* Get the name of a type */             \
                                                                                  \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
       DSLong *: "DSLong",  \
       const char *: "const pointer to char", \
      default: "other")


 void bye(DSLong** x) {
    DSLog("Bye!");
}

#define myNew(T, xs...) ({ \
    const T _xs[] = {xs}; \
    _xs; \
})

typedef struct {
    int x, y;
} Tuple;



     qvec(int) *iv = qvec_new(int);
    qvec_push(iv, 5);
    qvec_push(iv, 8);
    printf("%d\n", qvec_at(iv, 0));
    // qvec_at(iv, 1) = 5;
    qvec_print(iv);
    qvec_free(iv);

    auto r = myNew(char, 'a','b', 'c');
    DSLog("%d %d %d", r[0], r[1], r[2]);

    size_t qq;
    DSLong* __attribute__((cleanup(bye))) qqq;

    auto x = new(DSBoolean, true);

    DSLog("Hello World");
    DSLog("x = %s", ToString(x));
    DSLog("size_t is a %s", getType(qq));
    DSLog("DSLong* is a %s", getType(qqq));

    DSLog("r is a %s", getType(r));

    return 0;
