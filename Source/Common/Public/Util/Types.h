//
// Created by ASUS on 29/12/2020.
//

#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <fstream>

#include "Util/ExcessiveAssert.h"

#define __STRINGIFY(x) #x
#define LITERAL_TO_STRING(x) __STRINGIFY(x)

#define ARRAY_COUNT(x) (sizeof(x) / sizeof(x[0]))

#if defined(_MSC_VER)
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline
#endif

#define LIKELY(...) __VA_ARGS__
#define UNLIKELY(...) __VA_ARGS__

#define UNLOCK_DEBUG_METHODS (1)

using u1 = uint8_t;
using s1 = int8_t;

using u2 = uint16_t;
using s2 = int16_t;

using u4 = uint32_t;
using s4 = int32_t;

using u8 = uint64_t;
using s8 = int64_t;

using f4 = float;
using f8 = double;

// Macro for checking bitness (safer macros borrowed from
// https://www.fluentcpp.com/2019/05/28/better-macros-better-flags/)
#define IS_BITNESS( X ) IS_BITNESS_PRIVATE_DEFINITION_##X()

// Bitness checks borrowed from https://stackoverflow.com/a/12338526/201787
#if _WIN64 || (__GNUC__ && __x86_64__) || (defined(__APPLE__) && defined(__MACH__))
    #define IS_BITNESS_PRIVATE_DEFINITION_64() 1
    #define IS_BITNESS_PRIVATE_DEFINITION_32() 0
    static_assert(sizeof(void*) == 8, "Pointer size is unexpected for this bitness");
#elif _WIN32 || __GNUC__
    #define IS_BITNESS_PRIVATE_DEFINITION_64() 0
    #define IS_BITNESS_PRIVATE_DEFINITION_32() 1
    static_assert(sizeof(void*) == 4, "Pointer size is unexpected for this bitness");
#else
    #error "Unknown bitness!"
#endif


#if IS_BITNESS(64)
    using usz = u8;
    using ssz = s8;
#else
    using usz = u4;
    using ssz = s4;
#endif

// Determine endian
#if defined(__BYTE_ORDER__)
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define EJ_LITTLE_ENDIAN (1)
        #define EJ_BIG_ENDIAN (0)
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define EJ_LITTLE_ENDIAN (0)
        #define EJ_BIG_ENDIAN (1)
    #else
        #error Unknown endian!
    #endif
#else
    #error Can not determine endian
#endif


constexpr bool IsNativeLittleEndian()
{
    return EJ_LITTLE_ENDIAN;
}

constexpr bool IsNativeBigEndian()
{
    return EJ_BIG_ENDIAN;
}


namespace Util
{
    using WideString = std::wstring;
}
