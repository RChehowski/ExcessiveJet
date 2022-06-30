//
// Created by ASUS on 30/12/2020.
//

#ifndef CPP20_CMEMORY_H
#define CPP20_CMEMORY_H

#include "Util/Platform/Misc.h"

namespace Util
{
    class CMemory
    {
        static void Memcpy(void* const Dst, const void* const Src, const usz NumBytes);

        static s4 Memcmp(const void* const A, const void* const B, const usz NumBytes);

        static void* MallocImpl(usz Size, usz Alignment = 1);

    public:
        static constexpr usz DefaultMallocAlignment = sizeof(void*);

        template<class T>
        FORCEINLINE static T* Malloc(usz Size, usz Alignment = CMemory::DefaultMallocAlignment)
        {
            return reinterpret_cast<T*>(MallocImpl(Size, Alignment));
        }

        static void Free(const void* Ptr);

        static void MemZero(void* Ptr, usz Size);

        template<class T>
        static void MemZero(T& Item)
        {
            MemZero((void*)&Item, sizeof(T));
        }


        template<typename TDst, typename TSrc>
        static void Memcpy(TDst* const Dst, const TSrc* const Src, const usz NumBytes)
        {
            Memcpy(
                reinterpret_cast<void*>(Dst),
                reinterpret_cast<const void*>(Src),
                NumBytes
            );
        }

        template<typename TA, typename TB>
        static s4 Memcmp(const TA* const A, const TB* const B, const usz NumBytes)
        {
            return Memcmp(
                reinterpret_cast<const void*>(A),
                reinterpret_cast<const void*>(B),
                NumBytes
            );
        }
    };
}


#endif //CPP20_CMEMORY_H
