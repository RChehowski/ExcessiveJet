#pragma once

#include "Util/Types.h"

namespace VM
{
    constexpr usz VariableSlotSize = 4;

    /**
     * Variable type that can be stored in CLocalVariables or CThreadStack
     */
    enum class EVariableSlotType : u1
    {
        /** Value is not yet written. Nothing is yet stored in this slot. */
        None,

        /**
         * Object reference as an "oop" (java.lang.Object, java.lang.String, array of objects/strings, other object types)
         *
         * NOTE: All oops are currently 4 bytes in size, even for 64bit configuration (see "Compressed OOPs")
         */
        Reference,


        /** A 4 byte signed integral value */
        Int,

        /** A 4 byte signed floating point value */
        Float,

        /** A 8 byte signed integral value (long) */
        Long,

        /** A 8 byte signed floating point value (double) */
        Double,


        /**
         * The other part of a signed integral value (long)
         * NOTE: Since the slot size is 2 times less than a long value, long values take two slots.
         */
        Long_2,

        /**
         * The other part of a signed floating point value (double)
         * NOTE: Since the slot size is 2 times less than a double value, double values take two slots.
         */
        Double_2,
    };

    namespace Private
    {
        /** NOTE: Do not use directly, use the wrapper function instead */
        template <typename T> constexpr bool PRIVATE_VariableCanBeStored(){ return false; }

        template <> constexpr bool PRIVATE_VariableCanBeStored<oop>()     { return true; }
        template <> constexpr bool PRIVATE_VariableCanBeStored<s4>()      { return true; }
        template <> constexpr bool PRIVATE_VariableCanBeStored<float>()   { return true; }
        template <> constexpr bool PRIVATE_VariableCanBeStored<s8>()      { return true; }
        template <> constexpr bool PRIVATE_VariableCanBeStored<double>()  { return true; }
    }

    template <typename T>
    constexpr bool VariableCanBeStored()
    {
        static_assert(sizeof(T) == VariableSlotSize || sizeof(T) == (VariableSlotSize * 2));
        return Private::PRIVATE_VariableCanBeStored<T>();
    }

    template <typename T>
    constexpr bool VariableNeedsTwoSlots()
    {
        static_assert(VariableCanBeStored<T>());
        return std::is_same_v<T, s8> || std::is_same_v<T, double>;
    }

    constexpr const char* ToString(const EVariableSlotType VariableSlotType)
    {
        switch (VariableSlotType)
        {
            case EVariableSlotType::None:      return "None";
            case EVariableSlotType::Reference: return "Reference";
            case EVariableSlotType::Int:       return "Int";
            case EVariableSlotType::Float:     return "Float";
            case EVariableSlotType::Long:      return "Long";
            case EVariableSlotType::Double:    return "Double";
            case EVariableSlotType::Long_2:    return "Long_2";
            case EVariableSlotType::Double_2:  return "Double_2";

            default: return "<Unknown>";
        }
    }

    template<typename T>
    static constexpr VM::EVariableSlotType GetSlotType()
    {
        if constexpr (std::is_same_v<T, oop>)
            return VM::EVariableSlotType::Reference;

        if constexpr (std::is_same_v<T, s4>)
            return VM::EVariableSlotType::Int;

        if constexpr (std::is_same_v<T, float>)
            return VM::EVariableSlotType::Float;

        if constexpr (std::is_same_v<T, s8>)
            return VM::EVariableSlotType::Long;

        if constexpr (std::is_same_v<T, double>)
            return VM::EVariableSlotType::Double;

        return VM::EVariableSlotType::None;
    }
}
