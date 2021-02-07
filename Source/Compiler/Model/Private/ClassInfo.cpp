//
// Created by ASUS on 03/01/2021.
//

#include "ClassInfo.h"
#include "ClassReader.h"

#include <iostream>
#include <sstream>

#include "Attributes/SignatureAttributeInfo.h"
#include "Attributes/SourceFileAttributeInfo.h"

#include "ConstantPool/ConstantUtf8Info.h"
#include "ConstantPool/ConstantClassInfo.h"
#include "Debug/DebugMisc.h"

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

        // Original file
        {
            std::shared_ptr<CSourceFileAttributeInfo> SourceFileAttributeInfo =
                    GetAttributeOfType<CSourceFileAttributeInfo>();

            if (SourceFileAttributeInfo != nullptr)
            {
                std::shared_ptr<CConstantUtf8Info> SourceFileInfo =
                    ConstantPool->Get<CConstantUtf8Info>(SourceFileAttributeInfo->GetSourcefileIndex());
                ASSERT(SourceFileInfo != nullptr);

                Oss << "Original file: \"" << SourceFileInfo->GetStringUtf8() << "\"" << std::endl;
            }
        }

        // Signature
        {
            std::shared_ptr<CSignatureAttributeInfo> SignatureAttributeInfo =
                GetAttributeOfType<CSignatureAttributeInfo>();

            if (SignatureAttributeInfo != nullptr)
            {
                std::shared_ptr<CConstantUtf8Info> SignatureInfo =
                    ConstantPool->Get<CConstantUtf8Info>(SignatureAttributeInfo->GetSignatureIndex());
                ASSERT(SignatureInfo != nullptr);

                Oss << "Signature: \"" << SignatureInfo->GetStringUtf8() << "\"" << std::endl;
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
            std::shared_ptr<CConstantClassInfo> ThisClassInfo =
                    ConstantPool->Get<CConstantClassInfo>(ThisClass);
            ASSERT(ThisClassInfo != nullptr);

            std::shared_ptr<CConstantUtf8Info> ThisClassNameInfo =
                    ConstantPool->Get<CConstantUtf8Info>(ThisClassInfo->GetNameIndex());
            ASSERT(ThisClassNameInfo != nullptr);

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

            Oss << ClassKind << " " << ThisClassNameInfo->GetStringUtf8();
        }
        if (SuperClass != 0)
        {
            // The only class that does not have a superclass is java.lang.Object
            std::shared_ptr<CConstantClassInfo> SuperClassInfo =
                    ConstantPool->Get<CConstantClassInfo>(SuperClass);
            ASSERT(SuperClassInfo != nullptr);

            std::shared_ptr<CConstantUtf8Info> SuperClassNameInfo =
                    ConstantPool->Get<CConstantUtf8Info>(SuperClassInfo->GetNameIndex());
            ASSERT(SuperClassNameInfo != nullptr);

            Oss << " extends " << SuperClassNameInfo->GetStringUtf8();
        }

        if (!Interfaces.IsEmpty())
        {
            Oss << " implements ";

            usz InterfacesLeft = Interfaces.Size();
            for (u2 InterfaceClassIndex : Interfaces)
            {
                std::shared_ptr<CConstantClassInfo> InterfaceClassInfo =
                        ConstantPool->Get<CConstantClassInfo>(InterfaceClassIndex);

                std::shared_ptr<CConstantUtf8Info> InterfaceClassNameInfo =
                        ConstantPool->Get<CConstantUtf8Info>(InterfaceClassInfo->GetNameIndex());
                ASSERT(InterfaceClassNameInfo != nullptr);

                Oss << InterfaceClassNameInfo->GetStringUtf8();

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
    }

    void CClassInfo::Debug_PrintFields() const
    {
        std::ostringstream Oss;

        Oss << "========== FIELDS  (" << Fields.Size() << ") ==========" << std::endl;

        for (const CFieldInfo& FieldInfo : Fields)
        {
            Oss << FieldInfo.Debug_ToString(*this) << std::endl;
        }

        std::cout << Oss.str();
    }

    void CClassInfo::Debug_PrintMethods() const
    {
        std::ostringstream Oss;

        Oss << "========== METHODS (" << Methods.Size() << ") ==========" << std::endl;

        for (const CMethodInfo& MethodInfo : Methods)
        {
            Oss << MethodInfo.Debug_ToString(*this) << std::endl;
        }

        std::cout << Oss.str();
    }
}