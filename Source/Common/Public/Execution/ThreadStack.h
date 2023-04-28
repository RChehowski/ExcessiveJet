//
// Created by ASUS on 27/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"
#include "Util/Platform/Memory.h"
#include "Util/ExcessiveAssert.h"
#include "Execution/VariableSlotType.h"
#include "Execution/VariableSlotStorage.h"

#include <functional>

namespace VM
{
    struct CThreadStack
    {
    private:
#if WITH_ASSERT
        /** Check if we can read "NumSlots" values from the top of the stack */
        #define RangeCheck_Read(NumSlots)\
            ASSERT_MSG\
            (\
                (static_cast<u4>(NumSlots) <=  Size),\
                "Can not read %lu slots from the stack of size %lu",\
                static_cast<unsigned long>(NumSlots),\
                static_cast<unsigned long>(Size)\
            );

        /** Check if we can write "NumSlots" values to the top of the stack */
        #define RangeCheck_Write(NumSlots)\
            ASSERT_MSG\
            (\
                ((Capacity - Size) >= static_cast<u4>(NumSlots)),\
                "Can not write %lu slots to the stack with size %lu and capacity %lu",\
                static_cast<unsigned long>(NumSlots),\
                static_cast<unsigned long>(Size),\
                static_cast<unsigned long>(Capacity)\
            );
#else
        #define RangeCheck_Read(NumSlots)
        #define RangeCheck_Write(NumSlots)
#endif // WITH_ASSERT

        template<typename T>
        static FORCEINLINE void GenericDup(T* const Top)
        {
            // value -> value, value
            const T Value = Top[-1];
            Top[0] = Value;
        }

        template<typename T>
        static FORCEINLINE void GenericDupX1(T* const Top)
        {
            //  value2, value1 -> value1, value2, value1
            const T Value2 = Top[-2];
            const T Value1 = Top[-1];

            Top[-2] = Value1;
            Top[-1] = Value2;
            Top[ 0] = Value1;
        }

        // note: although all Dup2XXX opcodes operate 2-slot (8-byte) values to some degree, we cannot read them as 8-byte values
        // as neither the bytecode makes sure reads are 8-byte aligned, nor the C++ compiler or the platform can ensure correct 8-bit unaligned reads

        template<typename T>
        static FORCEINLINE void GenericDup2(T* const Top)
        {
            // {value2, value1} -> {value2, value1}, {value2, value1}
            const T Value2 = Top[-2];
            const T Value1 = Top[-1];

            Top[0] = Value2;
            Top[1] = Value1;
        }

        template<typename T>
        static FORCEINLINE void Generic_Dup2X1(T* const Top)
        {
            // value3, {value2, value1} -> {value2, value1}, value3, {value2, value1}
            const T Value3 = Top[-3];
            const T Value2 = Top[-2];
            const T Value1 = Top[-1];

            Top[-3] = Value2;
            Top[-2] = Value1;
            Top[-1] = Value3;
            Top[0] = Value2;
            Top[1] = Value1;
        }

        template<typename T>
        static FORCEINLINE void Generic_Dup2X2(T* const Top)
        {
            // {value4, value3}, {value2, value1} -> {value2, value1}, {value4, value3}, {value2, value1}
            const T Value4 = Top[-4];
            const T Value3 = Top[-3];
            const T Value2 = Top[-2];
            const T Value1 = Top[-1];

            Top[-4] = Value2;
            Top[-3] = Value1;
            Top[-2] = Value4;
            Top[-1] = Value3;
            Top[0] = Value2;
            Top[1] = Value1;
        }

        template<typename T>
        static FORCEINLINE void Generic_Swap(T* const Top)
        {
            // value2, value1 -> value1, value2
            const T Temp_M2 = Top[-2];
            const T Temp_M1 = Top[-1];

            Top[-2] = Temp_M1;
            Top[-1] = Temp_M2;
        }

    public:
        template<typename T>
        static constexpr u4 GetNumSlotsForType()
        {
            constexpr u4 NumSlots = static_cast<u4>(sizeof(T) / VM::VariableSlotSize);
            static_assert((NumSlots == 1) || (VM::VariableNeedsTwoSlots<T>() && (NumSlots == 2)));

            return NumSlots;
        }

        template<usz NumSlots>
        explicit CThreadStack(CVariableSlotStorage<NumSlots>& LocalVariablesStorage)
            : ValueMemory(LocalVariablesStorage.GetValueStorage())
            , TypeMemory(LocalVariablesStorage.GetTypeStorage())
            , Size(0UL)
            , Capacity(LocalVariablesStorage.GetStorageSize())
        {
        }

        CThreadStack() = delete;
        CThreadStack(const CThreadStack&) = delete;
        CThreadStack(CThreadStack&&) = delete;

        CThreadStack& operator=(const CThreadStack&) = delete;
        CThreadStack& operator=(CThreadStack&&) = delete;

        [[nodiscard]] FORCEINLINE usz GetSize() const
        {
            return static_cast<usz>(Size);
        }

        [[nodiscard]] FORCEINLINE usz GetCapacity() const
        {
            return static_cast<usz>(Capacity);
        }

        FORCEINLINE u4* GetTopValue()
        {
            return ValueMemory + Size;
        }

        FORCEINLINE VM::EVariableSlotType* GetTopType()
        {
            return TypeMemory + Size;
        }

        template <typename T>
        FORCEINLINE void Push(const T Value)
        {
            static_assert(VM::VariableCanBeStored<T>());

            constexpr usz NumSlots = GetNumSlotsForType<T>();
            static_assert((NumSlots == 1) || (NumSlots == 2), "Can only push to 1 or 2 slots");

            RangeCheck_Write(NumSlots);

            *reinterpret_cast<T*>(GetTopValue()) = Value;

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();

            VM::EVariableSlotType* TopType = GetTopType();

            // The "service" type is pushed to the BOTTOM of the stack
            if constexpr (SlotType == VM::EVariableSlotType::Long)
            {
                *(TopType++) = VM::EVariableSlotType::Long_2;
            }
            else if constexpr (SlotType == VM::EVariableSlotType::Double)
            {
                *(TopType++) = VM::EVariableSlotType::Double_2;
            }

            *TopType = SlotType;
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlots;
        }

        template <typename T>
        FORCEINLINE T Pop()
        {
            static_assert(VM::VariableCanBeStored<T>());

            constexpr u4 NumSlots = GetNumSlotsForType<T>();
            static_assert((NumSlots == 1) || (NumSlots == 2), "Can only pop 1 or 2 slots");

            RangeCheck_Read(NumSlots);

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            constexpr VM::EVariableSlotType SlotType = GetSlotType<T>();

            const VM::EVariableSlotType ActualType = *(GetTopType() - 1);
            ASSERT_MSG((ActualType == SlotType), "Actual type: %s, expected %s", VM::ToString(ActualType), VM::ToString(SlotType));

            // The "service" type is popped from the BOTTOM of the stack
            if constexpr (SlotType == VM::EVariableSlotType::Long)
            {
                const VM::EVariableSlotType ActualType2 = *(GetTopType() - 2);
                ASSERT_MSG((ActualType2 == VM::EVariableSlotType::Long_2), "Actual type: %s, expected Long_2", VM::ToString(SlotType));
            }
            else if constexpr (SlotType == VM::EVariableSlotType::Double)
            {
                const VM::EVariableSlotType ActualType2 = *(GetTopType() - 2);
                ASSERT_MSG((ActualType2 == VM::EVariableSlotType::Double_2), "Actual type: %s, expected Double_2", VM::ToString(SlotType));
            }
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            const T* const Data = reinterpret_cast<T*>(GetTopValue() - NumSlots);
            Size -= NumSlots;

            return *Data;
        }

        void PopDiscard(const u4 Times)
        {
            RangeCheck_Read(Times);

            Size -= Times;
        }
#pragma region Stack tricks

        FORCEINLINE void Dup()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(1);
            RangeCheck_Read(NumSlotsRead);

            constexpr u4 NumSlotsWrite = static_cast<u4>(1);
            RangeCheck_Write(NumSlotsWrite);

            GenericDup<u4>(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            GenericDup<VM::EVariableSlotType>(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlotsWrite;
        }

        FORCEINLINE void DupX1()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(2);
            RangeCheck_Read(NumSlotsRead);

            constexpr u4 NumSlotsWrite = static_cast<u4>(1);
            RangeCheck_Write(NumSlotsWrite);

            GenericDupX1<u4>(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            GenericDupX1<VM::EVariableSlotType>(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlotsWrite;
        }

        FORCEINLINE void Dup2()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(3);
            RangeCheck_Read(NumSlotsRead)

            constexpr u4 NumSlotsWrite = static_cast<u4>(2);
            RangeCheck_Write(NumSlotsWrite)

            GenericDup2(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            GenericDup2(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlotsWrite;
        }

        FORCEINLINE void Dup2X1()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(3);
            RangeCheck_Read(NumSlotsRead)

            constexpr u4 NumSlotsWrite = static_cast<u4>(2);
            RangeCheck_Write(NumSlotsWrite)

            Generic_Dup2X1(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            Generic_Dup2X1(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlotsWrite;
        }

        FORCEINLINE void Dup2X2()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(4);
            RangeCheck_Read(NumSlotsRead)

            constexpr u4 NumSlotsWrite = static_cast<u4>(2);
            RangeCheck_Write(NumSlotsWrite)

            Generic_Dup2X2(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            Generic_Dup2X2(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO

            Size += NumSlotsWrite;
        }

        FORCEINLINE void Swap()
        {
            constexpr u4 NumSlotsRead = static_cast<u4>(2);
            RangeCheck_Read(NumSlotsRead)

            Generic_Swap(GetTopValue());

#if EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
            Generic_Swap(GetTopType());
#endif // EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO
        }

        template<typename T>
        FORCEINLINE void ForEach(std::function<void(T)>&& Function)
        {
            constexpr VM::EVariableSlotType VariableSlotType = VM::GetSlotType<T>();
            static_assert
            (
                VariableSlotType != EVariableSlotType::Double_2 && VariableSlotType != EVariableSlotType::Long_2,
                "Double_2 and Long_2 are service slot types, they should not be used in this scenario"
            );

            for (u4 Index = 0; Index < Size; Index++)
            {
                const VM::EVariableSlotType CurrentVariableSlotType = TypeMemory[Index];
                if (VariableSlotType == CurrentVariableSlotType)
                {
                    Function(*reinterpret_cast<T*>(ValueMemory + Index));
                }
            }
        }
#pragma endregion

    private:
        // Stores values
        u4* const ValueMemory;

        // Used for validation and for Dup2 family of instruction that do care about types (such a shame)
        VM::EVariableSlotType* TypeMemory;

        u4 Size;
        u4 Capacity;
    };
}
