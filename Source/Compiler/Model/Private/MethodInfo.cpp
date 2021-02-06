//
// Created by ASUS on 01/02/2021.
//

#include "MethodInfo.h"

#include "ClassInfo.h"

namespace Parse
{
    void operator>>(CClassReader& Reader, CMethodInfo& Instance)
    {
        Reader >> Instance.AccessFlags;
        Reader >> Instance.NameIndex;
        Reader >> Instance.DescriptorIndex;

        Reader >> Instance.Attributes;
    }

#if UNLOCK_DEBUG_METHODS
    std::string CMethodInfo::Debug_ToString(const CClassInfo& ClassInfo) const
    {
        std::shared_ptr<const CConstantPool> ConstantPool = ClassInfo.GetConstantPool();

        std::ostringstream Oss;

        const std::shared_ptr<CConstantUtf8Info> NameString =
                ConstantPool->Get<CConstantUtf8Info>(NameIndex);

        const std::shared_ptr<CConstantUtf8Info> DescriptorString =
                ConstantPool->Get<CConstantUtf8Info>(DescriptorIndex);

        if (AccessFlags & EMethodAccessFlags::ACC_PUBLIC)        Oss << "public ";
        if (AccessFlags & EMethodAccessFlags::ACC_PRIVATE)       Oss << "private ";
        if (AccessFlags & EMethodAccessFlags::ACC_PROTECTED)     Oss << "protected ";
        if (AccessFlags & EMethodAccessFlags::ACC_STATIC)        Oss << "static ";
        if (AccessFlags & EMethodAccessFlags::ACC_FINAL)         Oss << "final ";
        if (AccessFlags & EMethodAccessFlags::ACC_SYNCHRONIZED)  Oss << "synchronized ";
        if (AccessFlags & EMethodAccessFlags::ACC_BRIDGE)        Oss << "<bridge> ";
        if (AccessFlags & EMethodAccessFlags::ACC_VARARGS)       Oss << "<varargs> ";
        if (AccessFlags & EMethodAccessFlags::ACC_NATIVE)        Oss << "native ";
        if (AccessFlags & EMethodAccessFlags::ACC_ABSTRACT)      Oss << "abstract ";
        if (AccessFlags & EMethodAccessFlags::ACC_STRICT)        Oss << "strict(fp) ";
        if (AccessFlags & EMethodAccessFlags::ACC_SYNTHETIC)     Oss << "<synthetic> ";

        std::string FunctionSignature = (std::string)DescriptorString->GetStringUtf8();

        Oss << Debug::DecodeMethodReturnType(FunctionSignature)
            << " " << NameString->GetStringUtf8()
            << "("
            << Debug::DecodeMethodArgumentTypesJoined(FunctionSignature)
            << ")";

        return Oss.str();
    }
#endif // UNLOCK_DEBUG_METHODS
}