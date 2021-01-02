//
// Created by ASUS on 30/12/2020.
//

#include "Platform/Memory.h"

#include <cstdlib>
#include <cstring>

namespace Util
{
    void Memory::Memcpy(void* const Dst, const void* const Src, const usz NumBytes)
    {
        memcpy(Dst, Src, NumBytes);
    }

    s4 Memory::Memcmp(const void* const A, const void* const B, const usz NumBytes)
    {
        return (s4)memcmp(A, B, NumBytes);
    }

    void* Memory::Malloc(usz Size, usz Alignment)
    {
        void* const Ptr = malloc(Size);
        return Ptr;
    }

    void Memory::Free(const void *const Ptr)
    {
        free(const_cast<void*>(Ptr));
    }
}