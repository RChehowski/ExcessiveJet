//
// Created by ASUS on 02/01/2021.
//

#include "Model/ConstantPool/ConstantInfos.h"
#include "Model/ClassReader.h"

#include <array>
#include <functional>

namespace Compiler
{
    typedef std::shared_ptr<CConstantInfo> (*CConstantInfoSpawnFunction)();

    using CConstantInfoSpawnFunctionTable = std::array<CConstantInfoSpawnFunction, (usz)EConstantPoolInfoTag::Num>;

    namespace Private
    {
        std::shared_ptr<CConstantInfo> New_ConstantUtf8Info()
        {
            return std::make_shared<CConstantUtf8Info>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantIntegerInfo()
        {
            return std::make_shared<CConstantIntegerInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantFloatInfo()
        {
            return std::make_shared<CConstantFloatInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantLongInfo()
        {
            return std::make_shared<CConstantLongInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantDoubleInfo()
        {
            return std::make_shared<CConstantDoubleInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantClassInfo()
        {
            return std::make_shared<CConstantClassInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantStringInfo()
        {
            return std::make_shared<CConstantStringInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantFieldRefInfo()
        {
            return std::make_shared<CConstantFieldRefInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantMethodRefInfo()
        {
            return std::make_shared<CConstantMethodRefInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantInterfaceMethodRefInfo()
        {
            return std::make_shared<CConstantInterfaceMethodRefInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantNameAndTypeInfo()
        {
            return std::make_shared<CConstantNameAndTypeInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantMethodHandleInfo()
        {
            return std::make_shared<CConstantMethodHandleInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantMethodTypeInfo()
        {
            return std::make_shared<CConstantMethodTypeInfo>();
        }

        std::shared_ptr<CConstantInfo> New_ConstantInvokeDynamicInfo()
        {
            return std::make_shared<CConstantInvokeDynamicInfo>();
        }


        std::shared_ptr<CConstantInfo> New_UNUSED_TAG()
        {
            ASSERT_MSG(false, "Unsupported tag");

            // Never supposed to be returned
            return std::shared_ptr<CConstantInfo>{ nullptr };
        }


        constexpr CConstantInfoSpawnFunctionTable GetConstantInfoSpawnFunctions()
        {
            CConstantInfoSpawnFunctionTable Table { nullptr };

            // Note that there will be "holes" in this array (by default assigned to nullptr) because these tags are not consecutive
            // but the losses are minor and array a lot faster than map.
            Table[(usz)EConstantPoolInfoTag::Utf8]                  = New_ConstantUtf8Info;
            Table[(usz)EConstantPoolInfoTag::Integer]               = New_ConstantIntegerInfo;
            Table[(usz)EConstantPoolInfoTag::Float]                 = New_ConstantFloatInfo;
            Table[(usz)EConstantPoolInfoTag::Long]                  = New_ConstantLongInfo;
            Table[(usz)EConstantPoolInfoTag::Double]                = New_ConstantDoubleInfo;
            Table[(usz)EConstantPoolInfoTag::Class]                 = New_ConstantClassInfo;
            Table[(usz)EConstantPoolInfoTag::String]                = New_ConstantStringInfo;
            Table[(usz)EConstantPoolInfoTag::FieldRef]              = New_ConstantFieldRefInfo;
            Table[(usz)EConstantPoolInfoTag::MethodRef]             = New_ConstantMethodRefInfo;
            Table[(usz)EConstantPoolInfoTag::InterfaceMethodRef]    = New_ConstantInterfaceMethodRefInfo;
            Table[(usz)EConstantPoolInfoTag::NameAndType]           = New_ConstantNameAndTypeInfo;
            Table[(usz)EConstantPoolInfoTag::MethodHandle]          = New_ConstantMethodHandleInfo;
            Table[(usz)EConstantPoolInfoTag::MethodType]            = New_ConstantMethodTypeInfo;
            Table[(usz)EConstantPoolInfoTag::InvokeDynamic]         = New_ConstantInvokeDynamicInfo;

            return Table;
        }
    }

    static constexpr CConstantInfoSpawnFunctionTable ConstantInfoSpawnFunctions = Private::GetConstantInfoSpawnFunctions();

    std::shared_ptr<CConstantInfo> CConstantInfo::NewConstantInfo(const EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        const usz ConstantPoolInfoTagAsSize = (usz)ConstantPoolInfoTag;
        ASSERT((ConstantPoolInfoTagAsSize >= (usz)0) && (ConstantPoolInfoTagAsSize < (usz)ConstantInfoSpawnFunctions.size()));

        const CConstantInfoSpawnFunction ConstantInfoSpawnFunction = ConstantInfoSpawnFunctions[ConstantPoolInfoTagAsSize];
        ASSERT_MSG(ConstantInfoSpawnFunction != nullptr, "Invalid tag: %d", static_cast<int>(ConstantPoolInfoTagAsSize));

        // Invoke the spawner function that will create an instance for us.
        return ConstantInfoSpawnFunction();
    }

    void operator>>(CClassReader &Reader, CConstantInfo &Instance)
    {
        // Note that DeserializeFrom() is a virtual call
        Instance.DeserializeFrom(Reader);
    }
}