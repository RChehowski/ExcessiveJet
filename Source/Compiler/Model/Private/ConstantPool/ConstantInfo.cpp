//
// Created by ASUS on 02/01/2021.
//

#include "ConstantPool/ConstantInfo.h"

#include "ConstantPool/ConstantUtf8Info.h"
#include "ConstantPool/ConstantLongInfo.h"
#include "ConstantPool/ConstantFloatInfo.h"
#include "ConstantPool/ConstantClassInfo.h"
#include "ConstantPool/ConstantStringInfo.h"
#include "ConstantPool/ConstantDoubleInfo.h"
#include "ConstantPool/ConstantIntegerInfo.h"
#include "ConstantPool/ConstantFieldRefInfo.h"
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "ConstantPool/ConstantInvokeDynamicInfo.h"
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"

#include "ClassReader.h"

#include <functional>
#include <unordered_map>

#define ADD_CONSTANT_INFO(CONSTANT_NAME)                                \
{                                                                       \
    EConstantPoolInfoTag::CONSTANT_NAME,                                \
    [](EConstantPoolInfoTag Tag)                                        \
    {                                                                   \
        return std::make_shared<CConstant##CONSTANT_NAME##Info>(Tag);   \
    }                                                                   \
}

namespace Compiler
{
    using CConstantInfoSpawnFunction = std::function<std::shared_ptr<CConstantInfo>(EConstantPoolInfoTag)>;
    using CTagToConstantInfoSpawnFunction = std::unordered_map<EConstantPoolInfoTag, CConstantInfoSpawnFunction>;

    void operator>>(CClassReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::shared_ptr<CConstantInfo> CConstantInfo::NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        static const CTagToConstantInfoSpawnFunction G_TagToConstantInfoSpawnFunction {
            ADD_CONSTANT_INFO(Utf8),
            ADD_CONSTANT_INFO(Long),
            ADD_CONSTANT_INFO(Float),
            ADD_CONSTANT_INFO(Class),
            ADD_CONSTANT_INFO(Double),
            ADD_CONSTANT_INFO(String),
            ADD_CONSTANT_INFO(Integer),
            ADD_CONSTANT_INFO(FieldRef),
            ADD_CONSTANT_INFO(MethodRef),
            ADD_CONSTANT_INFO(MethodType),
            ADD_CONSTANT_INFO(NameAndType),
            ADD_CONSTANT_INFO(MethodHandle),
            ADD_CONSTANT_INFO(InvokeDynamic),
            ADD_CONSTANT_INFO(InterfaceMethodRef),
        };

        auto It = G_TagToConstantInfoSpawnFunction.find(ConstantPoolInfoTag);

        ASSERT_MSG(It != G_TagToConstantInfoSpawnFunction.end(),
               "Unknown EConstantPoolInfoTag: %llu", (unsigned long long)ConstantPoolInfoTag);

        // Create a new instance
        return It->second(ConstantPoolInfoTag);
    }

    const char* CConstantInfo::ConstantPoolInfoTagToString(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        switch (ConstantPoolInfoTag)
        {
            case EConstantPoolInfoTag::Utf8:                return "Utf8";
            case EConstantPoolInfoTag::Integer:             return "Integer";
            case EConstantPoolInfoTag::Float:               return "Float";
            case EConstantPoolInfoTag::Long:                return "Long";
            case EConstantPoolInfoTag::Double:              return "Double";
            case EConstantPoolInfoTag::Class:               return "Class";
            case EConstantPoolInfoTag::String:              return "String";
            case EConstantPoolInfoTag::FieldRef:            return "FieldRef";
            case EConstantPoolInfoTag::MethodRef:           return "MethodRef";
            case EConstantPoolInfoTag::InterfaceMethodRef:  return "InterfaceMethodRef";
            case EConstantPoolInfoTag::NameAndType:         return "NameAndType";
            case EConstantPoolInfoTag::MethodHandle:        return "MethodHandle";
            case EConstantPoolInfoTag::MethodType:          return "MethodType";
            case EConstantPoolInfoTag::InvokeDynamic:       return "InvokeDynamic";

            default: return "Unknown Tag";
        }
    }
}