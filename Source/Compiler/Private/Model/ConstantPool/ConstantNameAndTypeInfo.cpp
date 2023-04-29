
#include "Model/ConstantPool/ConstantNameAndTypeInfo.h"
#include "Model/ClassReader.h"
#include "Model/Debug/DebugMisc.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantNameAndTypeInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantNameAndTypeInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantNameAndTypeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
    }

    std::string CConstantNameAndTypeInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        const Compiler::CConstantUtf8Info& Name =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(GetNameIndex());

        const Compiler::CConstantUtf8Info& Descriptor =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(GetDescriptorIndex());

        const std::string DescriptorString = Debug::DecodeType(Descriptor.ToResolvedString(ConstantPool));

        return DescriptorString + ' ' + Name.ToResolvedString(ConstantPool);
    }

}