//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_TYPES_H
#define CPP20_TYPES_H


#include <cstdint>
#include <string>

#define __STRINGIFY(x) #x
#define LITERAL_TO_STRING(x) __STRINGIFY(x)

#ifdef _MSC_VER
    #define FORCEINLINE __forceinline
#else
#endif

using u1 = uint8_t;
using s1 = int8_t;

using u2 = uint16_t;
using s2 = int16_t;

using u4 = uint32_t;
using s4 = int32_t;

using u8 = uint64_t;
using s8 = int64_t;

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
