//
// Created by raman.chakhouski on 4/13/2023.
//

#pragma once

#include "Util/Platform/Memory.h"

using Util::CMemory;

namespace VM
{
    /**
     * Raw memory storage allocated on the C++ stack, primarily needed for LocalVariables.
     * Does not do any checks or management, just allocates the memory.
     */
    template<typename TSlotType, usz NumSlots>
    struct CSlotStorage
    {
        static_assert((sizeof(TSlotType) <= 4) && std::is_pod_v<TSlotType>, "Only trivial types are allowed as slot types");

        constexpr CSlotStorage()
        {
            // Initialize each slot with its default value
            for (usz Index = 0; Index < NumSlots; ++Index)
            {
                new (ValueStorage + Index) TSlotType{};
            }
        }

        TSlotType* operator*()
        {
            return ValueStorage;
        }

        [[nodiscard]] constexpr FORCEINLINE usz GetNumSlots() const
        {
            return NumSlots;
        }

    private:
        TSlotType ValueStorage[NumSlots];
    };

    template<usz NumSlots>
    struct CLocalVariableSlotStorage
    {
        constexpr FORCEINLINE u4* GetValueStorage()
        {
            return *ValueStorage;
        }

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        constexpr FORCEINLINE VM::EVariableSlotType* GetTypeStorage()
        {
            return *TypeStorage;
        }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

        [[nodiscard]] constexpr FORCEINLINE usz GetNumSlots() const
        {
            return NumSlots;
        }

    private:
        CSlotStorage<u4, NumSlots> ValueStorage;

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        CSlotStorage<VM::EVariableSlotType, NumSlots> TypeStorage;
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    };

    template<usz NumSlots>
    struct CThreadStackSlotStorage
    {
        constexpr FORCEINLINE u4* GetValueStorage()
        {
            return *ValueStorage;
        }

        constexpr FORCEINLINE VM::EVariableSlotType* GetTypeStorage()
        {
            return *TypeStorage;
        }

        [[nodiscard]] constexpr FORCEINLINE usz GetNumSlots() const
        {
            return NumSlots;
        }

    private:
        CSlotStorage<u4, NumSlots> ValueStorage;
        CSlotStorage<VM::EVariableSlotType, NumSlots> TypeStorage;
    };
}
