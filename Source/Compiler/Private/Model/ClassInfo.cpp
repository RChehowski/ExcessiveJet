//
// Created by ASUS on 03/01/2021.
//

#include "Model/ClassInfo.h"
#include "Model/ClassReader.h"

#include <iostream>
#include <sstream>

#include "Model/Attributes/SignatureAttributeInfo.h"
#include "Model/Attributes/SourceFileAttributeInfo.h"

#include "Model/ConstantPool/ConstantUtf8Info.h"
#include "Model/ConstantPool/ConstantClassInfo.h"
#include "Model/Debug/DebugMisc.h"

using Util::IStringUtf8;

namespace Compiler
{
    const IStringUtf8& CClassInfo::GetNameString() const
    {
        const CConstantClassInfo& ThisClassInfo = ConstantPool->GetChecked<CConstantClassInfo>(ThisClass);
        const CConstantUtf8Info& ThisClassNameInfo = ConstantPool->GetChecked<CConstantUtf8Info>(
		        ThisClassInfo.GetNameIndex());

        return ThisClassNameInfo.GetStringUtf8();
    }

    void CClassInfo::Debug_PrintClass() const
    {
        std::ostringstream Oss;

        Oss << "=========== CLASS ==========" << std::endl;

        // Original file
        {
            std::shared_ptr<CSourceFileAttributeInfo> SourceFileAttributeInfo =
                    GetAttributeOfType<CSourceFileAttributeInfo>();

            if (SourceFileAttributeInfo != nullptr)
            {
                const CConstantUtf8Info& SourceFileInfo = ConstantPool->GetChecked<CConstantUtf8Info>(
		                SourceFileAttributeInfo->GetSourcefileIndex());

                Oss << "Original file: \"" << SourceFileInfo.GetStringUtf8() << "\"" << std::endl;
            }
        }

        // Signature
        {
            std::shared_ptr<CSignatureAttributeInfo> SignatureAttributeInfo =
                GetAttributeOfType<CSignatureAttributeInfo>();

            if (SignatureAttributeInfo != nullptr)
            {
                const CConstantUtf8Info& SignatureInfo =
		                ConstantPool->GetChecked<CConstantUtf8Info>(SignatureAttributeInfo->GetSignatureIndex());

                Oss << "Signature: \"" << SignatureInfo.GetStringUtf8() << "\"" << std::endl;
            }
        }

        // Version
        {
            Oss << "Class Version: " << ClassVersion.ToString() << std::endl;
        }


        if (AccessFlags & EClassAccessFlags::ACC_PUBLIC)      Oss << "public ";
        if (AccessFlags & EClassAccessFlags::ACC_FINAL)       Oss << "final ";
        if (AccessFlags & EClassAccessFlags::ACC_SUPER)       Oss << "<super> ";
      //if (AccessFlags & EClassAccessFlags::ACC_INTERFACE)   Oss << "<interface> ";
        if (AccessFlags & EClassAccessFlags::ACC_ABSTRACT)    Oss << "abstract ";
        if (AccessFlags & EClassAccessFlags::ACC_SYNTHETIC)   Oss << "<synthetic> ";
      //if (AccessFlags & EClassAccessFlags::ACC_ANNOTATION)  Oss << "<annotation> ";
        if (AccessFlags & EClassAccessFlags::ACC_ENUM)        Oss << "<enum> ";

        {
            const CConstantClassInfo& ThisClassInfo = ConstantPool->GetChecked<CConstantClassInfo>(ThisClass);
            const CConstantUtf8Info& ThisClassNameInfo = ConstantPool->GetChecked<CConstantUtf8Info>(
		            ThisClassInfo.GetNameIndex());

            const char* ClassKind;
            if (AccessFlags & EClassAccessFlags::ACC_INTERFACE)
            {
                if (AccessFlags & EClassAccessFlags::ACC_ANNOTATION)
                    ClassKind = "@interface";
                else
                    ClassKind = "interface";
            }
            else
            {
                ClassKind = "class";
            }

            Oss << ClassKind << " " << ThisClassNameInfo.GetStringUtf8();
        }
        if (SuperClass != 0)
        {
            // The only class that does not have a superclass is java.lang.ObjectBase
            const CConstantClassInfo& SuperClassInfo = ConstantPool->GetChecked<CConstantClassInfo>(SuperClass);
            const CConstantUtf8Info& SuperClassNameInfo = ConstantPool->GetChecked<CConstantUtf8Info>(
		            SuperClassInfo.GetNameIndex());

            Oss << " extends " << SuperClassNameInfo.GetStringUtf8();
        }

        if (!Interfaces.empty())
        {
            Oss << " implements ";

            usz InterfacesLeft = Interfaces.size();
            for (u2 InterfaceClassIndex : Interfaces)
            {
                const CConstantClassInfo& InterfaceClassInfo = ConstantPool->GetChecked<CConstantClassInfo>(
		                InterfaceClassIndex);
                const CConstantUtf8Info& InterfaceClassNameInfo = ConstantPool->GetChecked<CConstantUtf8Info>(
		                InterfaceClassInfo.GetNameIndex());

                Oss << InterfaceClassNameInfo.GetStringUtf8();

                if (--InterfacesLeft > 0)
                {
                    Oss << ", ";
                }
            }
        }

        Oss << std::endl;
        std::cout << Oss.str();

        Debug_PrintFields();
        Debug_PrintMethods();

        std::cout.flush();
    }

    void CClassInfo::Debug_PrintFields() const
    {
        std::ostringstream Oss;

        Oss << "========== FIELDS  (" << Fields.size() << ") ==========" << std::endl;

        for (const CFieldInfo& FieldInfo : Fields)
        {
            Oss << FieldInfo.Debug_ToString(*this) << std::endl;
        }

        std::cout << Oss.str();
    }

    void CClassInfo::Debug_PrintMethods() const
    {
        std::ostringstream Oss;

        Oss << "========== METHODS (" << Methods.size() << ") ==========" << std::endl;

        for (const CMethodInfo& MethodInfo : Methods)
        {
            Oss << MethodInfo.Debug_ToString(*this) << std::endl;
        }

        std::cout << Oss.str();
    }

    void operator>>(CClassReader &Reader, CClassInfo &Instance)
    {
        ASSERT(Reader.IsAtBegin());

        Reader >> Instance.Magic;
        ASSERT(Instance.Magic == 0xCAFEBABE);

        Reader >> Instance.ClassVersion;

        Reader >> Instance.ConstantPool;

        // The reader will need to access the constant pool to deserialize attributes
        Reader.SetConstantPool(Instance.ConstantPool);

        Reader >> Instance.AccessFlags;
        Reader >> Instance.ThisClass;
        Reader >> Instance.SuperClass;

        Reader >> Instance.Interfaces;
        Reader >> Instance.Fields;
        Reader >> Instance.Methods;

        Reader >> Instance.Attributes;

        // Constant pool is not needed anymore
        Reader.SetConstantPool(nullptr);

        ASSERT(Reader.IsAtEnd());
    }
}