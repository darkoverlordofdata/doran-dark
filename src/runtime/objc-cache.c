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
// struct objc_cache _objc_empty_cache =
// {
//     0,        // mask
//     0,        // occupied
//     { NULL }  // buckets
// };

/**
 * No cache. I'm storing a vtable in each Class object in it's place.
 * When calling a method via the generic selector, we bypass sendMsg.
 */
