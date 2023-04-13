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
        static usz GetNumSlotsForType()
        {
            constexpr usz NumSlots = sizeof(T) / VM::VariableSlotSize;
            static_assert((NumSlots == 1) || (VM::VariableNeedsTwoSlots<T>() && (NumSlots == 2)));

            return NumSlots;
        }

        template<usz NumSlots>
        explicit CThreadStack(CVariableSlotStorage<NumSlots>& LocalVariablesStorage)
            : Bottom(LocalVariablesStorage.GetStorage())
#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            , Top(LocalVariablesStorage.GetStorage())
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            , Max(LocalVariablesStorage.GetStorage() + LocalVariablesStorage.GetStorageSize())
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
        FORCEINLINE void Push(T Value)
        {
            static_assert(VM::VariableCanBeStored<T>());

            T* const Data = reinterpret_cast<T*>(Top);

            Top += GetNumSlotsForType<T>();
            ASSERT(Top < Max);

            *Data = Value;
        }

        template <typename T>
        FORCEINLINE T Pop()
        {
            static_assert(VM::VariableCanBeStored<T>());

            T* const Data = reinterpret_cast<T*>(Top);
            const T Value = *Data;

            Top -= GetNumSlotsForType<T>();
            ASSERT(Top >= Bottom);

            return Value;
        }

    private:
        u4* const Bottom;
        u4* Top;
        u4* const Max;
    };
}
