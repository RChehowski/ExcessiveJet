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
#include <array>


namespace Compiler
{
    typedef std::shared_ptr<CConstantInfo> (*CConstantInfoSpawnFunction)(const EConstantPoolInfoTag);

    namespace Private
    {
        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantUtf8Info(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantUtf8Info>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantIntegerInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantIntegerInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantFloatInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantFloatInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantLongInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantLongInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantDoubleInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantDoubleInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantClassInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantClassInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantStringInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantStringInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantFieldRefInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantFieldRefInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantMethodRefInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantMethodRefInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantInterfaceMethodRefInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantInterfaceMethodRefInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantNameAndTypeInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantNameAndTypeInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantMethodHandleInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantMethodHandleInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantMethodTypeInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantMethodTypeInfo>(Tag);
        }

        FORCEINLINE std::shared_ptr<CConstantInfo> New_ConstantInvokeDynamicInfo(const EConstantPoolInfoTag Tag)
        {
            return std::make_shared<CConstantInvokeDynamicInfo>(Tag);
        }
    }

    std::array<CConstantInfoSpawnFunction, (usz)EConstantPoolInfoTag::Num> GetConstantInfoSpawnFunctions()
    {
        std::array<CConstantInfoSpawnFunction, (usz)EConstantPoolInfoTag::Num> ConstantInfoSpawnFunctions {};

        // Note that there will be "holes" in this array (by default assigned to nullptr) because these tags are not consecutive
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Utf8] = Private::New_ConstantUtf8Info;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Integer] = Private::New_ConstantIntegerInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Float] = Private::New_ConstantFloatInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Long] = Private::New_ConstantLongInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Double] = Private::New_ConstantDoubleInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::Class] = Private::New_ConstantClassInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::String] = Private::New_ConstantStringInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::FieldRef] = Private::New_ConstantFieldRefInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::MethodRef] = Private::New_ConstantMethodRefInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::InterfaceMethodRef] = Private::New_ConstantInterfaceMethodRefInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::NameAndType] = Private::New_ConstantNameAndTypeInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::MethodHandle] = Private::New_ConstantMethodHandleInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::MethodType] = Private::New_ConstantMethodTypeInfo;
        ConstantInfoSpawnFunctions[(usz)EConstantPoolInfoTag::InvokeDynamic] = Private::New_ConstantInvokeDynamicInfo;

        return ConstantInfoSpawnFunctions;
    }

    std::shared_ptr<CConstantInfo> CConstantInfo::NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        static const std::array<CConstantInfoSpawnFunction, (usz)EConstantPoolInfoTag::Num> ConstantInfoSpawnFunctions = GetConstantInfoSpawnFunctions();

        const CConstantInfoSpawnFunction ConstantInfoSpawnFunction = ConstantInfoSpawnFunctions[(usz)ConstantPoolInfoTag];
        ASSERT(ConstantInfoSpawnFunction != nullptr);

        return ConstantInfoSpawnFunction(ConstantPoolInfoTag);
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

    void operator>>(CClassReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}