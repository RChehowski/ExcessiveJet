//
// Created by ASUS on 03/01/2021.
//

#include "ClassInfo.h"
#include "ClassReader.h"

#include <iostream>
#include <sstream>

#include "ConstantPool/ConstantUtf8Info.h"
#include "ConstantPool/ConstantClassInfo.h"

namespace Parse
{
    void CClassInfo::Deserialize(CClassReader& Reader, EClassInfoDeserializingMode ClassInfoDeserializingMode)
    {
        ASSERT(Reader.IsAtBegin());

        Reader >> Magic;
        ASSERT(Magic == 0xCAFEBABE);

        Reader >> ClassVersion;

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

    void CClassInfo::Debug_PrintClass() const
    {
        std::ostringstream Oss;
        if (AccessFlags & EClassAccessFlags::ACC_PUBLIC)      Oss << "public ";
        if (AccessFlags & EClassAccessFlags::ACC_FINAL)       Oss << "final ";
        if (AccessFlags & EClassAccessFlags::ACC_SUPER)       Oss << "<super> ";
//        if (AccessFlags & EClassAccessFlags::ACC_INTERFACE)   Oss << "<interface> ";
        if (AccessFlags & EClassAccessFlags::ACC_ABSTRACT)    Oss << "abstract ";
        if (AccessFlags & EClassAccessFlags::ACC_SYNTHETIC)   Oss << "<synthetic> ";
        if (AccessFlags & EClassAccessFlags::ACC_ANNOTATION)  Oss << "<annotation> ";
        if (AccessFlags & EClassAccessFlags::ACC_ENUM)        Oss << "<enum> ";

        {
            std::shared_ptr<CConstantClassInfo> ThisClassInfo =
                    ConstantPool->Get<CConstantClassInfo>(ThisClass);
            ASSERT(ThisClassInfo != nullptr);

            std::shared_ptr<CConstantUtf8Info> ThisClassNameInfo =
                    ConstantPool->Get<CConstantUtf8Info>(ThisClassInfo->GetNameIndex());
            ASSERT(ThisClassNameInfo != nullptr);

            Oss << ((AccessFlags & EClassAccessFlags::ACC_INTERFACE) ? "interface " : "class ");
            Oss << ThisClassNameInfo->GetStringUtf8();
        }
        if (SuperClass != 0)
        {
            std::shared_ptr<CConstantClassInfo> SuperClassInfo =
                    ConstantPool->Get<CConstantClassInfo>(SuperClass);
            ASSERT(SuperClassInfo != nullptr);

            std::shared_ptr<CConstantUtf8Info> SuperClassNameInfo =
                    ConstantPool->Get<CConstantUtf8Info>(SuperClassInfo->GetNameIndex());
            ASSERT(SuperClassNameInfo != nullptr);

            Oss << " extends " << SuperClassNameInfo->GetStringUtf8();
        }

        Oss << std::endl;
        std::cout << Oss.str();

        std::cout << "Fields:" << std::endl;
        Debug_PrintFields();

        std::cout << "Methods:" << std::endl;
        Debug_PrintMethods();
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

            if (FieldAccessFlags & EFieldAccessFlags::ACC_PUBLIC)     Oss << "public ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_PRIVATE)    Oss << "private ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_PROTECTED)  Oss << "protected ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_STATIC)     Oss << "static ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_FINAL)      Oss << "final ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_VOLATILE)   Oss << "volatile ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_TRANSIENT)  Oss << "transient ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_SYNTHETIC)  Oss << "<synthetic> ";
            if (FieldAccessFlags & EFieldAccessFlags::ACC_ENUM)       Oss << "<enum> ";

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

            const u2 MethodAccessFlags = MethodInfo.GetAccessFlags();

            if (MethodAccessFlags & EMethodAccessFlags::ACC_PUBLIC)        Oss << "public ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_PRIVATE)       Oss << "private ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_PROTECTED)     Oss << "protected ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_STATIC)        Oss << "static ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_FINAL)         Oss << "final ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_SYNCHRONIZED)  Oss << "synchronized ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_BRIDGE)        Oss << "<bridge> ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_VARARGS)       Oss << "<varargs> ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_NATIVE)        Oss << "native ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_ABSTRACT)      Oss << "abstract ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_STRICT)        Oss << "strict(fp) ";
            if (MethodAccessFlags & EMethodAccessFlags::ACC_SYNTHETIC)     Oss << "<synthetic> ";

            Oss << DescriptorString->GetStringUtf8() << " " << NameString->GetStringUtf8() << std::endl;
        }

        std::cout << Oss.str();
    }
}