//
// Created by ASUS on 30/12/2020.
//

#include "Platform/Memory.h"

#include <cstdlib>
#include <cstring>

namespace Util
{
    void Memory::Memcpy(void* const Dst, const void* const Src, const size_t NumBytes)
    {
        memcpy(Dst, Src, NumBytes);
    }

    s4 Memory::Memcmp(const void* const A, const void* const B, const size_t NumBytes)
    {
        return (s4)memcmp(A, B, NumBytes);
    }

    void* Memory::Malloc(size_t Size, size_t Alignment)
    {
        void* const Ptr = malloc(Size);
        return Ptr;
    }

    void Memory::Free(void *const Ptr)
    {
        free(Ptr);
    }
}