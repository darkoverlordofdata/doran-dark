/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
/**
 * lowest level internal core dependencies
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include <gc.h>
#include <math.h> 

/**
 *  MACRO Min
 *      cache results of calculation in pocket scope 
 */
#define Min(a, b)                                                       \
({                                                                      \
    auto _a = a;                                                        \
    auto _b = b;                                                        \
    (_a < _b) ? _a : _b;                                                \
})

/**
 *  MACRO Max
 *      cache results of calculation in pocket scope 
 */
#define Max(a, b)                                                       \
({                                                                      \
    auto _a = a;                                                        \
    auto _b = b;                                                        \
    (_a > _b) ? _a : _b;                                                \
})

/**
 *  MACRO overload
 *      method overload 
 */
#define overload __attribute__((overloadable))

#define DSfree(ptr) GC_FREE(ptr)
// #define DSfree(ptr) free(ptr)
#define DSmalloc(size) GC_MALLOC(size)
#define DSrealloc(old, new_size) GC_REALLOC(old, new_size)
// #define DSrealloc(old, new_size) realloc(old, new_size)
#define DScalloc(num, size) GC_MALLOC(num * size)
#define DScollect() GC_gcollect()


#ifndef nullptr
#define nullptr NULL
#endif

/** type inference */
#define var __auto_type
#define auto __auto_type

/**
 *  MACRO __FILENAME__
 *      extracts the filename from the path
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 *  MACRO NARG
 *      Count the number of arguments
 */
#define PP_NARG(...)                                                    \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                                                   \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                                                       \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,                       \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,                       \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,                       \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,                       \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,                       \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,                       \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N()                                                     \
         63,62,61,60,                                                   \
         59,58,57,56,55,54,53,52,51,50,                                 \
         49,48,47,46,45,44,43,42,41,40,                                 \
         39,38,37,36,35,34,33,32,31,30,                                 \
         29,28,27,26,25,24,23,22,21,20,                                 \
         19,18,17,16,15,14,13,12,11,10,                                 \
         9,8,7,6,5,4,3,2,1,0

/**
 *  MACRO join
 *      String.join(..)
 */
#define join(...) STR_JOIN(PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define $Join(...) $String.Join(PP_NARG(__VA_ARGS__), __VA_ARGS__)



//http://huoc.org/conditionals-constants-c11-generic.html
/**
 *  MACRO DEFAULT
 *      define default arguments
 */
struct _default_arg_;
#define __DEFAULT__ ((struct _default_arg_ *)NULL)
#define DEFAULT(arg, _default_val_)                                     \
        _Generic((arg),                                                 \
            struct _default_arg_ *: _default_val_,                      \
            default: (arg))


// int foobar(int, int, int);
// #define foobar(x, ...)                                                  \
//         foobar_((x), ##__VA_ARGS__, __DEFAULT__, __DEFAULT__)
// #define foobar_(x, z, t, ...)                                           \
//         (foobar)((x), DEFAULT((z), 42), DEFAULT((t), 36))
// int (foobar)(int x, int y, int z) {
//     Log("foobar x:%d", x);
//     Log("foobar y:%d", y);
//     Log("foobar z:%d", z);
//     // Log("foobar w:%d", w);
//     return 0;
// }

/**
 * Redefine true and false for use with _Generic,
 * such that true and false match bool, not int.
 */
#undef true
#undef false
#define true (_Bool)1
#define false (_Bool)0
#define YES true
#define NO false


typedef enum 
{
    TYPE_BOOLEAN,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_LONG,
    TYPE_SHORT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_ARRAY,
    TYPE_OBJECT

} TYPES;

/**
 * Friendlier type names
 */
typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int16_t Int16;
typedef uint16_t UInt16;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;
typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*IDispose)(void* const, void* const);

static inline char* STR_JOIN(int count, ...);
__attribute__((__format__ (__printf__, 1, 2)))
static inline void Log (char* format, ...);

static inline __attribute__((__format__ (__printf__, 1, 2))) char* DSsprintf(const char* format, ...);
static inline void DSvfprintf(FILE*, const char*, va_list);
static inline int DSvsnprintf(char*, size_t, const char*, va_list);


static inline char * strrstr(char *str1, char *str2);
static inline char * strndup (const char *str, size_t size);
#ifndef _WIN64
static inline int strcmpi (const char *s1, const char *s2);
static inline char* strlwr(char *str);
static inline char* strupr(char *str);
#endif
