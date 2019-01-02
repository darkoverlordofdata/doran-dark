#include <dark/DSClass.h>
#include <dark/DSLog.h>
#include <dark/runtime.h>

/***********************************************************************
* A static empty cache.  All classes initially point at this cache.
* When the first message is sent it misses in the cache, and when
* the cache is grown it checks for this case and uses malloc rather
* than realloc.  This avoids the need to check for NULL caches in the
* messenger.
***********************************************************************/

struct objc_cache _objc_empty_cache =
{
    0,        // mask
    0,        // occupied
    { NULL }  // buckets
};
