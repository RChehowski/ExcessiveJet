//
// Created by raman.chakhouski on 4/13/2023.
//

#pragma once

#include "Util/Platform/Memory.h"

using Util::CMemory;

namespace VM
{
    template<usz NumSlots>
    struct CVariableSlotStorage
    {
        constexpr FORCEINLINE u4* GetValueStorage()
        {
            return RawStorage;
        }

        [[nodiscard]] constexpr FORCEINLINE usz GetStorageSize() const
        {
            return sizeof(RawStorage);
        }

        [[nodiscard]] constexpr FORCEINLINE usz GetNumSlots() const
        {
            return NumSlots;
        }

        constexpr FORCEINLINE VM::EVariableSlotType* GetTypeStorage()
        {
            return DebugStorage;
        }

    private:
        u4 RawStorage[NumSlots] { static_cast<u4>(0) };
        VM::EVariableSlotType DebugStorage[NumSlots] { VM::EVariableSlotType::None };
    };
}
