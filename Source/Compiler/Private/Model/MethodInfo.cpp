//
// Created by ASUS on 01/02/2021.
//

#include <iomanip>
#include "Model/MethodInfo.h"
#include "Model/ClassInfo.h"

namespace Compiler
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
        Oss << GetNameWithSignature(*ConstantPool) << std::endl;

        if (std::shared_ptr<CCodeAttributeInfo> CodeAttributeInfo = GetAttribute<CCodeAttributeInfo>())
        {
        	Oss << "<Max stack: " << CodeAttributeInfo->GetMaxStack() << ", Max locals: " << CodeAttributeInfo->GetMaxLocals() << '>' << std::endl;

	        const std::shared_ptr<CLineNumberTableAttributeInfo> LineNumberTable =
	        		CodeAttributeInfo->GetAttribute<CLineNumberTableAttributeInfo>();

	        const std::vector<CLineNumberTableAttributeInfoEntry>* LineNumberInfoEntries =
			        LineNumberTable ? &LineNumberTable->GetLineNumberTable() : nullptr;

            DebugBytecodePrinter::CDebugPrinterContext Context(Oss, ConstantPool, CodeAttributeInfo->GetCode(), LineNumberInfoEntries);
            DebugBytecodePrinter::PrintBytecode(Context);
        }

        return Oss.str();
    }

    std::string CMethodInfo::GetName(const CConstantPool &ConstantPool) const
    {
        const CConstantUtf8Info& NameString = ConstantPool.GetChecked<CConstantUtf8Info>(NameIndex);
        return NameString.ToResolvedString(ConstantPool);
    }

    std::string CMethodInfo::GetNameWithSignature(const CConstantPool &ConstantPool, const CClassInfo* ClassInfoPtr) const
    {
        std::ostringstream Oss;

        const CConstantUtf8Info& NameString = ConstantPool.GetChecked<CConstantUtf8Info>(NameIndex);
        const CConstantUtf8Info& DescriptorString = ConstantPool.GetChecked<CConstantUtf8Info>(DescriptorIndex);

        if      (AccessFlags & EMethodAccessFlags::ACC_PUBLIC)        Oss << "public ";
        else if (AccessFlags & EMethodAccessFlags::ACC_PRIVATE)       Oss << "private ";
        else if (AccessFlags & EMethodAccessFlags::ACC_PROTECTED)     Oss << "protected ";
        else Oss << "<package private> ";

        if (AccessFlags & EMethodAccessFlags::ACC_STATIC)        Oss << "static ";
        if (AccessFlags & EMethodAccessFlags::ACC_FINAL)         Oss << "final ";
        if (AccessFlags & EMethodAccessFlags::ACC_SYNCHRONIZED)  Oss << "synchronized ";
        if (AccessFlags & EMethodAccessFlags::ACC_BRIDGE)        Oss << "<bridge> ";
        if (AccessFlags & EMethodAccessFlags::ACC_VARARGS)       Oss << "<varargs> ";
        if (AccessFlags & EMethodAccessFlags::ACC_NATIVE)        Oss << "native ";
        if (AccessFlags & EMethodAccessFlags::ACC_ABSTRACT)      Oss << "abstract ";
        if (AccessFlags & EMethodAccessFlags::ACC_STRICT)        Oss << "strictfp ";
        if (AccessFlags & EMethodAccessFlags::ACC_SYNTHETIC)     Oss << "<synthetic> ";

        const std::string FunctionSignature = (std::string)DescriptorString.GetStringUtf8();

        const std::string MethodReturnType = Debug::DecodeMethodReturnType(FunctionSignature);
        const std::string MethodArguments = Debug::DecodeMethodArgumentTypesJoined(FunctionSignature);

        Oss << MethodReturnType << ' ';

        if (ClassInfoPtr != nullptr)
        {
            Oss << ClassInfoPtr->GetNameString() << '.';
        }

        Oss << NameString.GetStringUtf8() << '(' << MethodArguments << ')';

        return Oss.str();
    }

#endif // UNLOCK_DEBUG_METHODS
}