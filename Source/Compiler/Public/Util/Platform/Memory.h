//
// Created by ASUS on 30/12/2020.
//

#pragma once

#include <optional>

#include "Util/Platform/Misc.h"

namespace Util
{
    struct CMemoryStatistics
    {
        //! Current amount of virtual memory mapped, all of which might not have been committed
        usz Mapped;
        //! Peak amount of virtual memory mapped, all of which might not have been committed
        usz MappedPeak;

        //! Current amount of memory in global caches for small and medium sizes (<32KiB)
        usz Cached;

        //! Current amount of memory allocated in huge allocations, i.e larger than LARGE_SIZE_LIMIT which is 2MiB by default
        usz HugeAlloc;
        //! Peak amount of memory allocated in huge allocations, i.e larger than LARGE_SIZE_LIMIT which is 2MiB by default
        usz HugeAllocPeak;

        //! Total amount of memory mapped since initialization
        usz MappedTotal;
        //! Total amount of memory unmapped since initialization
        usz UnmappedTotal;
    };

    class CMemory
    {
        static void Memcpy(void* const Dst, const void* const Src, const usz NumBytes);

        static s4 Memcmp(const void* const A, const void* const B, const usz NumBytes);

        static void* MallocImpl(usz Size, usz Alignment = 1);

    public:
        static constexpr usz DefaultMallocAlignment = sizeof(void*);

        static bool bInitialized;

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

        static std::optional<CMemoryStatistics> GetStatistics();
    };
}
