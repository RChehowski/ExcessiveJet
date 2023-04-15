//
// Created by rcheh on 6/24/2022.
//

#pragma once

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"
#include "Util/MathUtils.h"


using Util::CMathUtils;


constexpr usz oopAlignmentShift = 3;
constexpr usz oopAlignment = static_cast<usz>(1) << oopAlignmentShift;


struct CObjectHeapDimension
{
    static constexpr usz CompressedBitMask = 0xFFFFFFFFULL;
    static constexpr usz UncompressedBitMask = CompressedBitMask << oopAlignmentShift;

    static constexpr usz Size = UncompressedBitMask + static_cast<usz>(1);

    static constexpr usz Start  = static_cast<usz>(0x4000000000);
    static constexpr usz End    = Start + Size;
};


class alignas(4) oop
{
    FORCEINLINE static u4 MemoryAddressToOop(const void* const MemoryAddress)
    {
        // TODO: Subtract CObjectHeapDimension::Start
        ASSERT(CMathUtils::IsAligned(MemoryAddress, oopAlignment));

        const uintptr_t ShiftedMemoryAddress = reinterpret_cast<uintptr_t>(MemoryAddress) >> oopAlignmentShift;

        return static_cast<u4>(ShiftedMemoryAddress & CObjectHeapDimension::CompressedBitMask);
    }

    FORCEINLINE static void* OopToMemoryAddress(const u4 InOopValue)
    {
        // TODO: Add CObjectHeapDimension::Start
        const uintptr_t ShiftedMemoryAddress = static_cast<uintptr_t>(InOopValue) << oopAlignmentShift;

        return reinterpret_cast<void*>(ShiftedMemoryAddress + CObjectHeapDimension::Start);
    }

public:
    FORCEINLINE constexpr explicit oop(nullptr_t) : Value(static_cast<u4>(0))
    {
    }

    FORCEINLINE explicit oop(void* const MemoryAddress) : Value(MemoryAddressToOop(MemoryAddress))
    {
    }

    FORCEINLINE explicit oop(const u4 InOopValue) : Value(InOopValue)
    {
    }

    FORCEINLINE oop(const oop& Other) = default;
    FORCEINLINE oop(oop&& Other) = default;

    FORCEINLINE oop& operator=(const oop& Other) = default;
    FORCEINLINE oop& operator=(oop&& Other) = default;

    FORCEINLINE bool operator==(const oop& Other) const
    {
        return Value == Other.Value;
    }

    FORCEINLINE bool operator!=(const oop& Other) const
    {
        return Value != Other.Value;
    }

    FORCEINLINE void SetAddress(const void* const MemoryAddress)
    {
        Value = MemoryAddressToOop(MemoryAddress);
    }

    [[nodiscard]] FORCEINLINE void* GetAddress() const
    {
        return OopToMemoryAddress(Value);
    }

private:
    u4 Value;
};

static_assert(sizeof(oop) == 4);

static constexpr const oop Null{ nullptr };

template<typename T> constexpr bool TIsOop = std::is_same_v<T, oop>;
