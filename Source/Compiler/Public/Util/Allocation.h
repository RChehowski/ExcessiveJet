//
// Created by ASUS on 28/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "Platform/Memory.h"

namespace Util
{
    class CAllocation
    {
    public:
        FORCEINLINE CAllocation()
            : Data(nullptr)
            , Size(0)
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

        template <typename T = void>
        FORCEINLINE const T* sGet() const
        {
            return reinterpret_cast<const T*>(Data);
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
        u1* Data;
        usz Size;
    };
}
