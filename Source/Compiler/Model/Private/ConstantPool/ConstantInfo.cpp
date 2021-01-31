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

#define ADD_CONSTANT_INFO(Name)\
    {EConstantPoolInfoTag::Name, [](EConstantPoolInfoTag Tag){return std::make_shared<CConstant##Name##Info>(Tag);}}

namespace Parse
{
    using CConstantInfoSpawnFunction = std::function<std::shared_ptr<CConstantInfo>(EConstantPoolInfoTag)>;
    using CTagToConstantInfoSpawnFunction = std::unordered_map<EConstantPoolInfoTag, CConstantInfoSpawnFunction>;

    const CTagToConstantInfoSpawnFunction G_TagToConstantInfoSpawnFunction {
        ADD_CONSTANT_INFO(Utf8),
        ADD_CONSTANT_INFO(Integer),
        ADD_CONSTANT_INFO(Float),
        ADD_CONSTANT_INFO(Long),
        ADD_CONSTANT_INFO(Double),
        ADD_CONSTANT_INFO(Class),
        ADD_CONSTANT_INFO(String),
        ADD_CONSTANT_INFO(FieldRef),
        ADD_CONSTANT_INFO(MethodRef),
        ADD_CONSTANT_INFO(InterfaceMethodRef),
        ADD_CONSTANT_INFO(NameAndType),
        ADD_CONSTANT_INFO(MethodHandle),
        ADD_CONSTANT_INFO(MethodType),
        ADD_CONSTANT_INFO(InvokeDynamic),
    };

    void operator>>(CClassReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::shared_ptr<CConstantInfo> CConstantInfo::NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        auto It = G_TagToConstantInfoSpawnFunction.find(ConstantPoolInfoTag);

        ASSERT(It != G_TagToConstantInfoSpawnFunction.end());

        // Create a new instance
        return It->second(ConstantPoolInfoTag);
    }
}