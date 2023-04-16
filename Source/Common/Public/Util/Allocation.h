//
// Created by ASUS on 28/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "Util/DisposableMemoryReader.h"
#include "Compiler/Public/Util/Platform/Memory.h"

#define EXJ_ALLOCATION_REF_SIZE_CHECK (1)

namespace Util
{
    template <typename T>
    using TRefOrValueBySize = typename std::conditional<std::is_trivially_copyable_v<T> && (sizeof(T) <= sizeof(void*)), T, const T&>::type;

    class CAllocation
    {
    public:
        FORCEINLINE CAllocation() : Data(nullptr), Size(0)
        {
        }

        FORCEINLINE CAllocation(const usz InSize, const usz InAlignment = CMemory::DefaultMallocAlignment)
        {
            Allocate(InSize, InAlignment);
        }

        CAllocation(const CAllocation&) = delete;
        FORCEINLINE CAllocation(CAllocation&& InOther) noexcept
            : Data(InOther.Data)
            , Size(InOther.Size)
        {
            InOther.Data = nullptr;
            InOther.Size = (usz)0;
        }

        FORCEINLINE ~CAllocation()
        {
            Deallocate();
        }

        CAllocation& operator= (const CAllocation&) = delete;
        FORCEINLINE CAllocation& operator= (CAllocation&& InOther) noexcept
        {
            Data = InOther.Data;
            InOther.Data = nullptr;

            Size = InOther.Size;
            InOther.Size = (usz)0;

            return *this;
        }

        FORCEINLINE void Allocate(const usz InSize, const usz InAlignment = CMemory::DefaultMallocAlignment)
        {
            Data = CMemory::Malloc<u1>(InSize, InAlignment);
            Size = InSize;
        }

        FORCEINLINE void Deallocate()
        {
            if (IsPresent())
            {
                CMemory::Free(Data);
                Data = nullptr;

                Size = 0;
            }
        }

        [[nodiscard]]
        FORCEINLINE usz GetSize() const
        {
            return Size;
        }

        [[nodiscard]]
        FORCEINLINE usz IsPresent() const
        {
            return GetSize() > 0;
        }

        template <class T>
        FORCEINLINE T* Get()
        {
            return reinterpret_cast<T*>(Data);
        }

        template <typename T>
        FORCEINLINE const T* Get() const
        {
            return reinterpret_cast<const T *>(Data);
        }


        FORCEINLINE explicit operator void *()
        {
            return reinterpret_cast<void*>(Data);
        }

        static CAllocation EmptyAllocation()
        {
            return CAllocation();
        }

    private:
        u1* Data = nullptr;
        usz Size = static_cast<usz>(0);
    };

    /** The allocation that does not own its memory */
    class CAllocationRef
    {
    public:
        template<typename T>
        FORCEINLINE CAllocationRef(const T* const InData, const usz InSize)
            : Data(reinterpret_cast<const void*>(InData))
#if EXJ_ALLOCATION_REF_SIZE_CHECK
            , Size(InSize)
#endif
        {
        }

        template <typename T>
        FORCEINLINE auto GetAsWhole() const -> TRefOrValueBySize<T>
        {
#if EXJ_ALLOCATION_REF_SIZE_CHECK
            ASSERT_MSG(sizeof(T) == Size, "Allocation size is %llu, but sizeof(T) is %llu. Size mismatch.",
               (unsigned long long)Size,
               (unsigned long long)sizeof(T)
            );
#endif

            return *reinterpret_cast<const T*>(Data);
        }

        [[nodiscard]] FORCEINLINE CDisposableMemoryReader CreateMemoryReader() const
        {
            return CDisposableMemoryReader{ Data };
        }

    private:
        const void* Data;

#if EXJ_ALLOCATION_REF_SIZE_CHECK
        usz Size;
#endif
    };
}
