//
// Created by ASUS on 30/12/2020.
//

#include "Platform/Memory.h"

#include <cstdlib>
#include <cstring>
#include <MathUtils.h>

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

    void* Memory::MallocImpl(usz Size, usz Alignment)
    {
        // TODO: Write something more decent

        const usz SizeWithAlignment = Size + Alignment;

        void* const UnalignedMemory = malloc(SizeWithAlignment);
        void* const AlignedMemory = CMathUtils::Align(UnalignedMemory, Alignment);

        return AlignedMemory;
    }



    void Memory::Free(const void *const Ptr)
    {
        free(const_cast<void*>(Ptr));
    }

    void Memory::MemZero(void* Ptr, usz Size)
    {
        memset(Ptr, 0, Size);
    }
}