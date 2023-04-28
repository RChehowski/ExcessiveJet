//
// Created by ASUS on 05/04/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"
#include "Execution/VariableSlotType.h"
#include "Execution/VariableSlotStorage.h"

#include <vector>


namespace VM
{
    class CLocalVariables
    {
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        template <typename T>
        FORCEINLINE void SetDebugInfo(const u2 InIndex)
        {
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();
            DebugRamMemory[InIndex] = SlotType;

            if constexpr (SlotType == VM::EVariableSlotType::Long)
            {
                DebugRamMemory[InIndex + 1] = VM::EVariableSlotType::Long_2;
            }
            else if constexpr (SlotType == VM::EVariableSlotType::Double)
            {
                DebugRamMemory[InIndex + 1] = VM::EVariableSlotType::Double_2;
            }
        }

        template <typename T>
        FORCEINLINE void CheckDebugInfo(const u2 InIndex) const
        {
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();

            ASSERT(DebugRamMemory[InIndex] == SlotType);

            if constexpr (SlotType == VM::EVariableSlotType::Long)
            {
                ASSERT(DebugRamMemory[InIndex + 1] == VM::EVariableSlotType::Long_2);
            }
            else if constexpr (SlotType == VM::EVariableSlotType::Double)
            {
                ASSERT(DebugRamMemory[InIndex + 1] == VM::EVariableSlotType::Double_2);
            }
        }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

    public:
        template<usz NumSlots>
        explicit CLocalVariables(CVariableSlotStorage<NumSlots>& LocalVariablesStorage)
            : RawMemory(LocalVariablesStorage.GetValueStorage())
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            , DebugRamMemory(LocalVariablesStorage.GetTypeStorage())
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
        VM::EVariableSlotType* const DebugRamMemory;
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    };
}
