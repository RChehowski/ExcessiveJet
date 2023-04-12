//
// Created by ASUS on 02/01/2021.
//

#include "Model/ConstantPool/ConstantInfos.h"
#include "Model/ClassReader.h"

#include <array>
#include <functional>

namespace Compiler
{
    typedef CConstantInfo* (*CConstantInfoSpawnFunction)();

    using CConstantInfoSpawnFunctionTable = std::array<CConstantInfoSpawnFunction, (usz)EConstantPoolInfoTag::Num>;

    namespace Private
    {
        CConstantInfo* New_ConstantUtf8Info()
        {
            return new CConstantUtf8Info();
        }

	    CConstantInfo* New_ConstantIntegerInfo()
        {
	        return new CConstantIntegerInfo();
        }

	    CConstantInfo* New_ConstantFloatInfo()
        {
	        return new CConstantFloatInfo();
        }

	    CConstantInfo* New_ConstantLongInfo()
        {
	        return new CConstantLongInfo();
        }

	    CConstantInfo* New_ConstantDoubleInfo()
        {
	        return new CConstantDoubleInfo();
        }

	    CConstantInfo* New_ConstantClassInfo()
        {
	        return new CConstantClassInfo();
        }

	    CConstantInfo* New_ConstantStringInfo()
        {
	        return new CConstantStringInfo();
        }

	    CConstantInfo* New_ConstantFieldRefInfo()
        {
	        return new CConstantFieldRefInfo();
        }

	    CConstantInfo* New_ConstantMethodRefInfo()
        {
	        return new CConstantMethodRefInfo();
        }

	    CConstantInfo* New_ConstantInterfaceMethodRefInfo()
        {
	        return new CConstantInterfaceMethodRefInfo();
        }

	    CConstantInfo* New_ConstantNameAndTypeInfo()
        {
	        return new CConstantNameAndTypeInfo();
        }

	    CConstantInfo* New_ConstantMethodHandleInfo()
        {
	        return new CConstantMethodHandleInfo();
        }

	    CConstantInfo* New_ConstantMethodTypeInfo()
        {
	        return new CConstantMethodTypeInfo();
        }

	    CConstantInfo* New_ConstantInvokeDynamicInfo()
        {
	        return new CConstantInvokeDynamicInfo();
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

    CConstantInfo* CConstantInfo::NewConstantInfo(const EConstantPoolInfoTag ConstantPoolInfoTag)
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

	CConstantInfo *CPhantomConstantInfo::GetInstance()
	{
		static CPhantomConstantInfo PhantomConstantInfo{};
		return &PhantomConstantInfo;
	}
}