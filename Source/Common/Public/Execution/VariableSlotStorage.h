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
        CVariableSlotStorage()
        {
            CMemory::MemZero(GetStorage(), GetStorageSize());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            for (s4 Index = 0; Index < NumSlots; ++Index)
            {
                DebugStorage[Index] = VM::EVariableSlotType::None;
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
        FORCEINLINE VM::EVariableSlotType* GetDebugStorage()
        {
            return DebugStorage;
        }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

    private:
        alignas(4) u4 RawStorage[NumSlots];

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        // TODO: optimize (use less space, 4 bits per element)
        alignas(4) VM::EVariableSlotType DebugStorage[NumSlots];
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
    };
}
