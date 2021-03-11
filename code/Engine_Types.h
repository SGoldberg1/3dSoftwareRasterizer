#ifndef _ENGINE__TYPES_H
#define _ENGINE__TYPES_H

#include <stdint.h>

#define KILOBYTE(value) ((value) * 1024LL)
#define MEGABYTE(value) (KILOBYTE(value) * 1024LL)
#define GIGABYTE(value) (MEGABYTE(value) * 1024LL)
#define TERRABYTE(value) (GIGABYTE(value) * 1024LL)

#define Array_Length(array) ((sizeof(array)) / (sizeof(array[0])))
#define DefaultEmptyCase default:{}break

#if ENGINE_DEBUG
#define ASSERT(expression) if(!(expression)) { int* x = 0; *x = 0; }
#else
#define ASSERT(expression)
#endif


#define internal_function static
#define local_persist static
#define global_variable static

#define TRUE 1
#define FALSE 0

//////////////////////////////// ENGINE TYPES ////////////////////////////////

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef u64 memory_size;

typedef float r32;
typedef double r64;

typedef int32_t b32;


#endif //_ENGINE__TYPES_H
