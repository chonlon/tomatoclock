#ifndef LON_TYPE_DEFINES_H
#define LON_TYPE_DEFINES_H

#ifdef _MSC_VER
#define LON_MSVC
#elif
#define LON_GCC
#endif

#ifdef LON_MSVC
#include <intrin.h>
#elif defined LON_GCC
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef LON_MSVC
typedef signed __int8    int8_t;
typedef unsigned __int8  uint8_t;
typedef signed __int16   int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32   int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64   int64_t;
typedef unsigned __int64 uint64_t;
#endif

#endif // LON_TYPE_DEFINES_H
