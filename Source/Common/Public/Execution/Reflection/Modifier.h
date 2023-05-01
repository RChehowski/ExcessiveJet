//
// Created by rcheh on 4/30/2023.
//

#pragma once

#include "Util/Types.h"

// Must be in consistence with java.lang.reflect.Modifier
// Currently u2 is enough to fit all flags
enum class Modifier : u2
{
    // public modifiers
    PUBLIC      = GetBit<u4>( 0), // 1
    PRIVATE     = GetBit<u4>( 1), // 2
    PROTECTED   = GetBit<u4>( 2), // 4
    STATIC      = GetBit<u4>( 3), // 8
    FINAL       = GetBit<u4>( 4), // 16
    SYNCHRONIZED= GetBit<u4>( 5), // 32
    VOLATILE    = GetBit<u4>( 6), // 64
    TRANSIENT   = GetBit<u4>( 7), // 128
    NATIVE      = GetBit<u4>( 8), // 256
    INTERFACE   = GetBit<u4>( 9), // 512
    ABSTRACT    = GetBit<u4>(10), // 1024
    STRICT      = GetBit<u4>(11), // 2048

    // non-public modifiers
    BRIDGE      = GetBit<u4>( 6), // 64
    VARARGS     = GetBit<u4>( 7), // 128
    SYNTHETIC   = GetBit<u4>(12), // 4096
    ANNOTATION  = GetBit<u4>(13), // 8192
    ENUM        = GetBit<u4>(14), // 16384
};


#endif //EXCESSIVE_MODIFIER_H
