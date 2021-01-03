//
// Created by ASUS on 27/12/2020.
//

#include "ConstantPool.h"

#include <cstdio>
#include <functional>
#include <unordered_map>


namespace Parse
{
    typedef std::function<CConstantInfo*(EConstantPoolInfoTag)> CConstantInfoSpawnFunction;
    typedef std::unordered_map<EConstantPoolInfoTag, CConstantInfoSpawnFunction> CTagToConstantInfoSpawnFunction;

    using ECPIT = EConstantPoolInfoTag;
    const CTagToConstantInfoSpawnFunction G_TagToConstantInfoSpawnFunction = {
        { ECPIT::Utf8,               [](ECPIT Tag) { return new CConstantUtf8Info(Tag); } },
        { ECPIT::Integer,            [](ECPIT Tag) { return new CConstantIntegerInfo(Tag); } },
        { ECPIT::Float,              [](ECPIT Tag) { return new CConstantFloatInfo(Tag); } },
        { ECPIT::Long,               [](ECPIT Tag) { return new CConstantLongInfo(Tag); } },
        { ECPIT::Double,             [](ECPIT Tag) { return new CConstantDoubleInfo(Tag); } },
        { ECPIT::Class,              [](ECPIT Tag) { return new CConstantClassInfo(Tag); } },
        { ECPIT::String,             [](ECPIT Tag) { return new CConstantStringInfo(Tag); } },
        { ECPIT::FieldRef,           [](ECPIT Tag) { return new CConstantFieldRefInfo(Tag); } },
        { ECPIT::MethodRef,          [](ECPIT Tag) { return new CConstantMethodRefInfo(Tag); } },
        { ECPIT::InterfaceMethodRef, [](ECPIT Tag) { return new CConstantInterfaceMethodRefInfo(Tag); } },
        { ECPIT::NameAndType,        [](ECPIT Tag) { return new CConstantNameAndTypeInfo(Tag); } },
        { ECPIT::MethodHandle,       [](ECPIT Tag) { return new CConstantMethodHandleInfo(Tag); } },
        { ECPIT::MethodType,         [](ECPIT Tag) { return new CConstantMethodTypeInfo(Tag); } },
        { ECPIT::InvokeDynamic,      [](ECPIT Tag) { return new CConstantInvokeDynamicInfo(Tag); } }
    };

    CConstantInfo* New_ConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
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
