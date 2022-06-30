//
// Created by ASUS on 03/01/2021.
//

#include "Model/FieldInfo.h"
#include "Model/ClassReader.h"

#if UNLOCK_DEBUG_METHODS
    #include "Model/ClassInfo.h"
    #include "Model/Debug/DebugMisc.h"

    #include <sstream>
#endif // UNLOCK_DEBUG_METHODS

namespace Compiler
{
    void CFieldInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> AccessFlags;
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
        Reader >> Attributes;
    }

    void operator>>(CClassReader& Reader, CFieldInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

#if UNLOCK_DEBUG_METHODS
    std::string CFieldInfo::Debug_ToString(const CClassInfo& ClassInfo) const
    {
        std::shared_ptr<const CConstantPool> ConstantPool = ClassInfo.GetConstantPool();

        std::ostringstream Oss;

        const std::shared_ptr<CConstantUtf8Info> NameString =
                ConstantPool->Get<CConstantUtf8Info>(NameIndex);

        const std::shared_ptr<CConstantUtf8Info> DescriptorString =
                ConstantPool->Get<CConstantUtf8Info>(DescriptorIndex);

        if      (AccessFlags & EFieldAccessFlags::ACC_PUBLIC)     Oss << "public ";
        else if (AccessFlags & EFieldAccessFlags::ACC_PRIVATE)    Oss << "private ";
        else if (AccessFlags & EFieldAccessFlags::ACC_PROTECTED)  Oss << "protected ";
        else Oss << "<package private> ";

        if (AccessFlags & EFieldAccessFlags::ACC_STATIC)     Oss << "static ";
        if (AccessFlags & EFieldAccessFlags::ACC_FINAL)      Oss << "final ";
        if (AccessFlags & EFieldAccessFlags::ACC_VOLATILE)   Oss << "volatile ";
        if (AccessFlags & EFieldAccessFlags::ACC_TRANSIENT)  Oss << "transient ";
        if (AccessFlags & EFieldAccessFlags::ACC_SYNTHETIC)  Oss << "<synthetic> ";
        if (AccessFlags & EFieldAccessFlags::ACC_ENUM)       Oss << "<enum> ";

//        std::string DecodedDescriptorType = Debug::DecodeType((std::string)DescriptorString->GetStringUtf8());

//        Oss << DecodedDescriptorType << " " << NameString->GetStringUtf8();

        return Oss.str();
    }
#endif // UNLOCK_DEBUG_METHODS
}