//
// Created by ASUS on 30/12/2020.
//

#include "Platform/Memory.h"

#include <cstdlib>
#include <cstring>
#include <MathUtils.h>

namespace Util
{
    void CMemory::Memcpy(void* const Dst, const void* const Src, const usz NumBytes)
    {
        memcpy(Dst, Src, NumBytes);
    }

    s4 CMemory::Memcmp(const void* const A, const void* const B, const usz NumBytes)
    {
        return (s4)memcmp(A, B, NumBytes);
    }

    void* CMemory::MallocImpl(usz Size, usz Alignment)
    {
        // TODO: Write something more decent

        const usz SizeWithAlignment = Size + Alignment;

        void* const UnalignedMemory = malloc(SizeWithAlignment);
        void* const AlignedMemory = CMathUtils::Align(UnalignedMemory, Alignment);

        return AlignedMemory;
    }



    void CMemory::Free(const void *const Ptr)
    {
        free(const_cast<void*>(Ptr));
    }

    void CMemory::MemZero(void* Ptr, usz Size)
    {
        memset(Ptr, 0, Size);
    }
}