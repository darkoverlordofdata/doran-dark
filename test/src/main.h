

int foobar(int, int, int);
#define foobar(x, ...) foobar_((x), ##__VA_ARGS__, __DEFAULT__, __DEFAULT__)
#define foobar_(x, z, t, ...) (foobar)((x), DEFAULT((z), 42), DEFAULT((t), 36))
