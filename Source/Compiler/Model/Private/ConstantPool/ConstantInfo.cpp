//
// Created by ASUS on 02/01/2021.
//

#include "ConstantPool/ConstantInfo.h"

#include "ConstantPool/ConstantClassInfo.h"
#include "ConstantPool/ConstantDoubleInfo.h"
#include "ConstantPool/ConstantFieldRefInfo.h"
#include "ConstantPool/ConstantFloatInfo.h"
#include "ConstantPool/ConstantIntegerInfo.h"
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"
#include "ConstantPool/ConstantInvokeDynamicInfo.h"
#include "ConstantPool/ConstantLongInfo.h"
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "ConstantPool/ConstantStringInfo.h"
#include "ConstantPool/ConstantUtf8Info.h"
#include "ClassReader.h"

#include <functional>
#include <unordered_map>

namespace Parse
{
    typedef std::function<CConstantInfo*(EConstantPoolInfoTag)> CConstantInfoSpawnFunction;
    typedef std::unordered_map<EConstantPoolInfoTag, CConstantInfoSpawnFunction> CTagToConstantInfoSpawnFunction;

    using ETag = EConstantPoolInfoTag;
    const CTagToConstantInfoSpawnFunction G_TagToConstantInfoSpawnFunction {
            {ETag::Utf8,               [](ETag Tag) { return new CConstantUtf8Info(Tag); } },
            {ETag::Integer,            [](ETag Tag) { return new CConstantIntegerInfo(Tag); } },
            {ETag::Float,              [](ETag Tag) { return new CConstantFloatInfo(Tag); } },
            {ETag::Long,               [](ETag Tag) { return new CConstantLongInfo(Tag); } },
            {ETag::Double,             [](ETag Tag) { return new CConstantDoubleInfo(Tag); } },
            {ETag::Class,              [](ETag Tag) { return new CConstantClassInfo(Tag); } },
            {ETag::String,             [](ETag Tag) { return new CConstantStringInfo(Tag); } },
            {ETag::FieldRef,           [](ETag Tag) { return new CConstantFieldRefInfo(Tag); } },
            {ETag::MethodRef,          [](ETag Tag) { return new CConstantMethodRefInfo(Tag); } },
            {ETag::InterfaceMethodRef, [](ETag Tag) { return new CConstantInterfaceMethodRefInfo(Tag); } },
            {ETag::NameAndType,        [](ETag Tag) { return new CConstantNameAndTypeInfo(Tag); } },
            {ETag::MethodHandle,       [](ETag Tag) { return new CConstantMethodHandleInfo(Tag); } },
            {ETag::MethodType,         [](ETag Tag) { return new CConstantMethodTypeInfo(Tag); } },
            {ETag::InvokeDynamic,      [](ETag Tag) { return new CConstantInvokeDynamicInfo(Tag); } }
    };


    EConstantPoolInfoTag CConstantInfo::GetConstantPoolInfoTagByByte(const u1 TagByte)
    {
        // Try to find it in the map
        auto It = G_TagToConstantInfoSpawnFunction.find((EConstantPoolInfoTag)TagByte);
        if (It != G_TagToConstantInfoSpawnFunction.end())
        {
            return It->first;
        }
        else
        {
            // Not in the map, trigger assertion error
            ASSERT(false);
            return EConstantPoolInfoTag::Invalid_NotATag;;
        }
    }

    void operator>>(CClassReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    CConstantInfo* CConstantInfo::NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        auto It = G_TagToConstantInfoSpawnFunction.find(ConstantPoolInfoTag);
        if (It != G_TagToConstantInfoSpawnFunction.end())
        {
            // Create a new instance
            return It->second(ConstantPoolInfoTag);
        }
        else
        {
            return nullptr;
        }
    }
}