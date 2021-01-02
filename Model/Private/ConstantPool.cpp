//
// Created by ASUS on 27/12/2020.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "ConstantPool.h"

#include "Platform/Misc.h"
#include "Assert.h"


namespace Parse
{
    typedef std::function<CConstantInfo*(EConstantPoolInfoTag)> CConstantInfoSpawnFunction;
    typedef std::unordered_map<EConstantPoolInfoTag, CConstantInfoSpawnFunction> CTagToConstantInfoSpawnFunction;

    CTagToConstantInfoSpawnFunction GetTagToConstantInfoSpawnFunction() noexcept
    {
        using EInfoTag = EConstantPoolInfoTag;

        CTagToConstantInfoSpawnFunction TagToConstantInfoSpawnFunction = {
            { EInfoTag::Utf8,               [](EInfoTag Tag) { return new CConstantUtf8Info(Tag); } },
            { EInfoTag::Integer,            [](EInfoTag Tag) { return new CConstantIntegerInfo(Tag); } },
            { EInfoTag::Float,              [](EInfoTag Tag) { return new CConstantFloatInfo(Tag); } },
            { EInfoTag::Long,               [](EInfoTag Tag) { return new CConstantLongInfo(Tag); } },
            { EInfoTag::Double,             [](EInfoTag Tag) { return new CConstantDoubleInfo(Tag); } },
            { EInfoTag::Class,              [](EInfoTag Tag) { return new CConstantClassInfo(Tag); } },
            { EInfoTag::String,             [](EInfoTag Tag) { return new CConstantStringInfo(Tag); } },
            { EInfoTag::FieldRef,           [](EInfoTag Tag) { return new CConstantFieldRefInfo(Tag); } },
            { EInfoTag::MethodRef,          [](EInfoTag Tag) { return new CConstantMethodRefInfo(Tag); } },
            { EInfoTag::InterfaceMethodRef, [](EInfoTag Tag) { return new CConstantInterfaceMethodRefInfo(Tag); } },
            { EInfoTag::NameAndType,        [](EInfoTag Tag) { return new CConstantNameAndTypeInfo(Tag); } },
            { EInfoTag::MethodHandle,       [](EInfoTag Tag) { return new CConstantMethodHandleInfo(Tag); } },
            { EInfoTag::MethodType,         [](EInfoTag Tag) { return new CConstantMethodTypeInfo(Tag); } },
            { EInfoTag::InvokeDynamic,      [](EInfoTag Tag) { return new CConstantInvokeDynamicInfo(Tag); } }
        };

        return std::move(TagToConstantInfoSpawnFunction);
    }

    const CTagToConstantInfoSpawnFunction G_TagToConstantInfoSpawnFunction = GetTagToConstantInfoSpawnFunction();

    CConstantInfo* CConstantPool::NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        auto It = G_TagToConstantInfoSpawnFunction.find(ConstantPoolInfoTag);
        if (It != G_TagToConstantInfoSpawnFunction.end())
        {
            return It->second(ConstantPoolInfoTag);
        }
        else
        {
            return nullptr;
        }
    }
}
