//
// Created by ASUS on 30/12/2020.
//

#ifndef CPP20_MISC_H
#define CPP20_MISC_H

#include "Types.h"

namespace Util
{
    u1 BigEndianToNative(u1 Value);
    u2 BigEndianToNative(u2 Value);
    u4 BigEndianToNative(u4 Value);
    u8 BigEndianToNative(u8 Value);

    constexpr bool IsLittleEndian()
    {
        return true;
    }
}


#endif //CPP20_MISC_H
