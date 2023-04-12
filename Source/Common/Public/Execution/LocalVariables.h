//
// Created by ASUS on 05/04/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"
#include "Util/Platform/Memory.h"

#include <vector>

#define EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO (1)

using Util::CMemory;

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
enum class ELocalVariableSlotDebugType : u1
{
    None,
    Reference,

    Int,
    Float,

    Long,
    Double,

    Long_2,
    Double_2,

    // --- SERVICE --- //
    Num,
};
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO


template<usz NumSlots>
struct CLocalVariablesStorage
{
    CLocalVariablesStorage()
    {
        CMemory::MemZero(GetStorage(), GetStorageSize());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        for (s4 Index = 0; Index < NumSlots; ++Index)
        {
            DebugStorage[Index] = ELocalVariableSlotDebugType::None;
        }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    }

    FORCEINLINE u4* GetStorage()
    {
        return RawStorage;
    }

    constexpr FORCEINLINE usz GetStorageSize() const
    {
        return sizeof(RawStorage);
    }

    constexpr FORCEINLINE usz GetNumSlots() const
    {
        return NumSlots;
    }

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    FORCEINLINE ELocalVariableSlotDebugType* GetDebugStorage()
    {
        return DebugStorage;
    }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

private:
    alignas(4) u4 RawStorage[NumSlots];

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    // TODO: optimize (use less space, 4 bits per element)
    alignas(4) ELocalVariableSlotDebugType DebugStorage[NumSlots];
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
};

class CLocalVariables
{
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    template<typename T>
    static constexpr ELocalVariableSlotDebugType GetSlotType()
    {
        if constexpr (std::is_same_v<T, oop>)
            return ELocalVariableSlotDebugType::Reference;
        if constexpr (std::is_same_v<T, s4>)
            return ELocalVariableSlotDebugType::Int;
        if constexpr (std::is_same_v<T, float>)
            return ELocalVariableSlotDebugType::Float;
        if constexpr (std::is_same_v<T, s8>)
            return ELocalVariableSlotDebugType::Long;
        if constexpr (std::is_same_v<T, double>)
            return ELocalVariableSlotDebugType::Double;

        return ELocalVariableSlotDebugType::None;
    }

    template <typename T>
    FORCEINLINE void SetDebugInfo(const u2 InIndex)
    {
        constexpr ELocalVariableSlotDebugType SlotType = GetSlotType<T>();
        DebugRamMemory[InIndex] = SlotType;

        if constexpr (SlotType == ELocalVariableSlotDebugType::Long)
        {
            DebugRamMemory[InIndex + 1] = ELocalVariableSlotDebugType::Long_2;
        }
        else if constexpr (SlotType == ELocalVariableSlotDebugType::Double)
        {
            DebugRamMemory[InIndex + 1] = ELocalVariableSlotDebugType::Double_2;
        }
    }

    template <typename T>
    FORCEINLINE void CheckDebugInfo(const u2 InIndex) const
    {
        constexpr ELocalVariableSlotDebugType SlotType = GetSlotType<T>();

        ASSERT(DebugRamMemory[InIndex] == SlotType);

        if constexpr (SlotType == ELocalVariableSlotDebugType::Long)
        {
            ASSERT(DebugRamMemory[InIndex + 1] == ELocalVariableSlotDebugType::Long_2);
        }
        else if constexpr (SlotType == ELocalVariableSlotDebugType::Double)
        {
            ASSERT(DebugRamMemory[InIndex + 1] == ELocalVariableSlotDebugType::Double_2);
        }
    }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

public:
    template<usz NumSlots>
    explicit CLocalVariables(CLocalVariablesStorage<NumSlots>& LocalVariablesStorage)
        : RawMemory(LocalVariablesStorage.GetStorage())
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        , DebugRamMemory(LocalVariablesStorage.GetDebugStorage())
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        , NumElements(LocalVariablesStorage.GetNumSlots())
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
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        SetDebugInfo<T>(InIndex);
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

        *reinterpret_cast<T*>(RawMemory + InIndex) = InValue;
    }

    template <typename T>
    FORCEINLINE T Get(const u2 InIndex) const
    {
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        CheckDebugInfo<T>(InIndex);
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

        return *reinterpret_cast<const T*>(RawMemory + InIndex);
    }

    static usz GetNumBytes(const usz NumElements)
    {
        return NumElements * sizeof(std::remove_pointer_t<decltype(RawMemory)>);
    }

private:
    u4* const RawMemory;
    const u2 NumElements;

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    ELocalVariableSlotDebugType* const DebugRamMemory;
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
};
