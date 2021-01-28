//
// Created by ASUS on 10/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CByteBuffer
    {
    public:
        CByteBuffer(const usz InSize) : Size(InSize)
        {
        }

    private:
        usz Size;
        u1* Bytes;
    };
}
