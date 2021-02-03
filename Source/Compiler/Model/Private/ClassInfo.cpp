//
// Created by ASUS on 03/01/2021.
//

#include "ClassInfo.h"
#include "ClassReader.h"

#include <iostream>
#include <sstream>
#include "ConstantPool/ConstantUtf8Info.h"

namespace Parse
{
    void CClassInfo::Deserialize(CClassReader& Reader, EClassInfoDeserializingMode ClassInfoDeserializingMode)
    {
        ASSERT(Reader.IsAtBegin());

        Reader >> Magic;
        ASSERT(Magic == 0xCAFEBABE);

        Reader >> MinorVersion;
        Reader >> MajorVersion;

        Reader >> ConstantPool;
        Reader.SetConstantPool(ConstantPool);

        Reader >> AccessFlags;
        Reader >> ThisClass;
        Reader >> SuperClass;

        Reader >> Interfaces;
        Reader >> Fields;
        Reader >> Methods;

        Reader >> Attributes;

        ASSERT(Reader.IsAtEnd());
    }

    void CClassInfo::Debug_PrintFields() const
    {
        std::ostringstream Oss;

        usz Index = 1;
        for (const CFieldInfo& FieldInfo : Fields)
        {
            const std::shared_ptr<CConstantUtf8Info> NameString =
                    ConstantPool->Get<CConstantUtf8Info>(FieldInfo.GetNameIndex());

            const std::shared_ptr<CConstantUtf8Info> DescriptorString =
                    ConstantPool->Get<CConstantUtf8Info>(FieldInfo.GetDescriptorIndex());

            Oss << Index++ << ") ";

            const u2 FieldAccessFlags = FieldInfo.GetAccessFlags();
            if (FieldAccessFlags & EFieldAccessFlag::ACC_PUBLIC)     Oss << "public ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_PRIVATE)    Oss << "private ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_PROTECTED)  Oss << "protected ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_STATIC)     Oss << "static ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_FINAL)      Oss << "final ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_VOLATILE)   Oss << "volatile ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_TRANSIENT)  Oss << "transient ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_SYNTHETIC)  Oss << "<synthetic> ";
            if (FieldAccessFlags & EFieldAccessFlag::ACC_ENUM)       Oss << "<enum> ";

            Oss << DescriptorString->GetStringUtf8() << " " << NameString->GetStringUtf8() << std::endl;
        }

        std::cout << Oss.str();
    }

    void CClassInfo::Debug_PrintMethods() const
    {
        std::ostringstream Oss;
        usz Index = 1;

        for (const CMethodInfo& MethodInfo : Methods)
        {
            const std::shared_ptr<CConstantUtf8Info> NameString =
                    ConstantPool->Get<CConstantUtf8Info>(MethodInfo.GetNameIndex());

            const std::shared_ptr<CConstantUtf8Info> DescriptorString =
                    ConstantPool->Get<CConstantUtf8Info>(MethodInfo.GetDescriptorIndex());

            Oss << Index++ << ") ";

            const u2 AccessFlags = MethodInfo.GetAccessFlags();
            if (AccessFlags & EMethodAccessFlag::ACC_PUBLIC)        Oss << "public ";
            if (AccessFlags & EMethodAccessFlag::ACC_PRIVATE)       Oss << "private ";
            if (AccessFlags & EMethodAccessFlag::ACC_PROTECTED)     Oss << "protected ";
            if (AccessFlags & EMethodAccessFlag::ACC_STATIC)        Oss << "static ";
            if (AccessFlags & EMethodAccessFlag::ACC_FINAL)         Oss << "final ";
            if (AccessFlags & EMethodAccessFlag::ACC_SYNCHRONIZED)  Oss << "synchronized ";
            if (AccessFlags & EMethodAccessFlag::ACC_BRIDGE)        Oss << "<bridge> ";
            if (AccessFlags & EMethodAccessFlag::ACC_VARARGS)       Oss << "<varargs> ";
            if (AccessFlags & EMethodAccessFlag::ACC_NATIVE)        Oss << "native ";
            if (AccessFlags & EMethodAccessFlag::ACC_ABSTRACT)      Oss << "abstract ";
            if (AccessFlags & EMethodAccessFlag::ACC_STRICT)        Oss << "strict(fp) ";
            if (AccessFlags & EMethodAccessFlag::ACC_SYNTHETIC)     Oss << "<synthetic> ";

            Oss << DescriptorString->GetStringUtf8() << " " << NameString->GetStringUtf8() << std::endl;
        }

        std::cout << Oss.str();
    }
}