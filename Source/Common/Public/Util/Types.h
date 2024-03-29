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

#if EXJ_64
    using usz = u8;
    using ssz = s8;
#elif EXJ_32
    using usz = u4;
    using ssz = s4;
#else
    #error Unexpected bitness
#endif

FORCEINLINE bool IsNativeLittleEndian()
{
    constexpr u4 _u4 = 0x01000002UL;
    const u1 _u1 = (const u1&)_u4;

    return _u1 == (u1)2;
}


namespace Util
{
    using WideString = std::wstring;
}

template<bool bFlag = false> void ConditionalStaticAssert() { static_assert(bFlag, "Conditional static_assert"); }

#define EXJ_STATIC_ASSERT_CONDITIONAL() ConditionalStaticAssert<true>()

template <typename T>
constexpr T GetBit(const s4 Bit)
{
    return static_cast<T>(1) << static_cast<T>(Bit);
}
