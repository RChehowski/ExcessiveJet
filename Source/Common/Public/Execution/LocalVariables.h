//
// Created by ASUS on 05/04/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"

#include <vector>


class CLocalVariables
{
    template<typename T>
    constexpr bool DoesNeedTwoSlots()
    {
        return std::is_same_v<T, double> || std::is_same_v<T, s8>;
    }

public:
    explicit CLocalVariables(void* InRawMemory, const u2 InNumElements)
        : RawMemory(reinterpret_cast<u4*>(InRawMemory))
        , NumElements(InNumElements)
    {
    }

    CLocalVariables(const CLocalVariables&) = delete;
    CLocalVariables(CLocalVariables&&) = delete;

    ~CLocalVariables() = default;

    CLocalVariables operator=(const CLocalVariables&) = delete;
    CLocalVariables operator=(CLocalVariables&&) = delete;

    template <typename T>
    FORCEINLINE void Set(const u2 InIndex, const T InValue)
    {
        *reinterpret_cast<T*>(RawMemory + InIndex) = InValue;
    }

    template <typename T>
    FORCEINLINE T Get(const u2 InIndex) const
    {
        return *reinterpret_cast<const T*>(RawMemory + InIndex);
    }

    static usz GetNumBytes(const usz NumElements)
    {
        return NumElements * sizeof(std::remove_pointer_t<decltype(RawMemory)>);
    }

private:
    u4* const RawMemory;
    const u2 NumElements;
};
