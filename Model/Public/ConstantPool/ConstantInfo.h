//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"
#include "Assert.h"

#include <string>

namespace Parse
{
    enum class EConstantPoolInfoTag : u1
    {
        Utf8 = 1,
        Integer = 3,
        Float = 4,
        Long = 5,
        Double = 6,
        Class = 7,
        String = 8,
        FieldRef = 9,
        MethodRef = 10,
        InterfaceMethodRef = 11,
        NameAndType = 12,
        MethodHandle = 15,
        MethodType = 16,
        InvokeDynamic = 18,

        Invalid_NotATag = 255
    };


    class CConstantInfo
    {
    public:
        FORCEINLINE explicit CConstantInfo(const EConstantPoolInfoTag InConstantPoolInfoTag)
            : ConstantPoolInfoTag(InConstantPoolInfoTag)
        {
        }

        virtual ~CConstantInfo() = default;

        FORCEINLINE EConstantPoolInfoTag GetConstantPoolInfoTag() const
        {
            return ConstantPoolInfoTag;
        }

        virtual std::string ToString() const = 0;

        FORCEINLINE static EConstantPoolInfoTag GetConstantPoolInfoTagByByte(const u1 TagByte)
        {
            switch (TagByte)
            {
                case (u1) EConstantPoolInfoTag::Utf8:
                case (u1) EConstantPoolInfoTag::Integer:
                case (u1) EConstantPoolInfoTag::Float:
                case (u1) EConstantPoolInfoTag::Long:
                case (u1) EConstantPoolInfoTag::Double:
                case (u1) EConstantPoolInfoTag::Class:
                case (u1) EConstantPoolInfoTag::String:
                case (u1) EConstantPoolInfoTag::FieldRef:
                case (u1) EConstantPoolInfoTag::MethodRef:
                case (u1) EConstantPoolInfoTag::InterfaceMethodRef:
                case (u1) EConstantPoolInfoTag::NameAndType:
                case (u1) EConstantPoolInfoTag::MethodHandle:
                case (u1) EConstantPoolInfoTag::MethodType:
                case (u1) EConstantPoolInfoTag::InvokeDynamic:
                    return (EConstantPoolInfoTag)TagByte;

                default:
                    ASSERT(false);
                    return EConstantPoolInfoTag::Invalid_NotATag;
            }
        }

    private:
        const EConstantPoolInfoTag ConstantPoolInfoTag;
    };
}
