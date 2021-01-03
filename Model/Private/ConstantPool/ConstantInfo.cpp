//
// Created by ASUS on 02/01/2021.
//

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    EConstantPoolInfoTag CConstantInfo::GetConstantPoolInfoTagByByte(const u1 TagByte)
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

    void operator>>(Util::CMemoryReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}