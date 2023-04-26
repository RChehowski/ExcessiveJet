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

    static constexpr usz Size = CompressedBitMask + static_cast<usz>(1);

    static constexpr uintptr_t Start  = static_cast<uintptr_t>(0x400000000);
    static constexpr uintptr_t End    = Start + Size;
};

constexpr usz oopSize = 4;

/**
 * Non-typed compressed object pointer that can be converted to any object type.
 * Does not do any type checks, acts similar to a "void*" pointer in C/C++.
 *
 * Stored in memory as a 4 byte value, can be uncompressed to a normal object on demand.
 */
class alignas(oopSize) oop
{
    FORCEINLINE static u4 MemoryAddressToOop(const void* const MemoryAddress)
    {
        ASSERT_MSG
        (
            (reinterpret_cast<uintptr_t>(MemoryAddress) >= CObjectHeapDimension::Start) &&
            (reinterpret_cast<uintptr_t>(MemoryAddress) >= CObjectHeapDimension::End),
            "Memory address must be located within the object heap dimension: [%llu, %llu). Got: %llu",
            static_cast<unsigned long long>(CObjectHeapDimension::Start),
            static_cast<unsigned long long>(CObjectHeapDimension::End),
            reinterpret_cast<unsigned long long>(MemoryAddress)
        );
        ASSERT_MSG
        (
            CMathUtils::IsAligned(MemoryAddress, oopAlignment),
            "Memory address %llu must be aligned by %llu",
            reinterpret_cast<unsigned long long>(MemoryAddress),
            static_cast<unsigned long long>(oopAlignment)
        );

        const uintptr_t ShiftedMemoryAddress = reinterpret_cast<uintptr_t>(MemoryAddress) >> oopAlignmentShift;

        return static_cast<u4>(ShiftedMemoryAddress & CObjectHeapDimension::CompressedBitMask);
    }

    FORCEINLINE static void* OopToMemoryAddress(const u4 InOopValue)
    {
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
static_assert(sizeof(oop) == oopSize, "Unexpected oop size");


static constexpr const oop Null{ nullptr };

template<typename T> constexpr bool TIsOop = std::is_same_v<T, oop>;
