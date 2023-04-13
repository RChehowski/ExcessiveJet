//
// Created by ASUS on 27/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"
#include "Util/Platform/Memory.h"
#include "Util/ExcessiveAssert.h"
#include "Execution/VariableDebugType.h"
#include "Execution/VariableSlotStorage.h"

namespace VM
{
    struct CThreadStack
    {
        template<typename T>
        static constexpr usz GetNumSlotsForType()
        {
            constexpr usz NumSlots = sizeof(T) / VM::VariableSlotSize;
            static_assert((NumSlots == 1) || (VM::VariableNeedsTwoSlots<T>() && (NumSlots == 2)));

            return NumSlots;
        }

        template<usz NumSlots>
        explicit CThreadStack(CVariableSlotStorage<NumSlots>& LocalVariablesStorage)
            : Bottom(LocalVariablesStorage.GetStorage())
            , Top(LocalVariablesStorage.GetStorage())
            , Max(LocalVariablesStorage.GetStorage() + LocalVariablesStorage.GetStorageSize())
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            , DebugRawMemory(LocalVariablesStorage.GetDebugStorage())
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        {
        }

        CThreadStack() = delete;
        CThreadStack(const CThreadStack&) = delete;
        CThreadStack(CThreadStack&&) = delete;

        CThreadStack& operator=(const CThreadStack&) = delete;
        CThreadStack& operator=(CThreadStack&&) = delete;

        [[nodiscard]] FORCEINLINE usz GetSize() const
        {
            return static_cast<usz>(Top - Bottom);
        }

        [[nodiscard]] FORCEINLINE usz GetCapacity() const
        {
            return static_cast<usz>(Max - Bottom);
        }

        template <typename T>
        FORCEINLINE void Push(const T Value)
        {
            static_assert(VM::VariableCanBeStored<T>());

            T* const Data = reinterpret_cast<T*>(Top);

            constexpr usz NumSlots = GetNumSlotsForType<T>();

            Top += NumSlots;
            ASSERT(Top < Max);

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();

            *DebugRawMemory = SlotType;
            DebugRawMemory = DebugRawMemory + 1;

            if constexpr (NumSlots == 2)
            {
                if constexpr (SlotType == VM::EVariableSlotType::Long)
                {
                    *DebugRawMemory = VM::EVariableSlotType::Long_2;
                }
                else if constexpr (SlotType == VM::EVariableSlotType::Double)
                {
                    *DebugRawMemory = VM::EVariableSlotType::Double_2;
                }

                DebugRawMemory = DebugRawMemory + 1;
            }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            *Data = Value;
        }

        template <typename T>
        FORCEINLINE T Pop()
        {
            static_assert(VM::VariableCanBeStored<T>());

            constexpr usz NumSlots = GetNumSlotsForType<T>();
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();

            if constexpr (NumSlots == 2)
            {
                DebugRawMemory = DebugRawMemory - 1;
                const VM::EVariableSlotType ActualType = *DebugRawMemory;

                if constexpr (SlotType == VM::EVariableSlotType::Long)
                {
                    ASSERT_MSG(ActualType == VM::EVariableSlotType::Long_2, "Actual type: %s, expected Long_2", VM::ToString(SlotType));
                }
                else if constexpr (SlotType == VM::EVariableSlotType::Double)
                {
                    ASSERT_MSG(ActualType == VM::EVariableSlotType::Double_2, "Actual type: %s, expected Double_2", VM::ToString(SlotType));
                }
            }

            DebugRawMemory = DebugRawMemory - 1;
            const VM::EVariableSlotType ActualType = *DebugRawMemory;
            ASSERT_MSG(ActualType == SlotType, "Actual type: %s, expected %s", VM::ToString(ActualType), VM::ToString(SlotType));
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Top -= NumSlots;
            ASSERT(Top >= Bottom);

            T* const Data = reinterpret_cast<T*>(Top);
            const T Value = *Data;

            return Value;
        }

    private:
        u4* const Bottom;
        u4* Top;
        u4* const Max;

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        VM::EVariableSlotType* DebugRawMemory;
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    };
}
