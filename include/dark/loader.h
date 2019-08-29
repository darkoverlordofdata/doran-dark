
#include <stdio.h>
#include <assert.h>
#include <dark/core/class.h>
#include <dark/core/object.h>
#include <dark/core/comparable.h>

#include <dark/types/boolean.h>
#include <dark/types/char.h>
#include <dark/types/double.h>
#include <dark/types/float.h>
#include <dark/types/integer.h>
#include <dark/types/long.h>
#include <dark/types/number.h>
#include <dark/types/short.h>
#include <dark/types/string.h>
#include <dark/types/stringbuilder.h>
#include <dark/io/file.h>
#include <dark/io/filesystem.h>
#include <dark/collections/array.h>
#include <dark/collections/map.h>
#include <dark/collections/list.h>
#include <dark/runtime.h>


/** 
 * load framework builtin classes 
 */
static void LoadDarkFX() 
{
    /** register Object */
    Class obj;
    RegisterClass(obj = ClassLoadObject(Nil));

    /** register Comparable */
    Class cmp;
    RegisterClass(cmp = ClassLoadComparable(obj));

    /** register DSNumber */
    Class num;
    RegisterClass(num = ClassLoadNumber(cmp));

    RegisterClass(ClassLoadException(obj));
    RegisterClass(ClassLoadArray(obj));
    RegisterClass(ClassLoadList(obj));
    RegisterClass(ClassLoadMap(obj));
    RegisterClass(ClassLoadBoolean(cmp));
    RegisterClass(ClassLoadChar(num));
    RegisterClass(ClassLoadDouble(num));
    RegisterClass(ClassLoadFloat(num));
    RegisterClass(ClassLoadInteger(num));
    RegisterClass(ClassLoadLong(num));
    RegisterClass(ClassLoadShort(num));
    RegisterClass(ClassLoadString(obj));
    RegisterClass(ClassLoadStringBuilder(obj));
    FileSystemInit();
    // RegisterClass(ClassLoadDSFileSystem(obj));
    RegisterClass(ClassLoadFile(cmp));
}



static inline void __attribute__((constructor(101))) darkfx_load()
{
    #ifdef USE_GC
    Log("Using boeme garbage collection");
    GC_INIT();
    GC_enable_incremental();
    #endif
    LoadDarkFX();
}

/**
 *  stop the garbage collector
 */
static inline void __attribute__((destructor)) darkfx_unload()
{
}

