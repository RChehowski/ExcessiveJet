//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_TYPES_H
#define CPP20_TYPES_H


#include <cstdint>
#include <cstdio>
#include <string>

#define __STRINGIFY(x) #x
#define LITERAL_TO_STRING(x) __STRINGIFY(x)

#if defined(_MSC_VER)
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline
#endif

using u1 = uint8_t;
using s1 = int8_t;

using u2 = uint16_t;
using s2 = int16_t;

using u4 = uint32_t;
using s4 = int32_t;

using u8 = uint64_t;
using s8 = int64_t;

// Macro for checking bitness (safer macros borrowed from
// https://www.fluentcpp.com/2019/05/28/better-macros-better-flags/)
#define IS_BITNESS( X ) IS_BITNESS_PRIVATE_DEFINITION_##X()

// Bitness checks borrowed from https://stackoverflow.com/a/12338526/201787
#if _WIN64 || (__GNUC__ && __x86_64__)
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


namespace Util
{
    using WideString = std::wstring;
}

enum class ClassAccessFlags : uint16_t
{
    // Declared public; may be accessed from outside its package.
    ACC_PUBLIC      = 0x0001,

    // Declared final; no subclasses allowed.
    ACC_FINAL       = 0x0010,

    // Treat superclass methods specially when invoked by the invokespecial instruction.
    ACC_SUPER       = 0x0020,

    // Is an interface, not a class.
    ACC_INTERFACE   = 0x0200,

    // Declared abstract; must not be instantiated.
    ACC_ABSTRACT 	= 0x0400,

    // Declared synthetic; not present in the source code.
    ACC_SYNTHETIC 	= 0x1000,

    // Declared as an annotation type.
    ACC_ANNOTATION 	= 0x2000,

    // Declared as an enum type.
    ACC_ENUM        = 0x4000
};

#define STRIP_DEBUG_INFO 0

#endif //CPP20_TYPES_H
