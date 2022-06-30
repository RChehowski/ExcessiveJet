//
// Created by rcheh on 6/24/2022.
//

#pragma once

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"
#include "Util/MathUtils.h"

#include <numeric>

#define USE_COMPRESSED_OOPS ((1) && IS_BITNESS(64))

#if IS_BITNESS(64)
    #define USE_64_OOPS (!USE_COMPRESSED_OOPS)
#else
    #define USE_64_OOPS (0)
#endif

#if USE_64_OOPS
    /** Ordinary Object Pointer. 64 bit in this configuration */
    using oopValue = u8;
#else
    /** Ordinary Object Pointer. 32 bit in this configuration */
    using oopValue = u4;
#endif // IS_BITNESS


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


class oop
{
    static_assert(sizeof(uintptr_t) == 8);

#if USE_COMPRESSED_OOPS
    template<typename T>
    FORCEINLINE static oopValue MemoryAddressToOop(T* const MemoryAddress)
    {
        ASSERT(CMathUtils::IsAligned(MemoryAddress, oopAlignment));

        const uintptr_t ShiftedMemoryAddress
            = reinterpret_cast<uintptr_t>(MemoryAddress) >> oopAlignmentShift;

        ASSERT((ShiftedMemoryAddress & CObjectHeapDimension::CompressedBitMask) == static_cast<uintptr_t>(0));

        return static_cast<oopValue>(ShiftedMemoryAddress & CObjectHeapDimension::CompressedBitMask);
    }
#else
    template<typename T>
    FORCEINLINE static oopValue MemoryAddressToOOP(T* const MemoryAddress)
    {
        return reinterpret_cast<oopValue>(MemoryAddress);
    }
#endif // USE_COMPRESSED_OOPS


#if USE_COMPRESSED_OOPS
    template<typename T>
    FORCEINLINE static T* OopToMemoryAddress(const oopValue InOopValue)
    {
        const uintptr_t ShiftedMemoryAddress = static_cast<uintptr_t>(InOopValue) << oopAlignmentShift;

        return reinterpret_cast<T*>(ShiftedMemoryAddress + CObjectHeapDimension::Start);
    }
#else
    template<typename T>
    FORCEINLINE static T* OopToMemoryAddress(const oopValue InOopValue)
    {
        return reinterpret_cast<T*>(InOopValue);
    }
#endif // USE_COMPRESSED_OOPS

    /**
     * Only used for null
     */
    FORCEINLINE constexpr explicit oop() : Value(static_cast<oopValue>(0)) {}

public:
    template <typename T>
    FORCEINLINE explicit oop(T* const MemoryAddress) : Value(MemoryAddressToOop(MemoryAddress)) {}

    FORCEINLINE explicit oop(const oopValue InOopValue) : Value(InOopValue) {}

    FORCEINLINE oop(const oop& Other) = default;
    FORCEINLINE oop(oop&& Other) = default;

    FORCEINLINE oop& operator=(const oop& Other) = default;
    FORCEINLINE oop& operator=(oop&& Other) = default;

    [[nodiscard]] FORCEINLINE bool IsNull() const
    {
        return Value == static_cast<oopValue>(0);
    }

    template<typename T>
    FORCEINLINE void Set(T* const MemoryAddress)
    {
        Value = MemoryAddressToOop(MemoryAddress);
    }

    template<typename T>
    FORCEINLINE T* Get()
    {
        return OopToMemoryAddress<T>(Value);
    }

    [[nodiscard]] FORCEINLINE oopValue GetValue() const
    {
        return Value;
    }

    static const oop Null;

private:
    oopValue Value;
};





