#include <dark/core.h>
#include <stdlib.h>
tgc_t dark_gc;

/**
 *  start the garbage collector
 */
void __attribute__((constructor)) dark_gc_ctor()
{
    int local;
	tgc_start (&dark_gc, &local);
}

/**
 *  stop the garbage collector
 */
void __attribute__((destructor)) dark_gc_dtor()
{
    tgc_stop (&dark_gc);
}

